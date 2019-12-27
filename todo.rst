TODO 
====

* But in tree234(const  tree234&) copy ctor. Fails to clone tree.
* Make sure the deletion description for tree234 matches that of the remove() code in ~/d/notes/tree234.rst.

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
