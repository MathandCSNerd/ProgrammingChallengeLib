#GraphLib

This directory contains the graph class and methods I use in
programming challenges.

The file main.cc exists to help demonstrate use.

At the moment it's setup as a correct submission to a certain
programming problem on a certain website.
Currently this only demonstrates the most rudimentary usage of the
class however. The class is written in a versatile manner and can
be applied to many more situations.

Please Note the website puts certain constraints on the inputs which
that code assumes. The code probably works with most other similar
constraints but it's has been tested using those. Instructions on how
to format input are inside main.cc.

I plan to add more to it over time as I become satisfied with my
implementations.

Lastly: I mainly use header files in this library. This is in an effort
to imitate the STL's way of getting around the classic C++ template
object file implementation issue. I have thought about changing this
in the future once I decide on all of the data types I wish to
accommodate, but for now that's the way it is.

<pre>
Future addition plans:
  Motion Planning Grid class
  Bellman Ford
  Floyd Warshall
  Prims

Future Modifications:
  create namespace either for entire graph library or separate parts
  change "dstra" to better accommodate motion planning
</pre>
