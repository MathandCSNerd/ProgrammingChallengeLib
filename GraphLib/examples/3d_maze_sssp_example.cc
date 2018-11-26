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

// This file demonstrates how to use the motionPlanningGrid
// to find the shortest path from a source in an n-dimensional
// maze.
//
// More specifically I've set this up for a 3-dimensional maze,
// but the motionPlanningGrid class should work for an
// arbitrary number of dimensions within reason.
//
// input is read from stdin and indexes start at 0

/*INPUT FORMAT:
 *
 * number of queries (q)
 * query1_row query1_col
 * query2_row query2_col
 * ...
 * queryq_row queryq_col
 *
 * ex:
 * 2    //2 queries
 * 2 1  //first destination is row 2 col 1
 * 1 3  //second destination is row 1 col 3
 */

#include <iostream>
#include "../graphlibs.h"

using namespace std;

const int size = 4;
int const sizes[3] = {size, size - 1, size + 1};
long long theMaze[size][size - 1][size + 1] = {
    {{1, 1, 1, 1, 1}, {-1, -1, -1, -1, -1}, {1, 1, 1, 1, 1}},

    {{5, 4, 3, 2, 1}, {1, 4, -1, 2, 1}, {4, 1, 1, 1, 3}},

    {{1, 7, 1, 1, 1}, {1, 1, 7, 1, 7}, {1, 7, -1, 7, -1}},

    {{1, 2, -1, -1, 5}, {1, 3, -1, 4, 1}, {-1, -1, 3, 1, 1}}

};

void DoCase() {
  long long x, y, z;
  MatCoords tmpCoord({sizes[0], sizes[1], sizes[2]});
  MotionPlanningGrid<long long> g(tmpCoord);

  // this is the input loop
  // Weights are initialized to infinity until
  // I give them a weight. In this case all
  // negative values are infinite weight.
  for (long long i = 0; i < sizes[0]; ++i) {
    for (long long i2 = 0; i2 < sizes[1]; ++i2) {
      for (long long i3 = 0; i3 < sizes[2]; ++i3) {
        if (theMaze[i][i2][i3] < 0)
          ;
        else {
          tmpCoord.Set({i, i2, i3});
          g(tmpCoord) = theMaze[i][i2][i3];
        }
      }
    }
  }

  cout << "#######################################################\n\n";
  cout << "The following is a 2d printout of the 3d maze: " << endl;
  cout << "Each slice represents a different depth layer (index 0)\n";
  g.Print();
  cout << "#######################################################\n\n";
  // set the source to be 0,0
  MatCoords source({0, 0, 0});
  auto dostra = NewDijkstraSSSPInstance(g, source);

  MatCoords dest;

  long long q;
  cout << "input number of queries: " << endl;
  cin >> q;
  // this loop performs the number of queries the user requests
  for (long long i = 0; i < q; ++i) {
    cout << "input query: " << i << endl;
    cin >> x >> y >> z;
    dest.Set({x, y, z});
    cout << "query " << i << ": (" << x << ' ' << y << ' ' << z << ") " << endl;

    // ShortestPathCost will return an infNum class
    // if path DNE, the number will be infinity
    auto tmp = dostra.ShortestPathCost(dest);
    cout << "COST: " << tmp << endl;

    // if the path dne, path will be an empty list
    auto path = dostra.ShortestPath(dest);
    cout << "####PATH#####" << endl;
    for (auto it : path) cout << it << ' ';
    cout << endl << endl;
  }
}

int main() {
  using namespace std;
  DoCase();

  return 0;
}
