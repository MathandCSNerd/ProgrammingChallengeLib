/* Copyright 2018 Matthew Macallister
 *
 * This file is part of ProgrammingChallengeLib.
 *
 * ProgrammingChallengeLib is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ProgrammingChallengeLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProgrammingChallengeLib.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

// this file demonstrates how to use the graph class on an SSSP problem
// input is read from stdin

/*INPUT FORMAT:
 *
 * nodes edges queries source
 * edge1_node1 edge1_node2 weight1
 * edge2_node1 edge2_node2 weight2
 * ...
 * query1
 * query2
 * ...
 * nodes edges queries source
 * ...
 *
 * ex:
 * 4 3 4 0  #4 nodes, 3 edges, 4 queries, source is 0
 * 0 2 6    #first edge goes from 0 to 2 with weight 6
 * 2 1 3    #next edge goes from 2 to 1 with weight 3
 * 0 3 2    #next edge goes from 0 to 3 with weight 2
 * 0        #query 1 is length of path from 0->0
 * 1        #query 2 is length of path from 0->1
 * 2        #query 3 is length of path from 0->2
 * 3        #query 4 is length of path from 0->3
 * 0 0 0 0  #end input
 */

#include <iostream>
#include "../directedGraph.h"
#include "../dijkstraSSSP.h"

using namespace std;

void DoCase(long long n, long long m, long q, long long s) {
  DirectedListGraph<long long> g;

  long long x, y, z, tmp;

  // this changes the size of the graph to n nodes
  g.ChangeSize(n);

  // this loop adds all the connection information
  for (long long i = 0; i < m; ++i) {
    cin >> x >> y >> z;
    g.AddConnection(x, y, z);
  }

  // This is the initial call to the SSSP solver
  // this is required for intilization purposes and
  // must be called any time one wants to switch source
  // nodes.
  DijkstraSSSP(s, s, g);

  // this loop iterates through the queries
  for (long long i = 0; i < q; ++i) {
    cin >> x;

    // This calls the SSSP solver from the previously defined source
    // node, to node x, with graph object g.
    tmp = DijkstraSSSP(-1, x, g);

    if (tmp < 0)
      cout << "Impossible" << endl;
    else
      cout << tmp << endl;
  }
}

int main() {
  using namespace std;

  // this is an input loop for the first line of each case
  long long n, m, q, s;
  cin >> n >> m >> q >> s;
  while (n || m || q || s) {
    DoCase(n, m, q, s);
    cin >> n >> m >> q >> s;
    cout << endl;
  }

  return 0;
}
