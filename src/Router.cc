/*
 * Router.cc
 *
 *  Created on: Apr 18, 2022
 *      Author: Hao
 */

#include "Router.h"

namespace lfs {

Define_Module(Router);

Router::Router(){}

Router::~Router(){}

void Router::initialize(){
    int num_out = gateSize("out");

    if(strcmp(getFullName(), "mds_oss") == 0){
        if(num_out != OSS_NUM)
            throw cRuntimeError("%d of OSSes has been configured, but not equal to OSS_NUM in 'method.h'", num_out);
    }

    for(int i=0 ;i<num_out; i++){
        cGate* g = gate("out", i);
        gates_map[g->getNextGate()->getOwnerModule()->getFullName()] = i;
    }
}

void Router::handleMessage(cMessage *msg){
    Job *job = check_and_cast<Job*>(msg);
    int num_out = gateSize("out");
    int out_to_gate = intuniform(0, num_out-1);
    if(job->getPkg().getByteLength() <= 0)
        throw cRuntimeError("Package size can't be non-positive number!\n");

    if(strcmp(getFullName(), "split_mtu") == 0){
        if(!job->getBack_from_ost()) { // if from MDS
            if(job->getWork_type() == 'r') {
                send(job, "out", out_to_gate);
            }else{ // split data into pakages by MTU, and feed into network channels
                int64_t pkg_size = job->getPkg().getByteLength();
                int64_t num_pkgs = pkg_size/MTU + (pkg_size%MTU>0);
                for(int64_t i=num_pkgs; i>0; i--){
                    Job *j = job->dup();
                    cPacket net_pkg;
                    int net_pkg_size;
                    if(i > 1)
                        net_pkg_size = MTU;
                    else
                        net_pkg_size = pkg_size - MTU*(num_pkgs-1);
                    net_pkg.setByteLength(net_pkg_size);
                    j->setPkg(net_pkg);
                    send(j, "out", out_to_gate);
                }
            }
        }else{ // from OSTs
            if(job->getWork_type() == 'r') { // Aggregate read stripe blocks from OSTs, and then split into net packages
                unsigned int j_id(job->getJob_id());
                int t_id(job->getTask_id());
                if(arrived_pkg_after_ost.count(j_id) && arrived_pkg_after_ost[j_id].count(t_id))
                    arrived_pkg_after_ost[j_id][t_id].second += job->getPkg().getByteLength();
                else{
                    arrived_pkg_after_ost[j_id][t_id].first = job->getInit_data_size();
                    arrived_pkg_after_ost[j_id][t_id].second = job->getPkg().getByteLength();
                }

                if(arrived_pkg_after_ost[j_id][t_id].first == arrived_pkg_after_ost[j_id][t_id].second) {
                    int64_t pkg_size = arrived_pkg_after_ost[j_id][t_id].first;
                    int64_t num_pkgs = pkg_size/MTU + (pkg_size%MTU>0);
                    for(int64_t i=num_pkgs; i>0; i--){
                        Job *j = job->dup();
                        cPacket net_pkg;
                        int net_pkg_size;
                        if(i > 1)
                            net_pkg_size = MTU;
                        else
                            net_pkg_size = pkg_size - MTU*(num_pkgs-1);
                        net_pkg.setByteLength(net_pkg_size);
                        j->setPkg(net_pkg);
                        send(j, "out", out_to_gate);
                    }
                    arrived_pkg_after_ost[j_id].erase(t_id);
                    if(arrived_pkg_after_ost[j_id].empty())
                        arrived_pkg_after_ost.erase(j_id);
                }
                delete job;

            }else{ // just pass a completed write request from 'aggregate' module
                send(job, "out", out_to_gate);
            }
        }

    }else if(strcmp(getFullName(), "split_page") == 0){
        std::string gate_name =  "oss[" + std::to_string(job->getAssigned_oss_id()) +"]";
        if(!gates_map.count(gate_name))
            throw cRuntimeError("No such gate: %s exists!\n", gate_name.c_str());

        if(!job->getBack_from_ost()) { // if comes from MDS
            if(job->getWork_type() == 'r'){ // for r_req
                int64_t pkg_size = job->getPkg().getByteLength();
                int64_t num_pkgs = pkg_size/PAGE_SIZE + (pkg_size%PAGE_SIZE>0);
                for(int64_t i=num_pkgs; i>0; i--){
                    Job *j = job->dup();
                    cPacket page_pkg;
                    int page_pkg_size;
                    if(i > 1)
                        page_pkg_size = PAGE_SIZE;
                    else
                        page_pkg_size = pkg_size - PAGE_SIZE*(num_pkgs-1);
                    page_pkg.setByteLength(page_pkg_size);
                    j->setPkg(page_pkg);
                    send(j, "out", gates_map[gate_name]);
                }
            }else{ // for w_req from MDS, split into page_size to OSS
                unsigned int j_id(job->getJob_id());
                int t_id(job->getTask_id());
                // update record for each incoming w_req.
                if(arrived_pkg_after_mds.count(j_id) && arrived_pkg_after_mds[j_id].count(t_id))
                    arrived_pkg_after_mds[j_id][t_id].second += job->getPkg().getByteLength();
                else{
                    arrived_pkg_after_mds[j_id][t_id].first = job->getInit_data_size();
                    arrived_pkg_after_mds[j_id][t_id].second = job->getPkg().getByteLength();
                }

                // if all packages belonging to the same job & task arrived, congregate them and split into pages to OSS
                if(arrived_pkg_after_mds[j_id][t_id].first == arrived_pkg_after_mds[j_id][t_id].second){
                    int64_t pkg_size = arrived_pkg_after_mds[j_id][t_id].first;
                    int64_t num_pkgs = pkg_size/PAGE_SIZE + (pkg_size%PAGE_SIZE>0);
                    for(int64_t i=num_pkgs; i>0; i--){
                        Job *j = job->dup();
                        cPacket page_pkg;
                        int page_pkg_size;
                        if(i > 1)
                            page_pkg_size = PAGE_SIZE;
                        else
                            page_pkg_size = pkg_size - PAGE_SIZE*(num_pkgs-1);
                        page_pkg.setByteLength(page_pkg_size);
                        j->setPkg(page_pkg);
                        send(j, "out", gates_map[gate_name]);
                    }
                    arrived_pkg_after_mds[j_id].erase(t_id);
                    if(arrived_pkg_after_mds[j_id].empty())
                        arrived_pkg_after_mds.erase(j_id);
                }
            }

            delete job;
        }else { // return back from OSTs
            if(job->getWork_type() == 'r') { // aggregate into a completed read request
                unsigned int j_id(job->getJob_id());
                int t_id(job->getTask_id());
                if(arrived_pkg_after_ost.count(j_id) && arrived_pkg_after_ost[j_id].count(t_id))
                    arrived_pkg_after_ost[j_id][t_id].second += job->getPkg().getByteLength();
                else{
                    arrived_pkg_after_ost[j_id][t_id].first = job->getInit_data_size();
                    arrived_pkg_after_ost[j_id][t_id].second = job->getPkg().getByteLength();
                }

                if(arrived_pkg_after_ost[j_id][t_id].first == arrived_pkg_after_ost[j_id][t_id].second) {
                    Job *j = job->dup();
                    cPacket pkg;
                    pkg.setByteLength(j->getInit_data_size());
                    j->setPkg(pkg);
                    send(j, "out", gates_map["sink"]);
                    arrived_pkg_after_ost[j_id].erase(t_id);
                    if(arrived_pkg_after_ost[j_id].empty())
                        arrived_pkg_after_ost.erase(j_id);
                }

                delete job;
            }else{ // w_req has been aggregated in 'split_mtu' module
                send(job, "out", gates_map["sink"]);
            }
        }

    }else if(strcmp(getFullName(), "aggregate") == 0) { // aggreagate both r_req and w_req
        unsigned int j_id(job->getJob_id());
        int t_id(job->getTask_id());
        if(arrived_pkg_after_mds.count(j_id) && arrived_pkg_after_mds[j_id].count(t_id))
            arrived_pkg_after_mds[j_id][t_id].second += job->getPkg().getByteLength();
        else{
            arrived_pkg_after_mds[j_id][t_id].first = job->getInit_data_size();
            arrived_pkg_after_mds[j_id][t_id].second = job->getPkg().getByteLength();
        }

        if(arrived_pkg_after_mds[j_id][t_id].first == arrived_pkg_after_mds[j_id][t_id].second) {
            Job *j = job->dup();
            cPacket pkg;
            pkg.setByteLength(j->getInit_data_size());
            j->setPkg(pkg);
            send(j, "out", j->getAssigned_ost_id());
            arrived_pkg_after_mds[j_id].erase(t_id);
            if(arrived_pkg_after_mds[j_id].empty())
                arrived_pkg_after_mds.erase(j_id);
        }

        delete job;

    }else{
        send(job, "out", out_to_gate);
    }
}

};



