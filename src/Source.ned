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

//
// Generates messages with a configurable interarrival time.
//
simple Source
{
    parameters:
        volatile double sendInterval @unit(s) = default(exponential(2.7e-7s));
        //volatile double avgPkgSize = default(exponential(1.0));
        @display("i=block/source");
    gates:
        output out;
}