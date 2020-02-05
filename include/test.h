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

template<class  Key, class Value> void test_iterators(const tree234<Key, Value>& ctree)
{
    auto citer = ctree.begin();
    auto firstxx = citer->first;
    auto& secondxx = citer->second;
    
    Value v;
    
    auto nconst_tree = const_cast<tree234<Key, Value>&>(ctree);
    
    auto iter = nconst_tree.begin();
    
    auto firstyy = iter->first;
    auto& secondyy = iter->second;
        
    
    secondyy = v;
    
    auto &secondzz = (*iter).second;
    
    secondzz = v;
}

#endif
