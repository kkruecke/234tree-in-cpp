TODO 
====

"Bug"s
------

destroy_tree is not needed because 'root.reset()' is sufficient.

Design Bug
----------

Using shared_ptr<Node> improves efficiency. For example, when we copy a tree, we only have to copy a shared_ptr, but there is a drawback. For the details see:

* `C++11 Smart Pointer Tutorial Series: Part 1 of **shared_ptr Tutorial and Examples** <https://thispointer.com/learning-shared_ptr-part-1-usage-details/>`_
* `C++11 Smart Pointer – Part 5: shared_ptr, Binary trees and the problem of Cyclic References <https://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/>`_
* `Implementation of Binary Search Trees ViaSmart Pointer <https://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/>`_

Questions about the first article:

* What is the fundamental issue with the 'parent' pointer?

* Can the issue be solved by simply using a raw pointer instead of a using weak_ptr, or is weark_ptr necessary to ensure memory is properly managed in trees? 

.. todo:: Once I have the answer, add the reasoning to the 'binary search tree' text. Same with 2-3 trees and 2-3-4 trees. And ultimately red-black trees

* Why does weak_ptr exist, what does doe it do exactly, and when must it be used?

* What are the issues with shared_ptr in terms of its effect on not managing memory properly?

A: Problem: See comments in ~/bst/todo.rst 


Resources for Understanding in-place construction using C++17
-------------------------------------------------------------

*  Explanation of map::emplace(): https://en.cppreference.com/w/cpp/container/map/emplace 
*  **STL Cookbook Item 56** explains try_emplace()
* `Improved insertion interface for unique-key maps <https://isocpp.org/files/papers/n4279.html>`_
* `Perfect Forwarding of Parameter Groups in C++11 <http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html>`_.
