TODO 
====

* Compare default ~tree234() with a version that calls destroy_tree() by using the sample_value class in include/sample-value.h whose dtort prints to cout. 

* Make sure the deletion description for tree234 matches that of the remove() code in ~/d/notes/tree234.rst. 

* BUG: Code blows up when we try to remove from a tree that has a 2-node root and two 2-node children. For example

  tree234<int, int> stree = { {5, 5}, {40, 40}, {70, 70}, {120, 120}};
  stree.remove(40);
  cout << stree;
  stree.remove(70); //<-- BUG: Delete root of tree with 2-node root with two 2-node children. We failed to special case the root being a 2-node with 2-node children


  tree234<int, int> tree = { { 

Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
