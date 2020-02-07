#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "tree234.h"
#include "test.h"
#include "sample-value.h"

using namespace std;

template<class Key, class Value> void print(const tree234<Key, Value>& tree, ostream& ostr)
{
   for(auto&& [key, value] : tree) {
      
      ostr << key << ", " << flush;
   }
   
   ostr << endl;
}
/*
 This causes the bug in new-tree234.h
 */
template<class Key, class Value> void test(const tree234<Key, Value>& tree, ostream& ostr)
{
   // This has a  bug. 
   auto rend = tree.rend();
   
   auto riter = tree.rbegin();
   
   auto i = 1;
   
   while (riter != rend) {

      auto&& [key, value] = *riter;

      ostr << key << ", " << flush;
      
      if (key == 87) {

    	  auto debug = 10;
    	  ++debug;
     }   
     cout << "\n==================\nBefore doing ++riter: " << riter.base();
     ++riter;
     cout << "\n==================\nAfter ++riter: " << riter.base();
     ++i;
   }
  
}

template<class Key, class Value> void rprint(const tree234<Key, Value>& tree, ostream& ostr)
{
   // This has a  bug. 
   auto end = tree.rend();
   
   auto iter = tree.rbegin();
   
   while(iter != end) {
 
      auto&& [key, value] = *iter;

      ostr << key << ", " << flush;
      
      if (key == 93) {
          
          int debug = 10;
          ++debug;
       }
      
       ++iter;
   }
   
   ostr << endl;
}

int main(int argc, char** argv)
{
  vector keys = { 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 0, 27, 62, 87, 37, 92, 79, 23, 17, 97, 55, 51, 69, 1, 2, 33, 26, 5};
  
  tree234<int, int> tree = { {60, 60}, {30, 30}, {10, 10}, {20, 20}, {50, 50}, {40, 40}, {70, 70}, {80, 80}, {15, 15}, {90, 90}, {0, 0}, {27, 27}, {62, 62}, {87, 87}, {37, 37}, {92, 92}, {79, 79}, {23, 23}, {17, 17}, {97, 97}, {55, 55}, {51, 51}, {69, 69}, {1, 1}, {2, 2}, {33, 33}, {26, 26}, {15, 15}, {5, 5}};

  vector< pair<int,int> > append  = { {60, 60}, {30, 30}, {10, 10}, {20, 20}, {50, 50}, {40, 40}, {70, 70}, {80, 80}, {15, 15}, {90, 90}, {0, 0}, {27, 27}, {62, 62}, {87, 87}, {37, 37}, {92, 92}, {79, 79}, {23, 23}, {17, 17}, {97, 97}, {55, 55}, {51, 51}, {69, 69}, {1, 1}, {2, 2}, {33, 33}, {26, 26}, {15, 15}, {5, 5}}; 
  
  for (auto&& [key, value] /*pr*/ : append) {

      ++key;
      ++value;
  }

  // Start sp-case
  tree234<int, int> tree1 = { {5, 5}, {40, 40}, {70, 70}, {120, 120}};

  cout << "tree1: \n" << tree1;

  tree1.remove(40);
  
  tree234<int, int> tree11{tree1};
  
  cout << "\ntree11:  " << tree11;
  
  tree11.remove(5);
  
  cout << "\ntree11 after tree11.remove(5):  " << tree11;

  tree234<int, int> tree2{tree1};

  tree2.insert(999, 999);

  tree2.insert(-999, -999);

  tree234<int, int> tree3{tree1};
  
  cout << "\ntree1 after tree1.remove(40):" << tree1;

  tree1.remove(70); //<-- BUG: We failed to speical case the root being a 2-node with 2-node children

  cout << "\ntree1 after tree1.remove(70):"  << tree1;

  // Try deleting min and max value from a tree234.

  cout << "\ntree2:" << tree2;
  tree2.remove(999);

  cout << "\ntree2 after tree2.remove(999):" << tree2;
  
  tree2.remove(-999);
  
  cout << "\ntree2 after tree2.remove(-999):" << tree2;
  
  cout << "\ntree3:" << tree3;
  tree3.remove(-999);

  cout << "\ntree3 after tree3.remove(-999):" << tree3 << "\n";
 
  cout << tree3 << flush;
  
  cout << "\nTest of new code: ===========\n";
  auto iter = tree.begin();
  auto end = tree.end();

 /*
  for(auto&& x : tree) {
      
      cout << x.first << ", " << flush;
  }
 */
 
  for(auto&& [key, value] : tree) {
      
      cout << key << ", " << flush;
  }

  cout << flush << "\n";

  tree.printlevelOrder(cout);

  test(tree, cout); 

  /*
  vector< pair<int, int> > vec_pairs[] = {   {{ 20, 20 },  { 40, 40 },  { 60, 60 },  { 70, 70 },  { 80, 80 },  { 90, 90 },  {100, 100}, {120, 120} }, {{ 20, 20 },  { 40, 40 },  { 60, 60 },  { 41, 41 },  { 42, 42 },  { 43, 43 },  {44, 44}}, {{ 20, 20 }, { 40, 40 }, { 60, 60 }, {  0,  0 }, {  1,  1 }, {  2,  2 }, {  3,  3 }} };
  
  for (auto& vec : vec_pairs) {
      
       test_insert(vec);
       cout << "\nTest Completed\n";
  }
   
   
  cout << "Printing tree in level order" << endl;
  tree.printlevelOrder(cout);
   
  // Lambda for printing ints in tree234
  // auto print_keys = [&](auto& x) -> ostream& { cout << x << ' '; return cout; };
   
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
*/
  
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

    cout << "\n====== BUG =========\n";

    test(tree, cout); 
    cout << "\n\n========== Test of reverse_iterator class ===================" << endl;

    rprint(tree, cout); 
  
    if (rc == false) {
         
        cerr << "\nExiting upon remove error!!!" << endl;
        return 0;
    }
 
    cout << "\n\n========== Test of isBalanced() ===================" << endl;

    string str_balanced{ tree.isBalanced() ? "true" : "false"};

    cout << "\ntree.isBalanced() == " << str_balanced << endl;
  }

  cout << "\n==== Final Tree ========\n" << endl;

  //tree.levelOrderTraverse(BasicTreePrinter{});

  tree.printlevelOrder(cout);
  
  {
   tree234<int, sample_value> x{ {1, sample_value()} , {10, sample_value()}, {20, sample_value()}, {30, sample_value()}, {50, sample_value()}, {-1, sample_value()}, {-10, sample_value()}, {0, sample_value()}, {34, sample_value()}, {2, sample_value()},  {99, sample_value()}, {7, sample_value()}, {4, sample_value()} };
   auto debug = 10;
   cout << "==================" << endl;
  }
  
  cout << endl;
  cout << flush;

  return 0;
}
