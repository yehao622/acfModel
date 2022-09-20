//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Source.h"

namespace lfs {

Define_Module(Source);

Source::Source(){}

Source::~Source(){}

void Source::initialize()
{
    id = 1;
    tid = 1;
    if(strcmp(getName(), "source") == 0){
        Job *timerMessage = new Job();
        scheduleAt(simTime(), timerMessage);
    }

}

void Source::handleMessage(cMessage *msg)
{
    if(id == UINT_MAX)  endSimulation();

    Job *job = check_and_cast<Job*>(msg);
    job->setCached(false);
    job->setBack_from_ost(false);
    int out_to_ost_index = id % OST_NUM; //intuniform(0, OST_NUM-1, 0);
    job->setAssigned_ost_id(out_to_ost_index);
    int out_to_oss_index = out_to_ost_index % OSS_NUM;
    job->setAssigned_oss_id(out_to_oss_index);
    job->setJob_id(id);
    job->setTask_id(tid);
    cPacket pkg = cPacket(job->getPkg());
    double data_size = 1.0/16384;//par("avgPkgSize1");
    pkg.setByteLength((long long)(data_size*1024*1024));
    job->setPkg(pkg);
    job->setInit_data_size(data_size*1024*1024);
    if(uniform(0.0, 1.0, 0)<1.0)
        job->setWork_type('r');
    else
        job->setWork_type('w');
    job->setGenerate_time(simTime());
    job->setArrive_time_queue(simTime());
    job->setLeave_time_queue(simTime());
    job->setArrive_time_server(simTime());
    job->setLeave_time_server(simTime());
    send(job, "out"); // source module has only one output gate
//    tid++;

    Job *timerMessage = new Job();
    scheduleAt(simTime()+par("sendInterval").doubleValue(), timerMessage);
//    if(tid == 1){
        id++;
//        tid = 0;
//    }
}

void Source::finish(){}

}; // namespace
