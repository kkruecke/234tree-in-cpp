/*
 * Returns: pair<bool, int>
 * first --  if first true is there is a 3 or 4 node sibling; otherwise, false implies all siblings are 2-nodes 
 * second -- contains the child index of the sibling to be used. 
 *
 */

std::pari<bool, int> Node::chooseSibling(int child_index)
{

   int left_adjacent = child_index - 1;
   int right_adjacent = child_index  + 1;

   bool has3or4NodeSibling = false;

   int parentChildrenTotal = parent->getChildCount();

   int sibling_index = left_adjacent; // We assume sibling is to the left unless we discover otherwise.
    
   if (right_adjacent < parentChildrenTotal && !parent->children[right_adjacent]->isTwoNode()) {

        has3or4NodeSibling = true;
        sibling_index = right_adjacent;  

   } else if (left_adjacent >= 0 && !parent->children[left_adjacent]->isTwoNode()) {

        has3or4NodeSibling = true;
        sibling_index = left_adjacent;  

   } else if (right_adjacent < parentChildrenTotal) { // There are no 3- or 4-nodes siblings. Therefore the all siblings 
                                                      // are 2-node(s).

        sibling_index = right_adjacent; 
   } 

   return {has3or4NodeSibling, sibling_index}
}
