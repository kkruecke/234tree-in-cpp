#ifndef basic_tree_printer_h
#define basic_tree_printer_h

#include "tree-printer-interface.h"
#include <iostream>
#include <string>

template<class K> class Tree234; // fwd ref.

template<class K> class BasicTreePrinter : TreePrinterInterface {

   const Tree234<K>& tree;    
   int prior_level; 
   int depth;
   void operator()(std::ostream& ostr, const typename Tree234<K>::Node234 *current, int level);

public:
    BasicTreePrinter(const Tree234<K>& t);
    
    BasicTreePrinter(const BasicTreePrinter<K>& np) : prior_level{np.prior_level}, depth{np.depth}, tree{np.tree} {}
    
    void print_level_order(std::ostream& ) override;
    void print_in_order(std::ostream&) override;
    void print_pre_order(std::ostream&) override;
    void print_post_order(std::ostream&) override;
};

template<class K> inline BasicTreePrinter<K>::BasicTreePrinter(const Tree234<K>& t) : prior_level{0}, tree{t}
{
  // Determine how many levels the tree has.
  depth = tree.getDepth();
}

template<class K> inline void BasicTreePrinter<K>::print_level_order(std::ostream& ostr) 
{

 class PrintLevelOrderFunctor {
     std::ostream& ostr;
     BasicTreePrinter<K>& tree_printer;
   public:
     PrintLevelOrderFunctor(std::ostream& o, BasicTreePrinter<K>& t) : ostr{o}, tree_printer{t} {}
     PrintLevelOrderFunctor(const PrintLevelOrderFunctor& func) : ostr{func.ostr}, tree_printer{func.tree_printer} {}
   
     std::ostream& operator()(const typename Tree234<K>::Node234 *current, int level)
     {
        tree_printer.operator()(ostr, current, level);
     } 
 };

  PrintLevelOrderFunctor functor{ostr, *this};
    
  tree.levelOrderTraverse(functor);
  ostr << std::flush;
}

template<class K> inline void BasicTreePrinter<K>::print_in_order(std::ostream& ostr) 
{
  auto lambda = [&](K k) -> std::ostream& { ostr << k << ' '; return ostr; };
  
  tree.inOrderTraverse(lambda);    
  ostr << std::flush;
}

template<class K> inline void BasicTreePrinter<K>::print_pre_order(std::ostream& ostr) 
{
  auto lambda = [&](K k) -> std::ostream& { ostr << k << ' '; return ostr; };
  
  tree.preOrderTraverse(lambda);    
  ostr << std::flush;
}

template<class K> inline void BasicTreePrinter<K>::print_post_order(std::ostream& ostr) 
{
  auto lambda = [&](K k) -> std::ostream& { ostr << k << ' '; return ostr; };
  
  tree.postOrderTraverse(lambda);    
  ostr << std::flush;
}

// for level order print of tree
template<class K> void BasicTreePrinter<K>::operator()(std::ostream& ostr, const typename Tree234<K>::Node234 *current, int level)
{
    // Did level change?
    if (level != prior_level) {

        ostr << "\n\n" << "level = " <<  level; 
        prior_level = level;
        
        // Provide some basic spacing to tree appearance.
        std::size_t num = depth - level + 1;
        
        std::string str( num, ' ');
        
        ostr << str;
    }
    
    ostr <<  " [ ";
    
    for(auto i = 0; i < current->getTotalItems(); ++i) {
        
        ostr << current->getKey(i);
        
        if (i != current->getTotalItems() - 1) {
            
            ostr << ", ";
        }
    }
    
    ostr << " ] ";
}
#endif
