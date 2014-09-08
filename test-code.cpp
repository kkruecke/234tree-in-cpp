/* 
 * File:   main.cpp
 * Author: kurt
 *
 * Created on April 22, 2013, 6:56 PM
 */

#include <cstdlib>
#include "tree234.h"
#include <iostream>
#include <vector>
using namespace std;

/* Use this code if you get compile error about lambda

 */

int main(int argc, char** argv) 
{
    vector<int> v { 10, 20, 30, 40, 50 ,60, 70 , 80, 90, 37, 36, 35, 34 };

    Tree234<int> tree;

    for (auto iter = v.begin(); iter != v.end(); ++iter)     {
        
        tree.insert(*iter);
    }
        
    tree.search(80);

    /* Using a lambda below is equivalent to doing 

        void print_int(int x)  { cout << x << ' '; } 
        tree.traverse(print_int); 
    */

    tree.traverse([](int x){ cout << x << ' '; }); 
    cout << endl;
       
    return 0;
}

