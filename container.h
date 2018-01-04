class container : std::array<KeyValue, 3> { 

    int totalItems;

  public:
    // Same ctors are std::array

    // Ctors: default, copy, move  

  
    int getTotalItems() const noexcept
    {
        return totalItems;
    }
};
