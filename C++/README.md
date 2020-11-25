# ProgrammingChallengeLib C++ Libs

This is the collection of C++ libraries in my Programming Challenge Lib.

I mostly stick to the [Google Style Guide](https://google.github.io/styleguide/cppguide.html) and I run clang-format on my code to help ensure compliance. There are some places where I differ due to the scope as well as intended usage of the project.

Lastly, I've written this library with the intent that the code I write should be as easy for the end user (me) to use as possible (which is why most of it is templated). With that in mind, wherever there is a function with a similar parallel in the standard libraries, I will try to mimic the function signatures in the standard library as best as I can within reason. This is done for consistency and ease of use.
For example: I have a CountingSort function which is a void function which takes 2 arguments, one to a first iterator, and the other to the last iterator. This mimics one function signature of std::sort which takes the same arguments.
