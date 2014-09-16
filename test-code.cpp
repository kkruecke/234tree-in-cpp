/* 
 * File:   main.cpp
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

int main(int argc, char** argv) 
{
    //int v[] = { 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 27, 92, 79,23, 17, 97, 55, 51, 69};
    vector<int> v{ 60, 30, 10, 20, 50, 40, 70, 80, 15, 90, 100, 27, 62, 87, 37, 27, 92, 79,23, 17, 97, 55, 51, 69};
    // v
    
    int delete_values[] = { 40 }; //, 
    
    Tree234<int> tree;
      
    for(int i = 0; i < v.size(); ++i) {
        
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
        
    vector< int > v_copy;
    
    copy(v.begin(), v.end(), back_inserter(v_copy));
    
    //--int remove_items[] = { 100, 40, 15, 10, 80, 60, 30, 50, 20, 10, 70, 90 };
    
    /*
     * BUGS: 
     * After removing 30, the tree seems to be wrong.
     * 
     */ 
            
    //--for (auto i = 0; i < sizeof(remove_items)/sizeof(int); ++i) {
    for (vector<int>::iterator iter = v_copy.begin(); iter != v_copy.end(); ++iter) {
        
        int item = *iter;
        
        bool rc = tree.remove(item);
        
        string str_remove_status = rc ? string(" successfully removed ") : string(" not successfully removed ");
        
        cout << "item " << item << str_remove_status;
        
        
        
       
        if (item != 23) {
            cout << "\n\n=======Tree Debug (PostOrder) Printer  =====================" << endl;
            tree.debug_dump(debug_printer);
            cout << "\n=================== Normal Tree Print =======================\n";
            tree.traverse(printer);
                       
        } else {
            cout << "\n\n=======Tree Debug (PostOrder) Printer  =====================" << endl;
            tree.debug_dump(debug_printer);
            cout << "\n=================== Normal Tree Print =======================\n";
            tree.traverse(printer);
        }  
        
        cout << endl;
    }
    
    cout << "Final Tree\n============\n" << endl;
    
    tree.debug_dump(debug_printer);
    
    cout << endl;
  
     
    return 0;
}

