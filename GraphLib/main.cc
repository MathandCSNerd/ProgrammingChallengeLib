/* Copyright 2018 Matthew Macallister
 *
 * This file is part of ProgrammingChallengeLib.
 *
 * ProgrammingChallengeLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ProgrammingChallengeLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProgrammingChallengeLib.  If not, see <https://www.gnu.org/licenses/>.
 */

//#########################
//GRAPH TEST CODE
//#########################

/*INPUT FORMAT:
 *
 * nodes edges queries source
 * edge1_node1 edge1_node2
 * edge2_node1 edge2_node2
 * ...
 * query1
 * query2
 * ...
 * source
 *
 * ex:
 * 4 3 4 0  #4 nodes, 3 edges, 4 queries, source is 0
 * 0 2 6    #first edge goes from 0 to 2 with weight 6
 * 2 1 3    #next edge goes from 2 to 1 with weight 3
 * 0 3 2    #next edge goes from 0 to 3 with weight 2
 * 0        #first query is length of path to 0
 * 1        #query 2
 * 2        #query 3
 * 3        #query 4
 * 0 0 0 0  #end input
 */

#include "directedGraph.h"
#include "dstra.h"
#include <iostream>

using namespace std;

template <class weightType>
using mgraph = DirectedListGraph<weightType>;

void DoCase(long long n, long long m, long q, long long s){
  mgraph<long long> g;
  long long x,y,z,tmp;

  g.ChangeSize(n);
  for(long long i = 0; i < m; ++i){
    cin >> x >> y >> z;
    g.AddConnection(x,y,z);
  }
  Dstra(s,s,g);

  for(long long i = 0; i < q; ++i){
    cin >> x;
    tmp = Dstra(-1,x,g);
    if(tmp < 0)
      cout << "Impossible" << endl;
    else
      cout << tmp << endl;
  }
}

int main(){
  using namespace std;

  //test for basic graph functionality
  {
  /*int arr[5][5]={
  {1,1,2,3,4},
  {0,0,2,3,4},
  {0,0,1,0,0},
  {0,0,0,3,4},
  {0,0,0,0,4}
  };
  const int s =5;
  mgraph<int> g;
  g.SetDirected(0);
  g.ChangeSize(5);
  for(int i = 0; i < s; ++i)
    for(int i2 = 0; i2 < s; ++i2)
      if(arr[i][i2])
        //g.AddConnection(i,i2);
        g.AddConnection(i,i2,arr[i][i2]);
  g.PrintGraph();

  cout << endl;
  for(auto it = g.Begin(1); it != g.End(1); ++it)
    it->Print();
  cout << endl;*/
  }

  //test for sssp, non-negative weights
  {
  long long n,m,q,s;
  cin >> n >> m >> q >> s;
  while(n || m || q || s){
    DoCase(n,m,q,s);
    cin >> n >> m >> q >> s;
    cout << endl;
  }
  }

  return 0;
}
