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

#ifndef CONTAINER_MAX_ELEMENT_QUEUE
#define CONTAINER_MAX_ELEMENT_QUEUE

#include <deque>
#include <iostream>
#include <queue>

// this class is a queue which provides a MaxElement function which
// returns the maximum element in constant time
// the queue can optionally be given a window size, which ensures it
// only holds onto window_size items at most
// I've provided an alias named "MaxElementQueue" for the case where
// one does not need a window size
template <class myType>
class WindowedMaxElementQueue {
 public:
  WindowedMaxElementQueue(size_t x) : size(x), count(0) {}
  WindowedMaxElementQueue() : size(0), count(0) {}

  void Reset() {
    while (windowQueue.size()) windowQueue.pop_back();
    while (elementQueue.size()) elementQueue.pop();
    count = 0;
  }

  void push(myType& x) {
    ++count;

    UpdateWindow();

    elementQueue.push(x);
    if (size)
      while (elementQueue.size() > size) elementQueue.pop();

    while (windowQueue.size() && x >= windowQueue.back().first)
      windowQueue.pop_back();

    windowQueue.push_back(std::make_pair(x, count - 1));
  }

  // TODO: decide what to do on empty queue
  void pop() {
    if (elementQueue.size()) {
      elementQueue.pop();

      // update the window, to remove the front of
      // elementQueue if present and outside window
      ++count;
      UpdateWindow();
      --count;
    }
  }

  // TODO: decide what to do on empty queue
  const myType& MaxElement() const {
    if (windowQueue.size()) return windowQueue.front().first;
  }

  // TODO: decide what to do on empty queue
  const myType& Front() const {
    if (windowQueue.size()) return elementQueue.front();
  }

  size_t Size() const { return elementQueue.size(); }

 private:
  void UpdateWindow() {
    if (size)
      while (windowQueue.size() && windowQueue.front().second + size < count)
        windowQueue.pop_front();
  }

  size_t size;
  size_t count;
  std::deque<std::pair<myType, myType>> windowQueue;
  std::queue<myType> elementQueue;
};

template <class T>
using MaxElementQueue = WindowedMaxElementQueue<T>;

#endif
