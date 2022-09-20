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

package lfs;

simple Server
{
    parameters:
        @display("i=block/server");
        @signal[averageIOPS](type="double");
        @signal[waitInStation](type="double");
        @statistic[averageIOPS](title="Average IO throughput";record=histogram);
        @statistic[waitInStation](title="Average waiting time in station";record=histogram);
//        @statistic[busy](title="server busy state";record=vector?,timeavg;interpolationmode=sample-hold);

        // # of requests per second
        volatile double mds_rate_r @unit(s) = default(exponential(3e-9s));
        volatile double mds_rate_w @unit(s) = default(exponential(6e-9s));
        
        // rates 2 lines below are MB/s 
        volatile double oss_rate @unit(s) = default(exponential(1.2e-4s));
        volatile double one_channel_rate @unit(s) = default(exponential(5.5e-4s));
        
        // OST write rate seconds per KB
        volatile double ost_rate_l1k_w @unit(s) = default(exponential(2.55e-5s));
        volatile double ost_rate_l4k_w @unit(s) = default(exponential(2.72e-5s));
        double slope_l4k_w @unit(s) = default(3.2e-6s);
        volatile double ost_rate_l8k_w @unit(s) = default(exponential(3.64e-5s));
        double slope_l8k_w @unit(s) = default(1.15e-6s);
        volatile double ost_rate_l16k_w @unit(s) = default(exponential(4.10e-5s));
        double slope_l16k_w @unit(s) = default(1.55e-6s);
        volatile double ost_rate_l32k_w @unit(s) = default(exponential(5.34e-5s));
        double slope_l32k_w @unit(s) = default(1.88e-6s);
        volatile double ost_rate_l256k_w @unit(s) = default(exponential(8.35e-5s));
        double slope_l256k_w @unit(s) = default(1.58e-6s);
        volatile double ost_rate_g256k_w @unit(s) = default(exponential(4.37e-4s));
        // OST read rate seconds per KB
        volatile double ost_rate_l64_r @unit(s) = default(exponential(2.00e-6s));
        volatile double ost_rate_l1k_r @unit(s) = default(exponential(3.05e-6s));
        volatile double ost_rate_l4k_r @unit(s) = default(exponential(3.10e-6s));
        double slope_l4k_r @unit(s) = default(3.2e-6s);
        volatile double ost_rate_l8k_r @unit(s) = default(exponential(1.20e-5s));
        double slope_l8k_r @unit(s) = default(8.75e-7s);
        volatile double ost_rate_l16k_r @unit(s) = default(exponential(1.55e-5s));
        double slope_l16k_r @unit(s) = default(1.44e-6s);
        volatile double ost_rate_l32k_r @unit(s) = default(exponential(2.7e-5s));
        double slope_l32k_r @unit(s) = default(1.19e-6s);
        volatile double ost_rate_l256k_r @unit(s) = default(exponential(4.6e-5s));
        double slope_l256k_r @unit(s) = default(1.12e-6s);
        volatile double ost_rate_g256k_r @unit(s) = default(exponential(2.97e-4s));
    gates:
        input in[];
        output out;
}