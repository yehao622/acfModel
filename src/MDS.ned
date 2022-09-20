package lfs;

module MDS
{
    parameters:
        int core_count = default(1);
        @display("bgb=415,282;i=device/server;is=n");
    gates:
        input in;
        output out;
    submodules:
        mdsEntry: Router {
            @display("p=140,200");
        }
        mdsQueue[core_count]: Queue {
            @display("p=140,108");
        }
        mdsCore[core_count]: Server {
            @display("p=298,108");
        }
        mdsExit: Router {
            @display("p=298,200");
        }
    connections:
        in --> mdsEntry.in++;
        for i=0..core_count-1 {
            mdsEntry.out++ --> mdsQueue[i].in++;
            mdsQueue[i].out --> mdsCore[i].in++;
            mdsCore[i].out --> mdsExit.in++;
        }
        mdsExit.out++ --> out;
}