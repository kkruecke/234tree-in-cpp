#include "tree-printer.h"
#include <iostream>

using namespace std;

void TreePrinter::operator()(const Tree234<int>::Node234 *current, int level)
{
    // Did level change?
    if (level != prior_level) {

        cout << "\n" << "level = " <<  level; 
        prior_level = level;
    }
    
    cout <<  " [ ";
    
    for(auto i = 0; i < current->getTotalItems(); ++i) {
        
        cout << current->getKey(i);
        
        if (i != current->getTotalItems() - 1) {
            
            cout << ", ";
        }
    }
    
    cout << " ] ";
}
