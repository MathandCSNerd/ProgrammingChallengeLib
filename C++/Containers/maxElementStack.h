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

#ifndef CONTAINER_MAX_ELEMENT_STACK
#define CONTAINER_MAX_ELEMENT_STACK

#include <deque>
#include <iostream>
#include <stack>

// this class is a stack which provides a MaxElement function which
// returns the maximum element in constant time
// this class requires O(n) auxillary memory to pointers to
// maxElements in average case it would probably be closer to n/2
// pointers to elements
template <class myType>
class MaxElementStack {
 public:
  MaxElementStack() {}

  void Reset() {
    while (maxStack.size()) maxStack.pop_back();
    while (elementStack.size()) elementStack.pop();
  }

  void push(myType& x) {
    elementStack.push(x);
    if (!maxStack.size() || !(x < (*maxStack.top())))
      maxStack.push(&(elementStack.top()));
  }

  void pop() {
    if (elementStack.size()) {
      // the first condition shouldn't be neccessary since
      // elementStack.size() > 0 implies maxStack.size() > 0
      // but I'm putting it in to ensure that even an invalid
      // state won't segfault
      if (maxStack.size() and *(maxStack.top()) == (elementStack.top()))
        maxStack.pop();
      elementStack.pop();
    }
  }

  // TODO: decide what to do on empty stack
  const myType& MaxElement() const {
    if (maxStack.size()) return *maxStack.top();
  }

  // TODO: decide what to do on empty stack
  const myType& Top() const {
    if (elementStack.size()) return elementStack.top();
  }

  size_t Size() const { return elementStack.size(); }

 private:
  // According to the c++ standard, the default template argument
  // for the underlying container for stack is to use a deque,
  // but I'm being more explicit for readability.
  //
  // When pop'ing elements from the ends in a deque, pointers are
  // only invalidated if the element to which they're pointing is
  // removed so I can keep a stack of pointers to max elements in
  // another stack as long as I pop off pointers to items as I pop
  // off the items themselves.
  std::stack<myType*> maxStack;
  std::stack<myType, std::deque<myType> > elementStack;
};

#endif
