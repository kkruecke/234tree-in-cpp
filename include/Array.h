template<class T, std::size_t _Num> class Array { // For 2 3 tree, Array<KeyValue, 2>. For 2 3 4 tree, Array<KeyValue, 3>

   std::size_t   size_;  
   T array[_Num]; 

  public:

    // Member types
    using    value_type                T;
    using    pointer                   value_type *;
    using    const_pointer             const value_type;
    using    reference                 value_type;
    using    const_reference           const value_type;
    using    iterator                  value_type;
    using    const_iterator            const value_type;
    using    size_type                 std::size_t;
    using    difference_type           std::ptrdiff_t;
    using    reverse_iterator          std::reverse_iterator<iterator>;
    using    const_reverse_iterator    std::reverse_iterator<const_iterator>;


  // Assignment
  operator=

  size_type size() const noexcept
  { 
     return size_; 
  } 

  // Index
  constexpr reference operator[](int i) noexcept;
  constexpr const_reference T& operator[](int i) const noexcept;
  constexpr reference at(int i) noexcept;
  constexpr const_reference T& at(int i) const noexcept;


  // Iteration
  constexpr iterator begin() noexcept;
  constexpr iterator end() noexcept;
  constexpr const_iterator begin() const noexcept;
  constexpr const_iterator end()  const noexcept;

  constexpr const_iterator cbegin() const noexcept;
  constexpr const_iterator cend()  const noexcept;

  constexpr reverse_iterator rbegin() noexcept;
  constexpr reverse_iterator rend() noexcept;
  constexpr const_reverse_iterator rbegin() const noexcept;
  constexpr const_reverse_iterator rend() const noexcept;
  constexpr const_reverse_iterator crbegin() const noexcept;
  constexpr const_reverse_iterator crend() const noexcept;

  constexpr reverse_iterator rend() noexcept;
  constexpr const_reverse_iterator rend() const noexcept;
  constexpr const_reverse_iterator crend() const noexcept;


      // TODO: Add 'constexpr' and 'const' and 'noexcept' where appropriate.
      // TODO: increase size_ as elements are added. So check index value 
      // TODO:
      // Iterators.
       constexpr iterator
       begin() noexcept
       { return iterator(&array[0]); }
 
       constexpr const_iterator
       begin() const noexcept
       { return const_iterator(&array[0]); }
 
       constexpr iterator
       end() noexcept
       { return iterator(&array[size_]); }
 
       constexpr const_iterator
       end() const noexcept
       { return const_iterator(&array[size_]); } // <--
 
       constexpr reverse_iterator 
       rbegin() noexcept
       { return reverse_iterator(end()); }
 
       constexpr const_reverse_iterator 
       rbegin() const noexcept
       { return const_reverse_iterator(end()); }
 
       constexpr reverse_iterator 
       rend() noexcept
       { return reverse_iterator(begin()); }
 
       constexpr const_reverse_iterator 
       rend() const noexcept
       { return const_reverse_iterator(begin()); }
 
       // Capacity.
       constexpr size_type 
       size() const noexcept { return size_; }
 
       constexpr bool 
       empty() const noexcept { return size() == 0; }
 
       // Element access.
       reference
       operator[](size_type i)
       { return array[i]; }
 
       const_reference
       operator[](size_type i) const
       { return array[i]; }
 
       reference
       at(size_type i)
       { return _at<_Num>(i); }
 
       const_reference
       at(size_type __n) const
       { return _at<_Num>(i); }
 
       reference 
       front()
       { return *begin(); }
 
       const_reference 
       front() const
       { return *begin(); }
 
       reference 
       back()
       { return _Num ? *(end() - 1) : *end(); }
 
       const_reference 
       back() const
       { return _Num ? *(end() - 1) : *end(); }
 
       _Tp* 
       data()
       { return &array[0]; }
 
       const _Tp* 
       data() const
       { return &array[0]; }
 
     private:
       template<std::size_t _Mm> reference _at(int n)
       {
          if (n >= _Mm) // n > size_????
             throw std::range_error("array::_at");

          return array[n];
       }

       template<std::size_t _Mm> reference _at(int n)
       {
          if (n >= _Mm) // n > size_
             throw std::range_error("array::_at");

          return array[n];
       }
 
        
 size_type size() const { return _Num; }
 
      bool 
       empty() const { return size() == 0; }
 
       // Element access.
       reference
       operator[](size_type __n)
       { return array[__n]; }
 
       const_reference
       operator[](size_type __n) const
       { return array[__n]; }
 
       reference
       at(size_type __n)
       { return _at<_Num>(__n); }
 
       const_reference
       at(size_type __n) const
       { return _at<_Num>(__n); }
 
      constexpr  reference
       front()
       { return *begin(); }
 
       constexpr const_reference
       front() const
       { return *begin(); }
 
      constexpr  reference
       back()
       { return _Num ? *(end() - 1) : *end(); }
 
       constexpr const_reference
       back() const
       { return _Num ? *(end() - 1) : *end(); }
 
       _Tp* 
       data()
       { return &array[0]; }
 
       const _Tp* 
       data() const
       { return &array[0]; }
 
};
