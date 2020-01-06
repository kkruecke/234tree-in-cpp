TODO 
====

* Compare default ~tree234() with a version that calls destroy_tree() by using the sample_value class in include/sample-value.h whose dtort prints to cout. 

* Make sure the deletion description for tree234 matches that of the remove() code in ~/d/notes/tree234.rst. 

* The code to iterator and get the successor should also pass in the child_index, so I can eliminate the Node::getChildIndex() method. getSuccessor() is called from two places.
  One is the iterative in-order traversal. This can be changed to directly use the nested iterator class, so the change is isolated to the iterator class, to which can be added
  a child_node member variable as a possible solution.

Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
