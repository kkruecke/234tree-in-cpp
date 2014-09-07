/* 
 * File:   main.cpp
 * Author: kurt
 *
 * Created on August 13, 2014, 4:58 PM
 */

#include <cstdlib>
#include <iostream>
#include "tree234.h"
#include "TreePrinter.h"

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
    
    cout << "============================" << endl;
    
    int remove_index[] = { 10, 5, 8, 2, 7, 0, 1, 4, 3, 2, 6 };
            
    for (auto i = 0; i < sizeof(remove_index)/sizeof(int); ++i) {
        
        int item = v[ remove_index[i] ];
        
        tree.remove(item);
        
        cout << "Printing tree after removing  " << item << "\n";
        tree.traverse(printer);
    
        cout << endl;
    }
    
    
  
     
    return 0;
}

