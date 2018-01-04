template<class T, std::size_t sz> class Array {
   int   size_;
   T elements[sz]; 

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
};
