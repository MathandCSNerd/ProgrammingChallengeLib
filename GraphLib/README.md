# GraphLib

This directory contains the graph class and methods I use in
programming challenges.

The files in the examples directory exist to help demonstrate use of
the class. I plan to add more examples to it over time as I become
satisfied with my implementations.

Lastly: I mainly have implementation details contained in  header
files in this library. This is in an effort to imitate the STL's
way of getting around the C++ template object file implementation
issue. I have thought about changing this in the future once I decide
on all of the data types I wish to accommodate, but for now that's
the way it is.

<pre>
Future addition plans:
  Floyd Warshall
  Prims
  A\*

Future Modifications:
  Create namespace either for entire graph library or seperate
    namespaces for different parts.
  Modify motion planning grid code for n-dimensional grids

Potential Additions/Changes:
  Multigraphs
  Maybe modify motion planning grid class for use with Bellman Ford
    Not because there's any use case I can think of for that, but
    more just for consistency with Dijkstra's.
  Configuration Space Class and RRT
    These are unlikely to ever be useful to me in the context in
    which I use this library. If I ever decide to implement these,
    I'm probably just showing off.
</pre>
