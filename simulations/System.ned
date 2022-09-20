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

package lfs.simulations;

import lfs.Network;
import lfs.OSS;
import lfs.OST;
import lfs.Router;
import lfs.Source;
import lfs.Sink;
import lfs.MDS;

network System
{
    parameters:
        int oss_num = 4;
        int ost_num = 42;
        int cable_num = 4;
        @display("bgb=767,378");
    submodules:
        source: Source {
            @display("p=31,115");
        }
        sink: Sink {
            @display("p=673,48");
        }
        mds: MDS {
            @display("p=98,115");
        }
        split_mtu: Router {
            @display("p=142,297");
        }
        oss[oss_num]: OSS {
            @display("p=313,161");
        }
        aggregate: Router {
            @display("p=413,161");
        }
        ost[ost_num]: OST {
            @display("p=413,297");
        }
        split_page: Router {
            @display("p=244,48");
        }
        net_channels[cable_num]: Network {
            @display("p=181,160");
        }
    connections:
        source.out --> mds.in;
        mds.out --> split_mtu.in++;

        for i=0..cable_num-1 {
            split_mtu.out++ --> net_channels[i].in;
            net_channels[i].out --> split_page.in++;
        }

        for i=0..oss_num-1 {
            split_page.out++ --> oss[i].in;
            oss[i].out --> aggregate.in++;
        }

        for i=0..ost_num-1 {
            aggregate.out++ --> ost[i].in;
            ost[i].out --> split_mtu.in++;
        }
        split_page.out++ --> sink.in++;
}
