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

#include "../maxElementStack.h"

using namespace std;

int arr[8] = {1, 4, 5, 2, 6, 4, 1, 3};
class mint {
  // mint(){}
 public:
  bool operator<(const mint& that) { return x < that.x; }
  mint& operator=(const mint& that) {
    x = that.x;
    return *this;
  }
  int x;
};

void Print(MaxElementStack<int> mystack) {
  cout << "queue: ";
  while (mystack.Size()) {
    cout << mystack.Top() << ' ';
    mystack.pop();
  }
  cout << "\t";
  // mystack.Print();
}

int PrintingQueuePush(MaxElementStack<int>& mystack, int x) {
  mystack.push(x);
  Print(mystack);
  return mystack.MaxElement();
}

void PrintMax(MaxElementStack<int>& mystack) {
  cout << "Max: " << mystack.MaxElement() << endl;
}

void PrintStats(MaxElementStack<int>& mystack) {
  Print(mystack);
  PrintMax(mystack);
}

void PrintPush(MaxElementStack<int>& mystack, int x) {
  cout << "push " << x << endl;
  mystack.push(x);
}

void PrintPop(MaxElementStack<int>& mystack) {
  cout << "pop " << mystack.Top() << endl;
  mystack.pop();
}

void PushArrElements(MaxElementStack<int>& mystack, int begin, int end) {
  for (int i = begin; i < end; ++i) {
    PrintPush(mystack, arr[i]);
    PrintStats(mystack);
  }
  cout << endl;
}

int main() {
  // this piece is just here as a contrived example of
  // using the stack with a user-defined data type
  {
    cout << "START OF CONTRIVED EXAMPLE" << endl;
    MaxElementStack<mint> contrivedExample;
    mint contrivedExampleElement;
    contrivedExampleElement.x = 3;
    contrivedExample.push(contrivedExampleElement);
    cout << contrivedExample.MaxElement().x << endl;
    cout << "END OF CONTRIVED EXAMPLE" << endl;
  }

  MaxElementStack<int> mystack;

  PushArrElements(mystack, 0, 3);
  PrintPop(mystack);
  PrintStats(mystack);
  cout << endl;

  PushArrElements(mystack, 3, 6);
  PushArrElements(mystack, 0, 3);
  cout << endl;

  PrintPop(mystack);
  PrintPop(mystack);
  PrintStats(mystack);
  cout << endl;

  PushArrElements(mystack, 0, 2);
  cout << endl;

  PrintPop(mystack);
  PrintStats(mystack);
  cout << endl;

  while (mystack.Size()) PrintPop(mystack);

  cout << endl;
  return 0;
}
