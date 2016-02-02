#ifndef tree_printer_interface_h
#define tree_printer_interface_h

// abstract base class 
class TreePrinterInterface {

public:
    
    virtual void print_level_order() = 0;
    virtual void print_in_order() = 0;
    virtual void print_pre_order() = 0;
    virtual void print_post_order() = 0;
};
#endif
