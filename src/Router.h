/*
 * Router.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Hao
 */

#ifndef ROUTER_H_
#define ROUTER_H_

#include <omnetpp.h>
#include <unordered_map>
#include "Job_m.h"
#include "Queue.h"
#include "method.h"

using namespace omnetpp;

namespace lfs {
class Router  : public cSimpleModule
{
    private:
        std::unordered_map<std::string, int> gates_map;
        RECORDS arrived_pkg_after_mds, arrived_pkg_after_ost; // <Job_id, <task_id, <init_size, pkg_size>>>
    public:
        Router();
        virtual ~Router();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};
};


#endif /* ROUTER_H_ */
