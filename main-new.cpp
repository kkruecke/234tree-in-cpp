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
 
  tree234<int, int> tree =  {{ 60, 60}, { 30, 30}, { 10, 10}, { 20, 20}, { 50, 50}, { 40, 40}, { 70, 70}, { 80, 80}, { 15, 15}, { 90, 90}, { 100, 100}, { 27, 27}, { 62, 62}, { 87, 87}, { 37, 37}, \
                             { 92, 92}, { 79, 79},{ 23, 23}, { 17, 17}, { 97, 97}, { 55, 55}, { 51, 51}, { 69, 69}, { 1, 1}, { 201, 201}, { 2, 2}, { 33, 33}, { 26, 26}, { 150, 150}, {5, 5} };


  cout << "Printing tree in level order" << endl;

  tree.printlevelOrder(cout);
   
  // Lambda for printing ints in tree234
  // auto print_keys = [&](int i) -> ostream& { cout << i << ' '; return cout; };
   
  cout << "\n======================" << endl;
    
  cout << "\nPrinting actual tree in order\n" << endl;
   
  tree.printInOrder(cout);
  
  cout << endl;
  
    // Test copy constructor:
  tree234<int, int> tree2nd{tree};
  
  cout << "\nPrinting copy of tree\n" << endl;
  
  // Here we print the print using a print_keys instead of a function object.
  // Test of traversal methods

  // Testing find
  vector<int> keys;

  auto keys_inserter = back_inserter(keys);

  auto lambda = [&] (const pair<int, int>& pr) { keys_inserter = pr.first; };
  
  tree.inOrderTraverse(lambda);
  /* 
  for (auto& v : keys) {
      
      bool rc = tree.find(v);
      
      string str = (rc ? " success." : " failure.");
      
      cout << "tree.find(" << v << ") returns: " << str << endl;
      
      rc = tree.find(-v);
      
      str = (rc ? " success." : " failure.");
      
      cout << "tree.find(" << -v << ") returns: " << str << endl;
              
  }
*/
  // Here we print the print using a print_keys instead of a function object.
  // Test of traversal methods

  auto print_keys = [&](const pair<int, int> pr) { cout << pr.first << ", "; }; // lambda closure

  cout << "\nUsing traverse methods to print tree in-order:" << endl;
 
  tree.inOrderTraverse(print_keys);

  cout << "\nUsing traverse methods to print tree post order:" << endl;

  tree.postOrderTraverse(print_keys);

  cout << "\nUsing traverse methods to print tree pre-order:" << endl;

  tree.preOrderTraverse(print_keys);
  
  for (auto iter = keys.rbegin(); iter != keys.rend(); ++iter) {
    
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
