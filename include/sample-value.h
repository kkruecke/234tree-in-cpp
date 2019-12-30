#ifndef sample_value_h
#define sample_value_h

#include <vector>
#include <iostream>

class sample_value {

    std::vector<int> vec;

    static int counter = 0;

   public:
     sample_value(int size=1) : vec(1, ++counter) 
     {
     }
     ~sample_value()
     {
       std::cout << "In samle_value::~sample_value() vec[0] = " << vec[0] << std::endl;
     }
};

#endif
