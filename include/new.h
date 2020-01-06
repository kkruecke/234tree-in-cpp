 std::tuple<bool, typename tree234<Key, Value>::Node *, int> find_insert_node(Node *pcurrent, Key delete_key, int child_index) noexcept;
find_delete_node(Node *pnode, int child_index=0)

/*
  Input: Node * and its child index in parent
  Return: {bool: found/not found, Node *pFound, int key_index within pFound}
*/

template<class Key, class Value> std::tuple<bool, typename tree234<Key, Value>::Node *, int>   tree234<Key, Value>::find_insert_node(Node *pcurrent, Key delete_key, int child_index) noexcept
find_delete_node(Node *pnode, int child_index)
{
  if (nullptr == pcurrent)
       return {false, pcurrent, 0}

  if (pcurrent->isTwoNode()) {

       if (pcurrent == root.get() && root->children[0]->isTwoNode() &&  root->children[1]->isTwoNode()) {

            /*pcurrent =*/ makeRoot4Node();

       } else  {
             /*pcurrent =*/ convert2Node(pnode, child_index);
       }
  }

  // Search for it with loop, if found return it.
  auto i = 0; 
  
  for(;i < pcurrent->getTotalItems(); ++i) {

      if (delete_key == pcurrent->key(i)) {

          return {true, pcurrent, i}; // Found dlete_key to be deleted is at pcurrent->key(i).
      } 

      if (delete_key < pcurrent->key(i)) {

          // Recurse with left child of pcurrent. 
          return find_delete_node(pcurrent->children[i].get(), delete_key, i)
      } 
  }

  // If not found and delete_key is larger than all keys, recurse with right most child
  return find_delete_node(pcurrent->children[i].get(), delete_key, i);
}

