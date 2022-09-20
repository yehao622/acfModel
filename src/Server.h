/*
 * Server.h
 *
 *  Created on: Apr 16, 2022
 *      Author: Hao
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <omnetpp.h>
#include "Job_m.h"
#include "method.h"

using namespace omnetpp;

namespace lfs {
class Server : public cSimpleModule
{
    private:
        int job_count;
        bool free_status;
        simsignal_t avgIOPS;
        simsignal_t sWaitSignal;
        simtime_t end_time;
        simtime_t last_visit_time;
        void updateTimeStamp(Job* j);
        void mdsSendMessage(Job* j);
        void ossSendMessage(Job* j);
        void ostSendMessage(Job* j);
        void netSendMessage(Job* j);

    public:
        Server();
        virtual ~Server();
        virtual bool isIdle();
        simtime_t getEndTimeStamp();

    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
//        virtual void refreshDisplay() const override;
        virtual void finish() override;
};

}; //namespace



#endif /* SERVER_H_ */
