#ifndef basic_tree_printer_h
#define basic_tree_printer_h

#include "tree-printer-interface.h"
#include <iostream>
#include <string>
#include "tree234.h"

template<class K> class BasicTreePrinter : TreePrinterInterface {

   const Tree234<K>& tree;    
   int prior_level; 
   int depth;
   void operator()(const typename Tree234<K>::Node234 *current, int level);

public:
    BasicTreePrinter(const Tree234<K>& t);
    
    BasicTreePrinter(const BasicTreePrinter<K>& np) : prior_level{np.prior_level}, depth{np.depth}, tree{np.tree} {}
    
    void print_level_order() override;
    void print_in_order() override;
    void print_pre_order() override;
    void print_post_order() override;
    
};


template<class K> inline BasicTreePrinter<K>::BasicTreePrinter(const Tree234<K>& t) : prior_level{0}, tree{t}
{
  // Determine how many levels the tree has.
  depth = tree.getDepth();
}

template<class K> inline void BasicTreePrinter<K>::print_level_order() 
{
  auto lambda = [this](const typename Tree234<K>::Node234 *current, int level) { return operator()(current, level); }; 
 
  tree.levelOrderTraverse(lambda);    
}

template<class K> inline void BasicTreePrinter<K>::print_in_order() 
{
  auto lambda = [&](K k) -> std::ostream& { std::cout << k << ' '; return std::cout; };
  
  tree.inOrderTraverse(lambda);    
}

template<class K> inline void BasicTreePrinter<K>::print_pre_order() 
{
  auto lambda = [&](K k) -> std::ostream& { std::cout << k << ' '; return std::cout; };
  
  tree.preOrderTraverse(lambda);    
}

template<class K> inline void BasicTreePrinter<K>::print_post_order() 
{
  auto lambda = [&](K k) -> std::ostream& { std::cout << k << ' '; return std::cout; };
  
  tree.postOrderTraverse(lambda);    
}

// for level order print of tree
template<class K> void BasicTreePrinter<K>::operator()(const typename Tree234<K>::Node234 *current, int level)
{
    
    // Did level change?
    if (level != prior_level) {

        std::cout << "\n" << "level = " <<  level; 
        prior_level = level;
        
        // Provide some basic spacing to tree appearance.
        std::size_t num = depth - level + 1;
        
        std::string str( num, ' ');
        
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
