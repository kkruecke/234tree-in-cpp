#ifndef TREE234_H
#define	TREE234_H

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iosfwd>

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
    
    void DoDebug(std::ostream& ostr, Node234 *root);

    bool DoSearch(K key, Node234 *&location, int& index);

    template<typename Functor> void DoTraverse(Functor f, Node234 *root);

    void split(Node234 *node);  // called during insert to split 4-nodes
 
    void DestroyTree(Node234 *root); 

    // These methods are called during remove(K key
    bool remove(K key, Node234 *location) throw(std::logic_error); 

    Node234 *convertTwoNode(Node234 *node);

    Node234 *fuseSiblings(Node234 *parent, int node2_id, int sibling_id);
    
    Node234 *doRotation(Node234 *parent, int node2_id, int sibling_id);
 
  public:

   
   class Node234 {
      private: 
       friend class Tree234<K>;             
       static int MAX_KEYS;   

       Node234(K small);
       Node234(K small, K larger);
       Node234(K small, K middle, K large);

       Node234 *parent;
       int totalItems; /* If 1, two node; if 2, three node; if 3, four node. */   
       K keys[3];

       /*
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
      
       /* searchNode(K key, int& index, Node234 *&next)
        * Returns true if key is found in node. Sets index such that this->keys[index] == key
        * Returns false if key is if not found, and sets next to the next in-order child.
        */
       bool searchNode(K key, int& index, Node234 *&next);

       int insertKey(K key);
       void connectChild(int childNum, Node234 *child);
       
       /*
        * Remove key, if found, from node and shifting remaining keys to fill its gap.
        */  
       K removeKey(int index);
 
       /*
        *
        * Removes child node, shifts its children to fill the gap. Returns child pointer.
        */  
       Node234 *disconnectChild(int child_index); 
       void insertChild(int childNum, Node234 *pChild);

       /* 
        * Called during remove(K key).
        * Merges the 2-node children of a parent 2-node into the parent, making a 4-node. 
        */
       Node234 *fuseWithChildren(); 

    };  

    typedef Node234 Node;

     Tree234() { root = nullptr; } 
    ~Tree234(); 

    bool search(K key);

    template<typename Functor> void traverse(Functor f);
    
    void Debug(std::ostream& ostr);

    void insert(K key); 

    bool remove(K key);
};

template<typename K> int  Tree234<K>::Node234::MAX_KEYS = 3; 

template<typename K> inline int Tree234<K>::Node234::getChildCount() const
{
   return totalItems + 1; 
}

template<typename K> inline bool Tree234<K>::Node234::isTwoNode() const
{
   return (totalItems == 1) ? true : false;
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
/*
 * Node234 constructors. Note: While all children are initialize to nullptr, this is not really necessary. Instead your can simply set
 * children[0] = nullptr, since a Node234 is a leaf if and only if children[0] == 0/
 */
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
 * precondition: childIndex is within the range for the type of node.
 * child is not nullptr.
 */
template<typename K> inline void  Tree234<K>::Node234::connectChild(int childIndex, Node234 *child)
{
  children[childIndex] = child;
  
  if (child != nullptr) {
      
     child->parent = this;
  }
}
/*
 * precondition: childIndex is within the range for the type of node.
 * returns child pointer.
 */
template<typename K> inline typename Tree234<K>::Node234 *Tree234<K>::Node234::disconnectChild(int childIndex)
{
  Node234 *node = children[childIndex];

  // shift children (whose last 0-based index is totalItems) left to overwrite removed child i.
  for(int i = childIndex; i < totalItems; ++i) {

       children[i] = children[i + 1]; // shift remaining children to the left
  } 

  return node;
}

template<typename K> inline void Tree234<K>::Node234::insertChild(int childNum, Tree234<K>::Node234 *pChild)
{
  // shift children right in order to insert pChild
  int childCount =  totalItems + 1;  
  
  for(int i = childNum; i < childCount; ++i) { 

       children[i + 1] = children[i]; // shift remaining children to the right
  } 

  children[childNum] = pChild;

  if (!isLeaf()) {
      
   pChild->parent = this; // reset the child's parent pointer, too.
  }
  
  return;
}

/*
 * preconditions: node is not full, not a four node (full), and key is not already in node. It may or may not be a leaf node.
 * Shifts keys in node as needed so that key will be inserted in sorted position. Returns index of inserted key.
 */

template<typename K> inline int  Tree234<K>::Node234::insertKey(K key) 
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

    // key is smaller than all keys, so insert it at position 0

    keys[0] = key;  
  ++totalItems; // increase the total item count
    return 0;
}

template<typename K> inline K Tree234<K>::Node234::removeKey(int index)
{
  K key = keys[index]; 

  // shift to the left all keys to the right of index to the left
  for(int i = index; i < totalItems - 1; ++i) {

          keys[i] = keys[i + 1]; 
  } 

  totalItems--;

  return key;
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

template<typename K> inline void Tree234<K>::Debug(std::ostream& ostr)
{
   DoDebug(ostr, root);
}

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
 * In order traversal
 */
template<typename K> void Tree234<K>::DoDebug(std::ostream& ostr, Node234 *current)
{     
   if (current == nullptr) {

	return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DoDebug(ostr, current->children[0]);

            ostr << "\nTwo node   (" << current << "): key[0]: " << current->keys[0] << " parent:[" << current->getParent() << "] \n";

            DoDebug(ostr, current->children[1]);

            break;

      case 2: // three node
            DoDebug(ostr, current->children[0]);

            ostr << "\nThree node (" << current << "): key[0]: " << current->keys[0] << " parent:[" << current->getParent() << "] \n";

            DoDebug(ostr, current->children[1]);
 
            ostr << "Three node (" << current << "): key[1]: " << current->keys[1] << " parent:[" << current->getParent() << "] \n";

            DoDebug(ostr, current->children[2]);

            break;

      case 3: // four node
            DoDebug(ostr, current->children[0]);

            ostr << "\nFour node  (" << current << "): key[0]: " << current->keys[0] << " parent:[" << current->getParent() << "] \n";

            DoDebug(ostr, current->children[1]);
 
            ostr << "Four node  (" << current << "): key[1]: " << current->keys[1] << " parent:[" << current->getParent() << "] \n";

            DoDebug(ostr, current->children[2]);

            ostr << "Four node  (" << current << "): key[2]: " << current->keys[2] << " parent:[" << current->getParent() << "] \n";

            DoDebug(ostr, current->children[3]);
 
            break;
   }
}

/* 
 * Insertion based on this pseudo code:
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

                // return if key is already in tree
                return;
            } 

            // set current to next   
            current = next;  
       }
    }

    // Make sure key is not in the leaf node, which is 2- or 3-node.
    if (current->keys[0] == key || (current->totalItems == 2 && current->keys[1] == key)) {

        return;
    } 
 
    // current is now a leaf and not full (because we split all four nodes while descending).
    current->insertKey(key); 
}
/* 
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

    int insert_index = parent->insertKey(itemB);
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
 * Deletion based on pseudo code from pages 50-53 of: 
 *
 * www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *
 * We reduce deletion of an internal node's key to deletion of a leaf node's key by swapping the deleted key
 * with its in-order successor.
 */
template<typename K> bool Tree234<K>::remove(K key)
{
   if (root == nullptr) {

       return false; 

   } else if (root->isLeaf()) { 

         int index;
         Node234 *next = nullptr; 
         bool found = root->searchNode(key, index, next);

         if (found) { 

           /*
            * Remove key from root, when root is a leaf. This will also shift the in-order successor into its location.
            */
            root->removeKey(index);

            if (root->totalItems == 0) {

                delete root;
                root  = nullptr;
            }  
         }
 
         return found;

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
    Node234 *in_order_successor;
    
    // If key found in an internal node, search for in-order in_order_successor. 
    if (!found_node->isLeaf()) {
    
         // The next largest item with be the smallest item, the left most left node, of the subtree rooted at found_node->children[found_index + 1].
         in_order_successor = found_node->children[found_index + 1]; 
        
         // Traverse down the left-most branch until we find a leaf. 
         while (!in_order_successor->isLeaf()) {
        
             if (in_order_successor->isTwoNode()) {
        
                in_order_successor = convertTwoNode(in_order_successor);
             } 
        
             // Traverse the left subtree root at the smallest child
             in_order_successor = in_order_successor->children[0];
         }

    } else { // else we are at a leaf and the in_order_successor is in the same node.

         in_order_successor = found_node;
    }
    
    // We are now at the in-order successor leaf node. 

    // Remove in-order successor from leaf and overwrite deleted key with it. 
    // First, check if found_node is internal node
    if (found_node != in_order_successor) {

	    found_node->keys[found_index] = in_order_successor->removeKey(0);

    } else if (found_index + 1 <= found_node->totalItems) { 

            // The in-order in_order_successor is in same leaf node, so simply remove it, which will also overwrite its position by
            // shifting all keys to right of it one position left.
            in_order_successor->removeKey(found_index);

            /* 
             * Note: The line above is equivalent to doing:
             * found_node->keys[found_index] = in_order_successor->keys[found_index + 1];
             * found_node->totalItems--;  
             */

    } else { // found_index + 1 > found_node->totalItems

         throw std::logic_error(std::string("Bug found: There is a logic error in Tree234<K?::remove(Key k, Node234 *current"));
    }

    // Note, we did not need to disconnect a child because we are at a leaf node.
        
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
 * Case 2: If each adjacent sibling has only one item (and parent is a 3- or 4-node), we take its sole item together with an item from
 * parent and fuse them into the 2-node, making a 4-node. If the parent is also a 2-node (this only happens in the case of the root),
 * we fuse the three together into a 4-node. In either case, we shift the children as required.
 * 
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::convertTwoNode(Node234 *node)  
{                                                                         
   Node234 *convertedNode;
   Node234 *parent = node->getParent();

   int parentKeyTotal = parent->totalItems;
   int parentChildrenTotal = parentKeyTotal + 1;
   
   // First, we find the index of the 2-node such that parent->children[node2_index] == node, by comparing node's key to its parent's keys.
   int node2_index = 0;
   
   for (; node2_index < parentKeyTotal; ++node2_index) {
       /*
        * If we never break, then node->keys[0] is greater than the last key of its parent, which means
        * node == parent->children[parent->totalItems], the last child. 
        */

       if (node->keys[0] < parent->keys[node2_index] ) { 
            break;                               
       } 
   }

   // Determine if any adjacent sibling has a 3- or 4-node, giving preference to the right adjacent sibling first.
   bool has3or4NodeSibling = false;
   int sibling_index;

   int left_adjacent = node2_index - 1;
   int right_adjacent = node2_index  + 1;
    
   if (right_adjacent < parentChildrenTotal && !parent->children[right_adjacent]->isTwoNode()) {

	has3or4NodeSibling = true;
        sibling_index = right_adjacent;  

   } else if (!has3or4NodeSibling && left_adjacent >= 0 && !parent->children[left_adjacent]->isTwoNode()) {

	has3or4NodeSibling = true;
        sibling_index = left_adjacent;  

   } else if (right_adjacent < parentChildrenTotal) { // There are no 3- or 4-nodes siblings. Therefore the all siblings 
                                                      // are 2-node(s).
        sibling_index = right_adjacent; 

   } else { // sibling is to the left.

        sibling_index = left_adjacent; 
   }

   // Determine, based on whether the parent is a two node, whether to rotate or fuse. 
   // Check if its parent 2-node (or 3- or 4-node).
   bool parentIsTwoNode = parent->isTwoNode();

   if (has3or4NodeSibling == false) { // All adjacent siblings are also 2-nodes

         if (parentIsTwoNode) { // as is parent (which must be root); otherwise, it would have already been converted.

	     convertedNode = parent->fuseWithChildren();

        } else { // parent is 3- or 4-node 

             convertedNode = fuseSiblings(parent, node2_index, sibling_index);
        }

   } else { // it has a 3- or 4-node sibling.

        convertedNode = doRotation(parent, node2_index, sibling_index);
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

  totalItems = 3;

  Node234 *leftOrphan = children[0]; // so we can delete them later
  Node234 *rightOrphan = children[1];

  // make grandchildren the children.

  connectChild(0, leftOrphan->children[0]); // connectChild() will also reset parent pointer of right parameter.
  connectChild(1, leftOrphan->children[1]);
  connectChild(2, rightOrphan->children[0]); 
  connectChild(3, rightOrphan->children[1]);

  // delete children
  delete leftOrphan;
  delete rightOrphan;

  return const_cast<Node234 *>(this);  
}
/*
 * preconditions:
 * 1. sibling_id is a 3- or 4-node of parent. 
 * 2. node2_id is the node to convert from a 2-node to a 3-node
 * Returns:
 * A parent key is stolen and inserted into parent->children[node2_id], making it a 3-node. A key from the sibling replaces the stolen parent key.
 * The siblings orphaned child is adopted by the converted 2- now 3-node. 
 * The converted 2-node is returned.
 */
template<typename K> typename Tree234<K>::Node234 * Tree234<K>::doRotation(Node234 *parent, int node2_id, int sibling_id)
{
  Node234 *psibling = parent->children[sibling_id];

  Node234 *p2node = parent->children[node2_id];

  /* 
   * First get the index of the parent's key value such that either 
   *
   *   parent->children[node2_index]->keys[0]  <  parent->keys[index] <  parent->children[sibling_id]->keys[0] 
   *     
   *  or  
   *
   *    parent->children[sibling_id]->keys[0]  <  parent->keys[index] <  parent->children[node2_index]->keys[0]
   *
   */

  int parent_key_index = std::min(node2_id, sibling_id); 

  if (node2_id > sibling_id) { /* If sibling is to the left, then
          *
          * parent->children[sibling_id]->keys[0] < parent->keys[index] < parent->children[node2_index]->keys[0]
          *
          */ 

      // Add the parent's key to 2-node, making it a 3-node

      // 1. But first shift the 2-node's sole key right one position
      p2node->keys[1] = p2node->keys[0];      

      p2node->keys[0] = parent->keys[parent_key_index];  // 2. Now bring down parent key

      p2node->totalItems = 2; // 3. increase total items

      int total_sibling_keys = psibling->totalItems; 
      
      //--Node234 *pchild_of_sibling = psibling->disconnectChild(total_sibling_keys + 1); // 4. disconnect right-most child of sibling
      Node234 *pchild_of_sibling = psibling->disconnectChild(total_sibling_keys); // 4. disconnect right-most child of sibling

      K largest_sibling_key = psibling->removeKey(total_sibling_keys - 1); // remove the largest, the right-most, sibling's key.

      parent->keys[parent_key_index] = largest_sibling_key;  // 5. overwrite parent item with largest sibling key

      p2node->insertChild(0, pchild_of_sibling); // add former right-most child of sibling as its first child

  } else { // sibling is to the right: do a left rotation
  		/* sibling is to the right and therefore
   		 *
		 *   parent->children[node2_index]->keys[0]  <  parent->keys[index] <  parent->children[sibling_id]->keys[0] 
   		 */ 

      // pnode2->keys[0] doesn't change.
      p2node->keys[1] = parent->keys[parent_key_index];  // 1. insert parent key making 2-node a 3-node

      p2node->totalItems = 2; // 2. increase total items

      Node234 *pchild_of_sibling = psibling->disconnectChild(0); // disconnect first child of sibling.

      // Remove smallest key in sibling
      K smallest_sibling_key = psibling->removeKey(0);

      parent->keys[parent_key_index] = smallest_sibling_key;  // overwrite parent item with it.

      p2node->insertChild(p2node->totalItems, pchild_of_sibling); // add former first child of silbing as right-most child of our 3-node.
  }

  return p2node;
}

/*
 * Preconditions: 
 * 1. parent is a 3- or 4-node. 
 * 2. node2_id is the child index of the 2-node being converted (into a 3- or 4-node).
 * 3. sibling_id is a 2-node.
 *
 * Returns: node2_id is converted into 4-node by adding sibling's sole key together with a key "stolen" from the parent. The 
 * siblings children are adopted by the former 2- now 4-node. The parent becomes a 2-node, if it was a 3-node, or a 3-node, if it 
 * was a 4-node.
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::fuseSiblings(Node234 *parent, int node2_index, int sibling_index)
{
  Node234 *psibling;

  Node234 *p2node = parent->children[node2_index];

  // First get the index of the parent's key value to be stolen and added into the 2-node
  int parent_key_index = std::min(node2_index, sibling_index); 

  if (node2_index > sibling_index) { // sibling is to the left: 

      /* Adjust parent:
         1. Remove parent key (and shift its remaining keys and reduce its totalItems)
         2. Reset parent's children pointers after removing sibling.
       */

      K parent_key = parent->removeKey(parent_key_index); //this will do #1

      psibling = parent->disconnectChild(sibling_index); // This will do #2.

      // Now, add both the sibling's and parent's key to 2-node

      // 1. But first shift the 2-node's sole key right two positions
      p2node->keys[2] = p2node->keys[0];      

      p2node->keys[1] = parent_key;  // 2. bring down parent key

      p2node->keys[0] = psibling->keys[sibling_index]; // 3. insert adjacent sibling's sole key. 
 
      p2node->totalItems = 3; // 3. increase total items


      // Add sibling's children to the former 2-node, now 4-node...
      p2node->children[3] = p2node->children[1];  // ... but first shift its children right two positions
      p2node->children[2] = p2node->children[0];

      // Insert sibling's first two child. Note: connectChild() will also reset the parent pointer of these children to be p2node. 
      p2node->connectChild(1, psibling->children[1]); 
      p2node->connectChild(0, psibling->children[0]); 

  } else { // sibling is to the right: 

      
      /* Next adjust parent:
         1. Remove parent key (and shift its remaining keys and reduce its totalItems)
         2. Reset its children pointers 
       */

      K parent_key = parent->removeKey(parent_key_index); // this will #1

      psibling = parent->disconnectChild(sibling_index); // this does #2

      // p2node->key[0] is already in the correct position
      p2node->keys[1] = parent_key;  // 1. bring down parent key

      p2node->keys[2] = psibling->keys[sibling_index];  // 2. add sibling key. 
 
      p2node->totalItems = 3; // 3. make it a 4-node

      // Insert sibling's last two child. Note: connectChild() will also reset the parent pointer of these children to be p2node. 

      p2node->connectChild(3, psibling->children[1]);  // Add sibling's children
      p2node->connectChild(2, psibling->children[0]);  
  }

  delete psibling; // delete orphaned sibling

  return p2node;
}
#endif
