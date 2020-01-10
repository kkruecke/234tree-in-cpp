TODO 
====

* Compare default ~tree234() with a version that calls destroy_tree() by using the sample_value class in include/sample-value.h whose dtort prints to cout. 

* Bug: The iterator class is not efficient. The stack member variable causes the stack to be repeated copied and destroyed in 

The new version new-tree234 has a bug. See bug.cpp. 

Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
