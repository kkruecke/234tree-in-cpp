#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "include/tree234.h"

using namespace std;


int main(int argc, char** argv)
{
 
  vector<int> input{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 92, 79,23, 17, 97, 55, 51, 69, 1, 201, 2, 33, 26, 150, 5};

  tree234<int> tree {input};
  
  //--BasicTreePrinter<int> tree_printer{tree};

  cout << "Printing tree in level order" << endl;

  tree.printlevelOrder(cout);
   
  // Lambda for printing ints in tree234
  // auto print_keys = [&](int i) -> ostream& { cout << i << ' '; return cout; };
   
  cout << "\n======================" << endl;
    
  cout << "\nPrinting actual tree in order\n" << endl;
   
  tree.printInOrder(cout);
  
  cout << endl;
  
    // Test copy constructor:
  tree234<int> tree2nd  {tree};
  
  cout << "\nPrinting copy of tree\n" << endl;
  
  tree2nd.printInOrder(cout);
  
  cout << endl << flush;
  
  // Testing find
  
  for (auto& v : input) {
      
      bool rc = tree.find(v);
      
      string str = (rc ? " success." : " failure.");
      
      cout << "tree.find(" << v << ") returns: " << str << endl;
      
      rc = tree.find(-v);
      
      str = (rc ? " success." : " failure.");
      
      cout << "tree.find(" << -v << ") returns: " << str << endl;
              
  }

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
        
    tree.printlevelOrder(cout);
    
    cout << flush;

   cout << "\n\n=================== Normal Tree Print =======================\n" << endl;
  
   tree.printInOrder(cout);

    if (str_remove_status == string{" not successfully removed "}) {
         
        cerr << "\nExiting upon remove error!!!" << endl;

        //--cout << "\n\n=======Tree Debug =====================" << endl;

        return 0;
    }
  }

  cout << "\n==== Final Tree ========\n" << endl;

  //tree.levelOrderTraverse(BasicTreePrinter{});
  tree.printlevelOrder(cout);
  
  cout << endl;
  cout << flush;

  return 0;
}
