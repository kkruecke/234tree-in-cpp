TODO 
====

Design Bug
----------

Using shared_ptr<Node> improves efficiency. For example, when we copy a tree, we only have to copy a shared_ptr, but there is a drawback. For the details see:

* `C++11 Smart Pointer – Part 5: shared_ptr, Binary trees and the problem of Cyclic References <https://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/>`_
* `Implementation of Binary Search Trees ViaSmart Pointer <https://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/>`_

Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
