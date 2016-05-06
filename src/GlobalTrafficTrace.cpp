/*
 * Noxim - the NoC Simulator
 *
 * (C) 2005-2015 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the implementation of the global traffic trace
 */

#include "GlobalTrafficTrace.h"
#include "GlobalParams.h"
#include <math.h>

GlobalTrafficTrace::GlobalTrafficTrace()
{
}

bool GlobalTrafficTrace::load(const char *fname)
{
  // Open file
  ifstream fin(fname, ios::in);
  if (!fin)
    return false;

  // Initialize variables
  traffic_trace.clear();

  // Cycle reading file
  while (!fin.eof()) {
      char line[512];
      fin.getline(line, sizeof(line) - 1);

      if ((line[0] != '\0') || (line[0] != '%')) {
          if (line[0] != '%') {
              int time, group_src, group_dst, src, no_dst, no_flit;	// Mandatory

              int params = sscanf(line, "%d %d %d %d %d %d", &time, &group_src, &group_dst, &src, &no_dst, &no_flit);
              if (params >= 5)
              {
                  // Create a communication from the parameters read on the line
                  TraceCommunication communication;

                  if (params == 5)
                      no_flit = 1;
                  // Mandatory fields
                  communication.time = GlobalParams::reset_time + GlobalParams::stats_warm_up_time + time;
                  communication.no_flit = no_flit;
                  communication.group_src = group_src;
                  communication.group_dst = group_dst;
                  communication.src = src;
                  communication.no_dst = no_dst;

                  fin.getline(line, sizeof(line) - 1);
                  while (line[0] == '%')
                      fin.getline(line, sizeof(line) - 1);
                  stringstream ss(line);
                  for (int i = 0; i < no_dst; i++)
                  {
                      int dst;
                      ss >> dst;
                      printf("%d ", dst);
                      communication.dsts.push_back(dst);
                  }

                  // Add this communication to the vector of communications
                  traffic_trace.push_back(communication);
                  printf("\n");
              }
          }
      }
  }

  return true;
}

/*double GlobalTrafficTrace::getCumulativePirPor(const int src_id,
						    const int ccycle,
						    const bool pir_not_por,
						    vector < pair < int, double > > &dst_prob)
{
  double cpirnpor = 0.0;

  dst_prob.clear();

  for (unsigned int i = 0; i < traffic_trace.size(); i++) {
    Communication comm = traffic_trace[i];
    if (comm.src == src_id) {
      int r_ccycle = ccycle % comm.t_period;
      if (r_ccycle > comm.t_on && r_ccycle < comm.t_off) {
	cpirnpor += pir_not_por ? comm.pir : comm.por;
	pair < int, double >dp(comm.dst, cpirnpor);
	dst_prob.push_back(dp);
      }
    }
  }

  return cpirnpor;
}*/

bool GlobalTrafficTrace::canShoot(const int src_id, const int now, int * dest_id)
{
    bool shoot = false;
    for (unsigned int i = 0; i < traffic_trace.size(); i++)
    {
        TraceCommunication comm = traffic_trace[i];
        if (comm.src == src_id)
        {
            if ((now >=  comm.time) && (now < comm.time + comm.no_dst))
            {
                shoot = true;
                *dest_id = comm.dsts[now - comm.time];
                if (now == comm.time + comm.no_dst - 1)
                    traffic_trace.erase(traffic_trace.begin()+i);
//                printf("Shoot %d \n", now);
            }

            break;
        }
    }
    return shoot;
}

int GlobalTrafficTrace::occurrencesAsSource(const int src_id)
{
  int count = 0;

  for (unsigned int i = 0; i < traffic_trace.size(); i++)
    if (traffic_trace[i].src == src_id)
      count++;

  return count;
}
