/*
    Usage:
 
    DescentSearchIterator finder(root, value);
    
    do { 
    
      if (finder->found())
             break; 
    
       else if (finder->eot()) {
             break;
          
    } while (finder->next());

 */

/*
 K is value type
 */
template<class K>
class DescentSearchIterator {

    Node234 *current;
    K& k;
    int index;
    void next(); 
    
  public:
   DescentSearchIterator(Node234 *root, K& key) : k{key}, current{root} {}

   const Node234 *current()  { return current; }

   KeyDescendFinder& next();
   
   bool found() { return current[index] == k; }

   // conversion operator
   bool operator() { return current[index] == k; }

   // end of tree.
   bool eot() { return current->isLeaf(); } 

   int  current_index() { return index; }
};

void DescentSearchIterator::next()
{
  for(auto i = 0; i < current->totalItems; ++i) {

     if (value < current->keys[i]) {
            
           next = current->children[i].get(); 
           return false;

     } else if (current->keys[i] == value) {

         found_index = i;
         return true;
     }
  }

  // it is greater than the last key (because it is not less than or equal to it)
  next = current->children[totalItems].get(); 

  return false;
}
