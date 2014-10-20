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

#include <memory>
namespace std {
    
     template<typename _Tp>
    struct _MakeUniq
    { typedef unique_ptr<_Tp> __single_object; };

    
    template<typename _Tp, typename... _Args> inline typename _MakeUniq<_Tp>::__single_object
    make_unique(_Args&&... __args)
    { 
        return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); 
    }

    
}

using namespace std;

int main(int argc, char** argv)
{
   
  vector<int> v{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 27, 92, 79,23, 17, 97, 55, 51, 69};  
   
  Tree234<int> test_default;
     
  Tree234<int> tree{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 27, 92, 79,23, 17, 97, 55, 51, 69};

  TreePrinter printer(cout);
  
  cout << "Printing tree in pre order" << endl;
   
  tree.preOrderTraverse(printer);
  
  cout << "\n======================" << endl;
  
  cout << "Printing copy of tree" << endl;
   
  Tree234<int> newTree{tree};
  
  newTree.inOrderTraverse(printer);
  
  cout << "\n======================" << endl;
  
  cout << "Printing tree in order" << endl;
   
  tree.inOrderTraverse(printer);
  
  cout << endl;
    
  cout << "=======Tree Debug (PostOrder) Printer =====================" << endl;
  
  DebugPrinter debug_printer(cout);
  
  tree.debug_dump(debug_printer);
  
  cout << "\n============================" << endl;
  
  vector< int > v_copy;

  // make a copy of v, but in reverse order  
  copy(v.rbegin(), v.rend(), back_inserter(v_copy));
   
  for (auto item : v) {

    bool rc = tree.remove(item);
       
    string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");

    cout << "item " << item << str_remove_status;

    cout << "\n\n=======Tree Debug =====================" << endl;

    tree.debug_dump(debug_printer);

    cout << "\n=================== Normal Tree Print =======================\n";

    tree.inOrderTraverse(printer);
    cout << "\n-----------------------\n";

    cout << endl;
  }

  cout << "\n==== Final Tree ========\n" << endl;

  tree.debug_dump(debug_printer);

  cout << endl;

  return 0;
}
