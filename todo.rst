Things TODO
===========

Latest code in in ~/4/include/ntree234.h, in which the methods called remove(Node *, key) were reworked, causes a segementation fault. 

Write down the use cases for remove, using the printed examples in the folder, and from these create the pseudo code. 

pseduo code
remove(Node *psubtree, Key key)
{
  tupe<bool, Node *, int> tuple = {false, nullptr, 0};

  Node *current = psubtree;

/*
  while (true) { 

    if (current->isTwoNode()) {

        current = convertTwoNode(current);
    }

    result_tuple = current->find(key);

    if (get<0>(result_tuple)) { // found

        break;

    } else {

     current = pnode;

  } 
*/

  for (Node *current = psubtree; get<0>(result_tuple) == false; current = get<1>(result_tuple)) {

    if (current->isTwoNode()) {

        current = convertTwoNode(current);
    }

    result_tuple = current->find(key); 
  } 


  if (get<1>(result_tuple)->isLeaf()) {

     // Remove from node
     pfound_node->removeKeyValue(key_index); 

  } else { // internal node. Find successor, converting 2-nodes as we search.

     Node *pnode = get<1>(result_tuple);

     int key_index get<2>(result_tuple);

     Node *pchildSubTree = pnode->children[key_index + 1].get();

     if (pchildSubTree->isTwoNode)) {

        convertTwoNode(pchildSubTree); 

        if (pchildSubTree->getTotalItems() - 1 < key_index || pchildSubTree->key(key_index) != key) { // If key moved... 

            return remove(pchildSubTree, key);     // ...recurse, with new subtree as starting point.
        } 

        pchildSubTree = pchildSubTree->children[0].get(); // else we converted it, and set new pchildSubTree to its left most child.
     }
     
     // find min and convert 2-nodes as we search.
     Node *pmin = convert_min(pchildSubTree);

     pnode->keys_values[key_index] = pmin->keys_values[0]; // overwrite key to be deleted with its successor.
    
     pmin->removeKeyValue(0); // Since successor is not in a 2-node, delete it from the leaf.
  }
}


descent_transform() may or may not be useful.

See the TODOES in getSucessor() and convert_min.

Key References
--------------

Design. The pseudo code for remove is here:

* `2 3 4 Deletion Pseudo Code 1 <http://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf>`_
* `2 3 4 Deletion pseudo code 2 <http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf>`_  -- starting on page 63.
* ??????
* Walls and Mirrors textbook.

To get rid of returning values in reference paramaters. Use either a pair, a struct or a tuple to return the value using RVO.

Look at the current getSucccessor() logic and some of the current getRemoveSuccessor() logic. Start with pseudocode overview and design.



