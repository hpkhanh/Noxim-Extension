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

      if (line[0] != '\0') {
          if (line[0] != '%') {
              int time, src, no_dst, dst;	// Mandatory

              int params = sscanf(line, "%d %d %d ", &time, &src, &no_dst);
              if (params == 3) {
                  // Create a communication from the parameters read on the line
                  TraceCommunication communication;

                  // Mandatory fields
                  communication.time = time;
                  communication.src = src;
                  communication.no_dst = no_dst;
                  stringstream ss(line);

                  for (int i = 0; i < no_dst+3; i++)
                  {
                      ss >> dst;
                      printf("%d ", dst);
                      if (i >= 3)
                          communication.dsts.push_back(dst);
                  }

                  // Add this communication to the vector of communications
                  traffic_trace.push_back(communication);
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

int GlobalTrafficTrace::occurrencesAsSource(const int src_id)
{
  int count = 0;

  for (unsigned int i = 0; i < traffic_trace.size(); i++)
    if (traffic_trace[i].src == src_id)
      count++;

  return count;
}
