/*
 * Queue.cc
 *
 *  Created on: Apr 17, 2022
 *      Author: Hao
 */

#include "Queue.h"
#include <string>
#include "Server.h"

namespace lfs {

Define_Module(Queue);

Queue::Queue(){}

Queue::~Queue(){
    while(!jobs.empty())
        jobs.pop_front();
}

int Queue::getQueueLength(){
    return jobs.size();
}

void Queue::initialize(){
    time_to_remove_one_job = simTime();
    qLenSignal = registerSignal("queueLength");
    qWaitSignal = registerSignal("queueWaiting");
    int num_in = gateSize("in");

    for(int i=0; i<num_in; i++){
        cGate* gin = gate("in", i);
        std::string prev_module_class_name = gin->getPreviousGate()->getOwnerModule()->getNedTypeName();
        if(strcmp(prev_module_class_name.c_str(), "lfs.Queue") == 0){
            EV_ERROR << "Two Queue modules shall not connect directly!\n";
        }
    }

    // one queue must followed by exactly one server class module!
    cGate* gout = gate("out");
    std::string next_module_class_name = gout->getNextGate()->getOwnerModule()->getNedTypeName();
    if(strcmp(next_module_class_name.c_str(), "lfs.Server")){
        EV_ERROR << "After Queue, there should be a Server class module!\n";
    }

}

void Queue::handleMessage(cMessage *msg){
    emit(qLenSignal, getQueueLength());
    Job* job = check_and_cast<Job*>(msg);
    cGate* gout = gate("out");
    Server* svr = check_and_cast<Server*>(gout->getNextGate()->getOwnerModule());

    if(!job->isSelfMessage())
        job->setArrive_time_queue(simTime());
    else if(!jobs.empty())
        jobs.pop_front();

    emit(qLenSignal, getQueueLength());

    if(!job->isSelfMessage())
        jobs.push_back(job);
    else
        jobs.push_front(job);

    if(getServerStatus()){
        Job* j = jobs.front();
        j->setLeave_time_queue(simTime());
        send(j->dup(), "out");
        emit(qWaitSignal, (j->getLeave_time_queue() - j->getArrive_time_queue()).dbl());
        jobs.pop_front();
        delete j;
    }else{
        scheduleAt(svr->getEndTimeStamp(), jobs.front()->dup());
    }

    emit(qLenSignal, getQueueLength());
}

const bool Queue::getServerStatus() {
    cGate* gout = gate("out");
    Server* svr = check_and_cast<Server*>(gout->getNextGate()->getOwnerModule());
    return svr->isIdle();
}

bool Queue::tryToFetchJob(){
    Enter_Method("tryToFetchJob");
    if(!jobs.empty()){
        scheduleAt(simTime(), jobs.front()->dup());
        jobs.pop_front();
        return true;
    }
    return false;
}

void Queue::finish(){}
};
