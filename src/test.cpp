//#include "include/test.h"
#include "tree234.h"
#include <iostream>

using namespace std;

template<class  Key, class Value> void test_insert(const tree234<Key, Value>& tree)
{
  cout << "Printing tree in level order" << endl;

  tree.printlevelOrder(cout);
   
  // Lambda for printing ints in tree234
  // auto print_keys = [&](int i) -> ostream& { cout << i << ' '; return cout; };
   
  cout << "\n======================" << endl;
    
  cout << "\nPrinting actual tree in order\n" << endl;
   
  tree.printInOrder(cout);
  
  cout << endl;
  
    // Test copy constructor:
  tree234<Key, Value> tree2nd  {tree};
  
  cout << "\nPrinting copy of tree\n" << endl;
  
  tree2nd.printInOrder(cout);
  
  cout << endl << flush;

  // Here we print the print using a print_keys instead of a function object.
  // Test of traversal methods

  auto print_keys = [&](const pair<int, int>& pr) { 
                           cout << pr.first << ", "; 
        }; // lambda closure

  cout << "\nUsing traverse methods to print tree in-order:" << endl;
 
  tree.inOrderTraverse(print_keys);
}
