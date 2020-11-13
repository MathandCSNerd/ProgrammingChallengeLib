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

// this file demonstrates how to use the motionPlanningGrid
// class on an SSSP problem. In this example I've set source to
// 0,0 and the example grid I use is represented by the array
// "theMaze". All negative entries in the array I've considered
// to be obstacles.
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

const int size = 7;
long long theMaze[size][size] = {
    {6, 1, 1, 7, 1, 1, 1}, {1, -1, -1, 3, 1, 1, 1},   {1, -1, -1, 1, 1, 1, 1},
    {1, 1, 3, 1, 0, 1, 4}, {1, 3, 1, -1, -1, -1, -1}, {1, 5, 1, -1, 5, 1, 1},
    {1, 4, 1, 6, 1, -1, 1}};

void DoCase(long q) {
  long long x, y;
  // Coordinates<size_t> tmpCoord(size, size);
  MatCoords tmpCoord(size, size);
  MotionPlanningGrid<long long> g(tmpCoord);

  // Sets rows and cols of g to be "tmpCoord's" size.
  // g.ChangeSize(tmpCoord);

  // this is the input loop
  // Weights are initialized to infinity until
  // I give them a weight. In this case all
  // negative values are infinite weight.
  for (long long i = 0; i < size; ++i) {
    for (long long i2 = 0; i2 < size; ++i2) {
      if (theMaze[i][i2] < 0)
        ;
      else {
        tmpCoord.Set(i, i2);
        g(tmpCoord) = theMaze[i][i2];
      }
    }
  }

  g.Print();
  // set the source to be 0,0
  MatCoords source(0, 0);
  auto dostra = NewDijkstraSSSPInstance(g, source);

  MatCoords dest;

  // this loop performs the number of queries the user requests
  for (long long i = 0; i < q; ++i) {
    cin >> x >> y;  // row, col format
    dest.Set(x, y);
    cout << "case " << x << ' ' << y << ' ' << i << endl;

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
  long long q;

  for (int i = 0; i < size; ++i) {
    for (int i2 = 0; i2 < size; ++i2) cout << theMaze[i][i2] << ' ';
    cout << endl;
  }

  cin >> q;
  DoCase(q);

  return 0;
}
