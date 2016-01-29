#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "tree234.h"
#include "debug-printer.h"

using namespace std;

int main(int argc, char** argv)
{
  vector<int> input{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 27, 92, 79,23, 17, 97, 55, 51, 69, 1, 201, 2, 33, 26};
  
  Tree234<int> tree{ input };
   
  cout << "Printing tree in pre order" << endl;

  // Lambda for printing ints in Tree234
  auto lambda = [&](int i) -> ostream& { cout << i << ' '; return cout; };
   
  //tree.preOrderTraverse(printTree);
  tree.preOrderTraverse(lambda);
  
  cout << "\n======================" << endl;
    
  cout << "Printing copy of tree" << endl;
   
  Tree234<int> newTree{tree};
  
  newTree.inOrderTraverse(lambda);
  
  cout << "\n======================" << endl;
    
  cout << "Printing tree in order, using lambda" << endl;
   
  // Here we print the print using a lambda instead of a function object.
  tree.inOrderTraverse(lambda);
  
  cout << endl;
    
  cout << "=======Tree Debug (PostOrder) Printer =====================" << endl;
  
  DebugPrinter debug_printer(cout);
  
  tree.debug_dump(debug_printer);
  
  cout << "\n============================" << endl;
  
  for (auto& item : input) {

    bool rc = tree.remove(item);
       
    string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");
    
    cout << "item " << item << str_remove_status;
    
    if (str_remove_status == string{" not successfully removed "}) {
         
        cerr << "Exiting upon remove error!!!" << endl;
        cout << "\n\n=======Tree Debug =====================" << endl;

        tree.debug_dump(debug_printer);
        return 0;
    }


    cout << "\n\n=======Tree Debug =====================" << endl;

    tree.debug_dump(debug_printer);

    cout << "\n=================== Normal Tree Print =======================\n";

    tree.inOrderTraverse(lambda);
    cout << "\n-----------------------\n";

    cout << endl;
  }

  cout << "\n==== Final Tree ========\n" << endl;

  tree.debug_dump(debug_printer);

  cout << endl;
  cout << flush;

  return 0;
}
