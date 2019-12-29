TODO 
====

* Double check the logic again now that we are again using a std::unique_ptr<Node>. Do this by finishing the test_invariant() code and runningit. And by compiling the version of tree234.h
  from Sunday 12/28/2019 and looking at its output. Look at the Node::debug_print code in tree23, whose calling code is now partly missing.

 Add invariant testing/debug printing that is logical and clear.

* Check if the default ~tree234() works like post-order recursive deletion that destroy_tree() does. And check that destroy_tree() works as expected. 

* Make sure the deletion description for tree234 matches that of the remove() code in ~/d/notes/tree234.rst. 

* Make sure getRemoveSuccessor() is as efficient as possible. If it converts a 2-node to a 3- or 4-node, does the search resume without needless backtracking and needless merging of parent nodes?

* Consider using C++17 sentinel value for value returned by iterator and const_iterator end() methods, to simplify the implementation.
* reimplement insert and delte after reviewing algorithms and understand them better and what member variables their implementation will use.
  See the website urls by ::insert and ::delete. Read them, see how they compare or differ and then write out a canonical example and run it
  using the animation website. From this create pseudo code.

Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
