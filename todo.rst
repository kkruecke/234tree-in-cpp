TODO 
====

* Compare default ~tree234() with a version that calls destroy_tree() by using the sample_value class in include/sample-value.h whose dtort prints to cout. 

* Issue: 

   * The iterator class itself is efficient because it uses a stack of int's, but this in turns makes its copy constructor less efficient because the stack is copied. ``reverse_iterator::operator++()``, for example, copies the underlying iterator each time it executes. 
     The solution is to remove the stack from class iterator and also the ``iterator::push()`` and ``iterator::pop()`` methods, and to replace the line ``auto child_index = pop();`` in ``iterator::getLeafNodeSuccessor()`` and ``iterator::getLeafNodeSuccessor()`` with 
     ``auto child_index = pnode->getChildIndex()``.  This will make the iterator's copy constructor efficient but its performance a bit slower.

Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
