/*
 * method.h
 *
 *  Created on: May 3, 2022
 *      Author: Hao
 */

#ifndef METHOD_H_
#define METHOD_H_

#include "Job_m.h"
#include <tuple>
#include <unordered_map>
#include <fstream>

#define STRIPE_SIZE 1048576
#define STRIPE_COUNT 2
#define CACHE_HIT_RATIO 0.0
#define BLOCK_SIZE 4096
#define PAGE_SIZE 4096
#define OSS_NUM 4
#define OST_NUM 42
#define MTU 65520 //9000, 1500

using namespace omnetpp;
using namespace lfs;

typedef std::unordered_map<unsigned int, std::unordered_map<int, std::pair<int64_t, int64_t>>> RECORDS;
typedef std::unordered_map<unsigned int, std::unordered_map<int, int64_t>> RESULTS;

extern RESULTS read_res, write_res;

const int64_t sumSize(const RESULTS&);

#endif /* METHOD_H_ */
