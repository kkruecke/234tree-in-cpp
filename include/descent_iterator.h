/* 
  Search iterator usage:

    for (auto siterator siter{root.get(), key}; !siter.done(); ++siter)
    
        if (*siter == key) break;
    }

*/
class search_iterator {

    const Node *pnode;
    int index;
    const Key key; 
    bool at_end;

    bool is_found()
    {
       return found = pnode->key(index) == key ? true : false;
    }
    
    /* 
     * If key is not at current node and index, advances to next index or descends to node and its first key.
     *
     */ 
    void increment()
    {
      if (is_found()) return;

      for(auto i = 0; i < getTotalItems(); ++i) {
    
         if (lhs_key < key(i)) {
                
             if (pnode->isLeaf()) { // We are at leaf and the key is less than the key(i). No more nodes to search.

                at_end = true;
                return;                 

             } else {

                pnode = pnode->children[i].get(); 
                index = 0;
             }
    
         } else if (key(i) == key) {
     
              index = i;           
              return;
         }
      }

      if (pnode->isLeaf()) { // We are at a leaf and the item is greater than the largest key in the leaf. No more nodes to search.

          at_end = true;

      } else {
          pnode = pnode->children[pnode->getTotalItems()];
          index = 0;  
      }
    } 
    
   public:

     search_iterator(const Node *start, const Key& key_in) : pnode{start}, index{0}, key{key_in}, found{false}
     {
        
     }  

     search_iterator& operator++() // prefix
     {
       increment();   
       return *this;
     }      

     search_iterator& operator++(int) // postfix
     {
       search_iterator tmp{*this};
  
       if (!is_found()) increment();  

       return tmp;
     }
        
     const Key& operator*()
     {
        return pnode->key(index);
     }

     bool done() const    
     {
       if (is_found()) {

          return true;

       } else if (at_end) {

          return true;

       } else {

          return false;   
       }  
     }
};
