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

/* This files demonstrates some basic usage of the graph class
 */

#include <iostream>
#include "../graphContainers.h"

using namespace std;

int main() {
  using namespace std;

  // this is just an array that the test gets connection
  // information from
  int arr[5][5] = {{1, 1, 2, 3, 4},
                   {0, 0, 2, 3, 4},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 3, 4},
                   {0, 0, 0, 0, 4}};

  // s is the source node
  const int s = 5;

  // these two declarations are interchangeable in this context
  // one is for a graph which uses a list as a container
  // and the other is for an array based graph.
  //
  // Both have roughly the same interface.

  // UndirectedArrGraph<int> g;
  UndirectedListGraph<int> g;

  // this line sets the number of nodes in g to 5
  g.ChangeSize(5);

  // this is a simple for loop for adding all the connection
  // information from the array above
  for (int i = 0; i < s; ++i)
    for (int i2 = 0; i2 < s; ++i2)
      if (arr[i][i2]) g.AddConnection(i, i2, arr[i][i2]);

  // this prints the adjacency information in the graph
  // in the format the container defines
  // this output differs between array based graphs and
  // list based graphs
  g.PrintGraph();
  cout << endl;

  // This section iterates through all the connections from node 1
  //(note the indexing starts at 0) and outputs the weights
  for (auto it = g.begin(1); it != g.end(1); ++it) cout << it->Weight();
  cout << endl;

  // check whether or not the graph we're using is Directed
  cout << g.Directed() << endl;
  return 0;
}
