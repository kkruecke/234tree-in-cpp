/* 
 * File:   main.cpp
 * Author: kurt
 *
 * Created on August 13, 2014, 4:58 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "tree234.h"
#include "TreePrinter.h"
#include "DebugPrinter.h"

using namespace std;

int main(int argc, char** argv) 
{
    int v[] = { 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100 };
    
    int delete_values[] = { 40 }; //, 
    
    Tree234<int> tree;
      
    for(int i = 0; i < sizeof(v)/sizeof(int); ++i) {
        
       tree.insert(v[i]);    
    }
    
    TreePrinter printer(cout);
    
    cout << "Printing tree " << endl;
    
    tree.traverse(printer);
            
    cout << endl;
    cout << "=======Tree Debug (PostOrder) Printer  =====================" << endl;
    
    DebugPrinter debug_printer(cout);
    
    tree.debug_dump(debug_printer);
          
    cout << "============================" << endl;
    
    int remove_items[] = { 100, 40, 15, 10, 80, 60, 30, 50, 20, 10, 70, 90 };
    
    /*
     * BUGS: 
     * After removing 30, the tree seems to be wrong.
     * 
     */ 
            
    for (auto i = 0; i < sizeof(remove_items)/sizeof(int); ++i) {
        
        int item = remove_items[i];
        
        bool rc = tree.remove(item);
        
        string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");
        
        cout << "item " << item << str_remove_status;
        
        cout << "\n\n=======Tree Debug (PostOrder) Printer  =====================" << endl;
        
        tree.debug_dump(debug_printer);
    
        cout << endl;
    }
    
    cout << "Final Tree\n============\n" << endl;
    
    tree.debug_dump(debug_printer);
    
    cout << endl;
  
     
    return 0;
}

