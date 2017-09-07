#ifndef test_h_2394792374
#define test_h_2394792374

#include <iostream>
#include <utility>

template<class Key, class Value> class tree234; // Fwd ref.

template<class  Key, class Value> void test_insert(const tree234<Key, Value>& tree)
{
  std::cout << "Printing tree in level order" << std::endl;

  tree.printlevelOrder(std::cout);
   
  // Lambda for printing ints in tree234
  // auto print_keys = [&](int i) -> ostream& { std::cout << i << ' '; return std::cout; };
   
  std::cout << "\n======================" << std::endl;
    
  std::cout << "\nPrinting actual tree in order\n" << std::endl;
   
  tree.printInOrder(std::cout);
  
  std::cout << std::endl;
  
    // Test copy constructor:
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
