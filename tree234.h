#ifndef TREE234_H
#define	TREE234_H
/*
 * Based on http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt
 */
#include <utility>
#include <exception>

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

    Node234 *getNextChild(Node234 *current, K key);

    void split(Node234 *node);

    void convertTwoNode(Node234 *node);

    void DestroyTree(Node234 *root);

    bool remove(K key, Node234 *location);
 
    void fixUp(Node234 *current, int hit_index); 
  public:

   
   class Node234 {
      private: 
       friend class Tree234<K>;             
       static int MAX_KEYS;   
       Node234(K small);
       Node234(K small, K larger);
       Node234(K small, K middle, K large);

       Node234 *parent;
       
       int totalItems; /* If totalItems is 1, then two node; if 2, three node, if 3, four node. */   
       K keys[3];

       /* Note:
        * For two node, children[0] is left pointer and children[1] is right pointer.
        * For three node, children[0] is left pointer and children[1] is middle pointer and children[2] is right pointer.
        * Likewise for four nodes.
        */
       Node234 *children[4];

       bool find(K key, int& index);
       int insertItem(K key);
       bool isFull();
       Node234 *getParent();
       bool isLeaf() const; 
       void connectChild(int childNum, Node234 *child);
       bool isTwoNode() const;
       bool isThreeNode() const;
       /*
        * precondition: node is a two node.
        * output: four node. 
        * pseudo code: 
        * 1. Absorbs the children's keys. 
        * 2. Makes grandchildren its children and deletes former child nodes.
        */ 
       void adoptChildren();

       /*
        * Returns true if key is found in node and set index so that this->keys[index] == key
        * Returns false if key is if not found and sets next to point to next child with which to continue the search.
        */
       bool searchNode(K key, int& index, Node234 *&next);

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

template<typename K> inline bool Tree234<K>::Node234::isTwoNode() const
{
   return (totalItems == 1) ? true : false;
}
 
template<typename K> inline bool Tree234<K>::Node234::isThreeNode() const
{
   return (totalItems == 2) ? true : false;
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

          // value is greater than key[i]
          next = children[totalItems]; 
     }
  } 

  return hit;
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small) : totalItems(1)
{ 
   keys[0] = small; 

   for (int i = 0; i < MAX_KEYS + 1; i++) {		
       children[i] = nullptr;
    }
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle) : totalItems(2)
{ 
   keys[0] = small; 
   keys[1] = middle; 

   for (int i = 0; i < MAX_KEYS + 1; i++) {		
       children[i] = nullptr;
    }
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle, K large) : totalItems(3)
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

template<typename K> inline  bool Tree234<K>::Node234::isFull()  
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

/*
 * Is appears to duplicate the functionality searchNode, which takes one more reference parameter 
 */
template<typename K> inline bool Tree234<K>::Node234::find(K key, int& index)
{ 
   for(int i = 0; i < totalItems; i++) {
   
       if (keys[i] == key) {

            index = i;
            return true;
       }
   }
   return false;
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
/*
 * Precondition: current is initially root.
 * Descends tree getting next child until key found or leaf encountered.
 * If key is found, additionally returns node and index within node
 */
/*
template<typename K>  bool Tree234<K>::DoSearch(K key, Node234 *&location, int& index)
{
  Node234 *current = root;
  Node234 *next;

  if (root == nullptr) {

     return false;
  }

  while(true) {
 
      if (current->find(key, index)) { // TODO: replace find with searchNode

          location = current;
          return true; 

      } else if (current->isLeaf()) {

          return false;

      } else {

          current = getNextChild(current, key);	// TO: After replacing find() with cha
      }  
    }
}
*/
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

          return false;

      } else {

          current = next;
      }  
    }
}
/* 
 * Precondition: assumes node is not empty, not full, not a leaf
 * Returns next child (there could be up to three children)
 */
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

template<typename K> bool Tree234<K>::remove(K key)
{
   if (root == nullptr) {

       return false; 

   } else if (root->isLeaf()) { // <-- make this part of the general case of remove(K key, Node234 *location);
         int index;
         Node234 *next = nullptr; 
         bool found = root->searchNode(key, index, next);
         // . . . to be continued 
         return true;

   } else {
 
       return remove(key, root); 
  }
}

/*
 * The startegy is to turn two nodes, on the way down, into three or four nodes. Pseudo code:
 *
 *  See 
 * 1. www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt  pages 51-52
 * 
 * 2. http://ww3.algorithmdesign.net/handouts/24Trees.pdf     slides 11-13 
 *
 * 3. http://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree  detailed pseudo code
 * 
From:  http://penguin.ewu.edu/cscd320/Topic/B-Tree/2_3_4_Operations.html

Deletion — Avoid Parent Corrections

At each step of the traversal to delete (either to find the value or, for interior nodes, to find the in-order successor to replace that value), if you encounter
a 2-node, amplify it to a 3-node or a 4-node:

    If an adjacent sibling is a 3-node or a 4-node, redistribute values so the the present 2-node becomes a 3-node.

    If an adjacent sibling is a 2-node, merge the two nodes:  generate a 4-node by bringing down the key value from the parent — which is know to be either a
     3-node or a 4-node, and consequently can lose a key and a child without becoming illegal.

Consequently when you get to the leaf where the deletion will be performed, the value can be deleting and leave a valid node.
 */
template<typename K> bool Tree234<K>::remove(K key, Node234 *location)
{
   if (root == nullptr) {

       return false; 
   } 

   Node234 *current = root;
   Node234 *next = nullptr;

   int hit_index;

   /* Descend, looking for value or, if value is an interior node, its in-order successor leaf node. Convert two nodes as
      they are encountered to either 3-nodes or 4-nodes */

   while(true) {
       
       if (current != root && current->isTwoNode()) {

            // convert 2-node into 3- or 4-node 
            convertTwoNode(current); 
      
            // resume search with parent?
            current = current->getParent(); 
           
       } else if (current->searchNode(key, hit_index, next)) { // ...search for item in current node. 

              break; // we found it.  

       } else if (current->isLeaf()) { // done searching, not found.

             return false; 
          
       } else { // ... If not found, continue to descend. 

         current = next; 
       }
    }

    // Determine if it is a two node.
    // . . .
    fixUp(current, hit_index);

   
    return true;  
}
/*
 * preconditions: node is 2-node.
 * output: node is converted into either a 3- or a 4-node.
 * pseudo code: This method is the inverse of split(). There are three cases:  
 *  1. The parent is a 2-node.
 *  2. The parent is a 3-node.
 *  3. The parent is a 4-node.
 */
template<typename K> void Tree234<K>::convertTwoNode(Node234 *node) 
{
   Node234 *parent = node->getParent();

   if (parent->isTwoNode()) { // parent is 2-node and therefore its only sibling is also a 2-node

         // merge node and its sibling into parent
         parent->adoptChildren(); 

   } else { // parent is a 3- or 4-node. 

         //  Now check if it has a sibling that is a 3- or 4-node, in which case we do a rotate; otherwise, if all its siblings are all two node, we
         //  we fuse two adjacent siblings.

         // First, we need the index i where node == parent->children[i].
           for (auto i = 0; i < parent->totalItems; ++i) {

               if (node->key[0] < parent->keys[i] ) {
                    break;
               } 
           }

           int adjacent_siblings[2];
           int sibling_count;  // total possible silbing count is the same as parent->totalItems 

           // Now, we determine the siblings to check.
           // If i is the right-most child
           if (i == parent->totalItems + 1) { 

               silbing = i - 1; // the left child is the only possible adjacent sibling to check 

           }  else if (i == 1) { // We need to check both parent->children[0] and parent->children[2].
               
           } else if (i == 2 && parent->isFourNode() ) { // We check only sibling parent->children[3] 
             
           else { // i == 0 and we only need to check parent->children[1]

           }
           // If first sibling a two node
   }
            
}
/*
 * precondition: node is a 2-node.
 * output: 4-node. 
 * pseudo code: 
 * 1. Absorbs its children's keys as its own. 
 * 2. Makes its grandchildren its children and deletes its former, now orphaned child nodes.
 */ 
template<typename K> inline void Tree234<K>::Node234::adoptChildren()
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

  return;   // TODO: Should I return node, so the code knows from where to continue? 
}
/*
 * precondition: node is a 2-node. parent is a 3-node           
 * ouput: 4-node
 * pseudo code:
 * convert the 2-node into a 4-node by inserting into to it one value from the parent 3-node and
 * the value of the sibling on its right (or its left if it is the right-most sibling)           
 * Note: I believe the silbing will be -- but not sure why -- a 2-node, so we fuse            
 *           
 *           
 */           
template<typename K> inline void Tree234<K>::Node234::adoptParentandSibling()
{
  Node234 *parent = getParent();

  Key parentKey;
  Key middle; 

  if (keys[0] > parent->keys[1]) { // Then this is right child

       parentKey = parent->keys[1];

  } else { // Then this is left or middle child

       parentKey = parent->keys[0];

       if (keys[0] < parent->keys[0]) {

       } else {

       }            
  } 

  int insert_index = insertItem(parentKey);

  // remove is from parent by shifting, if necessary, and reducing totalItems by 1
  // ...
  parent->totalItems--;
  
  // move this's connections right, start from new last index up to insert_index

}
/*
 * preconditions: current is not a 2-node. current->keys[hit_index] is the value to remove from the node.
 *
 *
 */
template<typename K> void Tree234<K>::fixUp(Node234 *current, int hit_index)
{
    // We know current is in a 3- or 4-node.

    current->totalItems--; // adjust totalItems
 
    for(; hit_index < current->totalItems; ++hit_index)  { // shift all keys[] values to the right of hit_index, left
            
         current->keys[hit_index] = current->keys[hit_index + 1];
    }
    
    if (current->isLeaf()) { // if leaf, done

        return;
    } 
    // adjust the children, too
    // ... not done
}

#endif
