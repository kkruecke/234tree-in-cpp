#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "tree234.h"
#include "debug-printer.h"
#include "tree-printer.h"

using namespace std;

int main(int argc, char** argv)
{

  vector<int> input{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 27, 92, 79,23, 17, 97, 55, 51, 69, 1, 201, 2, 33, 26};
  
  Tree234<int> tree{ input };
  
  cout << "Printing tree in level order" << endl;
  
  TreePrinter<int> tree_printer{tree};

  //tree.levelOrderTraverse(TreePrinter<int>(tree));
  tree_printer.print_level_order();
  
  // Lambda for printing ints in Tree234
 // auto print_keys = [&](int i) -> ostream& { cout << i << ' '; return cout; };
   
  cout << "\n======================" << endl;
    
  cout << "\nPrinting actual tree in order, using lambda closure\n" << endl;
   
  // Here we print the print using a print_keys instead of a function object.
  //tree.inOrderTraverse(print_keys);
  tree_printer.print_in_order();
  
  cout << endl;
 
  // Here we the depth of each node's key
  /* 
  cout << "=======Tree Debug =====================" << endl;

  DebugPrinter debug_printer(cout);
  
  tree.debug_dump(debug_printer);
  
  cout << "\n============================" << endl;
  */
  
  
  DebugPrinter debug_printer(cout);

  for (auto& item : input) {

    bool rc = tree.remove(item);
       
    string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");
    
    cout<< "\n\nitem " << item << str_remove_status;
    
    cout << "\n\n=======Tree level order print =====================" << endl;
        
    tree_printer.print_level_order();
/*
    cout << "\n\n=======Tree Debug Print ==============================\n";

    tree.debug_dump(debug_printer);
*/
   cout << "\n\n=================== Normal Tree Print using lambda closure =======================\n\n";

   tree_printer.print_in_order();

    if (str_remove_status == string{" not successfully removed "}) {
         
        cerr << "Exiting upon remove error!!!" << endl;

        //--cout << "\n\n=======Tree Debug =====================" << endl;

        return 0;
    }
  }

  cout << "\n==== Final Tree ========\n" << endl;

  //tree.levelOrderTraverse(TreePrinter{});
  tree_printer.print_level_order();
  
  cout << endl;
  cout << flush;

  return 0;
}
