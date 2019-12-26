/* 
 *
 *
 *
 *
 */
int Node::getParentLeftChildIndex(int key_index) const
{ 
  // parent's keys_values.
  int index = 0;
 
  // TODO: Isn't there a method to do this? 
  // Determine the first parent child such that node is its left child.
  for (; index < parent->getTotalItems(); ++node2_index) {
      //
      // If we never break, then node->keys_values[0] is greater than the last key of its parent, which means
      // pnode == parent->children[parent->totalItems]. It is the last child. 
      //

      //if (pnode->key(0) < parent->key(node2_index) ) { 
      if (key(key_index) < parent->key(index) ) { 
           break;                               
      } 
  }

}
