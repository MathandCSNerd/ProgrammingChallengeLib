#GraphLib

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
  Motion Planning Grid class
  Bellman Ford
  Floyd Warshall
  Prims

Future Modifications:
  Create namespace either for entire graph library or separate parts
  Change "dstra" to better accommodate motion planning
  Rewrite the interface for "dstra" and Bellman Ford to be the same
    to allow to more generic calls to SSSP algorithms.
  Change the name of "dstra" to "DijkstraSSSP" to be more explicit
    with what it is.
</pre>
