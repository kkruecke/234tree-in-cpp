#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "include/tree234.h"
//--#include "include/new.h"
#include "include/debug-printer.h"
#include "include/basic-tree-printer.h"
using namespace std;


int main(int argc, char** argv)
{
 
  vector<int> input{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 92, 79,23, 17, 97, 55, 51, 69, 1, 201, 2, 33, 26, 150, 5};

  Tree234<int> tree {input};
  
  BasicTreePrinter<int> tree_printer{tree};

  cout << "Printing tree in level order" << endl;

  //tree.levelOrderTraverse(BasicTreePrinter<int>(tree));
  tree_printer.print_level_order(cout);
   
  // Lambda for printing ints in Tree234
  // auto print_keys = [&](int i) -> ostream& { cout << i << ' '; return cout; };
   
  cout << "\n======================" << endl;
    
  cout << "\nPrinting actual tree in order\n" << endl;
   
  tree_printer.print_in_order(cout);
  
  cout << endl;
  
    // Test copy constructor:
  Tree234<int> tree2nd  {tree};
  
  cout << "\nPrinting copy of tree\n" << endl;
  
  BasicTreePrinter<int> tree_printer2nd{tree2nd};
  
  tree_printer2nd.print_in_order(cout);
 
  cout << endl << flush;

  // Here we print the print using a print_keys instead of a function object.
  // Test of traversal methods

  auto print_keys = [=](int x) { cout << x << ", "; }; // lambda closure

  cout << "\nUsing traverse methods to print tree in-order:" << endl;
 
  tree.inOrderTraverse(print_keys);

  cout << "\nUsing traverse methods to print tree post order:" << endl;

  tree.postOrderTraverse(print_keys);

  cout << "\nUsing traverse methods to print tree pre-order:" << endl;

  tree.preOrderTraverse(print_keys);

  for (auto iter = input.rbegin(); iter != input.rend(); ++iter) {
    
    auto item = *iter;
    
    cout << "\nTree size is " << tree.size() << " before removing item " << item << endl;

    bool rc = tree.remove(item);
       
    string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");
    
    cout<< "\nitem " << item << str_remove_status;
    
    cout << "\nTree size is " << tree.size() << " after attempting to remove item " << item << "\n" << endl;

    cout << "\n\n=======Tree level order print =====================" << endl;
        
    tree_printer.print_level_order(cout);
    
    cout << flush;
        
/*
    cout << "\n\n=======Tree Debug Print ==============================\n";

    tree.debug_dump(debug_printer);
*/
   cout << "\n\n=================== Normal Tree Print =======================\n" << endl;

   tree_printer.print_in_order(cout);

    if (str_remove_status == string{" not successfully removed "}) {
         
        cerr << "\nExiting upon remove error!!!" << endl;

        //--cout << "\n\n=======Tree Debug =====================" << endl;

        return 0;
    }
  }

  cout << "\n==== Final Tree ========\n" << endl;

  //tree.levelOrderTraverse(BasicTreePrinter{});
  tree_printer.print_level_order(cout);
  
  cout << endl;
  cout << flush;

  return 0;
}
