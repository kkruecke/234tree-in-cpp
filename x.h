class search_iterator : public std::iterator<std::forward_iterator_tag, ???> {
  Key key;

  const Node *current;

  int index;

  bool end;

 bool find(key) // search current node. Advance if not found.
 {
   for (auto i = 0; i < current->totalItems(); ++i)     
 }

 void increment()
 {
   if (current->isLeaf()) return; // at end already

   find(key);
 }   


 search_iterator(Key k, const Node *pnode, bool) : key{k}, current{pnode}, index{0} {somehow go to end}

 public:

 search_iterator(Key k, const Node *pnode) : key{k}, current{pnode}, index{0}
 {
 }

 search_iterator& operator++()
 {
   increment(); 
   return *this;
 } 
};
