/*
 * method.cc
 *
 *  Created on: May 3, 2022
 *      Author: Hao
 */

#include "method.h"

const int64_t sumSize(const RESULTS& res) {
    int64_t ans(0);
    for(auto job:res)
        for(auto task:job.second)
            ans += task.second;

    return ans;
}
