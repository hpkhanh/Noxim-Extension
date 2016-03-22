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
  int src;          // ID of the source node (PE)
  int dst;          // ID of the destination node (PE)
  double pir;           // Packet Injection Rate for the link
  double por;           // Probability Of Retransmission for the link
  int t_on;         // Time (in cycles) at which activity begins
  int t_off;            // Time (in cycles) at which activity ends
  int t_period;             // Period after which activity starts again
};

class GlobalTrafficTrace {

  public:

    GlobalTrafficTrace();

    // Load traffic trace from file. Returns true if ok, false otherwise
    bool load(const char *fname);

    // Returns the cumulative pir por along with a vector of pairs. The
    // first component of the pair is the destination. The second
    // component is the cumulative shotting probability.
    double getCumulativePirPor(const int src_id,
                   const int ccycle,
                   const bool pir_not_por,
                   vector < pair < int, double > > &dst_prob);

    // Returns the number of occurrences of soruce src_id in the traffic
    // trace
    int occurrencesAsSource(const int src_id);

  private:

     vector < Communication > traffic_trace;
};


#endif /* __NOXIMGLOBALTRAFFICTRACE_H_ */
