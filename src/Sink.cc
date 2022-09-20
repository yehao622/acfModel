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

#include "Sink.h"

RESULTS read_res, write_res;

namespace lfs {

Define_Module(Sink);

void Sink::initialize()
{
    readThputSig = registerSignal("rThroughput");
    writeThputSig = registerSignal("wThroughput");
}

void Sink::handleMessage(cMessage *msg)
{
    Job* j = check_and_cast<Job*>(msg);

    if(j->getWork_type() == 'r'){
        read_res[j->getJob_id()][j->getTask_id()] = j->getInit_data_size();
    }else{
        write_res[j->getJob_id()][j->getTask_id()] = j->getInit_data_size();
    }

    if(j->getWork_type() == 'r'){
        double all_read_size = (double)sumSize(read_res) / (1024 * 1024);
        emit(readThputSig, all_read_size / simTime().dbl());
    }else {
        double all_write_size = (double)sumSize(write_res) / (1024 * 1024);
        emit(writeThputSig, all_write_size / simTime().dbl());
    }
    delete j;

    /*if(m.size() == 84000) {
        std::ofstream outfile;
        outfile.open("ind.txt", std::ios::trunc); // append instead of overwrite
        for(auto a:m)
            outfile << a.first << " : " << a.second << "\n";
        endSimulation();
    }*/
}

void Sink::finish()
{
//    recordStatistic(&iaTimeHistogram);
}

}; // namespace
