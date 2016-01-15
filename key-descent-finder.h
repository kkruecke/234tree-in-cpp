class KeyDescentFinder {

    Node234 *current;
    K& k;
    int index;
    
  public:
   KeyDescentFinder(Node234 *root, K& key) : k{key} {}
   const Node234 *current()  { return current; }
   KeyDescendFinder& next();
   bool found() { return current[index] == k; }
   int  current_index() { return index; }
};
