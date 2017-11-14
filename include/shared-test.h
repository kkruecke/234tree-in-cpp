#ifndef shared_test_h_999999
#define shared_test_h_999999

#include <iostream>

/*
 Object for testing trees implemented with shared_ptr's
 */

class SharedTest {

   int i;

  public:

   bool operator <(const const Test& lhs);
   bool operator==(const const Test& lhs);

   Test(int in) : i{in} {}
   Test(const Test& ) = default;

   Test(Test&& ) = default;

   Test& operator=(const Test&) = default;
   Test& operator=(Test&&) = default;
  ~Test()
   {
     std::cout << "In ~Test() with i = " << i << " and this = " << this << std::endl;
   }
 
};

#endif
