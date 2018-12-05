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

// this file demonstrates getting an minimum spanning forest from a
// given graph

/*INPUT FORMAT:
 *
 * nodes edges
 * edge1_node1 edge1_node2 weight1
 * edge2_node1 edge2_node2 weight2
 * ...
 * nodes edges
 * ...
 * 0 0
 *
 */

#include <iostream>
#include "../graphlibs.h"
#include "../mst/kruskals.h"

using namespace std;

void DoCase(long long n, long long m) {
  UndirectedListGraph<long long> g;

  long long x, y, z;
  InfNum<long long> tmp;

  // this changes the size of the graph to n nodes
  g.ChangeSize(n);

  // this loop adds all the connection information
  for (long long i = 0; i < m; ++i) {
    cin >> x >> y >> z;
    g.AddConnection(x, y, z);
  }

  cout << "the graph: " << endl;
  g.PrintGraph();
  cout << endl;

  auto forest = Kruskals(g);
  cout << forest.size() << " trees were found:" << endl;

  for (auto it : forest) {
    cout << "TREE: " << endl;
    it.PrintGraph();
  }
}

int main() {
  using namespace std;

  // this is an input loop for the first line of each case
  long long n, m, q, s;
  cin >> n >> m;
  while (n || m) {
    DoCase(n, m);
    cin >> n >> m;
    cout << endl;
  }

  return 0;
}
