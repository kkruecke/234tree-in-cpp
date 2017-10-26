  if (!pfound_node->isLeaf()) {// The key is in an internal node, so we now search for its in order successor, converting any 2-nodes encountered.

      // current->keys_values[0].key() will eventually hold the in-order successor, the left-most leaf node in the subtree rooted at
      // found_node->children[found_index + 1].
      current = pfound_node->children[key_index + 1].get(); 

      while (true) {

        if (current->isTwoNode()) { 
    
             current = convertTwoNode(const_cast<Node*>(current));

             

             // Check if key moved as a result of conversion?
             // Comments:
             // pfound_node is never a 2-node since remove( Key key, Node *) first converts any 2-nodes to 3- or 4-nodes before calling
             // SearchNode()--except in the case when the root is a 2-node. The root does not get immediately converted from a 2-node.
             // But this code handles that by detecting that the key has moved and recursively calling "remove(key, pfound_node)".
             // pfound_node is not deleted if pfound_node is the root (and the root is a 2-node), and no nodes get deleted when either a
             // rightRotation or leftRotation occurs. So pfound_node is safe then. Finally, pfound_node is not deleted during fuseSiblings().
             // fuseSiblings() deletes a 2-node sibling but not pfound_node itself. 
            
             if (pfound_node->getTotalItems() - 1 < key_index || pfound_node->keys_values[key_index].key() != key) { // then key moved

                 // ...simply recurse, starting with a new initial starting point of pfound_node.
                 return remove(key, pfound_node); 
             } 
        } 

        if (current->isLeaf()) { // At in order successor?

            break;  
        } 

        child_index = 0; // This must be set inside this loop, as it is used below.
        current = current->children[child_index].get(); // set current to left most child of the node, 
     }

  }


-------------------------
/*
 Looks for in order successor while converting any 2-nodes encountered to 3-nodes
 */
template<typename Key, typename Value> const Node *tree234<Key, Value>::getInternalNodeSuccessor_remove(Key key, const Node *current)
{
   while (true) {

      if (current->isTwoNode()) { 
    
             current = convertTwoNode(const_cast<Node*>(current));
      } 

      current->SearchNode(key, key_index, child_index, next)) { // ...advance down the tree. We use the side effects on next and child_index to traverse to successor. 

      if (current->isLeaf()) { // Are we done? 

         break; 
      } 

      child_index = 0; // This must be set inside this loop, as it is used below.
      current = current->children[child_index].get(); // set current to left most child of the node, 
  }
}

