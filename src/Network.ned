package lfs;

module Network
{
    parameters:
        int channel_count = default(12);
        @display("bgb=415,282;i=device/port;is=n");
    gates:
        input in;
        output out;
    submodules:
        netEntry: Router {
            @display("p=140,200");
        }
        netQueue[channel_count]: Queue {
            @display("p=140,108");
        }
        netCore[channel_count]: Server {
            @display("p=298,108");
        }
        netExit: Router {
            @display("p=298,200");
        }
    connections:
        in --> netEntry.in++;
        for i=0..channel_count-1 {
            netEntry.out++ --> netQueue[i].in++;
            netQueue[i].out --> netCore[i].in++;
            netCore[i].out --> netExit.in++;
        }
        netExit.out++ --> out;
}
