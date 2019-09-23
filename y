   auto child = pnode
   auto parent = child->parent;

   
   // Ascend the parent pointer as long as the node continues to be the right most child (of its parent). 
   for(;child == parent->getRightMostChild(); parent = parent->parent)  { 
   
       // child is still the right most child, but if it is also the root, then, there is no successor. child holds the largest keys in the tree. 
       if (parent == root.get()) {
          
           return {nullptr, 0};  // To indicate "no-successor" we return the pair: {nullptr, 0} TODO: I could return a tuple<bool, const Node *, int>
       }
   
       child = parent;
   }
   // We select the ancestor's smallest key that is larger than current_key.
   auto successor_index = 0;

   for (; successor_index < parent->getTotalItems() && current_key > parent->key(successor_index); ++successor_index);
     
   return {parent, successor_index};

