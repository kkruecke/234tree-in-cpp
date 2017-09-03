template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node234 *, int> tree234<Key, Value>::getLeafNodeSuccessor(const typename tree234<Key, Value>::Node234 *pnode, int index_of_key) const noexcept
{
  // 
  if (!pnode->isTwoNode() && (pnode->getTotalItems() - 1) != index_of_key) { // pnode is a 3 or 4-node and the index is not the right most.

      return std::make_pair(pnode, index_of_key + 1); 
  }

  /*
   If pnode is a 3- or 4-node, key_index is the right-most; or if pnode is a 2-node, it is by default he "right most"
   If child_index is the right most index (of the parent node), then we must ascent the tree until we encounter the first ancestor that is not a
   right-most child; otherwise, ....
   */
   if (child_index == pnode->parent->getRightMostChildIndex()) {


       while (??? != right-most) {

       }


   } else { // what do we do?



   }
   
} 

