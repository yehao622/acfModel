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

namespace lfs;

//
// TODO generated message class
//
message Job {
    bool cached;
    bool back_from_ost;
    char work_type;
    int assigned_oss_id;
    int assigned_ost_id;
    unsigned int job_id;
    int task_id; // child of job_id
    uint64_t init_data_size;
    simtime_t generate_time;
    simtime_t arrive_time_queue;
    simtime_t leave_time_queue;
    simtime_t arrive_time_server;
    simtime_t leave_time_server;
    omnetpp::cPacket pkg;
}
