/*
    Usage:
 
    KeyDesentFinder finder(root);
    
    do { 
    
      if (finder->found())
             break; 
    
       else if (finder->eot()) {
             break;
          
    } while (finder->next());

 */
class DescentSearchIterator {

    Node234 *current;
    K& k;
    int index;
    
  public:
   DescentSearchIterator(Node234 *root, K& key) : k{key} {}

   const Node234 *current()  { return current; }

   KeyDescendFinder& next();

   bool found() { return current[index] == k; }

   // end of tree.
   bool eot() { return current->isLeaf(); } 

   int  current_index() { return index; }
};
