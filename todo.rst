TODO 
====

* Compare default ~tree234() with a version that calls destroy_tree() by using the sample_value class in include/sample-value.h whose dtort prints to cout. 

* Bug: The iterator class is not efficient when reverse iteration is done. Itse use of the stack member variable causes the stack to be repeated copied and destroyed in 

   std::reverse_iterator::operator*() const
   {
      _Iterator __tmp = current; <-- Entire stack copied copy constructor.

      return *--__tmp;

   }  <-- __tmp destroyed. tree234::iterator's destructor destroys stack! 

Using a shared_ptr<stack<int>> child_indexes doesn't work because the iterator returned by end()--which the same iterator returned by rbegin()--does not shared the underlying stack that it created when
begin()--and when rend()--are called. They are two separate objects with separate state, so we also need to allocate a separate stack when end() is called.

Fix?: tree234::reverse_iterator ctors should never set child_indexes to nullptr since it still has to iterator over the tree. Its child_indexes must point to the stack of child_indexes as 

The new version new-tree234 that  Ideally it should just hold a Node pointer. Currently, there is a bug in new-tree234.h's iterator with reverse iteration.

Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
