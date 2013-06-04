/* 
 * File:   main.cpp
 * Author: kurt
 *
 * Created on April 22, 2013, 6:56 PM
 */

#include <cstdlib>
#include "tree234.h"
#include "TreePrinter.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) 
{
    
    int v[] = { 10, 20, 30, 40, 50 ,60, 70 , 80, 90, 37, 36, 35, 34 };
    int size = sizeof(v)/sizeof(int);
    
    Tree234<int> tree;
        
    
    tree.search(800);
    
    TreePrinter tree_printer(cout);
    tree.traverse(tree_printer); 
    cout << endl;
       
    return 0;
}

