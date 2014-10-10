#ifndef SPOINTER_H_234234
#define SPOINTER_H_234234

#include <memory>

template<typename T> class safe_ptr {
 
   T *p;
    
 public: 
      safe_ptr(T *pin) : p{pin} {}
     ~safe_ptr() {}
      safe_ptr() : p{nullptr} { }
      safe_ptr(const safe_ptr& rhs) : p{rhs.p} {}
      
      safe_ptr& operator=(const safe_ptr& rhs) 
      { 
          p = rhs.p;
          return *this;
      }

      safe_ptr& operator=(T *rhs) 
      { 
          p = rhs;
          return *this;
      }

      T *operator->() { return p; }
      T& operator*()  { return *p; }

      // prefix
      safe_ptr operator++() 
      { 
          ++p;
          return *this; 
      }

      // postfix
      safe_ptr operator++(int unused) 
      { 
         safe_ptr ret(*this); 
         p++;
         return ret; 
      }
      // prefix
      safe_ptr operator--() 
      { 
          --p;
          return *this; 
      }

      // postfix
      safe_ptr operator--(int unused) 
      { 
         safe_ptr ret(*this); 
         p--;
         return ret; 
      }

      safe_ptr operator+(int i) 
      { 
          return safe_ptr(p + i); 
      }
      
      safe_ptr operator-(int i) 
      { 
          return safe_ptr(p - i);
      }
};
#endif
