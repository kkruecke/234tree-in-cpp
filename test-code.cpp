/*
* File: main.cpp
* Author: kurt
*
* Created on August 13, 2014, 4:58 PM
*/
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "tree234.h"
#include "TreePrinter.h"
#include "DebugPrinter.h"

using namespace std;
template<typename T> class Tree;

template<typename T> class TreeInserter {
    
    Tree234<T>& tree;
    
public:
    
    TreeInserter(Tree234<T> &t) : tree(t) {}
    void operator()(int key) { tree.insert(key); }
};
/*
class GenSequence {
  int i;
 public:
   GenSequence(int start) : i(start) {}
   GenSequence(const GenSequence& g) : i(g.i) {}
   int operator()() { return i--; }
};
*/
int main(int argc, char** argv)
{
  vector<int> v{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 27, 92, 79,23, 17, 97, 55, 51, 69};

  Tree234<int> tree;
  
  TreeInserter<int> tree_inserter(tree);
  
  for_each(v.begin(), v.end(),  tree_inserter);
  
  TreePrinter printer(cout);
   
  cout << "Printing tree " << endl;
   
  tree.traverse(printer);
  
  cout << endl;
    
  cout << "=======Tree Debug (PostOrder) Printer =====================" << endl;
  
  DebugPrinter debug_printer(cout);
  
  tree.debug_dump(debug_printer);
  
  cout << "\n============================" << endl;
  
  vector< int > v_copy;
  
  copy(v.rbegin(), v.rend(), back_inserter(v_copy));
  
   
  for (vector<int>::reverse_iterator iter = v_copy.rbegin(); iter != v_copy.rend(); ++iter) {

    int item = *iter;
    
    if (item == 50) {
        cout << "50 FOUND\n"  << endl;
        //return 0;
    }

    bool rc = tree.remove(item);
       
    string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");

    cout << "item " << item << str_remove_status;

    cout << "\n\n=======Tree Debug =====================" << endl;

    tree.debug_dump(debug_printer);

    cout << "\n=================== Normal Tree Print =======================\n";

    tree.traverse(printer);
    cout << "\n-----------------------\n";

    cout << endl;
  }

  cout << "\n==== Final Tree ========\n" << endl;

  tree.debug_dump(debug_printer);

  cout << endl;

  return 0;
}
