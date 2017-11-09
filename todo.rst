TODOES
======

Supply Recursive Destructor for Node
------------------------------------

This code is in ~/NetBeansProjects/test/main.cpp

.. code-block:: cpp
 
    template<typename Key, typename Value> inline constexpr bool Node::~Node() noexcept
    {
      FreeChildren();
    }
    
    template<typename Key, typename Value> void Node::FreeChildren()
    {
      for(auto i = 0; i < getChildCount(); ++i) {
    
          FreeChildren(children[i]);
      }
    
      for(auto i = 0; i < getChildCount(); ++i) {
    
         childern[i].reset();
      } 
    }
       
Port to shared_ptr
------------------

Finish porting shared-tree234.h from unique\_ptr to shared\_ptr, review code in light of articles below, test nad debug. Understand implications of changes from unique\_ptr to shared\_ptr both pros and cons.

`MSDN Article on Shared Pointers <https://msdn.microsoft.com/en-us/library/hh279674.aspx>`_

See these links on shared_ptr<>:

* `Functional Data Structures in C++: Trees <https://bartoszmilewski.com/2013/11/25/functional-data-structures-in-c-trees/>`_ is a guide to shared_ptr implementation.
* `C++11 Smart Pointer – Part 5: shared_ptr, Binary trees and the problem of Cyclic References <http://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/>`_.
* `International Journal of Advanced Computer Science and Applications, Implementation of Binary Search Trees Via Smart Pointers <http://thesai.org/Downloads/Volume6No3/Paper_9-Implementation_of_Binary_Search_Trees_Via_Smart_Pointers.pdf>`_.
