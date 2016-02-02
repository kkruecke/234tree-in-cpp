#ifndef tree_printer_h
#define tree_printer_h

#include <iostream>
#include <string>
#include "tree234.h"

// fwd declarations
//template<typename K> class Tree234;

//template<typename K> class Node234; 

template<class K> class TreePrinter {
   const Tree234<K>& tree;    
   int prior_level; 
   int depth;

public:
    TreePrinter(const Tree234<K>& t);
    
    TreePrinter(const TreePrinter<K>& np) : prior_level{np.prior_level}, depth{np.depth}, tree{np.tree} {}
    
    void print();
    
    void operator()(const typename Tree234<K>::Node234 *current, int level);
};


template<class K> inline TreePrinter<K>::TreePrinter(const Tree234<K>& t) : prior_level{0}, tree{t}
{
  // Determine how many levels the tree has.
  depth = tree.getDepth();
}

template<class K> inline void TreePrinter<K>::print() 
{
  auto lambda = [this](const typename Tree234<K>::Node234 *current, int level) { return operator()(current, level); }; 
 
  tree.levelOrderTraverse(lambda);    
}

template<class K> void TreePrinter<K>::operator()(const typename Tree234<K>::Node234 *current, int level)
{
    
    // Did level change?
    if (level != prior_level) {

        std::cout << "\n" << "level = " <<  level; 
        prior_level = level;
        
        // Provide some basic spacing to tree appearance.
        std::size_t num = depth - level + 1;
        
        std::string str(num, ' ');
        
        std::cout << str;
    }
    
    std::cout <<  " [ ";
    
    for(auto i = 0; i < current->getTotalItems(); ++i) {
        
        std::cout << current->getKey(i);
        
        if (i != current->getTotalItems() - 1) {
            
            std::cout << ", ";
        }
    }
    
    std::cout << " ] ";
}

#endif
