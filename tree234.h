#ifndef TREE234_H
#define	TREE234_H

#include <utility>
#include <stdexcept>

// fwd declarations
template<typename T> class Tree234;    
template<typename K> class Node234; 

class duplicatekey :  public std::exception {
public:
    
  virtual const char* what() const throw()
  {
    return "Attempting to insert duplicate key ";
  }
};

template<typename K> class Tree234 {
  public:
  class Node234; // forward declaration of nested class.
      
  protected:

    Node234 *root; 
    
    bool DoSearch(K key, Node234 *&location, int& index);

    template<typename Functor> void DoTraverse(Functor f, Node234 *root);

    //--Node234 *getNextChild(Node234 *current, K key);

    void split(Node234 *node);

    Node234 *convertTwoNode(Node234 *node);

    void DestroyTree(Node234 *root);

    bool remove(K key, Node234 *location) throw(std::logic_error);

    // stubs: parameters undecided now
    void leftRotation();
    void rightRotation();
 
  public:

   
   class Node234 {
      private: 
       friend class Tree234<K>;             
       static int MAX_KEYS;   

       Node234(K small);
       Node234(K small, K larger);
       Node234(K small, K middle, K large);

       Node234 *parent;
       int totalItems; /* If totalItems is 1, then two node; if 2, three node; if 3, four node. */   
       K keys[3];

       /* Note:
        * For 2-nodes, children[0] is left pointer and children[1] is right pointer.
        * For 3-nodes, children[0] is left pointer, children[1] the middle pointer, and children[2] the right pointer.
        * And so on for 4-nodes.
        */
       Node234 *children[4];

       Node234 *getParent();
       int getChildCount() const;
       bool isFull() const;
       bool isLeaf() const; 
       bool isTwoNode() const;
       bool isThreeNode() const;
       bool isFourNode() const;
      
       /*
        * Returns true if key is found in node and sets index so that this->keys[index] == key
        * Returns false if key is if not found and sets next to point to the next child to search.
        */
       bool searchNode(K key, int& index, Node234 *&next);

       int insertItem(K key);
       void connectChild(int childNum, Node234 *child);

       void removeItem(int index);
       Node234 *disconnectChild(int childNum); 

       /* merges the 2-node children of a parent 2-node into the parent, making a 4-node. */
       Node234 *fuseWithChildren(); 

    };  

    typedef Node234 Node;

     Tree234() { root = nullptr; } 
    ~Tree234(); 

    bool search(K key);

     template<typename Functor> void traverse(Functor f);

     void insert(K key); // throw(duplicatekey) 

     bool remove(K key);
};

template<typename K> int  Tree234<K>::Node234::MAX_KEYS = 3; 

template<typename K> inline bool Tree234<K>::Node234::getChildCount() const
{
   return totalItems + 1; 
}

template<typename K> inline bool Tree234<K>::Node234::isTwoNode() const
{
   return (totalItems == 1) ? true : false;
}
 
template<typename K> inline bool Tree234<K>::Node234::isThreeNode() const
{
   return (totalItems == 2) ? true : false;
}
 
template<typename K> inline bool Tree234<K>::Node234::isFourNode() const
{
   return (totalItems == 3) ? true : false;
}
 
/*
 * Returns true if key is found in node, and it set index so that this->keys[index] == key.
 * Returns false if key is if not found, and it sets next to point to next child with which to continue the search.
 */
template<typename K> inline bool Tree234<K>::Node234::searchNode(K value, int& index, Node234 *&next)
{
 bool hit = false;

  for(auto i = 0; i < totalItems; ++i) {

     if (value < keys[i]) {
            
           next = children[i]; 
           break;

     } else if (keys[i] == value) {

         hit = true;
         index = i;
         break;

     } else if (i == totalItems - 1) { // it is greater than the last key
          
          next = children[totalItems]; 
     }
  } 

  return hit;
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small) : totalItems(1), parent(nullptr)
{ 
   keys[0] = small; 

   for (int i = 0; i < MAX_KEYS + 1; i++) {		
       children[i] = nullptr;
   }

}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle) : totalItems(2), parent(nullptr)
{ 
   keys[0] = small; 
   keys[1] = middle; 

   for (int i = 0; i < MAX_KEYS + 1; i++) {		
       children[i] = nullptr;
    }
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle, K large) : totalItems(3), parent(nullptr)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   keys[3] = large; 
    
   for (int i = 0; i < MAX_KEYS + 1; i++) {		
       children[i] = nullptr;
    }
}
/*
 * precondition: childNum is within the range for the type of node.
 * child is not nullptr.
 */
template<typename K> inline void  Tree234<K>::Node234::connectChild(int childNum, Node234 *child)
{
  children[childNum] = child;
  child->parent = this;
}
/*
 * precondition: childNum is within the range for the type of node.
 * returns child pointer.
 */
template<typename K> inline Node234 *Tree234<K>::Node234::disconnectChild(int childNum)
{
  // shift children left to overwrite removed child i.
  for(int i = childNum; i < getChildCount(); ++i) {

          children[i] = children[i + 1]; // shift to left
  } 
}
/*
 * preconditions: node is not full, i.e., not a four node (full), and key is not already in node. It may or may not be a leaf node.
 * shifts keys in node as needed so that key will be inserted in sorted position
 */

template<typename K> inline int  Tree234<K>::Node234::insertItem(K key) //<-- pass index, too--maybe?
{ 
  // start on right, examine items

  for(int i = totalItems - 1; i >= 0 ; i--) {

      if (key < keys[i]) { // if key[i] is bigger

          keys[i + 1] = keys[i]; // shift it right

      } else {

          keys[i + 1] = key; // insert new item
        ++totalItems;        // increase the total item count
          return i + 1;      // return index of inserted key.
      } 
    } 

    // shifted all items, insert new item at position 0

    keys[0] = key;  
  ++totalItems; // increase the total item count
    return 0;
}

template<typename K> inline K Tree234<K>::Node234::removeItem(int index)
{
  // shift keys left to overwrite removed key index.
  for(int i = index; i < totalItems; ++i) {

          keys[i] = keys[i + 1]; // shift to left
  } 

  totalItems--;
}

template<typename K> inline  bool Tree234<K>::Node234::isFull() const 
{ 
   return totalItems == MAX_KEYS;
}

template<typename K> inline  typename Tree234<K>::Node234 *Tree234<K>::Node234::getParent()  
{ 
   return parent;
}

template<typename K> inline  bool Tree234<K>::Node234::isLeaf() const 
{ 
   return !children[0] ? true : false;
}

template<typename K> inline Tree234<K>::~Tree234()
{
   DestroyTree(root);
}

/*
 * Post order traversal, deleting nodes
 */
template<typename K> void Tree234<K>::DestroyTree(Node234 *current)
{
  if (current == nullptr) {

	return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DestroyTree(current->children[0]);

            DestroyTree(current->children[1]);

            delete current;

            break;

      case 2: // three node
            DestroyTree(current->children[0]);

            DestroyTree(current->children[1]);
 
            DestroyTree(current->children[2]);

            delete current;

            break;

      case 3: // four node
            DestroyTree(current->children[0]);

            DestroyTree(current->children[1]);
 
            DestroyTree(current->children[2]);

            DestroyTree(current->children[3]);

            delete current;
 
            break;
   }
  
}

template<typename K> bool Tree234<K>::search(K key)
{
    // make sure tree has at least one element    
    if (root == nullptr) {
    
       return false;
        
    } else {
        int index;  
        Node234 *location;
        return DoSearch(key, location, index);
    }
}   

template<typename K>  bool Tree234<K>::DoSearch(K key, Node234 *&location, int& index)
{
  Node234 *current = root;
  Node234 *next;

  if (root == nullptr) {

     return false;
  }

  while(true) {
 
      if (current->searchNode(key, index, next)) { 

          location = current;
          return true; 

      } else if (current->isLeaf()) { 

          return false; // wasn't found

      } else {

          current = next;
      }  
    }
}
/* 
 * Precondition: assumes node is not empty, not full, not a leaf
 * Returns next child (there could be up to three children)
 */
/*
template<typename K> inline  typename Tree234<K>::Node234 *Tree234<K>::getNextChild(Node234 *current, K key)
{
 int i = 0;  
  for (; i < current->totalItems; i++) {        

     // Are we less?
     if (key < current->keys[i]) {

           return current->children[i];  
     }
  }

  // we're greater, so return right-most child
  return current->children[i];   
}
*/
template<typename K> template<typename Functor> inline void Tree234<K>::traverse(Functor f)
{     
  DoTraverse(f, root);    
}
/*
 * In order traversal
 */
template<typename K> template<typename Functor> void Tree234<K>::DoTraverse(Functor f, Node234 *current)
{     
   if (current == nullptr) {

	return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DoTraverse(f, current->children[0]);

            f(current->keys[0]);

            DoTraverse(f, current->children[1]);
            break;

      case 2: // three node
            DoTraverse(f, current->children[0]);

            f(current->keys[0]);

            DoTraverse(f, current->children[1]);
 
            f(current->keys[1]);

            DoTraverse(f, current->children[2]);
            break;

      case 3: // four node
            DoTraverse(f, current->children[0]);

            f(current->keys[0]);

            DoTraverse(f, current->children[1]);
 
            f(current->keys[1]);

            DoTraverse(f, current->children[2]);

            f(current->keys[2]);

            DoTraverse(f, current->children[3]);
 
            break;
   }
}
/* 
 * Insertion based on this code:
 *
 * http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt
 */
template<typename K> void Tree234<K>::insert(K key)
{
    if (root == nullptr) {

       root =  new Node234(key); 
       return; 
    } 

   Node234 *current = root;

   /* Descend until a leaf node is found, splitting four nodes as they are encountered */

   while(true) {
       
       if(current->isFull()) {// if four node, split it, moving a value up to parent.

            split(current); 
      
            // resume search with parent.
            current = current->getParent(); 
            
       }  else if( current->isLeaf() )  {

            /* done descending. */
            break;

       } else { // internal node

            Node234 *next;
            int index;
            
            if (current->searchNode(key, index, next) ) {

                // return if already in tree
                return;
            } 

            // set current to next   
            current = next;  
       }
    }

    // Make sure it is not in the leaf node, which is 2- or 3-node.
    if (current->keys[0] == key || (current->totalItems == 2 && current->keys[1] == key)) {

        return;
    } 
 
    // current is now a leaf and not full (because we split all four nodes while descending).
    current->insertItem(key); 
}
/* split(Node234 *nod)
 * Preconditions: node is full, a four node.
 *
 * Pseudo code
 * The four node is either: 
 * 1. the root
 * 2. has a two node parent
 * 3. has a three node parent
 */ 
template<typename K> void Tree234<K>::split(Node234 *node)
{
    K  itemB, itemC;
    Node234 *parent;

    int itemIndex;

    // remove two largest (of three total) keys...
        
    itemC = node->keys[2];
    itemB = node->keys[1]; 
    node->totalItems = 1; // ...by first setting totalItems to 1. 

    // Remove its two right-most children. 
    Node234 *child2 = node->children[2]; 
    Node234 *child3 = node->children[3]; 

    Node234 *newRight = new Node234(itemC); // make new right child node from largest item

    /* set its left and right children to be the two right-most children of node */
    if (child2 && child3) { // that is, if they are not zero
        
        newRight->connectChild(0, child2); // connect to 0 and 1

        newRight->connectChild(1, child3); // on newRight
    }

    /* we will covert node into a two node whose left and right children will be the two left most children
       This occurs by default. We only need adjust totalItems  */
    node->children[2] = nullptr; 
    node->children[3] = nullptr; 

    // if this is the root,
    if(node == root) { 

        /* make new root two node using node's middle value */  
        root = new Node234(itemB); 
        parent = root;          // root is parent of node
        root->connectChild(0, node); // connect node to root as left child
        root->connectChild(1, newRight);
        return;
    }         

    parent = node->getParent(); 
    bool bParentWas2Node = parent->totalItems == 1;

    // deal with parent, moving itemB middle value to parent.

    int insert_index = parent->insertItem(itemB);
    int last_index = parent->totalItems - 1;
    
    for(int i = last_index; i > insert_index; i--)  {// move parent's connections right, start from new last index up to insert_index

        Node234 *temp = parent->children[i];  // one child
        parent->connectChild(i + 1, temp);       // to the right
    }

    parent->connectChild(insert_index + 1,  newRight);

    /* 
     * By default, we do not need to insert node. It will be at the correct position. So we do not need to do:
     *     parent->connectChild(insert_index, node); 
     */
  
    return;
}
/*
 * Deletion based on pages 50-53 of: 
 *
 * www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 * 
 */
template<typename K> bool Tree234<K>::remove(K key)
{
   if (root == nullptr) {

       return false; 

   } else if (root->isLeaf()) { // <-- make this part of the general case of remove(K key, Node234 *location);

         int index;
         Node234 *next = nullptr; 
         bool found = root->searchNode(key, index, next);
         // if found...if 4-node, make to 3-node; if 3-node make 2-node; if 2-node empty tree. 
         return true;

   } else {
 
       return remove(key, root); 
  }
}

/*
 * This pseudo code is taken from pages 50-53 of: www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *
 * Deletion is similar to 2-3 trees: We "swap" the item to be deleted with its in-order successor, which
 * is always in a leaf node. "Swap" means we overwrite the item to be deleted with its in-order successor and then
 * remove the in-order successor from the leaf node.
 *
 * There is a problem, however: if the successor is a 2-node leaf, this leaves an empty leaf node, resulting in an unbalanced tree.
 * To prevent this, as we descend the tree we turn 2-nodes (other than the root) into 3-nodes or 4-nodes. 
 *
 * Case 1: If an adjacent sibling has 2 or 3 items (and the parent is a 3- or 4-node), we "steal" an item from sibling by
 * rotating items and moving subtree. See slide 51 at www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *         
 * Case 2: If each adjacent sibling (there are at most two) has only one item (and parent is a 3- or 4-node),
 * we fuse together the two, plus an item from parent, forming a 4-node and shifting the children appropriately. See
 * slide 52 of www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 * 
 * This technique is also explained and illustrated with several examples at pages 64-66 of
 * http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf and at:
 *
 * http://www.cs.toronto.edu/~krueger/cscB63h/lectures/tut04.txt 
 * and http://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf
 *
 */
template<typename K> bool Tree234<K>::remove(K key, Node234 *current) throw(std::logic_error)
{
   Node234 *next = nullptr;
   Node234 *found_node;
   int found_index;

   /* Search, looking for key, converting 2-nodes to 3- or 4-nodes as encountered */

   while(true) {

       if (current == nullptr) {
              
            return false;

       } else if (current != root && current->isTwoNode()) {

            // convert 2-node into 3- or 4-node 
            current = convertTwoNode(current); 
      
           
       } else if (current->searchNode(key, found_index, next)) { // ...search for item in current node. 

              found_node = current;
              break; // we found it.  

       } else {
          // ... If not found, continue to descend. 
           current = next; 
       }
    }

    // using found_index and node type, get the child pointer to follow
    // Debug line below
    if (found_index + 1 > found_node->totalItems) {

         throw std::logic_error(std::string("Bug found: There is a logic error in Tree234<K?::remove(Key k, Node234 *current"));
    }

    // Search for the in-order successor 
    Node234 *successor;
    
    // If key found in an internal node, descend 
    if (!found_node->isLeaf()) {
    
         // Find the smallest item in the subtree of next largest items.
         successor = found_node->children[found_index + 1]; 
        
         // search for in-order successor, again converting two nodes as we descend
         while (successor != nullptr) {
        
             if (successor->isTwoNode()) {
        
                successor = convertTwoNode(successor);
             } 
        
             // always take smallest child
             successor = successor->children[0];
         }

    } else { // else we are at a leaf and the successor is in the same node.

         successor = found_node;
    }
    
    // We are now at leaf. 
    // overwrite node key to be deleted with in-order successor. 
    if (found_node != successor) { // If found_node is internal node

	    found_node->keys[found_index] = successor->keys[0]; 

    } else if (found_index + 1 <= found_node->totalItems) { // Debug sanity test

            // The in-order successor is in same leaf node..
            found_node->keys[found_index] = successor->keys[found_index + 1];

    } else { // found_index + 1 > found_node->totalItems

         throw std::logic_error(std::string("Bug found: There is a logic error in Tree234<K?::remove(Key k, Node234 *current"));
    }

    // TODO: Now delete item from leaf -- shifting keys[] and reseting totalItems
        
    return true;  
}
/*
 * preconditions: node is 2-node.
 * output: node is converted into either a 3- or a 4-node.
 *
 * Code follows pages 51-53 of: www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 * and pages 64-66 of http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf
 *
 * Case 1: If an adjacent sibling--there are at most two--has 2 or 3 items, "steal" an item from the sibling by
 * rotating items and shifting children. See slide 51 at www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *         
 * Case 2: If each adjacent sibling has only one item (and parent is a 3- or 4-node), we take its sole item together with an item from parent and
 * fuse them into the 2-node, making a 4-node. If the parent is also a 2-node (this only happens in the case of the root), we fuse the three together
 * into a 4-node. Shift the children as required.
 * 
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::convertTwoNode(Node234 *node)  
{                                                                         
   Node234 *convertedNode;
   Node234 *parent = node->getParent();

   int parentKeyTotal = parent->totalItems;
   int parentChildrenTotal = parentKeyTotal + 1;
   
   // First, we find index such that parent->children[index] == node, by comparing node's key to its parent's keys.
   int index = 0;
   for (; index < parentKeyTotal; ++index) {
       /*
        * If we never break, then node->keys[0] is greater than the last key of its parent, which means
        * node == parent->children[totalItems].
        */

       if (node->keys[0] < parent->keys[index] ) { 
            break;                               
       } 
   }

   // adjacent_siblings and total_siblings not declared.
   bool has3or4NodeSibling = false;
   int sibling_index;

   int left_adjacent = index - 1;
   int right_adjacent = index  + 1;

   // Determine if any adjacent sibling has a 3- or 4-node, giving preference to the right adjacent sibling first.
    
   if (right_adjacent < parentChildrenTotal && !parent->children[left_adjacent]->isTwoNode()) {

	has3or4NodeSibling = true;
        sibling_index = right_adjacent  

   } else if (!has3or4NodeSibling && left_adjacent >= 0 && !parent->children[right_adjacent]->isTwoNode()) {

	has3or4NodeSibling = true;
        sibling_index = left_adjacent;  

   } else if (right_adjacent < parentChildrenTotal) { // There were no 3- or 4-nodes siblings. Therefore they are 2-node(s).

        sibling_index = right_adjacent; 

   } else { 

        sibling_index = left_adjacent; 
   }

   // Determine, based on whether the parent is a two node, whether to rotate or fuse. 
   // Check if is parent 2-node (or 3- or 4-node).
   bool parentIsTwoNode = parent->isTwoNode();

   if (parentIsTwoNode) {

        if (has3or4NodeSibling == false) {

		convertedNode = parent->fuseWithChildren();

        } else {

        }

   } else { // parent is 3- or 4-node.
       
        if (has3or4NodeSibling == false) {

        } else {

        } 
   }
   
   return convertedNode;
}
/*
 * precondition: node is a 2-node. Its children are both 2-nodes.
 * output: 4-node. 
 * pseudo code: 
 * 1. Absorbs its children's keys as its own. 
 * 2. Makes its grandchildren its children and deletes its former, now orphaned child nodes.
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::Node234::fuseWithChildren()
{
  // move key of 2-node 
  keys[1] = keys[0];

  // absorb children's keys
  keys[0] = children[0]->keys[0];    
  keys[2] = children[1]->keys[0];       

  Node234 *leftOrphan = children[0]; // so we can delete them later
  Node234 *rightOrphan = children[1];

  // make grandchildren the children.
  for(auto i = 0; i < MAX_KEYS + 1; i+=2) {

     Node234 *child = (i == 0) ? leftOrphan : rightOrphan;

     children[i] = child->children[0];       
     children[i + 1] = child->children[1];
  }

  // delete children
  delete leftOrphan;
  delete rightOrphan;

  return const_cast<Node234 *>(this);  
}
/*
template<typename K> bool Tree234<K>::checkSiblings(Node234 *node, int& index_of_nonTwoNode)
{
   // adjacent_siblings and total_siblings not declared.
   int total_siblings;
   int adjacent_siblings[2];

   
   switch (parentKeyTotal) {

       case 1: {// 2-node
               int sibling_index =  index ^= 1; // toggle index, which is 0 or 1 

               if (parent->children[ sibling_index ]->isTwoNode()) {

               } else { // its sibling is a 3- or 4-node and its parent is a 2-node


               }
       
               break;
       }
     
       case 2: // 3-node

               if (index == 1) {

                  total_siblings = 2; 
               
                  adjacent_siblings[0] =  index - 1;
                  adjacent_siblings[1] =  index + 1;
                  
               } else {

                  adjacent_siblings[0] = 1;  

               } 
               // Examine siblings for 3- or 4-node
               //...

               for (auto i = 0; i < total_siblings; ++i) {

                    if (!parent->children[ adjacent_siblings[i] ]->isTwoNode()) {

                         break;
                    }  
               }

               if (i == total_siblings) { // all adjacent siblings are 2-nodes

               }  
               break;

       case 3: // 4-node
               if (index == 0 || index == 3) {

                  adjacent_siblings[0] = (index == 0) ? 0 : 2;

               } else {
                  
                  total_siblings = 2; 
                  adjacent_siblings[0] = index - 1;
                  adjacent_siblings[1] = index + 1;

               }
               // Examine siblings for 3- or 4-node
               //...
               break;
           
   }
}
*/
#endif
