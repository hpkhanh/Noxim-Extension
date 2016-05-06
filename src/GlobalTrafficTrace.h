/*
 * GlobalTrafficTrace.h
 *
 *  Created on: Mar 22, 2016
 *      Author: khanh
 */

#ifndef __NOXIMGLOBALTRAFFICTRACE_H_
#define __NOXIMGLOBALTRAFFICTRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "DataStructs.h"

using namespace std;

// Structure used to store information into the trace
struct TraceCommunication {
  int time;
  int group_src;
  int group_dst;
  int src;          // ID of the source node (PE)
  int no_dst;
  int no_flit;
  vector <int> dsts;          // ID of the destination node (PE)
};

class GlobalTrafficTrace {

  public:

    GlobalTrafficTrace();

    // Load traffic trace from file. Returns true if ok, false otherwise
    bool load(const char *fname);

    // Returns the cumulative pir por along with a vector of pairs. The
    // first component of the pair is the destination. The second
    // component is the cumulative shooting probability.
/*    double getCumulativePirPor(const int src_id,
                   const int ccycle,
                   const bool pir_not_por,
                   vector < pair < int, double > > &dst_prob);*/
    bool canShoot(const int src_id, const int now, int * dest_id);

    // Returns the number of occurrences of source src_id in the traffic
    // trace
    int occurrencesAsSource(const int src_id);

  private:

     vector < TraceCommunication > traffic_trace;
};


#endif /* __NOXIMGLOBALTRAFFICTRACE_H_ */
