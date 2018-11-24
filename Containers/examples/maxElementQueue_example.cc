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

#include "../maxElementQueue.h"

using namespace std;

int arr[8] = {1, 4, 5, 2, 6, 4, 1, 3};

void Print(WindowedMaxElementQueue<int> myq) {
  cout << "queue: ";
  while(myq.Size()){
    cout << myq.Front() << ' ';
    myq.pop();
  }
  cout << "\t";
  //myq.Print();
}

int PrintingQueuePush(WindowedMaxElementQueue<int>& myq, int x) {
  myq.push(x);
  Print(myq);
  return myq.MaxElement();
}

void PrintMax(WindowedMaxElementQueue<int>& myq){
  cout << "Max: " << myq.MaxElement() << endl;
}

void PrintStats(WindowedMaxElementQueue<int>& myq){
  Print(myq);
  PrintMax(myq);
}

void PrintPush(WindowedMaxElementQueue<int>& myq, int x){
  cout << "push " << x << endl;
  myq.push(x);
}
    
void PrintPop(WindowedMaxElementQueue<int>& myq){
  cout << "pop " << myq.Front() << endl;
  myq.pop();
}

void PushArrElements(WindowedMaxElementQueue<int>& myq, int begin, int end){
  for (int i = begin; i < end; ++i){
    PrintPush(myq,arr[i]);
    PrintStats(myq);
  }
  cout << endl;
}

int main() {
  //max element q with a 3 window-size
  WindowedMaxElementQueue<int> myq(3);
 
  PushArrElements(myq, 0, 3);
  PrintPop(myq);
  PrintStats(myq);
  cout << endl;

  PushArrElements(myq, 3, 6);
  PushArrElements(myq, 0, 3);
  cout << endl;

  PrintPop(myq);
  PrintPop(myq);
  PrintStats(myq);
  cout << endl;

  PushArrElements(myq, 0, 2);
  cout << endl;

  PrintPop(myq);
  PrintStats(myq);
  cout << endl;

  while (myq.Size()) PrintPop(myq);

  return 0;
}
