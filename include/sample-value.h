#ifndef sample_value_h
#define sample_value_h

#include <vector>
#include <iostream>

class sample_value {

    std::vector<int> vec;

   public:
     sample_value(int size=5) : vec(1, size) 
     {
     }
     ~sample_value()
     {
       std::cout << "In samle_value::~sample_value() " << std::endl;
       
     }
};

#endif
