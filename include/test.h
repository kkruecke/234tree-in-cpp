#ifndef test_h_2394792374
#define test_h_2394792374

#include <iostream>
#include <vector>
#include <utility>

template<class Key, class Value> class tree234; // Fwd ref.

template<class  Key, class Value> void test_insert(std::vector<std::pair<Key, Value>>& vec_pairs)
{
  tree234<Key, Value> tree;
  
  for (auto& x : vec_pairs)   {
      
    tree.insert(x);    
    
    std::cout << "\n\nPrinting tree in after insert of " << x.first;

    tree.printlevelOrder(std::cout);
  }
}  
    // Test copy constructor:
template<class Key, class Value> void test_copy_ctor(const tree234<Key, Value>& tree)  
{
  tree234<Key, Value> tree2nd  {tree};
  
  std::cout << "\nPrinting copy of tree\n" << std::endl;
  
  tree2nd.printInOrder(std::cout);
  
  std::cout << std::endl << std::flush;

  // Here we print the print using a print_keys instead of a function object.
  // Test of traversal methods

  auto print_keys = [&](const std::pair<int, int>& pr) { 
                           std::cout << pr.first << ", "; 
        }; // lambda closure

  std::cout << "\nUsing traverse methods to print tree in-order:" << std::endl;
 
  tree.inOrderTraverse(print_keys);
}
#endif
