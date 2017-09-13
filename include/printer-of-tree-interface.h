#ifndef tree_printer_interface_h
#define tree_printer_interface_h

#include <iosfwd>

// abstract base class 
class PrinterOfTreeInterface {

public:
    virtual void print_level_order(std::ostream& ) = 0;
};
#endif
