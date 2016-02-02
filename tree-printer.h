#ifndef tree_printer_h
#define tree_printer_h

#include "tree234.h"


// fwd declarations
template<typename T> class Tree234;

template<typename T> class Node234; 

class TreePrinter {
    
   int prior_level; 

public:
    TreePrinter() : prior_level(0) {}
    TreePrinter(const TreePrinter& np) : prior_level{np.prior_level} {}
    
    void operator()(const Tree234<int>::Node234 *current, int level);
};
#endif
