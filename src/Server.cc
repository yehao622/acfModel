/*
 * Server.cc
 *
 *  Created on: Apr 16, 2022
 *      Author: Hao
 */

#include "Server.h"
#include <thread>
#include "Queue.h"

namespace lfs {

Define_Module(Server);

Server::Server(){}

Server::~Server(){}

void Server::initialize(){
    job_count = 0;
    free_status = true;
    avgIOPS = registerSignal("averageIOPS");
    sWaitSignal = registerSignal("waitInStation");
    end_time = simTime();
    last_visit_time = simTime();
}

simtime_t Server::getEndTimeStamp(){
    return end_time;
}

void Server::updateTimeStamp(Job* j){
    double delay_time(-1.0);
    int64_t pkg_size = j->getPkg().getByteLength();

    if(strcmp(getName(), "ossCore") == 0){
        delay_time = par("oss_rate").doubleValue();
        if(j->getWork_type() == 'w')
            end_time = simTime() + (double)pkg_size / (1024.0*1024.0) * delay_time;
        else
            end_time = simTime();

    }else if(strcmp(getName(), "netCore") == 0){
        delay_time = par("one_channel_rate").doubleValue();
        if((j->getWork_type()=='r' && j->getBack_from_ost()) ||
                (j->getWork_type()=='w' && !j->getBack_from_ost()))
            end_time = simTime() + (double)pkg_size / (1024.0*1024.0) * delay_time;
        else
            end_time = simTime();// + delay_time;

    }else if(strcmp(getName(), "mdsCore") == 0){
        if(j->getWork_type() == 'r')
            delay_time = 0;//par("mds_rate_r").doubleValue();
        else if(j->getWork_type() == 'w')
            delay_time = 0;//par("mds_rate_w").doubleValue();
        else
            throw cRuntimeError("Illegal work type definition at %s!\n", getName());
        end_time = simTime() + delay_time;

    }else if(strcmp(getName(), "ostCore") == 0){
        if(j->getWork_type() == 'r'){

            if(pkg_size <= 64)
                delay_time = par("ost_rate_l64_r").doubleValue();
            else if(pkg_size <= 1024)
                delay_time = par("ost_rate_l1k_r").doubleValue();
            else if(pkg_size <= 1024*4)
                delay_time = par("ost_rate_l4k_r").doubleValue() + ((double)pkg_size/1024 - 1.0) * par("slope_l4k_r").doubleValue();
            else if(pkg_size <= 1024*8)
                delay_time = par("ost_rate_l8k_r").doubleValue() + ((double)pkg_size/1024 - 4.0) * par("slope_l8k_r").doubleValue();
            else if(pkg_size <= 1024*16)
                delay_time = par("ost_rate_l16k_r").doubleValue() + ((double)pkg_size/1024 - 8.0) * par("slope_l16k_r").doubleValue();
            else if(pkg_size <= 1024*32)
                delay_time = par("ost_rate_l32k_r").doubleValue() + ((double)pkg_size/1024 - 16.0) * par("slope_l32k_r").doubleValue();
            else if(pkg_size <= 1024*256)
                delay_time = par("ost_rate_l256k_r").doubleValue() + ((double)pkg_size/1024 - 32.0) * par("slope_l256k_r").doubleValue();
            else
                delay_time = (double)pkg_size / (1024*256) * par("ost_rate_g256k_r").doubleValue();

        }else if(j->getWork_type() == 'w'){

            if(pkg_size <= 1024)
                delay_time = par("ost_rate_l1k_w").doubleValue();
            else if(pkg_size <= 1024*4)
                delay_time = par("ost_rate_l4k_w").doubleValue() + ((double)pkg_size/1024 - 1.0) * par("slope_l4k_w").doubleValue();
            else if(pkg_size <= 1024*8)
                delay_time = par("ost_rate_l8k_w").doubleValue() + ((double)pkg_size/1024 - 4.0) * par("slope_l8k_w").doubleValue();
            else if(pkg_size <= 1024*16)
                delay_time = par("ost_rate_l16k_w").doubleValue() + ((double)pkg_size/1024 - 8.0) * par("slope_l16k_w").doubleValue();
            else if(pkg_size <= 1024*32)
                delay_time = par("ost_rate_l32k_w").doubleValue() + ((double)pkg_size/1024 - 16.0) * par("slope_l32k_w").doubleValue();
            else if(pkg_size <= 1024*256)
                delay_time = par("ost_rate_l256k_w").doubleValue() + ((double)pkg_size/1024 - 32.0) * par("slope_l256k_w").doubleValue();
            else
                delay_time = (double)pkg_size / (1024*256) * par("ost_rate_g256k_w").doubleValue();

        }else
            throw cRuntimeError("Illegal work type definition at %s!\n", getName());
        end_time = simTime() + delay_time;
    }else
        throw cRuntimeError("Server has no corresponding rule at %s!\n", getName());
}

void Server::mdsSendMessage(Job* j){
    updateTimeStamp(j);
    j->setLeave_time_server(end_time);
    sendDelayed(j, end_time-simTime(), "out");
}

void Server::ossSendMessage(Job* j){
    updateTimeStamp(j);
    j->setLeave_time_server(end_time);
    sendDelayed(j, end_time-simTime(), "out");
}

void Server::ostSendMessage(Job* j){
    updateTimeStamp(j);
    j->setLeave_time_server(end_time);
    j->setBack_from_ost(true);
    //emit(sWaitSignal, (j->getLeave_time_server() - j->getArrive_time_queue()).dbl());
    sendDelayed(j, end_time-simTime(), "out");
}

void Server::netSendMessage(Job* j){
    updateTimeStamp(j);
    j->setLeave_time_server(end_time);
    sendDelayed(j, end_time-simTime(), "out");
}

void Server::handleMessage(cMessage *msg){
    Job *job = check_and_cast<Job*>(msg);

    if(!job->isSelfMessage()){
        job_count++;
        free_status = false;
        job->setArrive_time_server(simTime());

        if(strcmp(getName(), "mdsCore") == 0){
            mdsSendMessage(job);
        }else if(strcmp(getName(), "ossCore") == 0){
            ossSendMessage(job);
        }else if(strcmp(getName(), "ostCore") == 0){
            ostSendMessage(job);
        }else if(strcmp(getName(), "netCore") == 0){
            netSendMessage(job);
        }else{
            cRuntimeError("Need to implement new module!");
        }

        scheduleAt(end_time, new Job());

        if((simTime()-last_visit_time).dbl() >= 0.01){
            double instant_rate = (double)job_count / (simTime()-last_visit_time).dbl();
            last_visit_time = simTime();
            emit(avgIOPS, instant_rate);
            job_count = 0;
        }
    }else{
        delete job;
        free_status = true;
    }
}

/*void Server::refreshDisplay() const {
    getDisplayString().setTagArg("i2", 0, jobServiced ? "status/execute" : "");
}*/

void Server::finish(){}

bool Server::isIdle(){
    return (simTime()>=end_time) && free_status;
}

};
