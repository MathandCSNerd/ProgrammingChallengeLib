# ProgrammingChallengeLib

This is a library that I have used for programming challenges online and in person. I will not be mentioning any names so as to avoid abuse by via search engine.

Originally much of what is in this library (and much of what I plan to put in this library) was just bits of code I've used for these challenges and eventually needed at least twice.

I am aware many of the functions and classes I will be putting in here have already been implemented in libraries such at Boost and Eigen, but usage of third-party libraries is barred either by the challenge itself, or by a self-imposed handicap.

I mostly stick to the [Google Style Guide](https://google.github.io/styleguide/cppguide.html) and I run clang-format on my code to help ensure compliance. There are some places where I differ due to the scope as well as intended usage of the project.

I also plan to add implementations of most parts of this library in Python3 as well, but I'm first focusing on C++.

Lastly, I've written this library with the intent that the code I write should be as easy for the end user (me) to use as possible. With that in mind, wherever there is a function with a similar parralel in the standard libraries, I will try to mimic the function signatures in the standard library as best as I can within reason. This is done for consistency and ease of use.
For example: I have a CountingSort function which is a void function which takes 2 arguments, one to a first iterator, and the other to the last iterator. This mimics one function signature of std::sort which takes the same arguments.

I'm hosting this library on github in order to share it with friends, collegues, etc.
