/* 
  Searches for removal node. Converts 2-nodes to 3- or 4-nodes as it searches. 
*/
class remove_descent_iterator {

    tree234<Ket, Value>& tree;

    const Node *pnode;

    int index;

    const Key& key; 

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

     search_iterator(tree234const Node *start, const Key& key_in) : pnode{start}, index{0}, key{key_in}, found{false}
     {
        
     }  

     search_iterator& operator++() // prefix
     {
       increment();   
       return *this;
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

// TO: Make a new method with helper routines that does what search_iterator does
remove_convert_find(const Key& key)
{
  // Uses search_titerator but add convertToTwoNode.
  search_iterator siter{*this, key};
  while (true) {

     if 
    
  } 
  
}
