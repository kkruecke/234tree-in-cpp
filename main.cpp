#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "include/tree234.h"
#include "include/test.h"

using namespace std;

template<class Key, class Value> void print(const tree234<Key, Value>& tree, ostream& ostr)
{
   for(auto& pr : tree) {
       
      ostr << pr.first << ", " << flush;
   }
   
   ostr << endl;
}
/*
template<class Key, class Value> void rprint(const tree234<Key, Value>& tree, ostream& ostr)
{
   // This works
   typename tree234<Key, Value>::const_iterator start{tree,  tree234<Key, Value>::iterator_position::end};
   typename tree234<Key, Value>::const_iterator finish(tree, tree234<Key, Value>::iterator_position::beg);
 
   while( start != finish) {
 
      auto& pr = *start;
      ostr << pr.first << ", " << flush;
           
      --start;
   }
   
   ostr << endl;
}
*/

template<class Key, class Value> void rprint(const tree234<Key, Value>& tree, ostream& ostr)
{
   // This has a  bug. 
   auto end = tree.rend();
   auto iter = tree.rbegin();
   
   while( iter != end) {
 
      auto& pr = *iter;

      ostr << pr.first << ", " << flush;
      
      if (pr.first == 1 ) {
          
          int debug = 10;
          ++debug;
       }
      
       ++iter;
   }
   
   ostr << endl;
}

int main(int argc, char** argv)
{
  vector<int> keys = { 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 0, 27, 62, 87, 37, 92, 79, 23, 17, 97, 55, 51, 69, 1, 2, 33, 26, 5};

  tree234<int, int> tree = { {60, 60}, {30, 30}, {10, 10}, {20, 20}, {50, 50}, {40, 40}, {70, 70}, {80, 80}, {15, 15}, {90, 90}, {0, 0}, {27, 27}, {62, 62}, {87, 87}, {37, 37}, {92, 92}, {79, 79}, {23, 23}, {17, 17}, {97, 97}, {55, 55}, {51, 51}, {69, 69}, {1, 1}, {2, 2}, {33, 33}, {26, 26}, {15, 15}, {5, 5}};
  
  
  vector< pair<int, int> > vec_pairs[] = {   {{ 20, 20 },  { 40, 40 },  { 60, 60 },  { 70, 70 },  { 80, 80 },  { 90, 90 },  {100, 100}, {120, 120} }, {{ 20, 20 },  { 40, 40 },  { 60, 60 },  { 41, 41 },  { 42, 42 },  { 43, 43 },  {44, 44}}, {{ 20, 20 }, { 40, 40 }, { 60, 60 }, {  0,  0 }, {  1,  1 }, {  2,  2 }, {  3,  3 }} };
  
  for (auto& vec : vec_pairs) {
      
       test_insert(vec);
       cout << "\nTest Completed\n";
  }
   
   
  cout << "Printing tree in level order" << endl;
  tree.printlevelOrder(cout);
   
  // Lambda for printing ints in tree234
  // auto print_keys = [&](int i) -> ostream& { cout << i << ' '; return cout; };
   
  cout << "\n======================" << endl;
    
  cout << "\nPrinting actual tree in order\n" << endl;
   
  tree.printInOrder(cout);
  
  cout << endl;
  
    // Test copy constructor:
  tree234<int, int> tree2nd  {tree};
  
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

  
  cout << "\nPrinting the keys to be removed\n\n";
  
  copy(keys.rbegin(), keys.rend(), ostream_iterator<int>(cout, ", "));
  
  cout << flush;
  for (auto iter = keys.rbegin(); iter != keys.rend(); ++iter) {
    
    auto item = *iter;
    
    cout << "\nTree size is " << tree.size() << " before removing item " << item << endl;
    
    if (*iter == 1) {
        
          int debug = 0;
          ++debug; 
    }
    
    bool rc = tree.remove(item);
       
    string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");
    
    cout<< "\nitem " << item << str_remove_status;
    
    cout << "\nTree size is " << tree.size() << " after attempting to remove item " << item << "\n" << endl;
    cout << "\n\n=======Tree level order print =====================" << endl;
        
    tree.printlevelOrder(cout);
    cout << flush;
    cout << "\n\n=================== Normal Tree Print =======================\n" << endl;
  
    tree.printInOrder(cout);
    cout << "\n\n========== Print of tree using for loop ===================" << endl;
    print(tree, cout);
 
    cout << "\n\n========== Test of reverse_iterator class ===================" << endl;
    rprint(tree, cout); 
  
    if (rc == false) {
         
        cerr << "\nExiting upon remove error!!!" << endl;
        //--cout << "\n\n=======Tree Debug =====================" << endl;
        return 0;
    }
 
    cout << "\n\n========== Test of isBalanced() ===================" << endl;
    string str_balanced{ tree.isBalanced() ? "true" : "false"};
    cout << "\ntree.isBalanced() == " << str_balanced << endl;
  }
  cout << "\n==== Final Tree ========\n" << endl;
  //tree.levelOrderTraverse(BasicTreePrinter{});
  tree.printlevelOrder(cout);
  
  cout << endl;
  cout << flush;

  return 0;
}
