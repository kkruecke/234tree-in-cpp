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

    void convert(Node234 *node);

    void DestroyTree(Node234 *root);

    bool remove(K key, Node234 *location=0);
  public:

   
   class Node234 {
      private: 
       friend class Tree234<K>;             
       static int MAX;   
       Node234(K small);
       Node234(K small, K larger);
       Node234(K small, K middle, K large);

       Node234 *parent;
       
       int totalItems; /* If totalItems is 1, then two node; if 2, then three node, if 3, then four node. */   
       K keys[3];

       /* Note:
        * For two node, children[0] is left pointer and children[1] is right pointer.
        * For three node, children[0] is left pointer and children[1] is middle pointer and children[2] is right pointer.
        * For four node, obviously we use all four children.
        */
       Node234 *children[4];

       bool find(K key, int& index);
       int insertItem(K key);
       bool isFull();
       Node234 *getParent();
       bool isLeaf(); 
       void connectChild(int childNum, Node234 *child);

       /*
        * Returns true if found with hit_index set; if not found, next points to next child to traverse.
        */
       bool searchNode(K key, Node234 *&next);

    };  
    typedef Node234 Node;

     Tree234() { root = nullptr; } 
     ~Tree234(); 
     bool search(K key);
     template<typename Functor> void traverse(Functor f);
     void insert(K key); // throw(duplicatekey) 
     bool remove(K key);
};

template<typename K> int  Tree234<K>::Node234::MAX = 3;

/*
 * Returns: true if found with i set to index of item; false if not found, with next set to next link to descend.
 *           
 */

template<typename K> inline bool Tree234<K>::Node234::searchNode(K value, Node234 *&next)
{
 bool hit = false;

  for(auto i = 0; i < totalItems; ++i) {

     if (value < keys[i]) {
            
           next = children[i]; 
           break;

     } else if (keys[i] == value) {

         hit = true;
         
         break;

     } else if (i == totalItems - 1) { // it is greater than the last key

          // value is greater than key[i]
          next = children[totalItems]; 
     }
  } 

  return false;
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small) : totalItems(1)
{ 
   keys[0] = small; 

   for (int i = 0; i < MAX; i++) {		
       children[i] = nullptr;
    }
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle) : totalItems(2)
{ 
   keys[0] = small; 
   keys[1] = middle; 

   for (int i = 0; i < MAX; i++) {		
       children[i] = nullptr;
    }
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle, K large) : totalItems(3)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   keys[3] = large; 
    
   for (int i = 0; i < MAX; i++) {		
       children[i] = nullptr;
    }
}
/*
 * precondition: childNum is within the range for the type of node.
 * child is not 0.
 */
template<typename K> inline void  Tree234<K>::Node234::connectChild(int childNum, Node234 *child)
{
  children[childNum] = child;
  child->parent = this;
}
/*
 * preconditions: node is not full, i.e., not a four node (full), and key is not already in node. It may or may not be a leaf.
 * shifts keys in node as needed so that key will be inserted in sorted position
 */

template<typename K> inline int  Tree234<K>::Node234::insertItem(K key)
{ 
  // start on right, examine items

  for(int i = totalItems - 1; i >= 0 ; i--) {

        if (key < keys[i]) { // if key[i] is bigger

            keys[i + 1] = keys[i]; // shift it right

        } else {

            keys[i + 1] = key; // insert new item
          ++totalItems;        // increase the total item count
            return i + 1;      // return index to inserted key.
        } 
    } 

    // shifted all items, insert new item at position 0

    keys[0] = key;  
  ++totalItems; // increase the total item count
    return 0;
}

template<typename K> inline  bool Tree234<K>::Node234::isFull()  
{ 
   return totalItems == MAX;
}

template<typename K> inline  typename Tree234<K>::Node234 *Tree234<K>::Node234::getParent()  
{ 
   return parent;
}
template<typename K> inline  bool Tree234<K>::Node234::isLeaf()  
{ 
   return !children[0] ? true : false;
}

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
template<typename K>  bool Tree234<K>::DoSearch(K key, Node234 *&location, int& index)
{
  Node234 *current = root;

  if (root == nullptr) {

     return false;
  }

  while(true) {
 
      if (current->find(key, index)) {

          location = current;
          return true; 

      } else if (current->isLeaf()) {

          return false;

      } else {

          current = getNextChild(current, key);	
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
  // <--- TODO(Bug): There is no test for equality, so we could be equal!

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
            int i;
            if (current->searchNode(key, i, next) ) {

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

    Node234 *parent, *child2, *child3;

    int itemIndex;

    // remove two largest (of three total) keys...
        
    itemC = node->keys[2];
    itemB = node->keys[1]; 
    node->totalItems = 1; // ...by setting totalItems to 1. 

    // Remove two right-most children from this node. 
    child2 = node->children[2]; 
    child3 = node->children[3]; 

    Node234 *newRight = new Node234(itemC); // make new right child node from largest item

    /* set its left and right children to be the two right-most children of node */
    if (child2 && child3) { // patch: that is, if they are not zero
        
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
                     
         bool found = root->searchNode(key);
         // . . . to be continued 


   } else {
 
       return remove(key, root); 
  }
}
/*
 * The delete alogithm is depicted at: http://www.cs.mtsu.edu/~jhankins/files/3110/presentations/2-3Trees.ppt 
 * The startegy is to turn two nodes on the way down into three or four nodes. Pseudo code:
 * www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt
 * http://penguin.ewu.edu/cscd320/Topic/B-Tree/2_3_4_Operations.html
 * http://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree
 */
template<typename K> bool Tree234<K>::remove(K key, Node234 *location)
{

  return true;
/*
Deletion — Avoid Parent Corrections

At each step of the traversal to delete (either to find the value or, for interior nodes, to find the in-order successor to replace that value), if you encounter
a 2-node, amplify it to a 3-node or a 4-node:

    If an adjacent sibling is a 3-node or a 4-node, redistribute values so the the present 2-node becomes a 3-node.

    If an adjacent sibling is a 2-node, merge the two nodes:  generate a 4-node by bringing down the key value from the parent — which is know to be either a
     3-node or a 4-node, and consequently can lose a key and a child without becoming illegal.

Consequently when you get to the leaf where the deletion will be performed, the value can be deleting and leave a valid node.
 */

   if (root == nullptr) {

       return false; 
   } 

   Node234 *current = root;

   /* Descend, looking for value or, if value is an interior node, its in-order successor leaf node. Convert two nodes as they are encountered to either 3-nodes
      or 4-nodes */
   /* TODO: Finish  
   while(true) {
       
       if (current->totalItems == 1 && !current->isLeaf()) {// if two node, convert it to 3- or 4-node

            convert(current); 
      
            // resume search with parent.
            current = current->getParent(); 

       } else if (current->searchNode(found ....) {

    

           // not root
    }
    */
    // current is now a leaf and not full (because we split all four nodes while descending).
      
}
#endif
