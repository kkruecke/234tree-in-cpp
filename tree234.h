#ifndef  TREE23_H
#define	TREE23_H
// TODO: insertItem() is differs slightly from java source. Also, connectChild() is missing. 
/*
 * Based on http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt
 * See also: http://grail.cba.csuohio.edu/~lin/cis506/Chapt10.pdf
 */
#include <utility>
#include <iostream>
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

template<typename K> class Node234 {
   private: 
       friend class Tree234<K>;             
       static int MAX;   
       Node234(K small);
       Node234(K small, K larger);
       Node234(K small, K middle, K large);

       Node234<K> *parent;
       
       int totalItems; /* If totalItems is 1, then two node; if 2, then three node, if 3, then four node. */   
       K keys[3];
       Node234<K> *children[3];

       bool find(K key, int& index);
       int insertItem(K key);
       bool isFull();
       Node234<K> *getParent();
       bool isLeaf(); 
};  

int Node234<K>::MAX = 3;
/*
 * preconditions: node is not full, not a four node (full), and key is not already in node.
 * shifts keys in node as needed so that key will be inserted in sorted position
 */
template<typename K> inline int Node234<K>::insertItem(K key)
{ 
  // start on right, examine items

  for(int i = totalItems - 1; i >= 0 ; i--) {

/* java code had a check for 'null' evidently bc of the way Node234<K>::removeItem() works
        if (values[i] == null) {

            continue;
        } else if (key < keys[i]) { // if it's bigger  
*/
        if(key < keys[i]) { // if it's bigger

            keys[i + 1] = keys[i]; // shift keys[i] right

        } else {

            keys[i + 1] = key; // insert new item

            return i + 1; // return index to inserted key.
        } 
    } 

    // shifted all items, insert new item

    keys[0] = key;  
  ++totalItems; // increase the total item count
    return 0;

  /*
   * TODO: shift pointers appropriately?
   * A: I believe we are inserting into a leaf, so that is not needed?
   */
}

template<typename K> inline  bool Node234<K>::isFull()  
{ 
   return totalItems == 3;
}

template<typename K> inline  Node234<K> *Node234<K>::getParent()  
{ 
   return parent;
}
template<typename K> inline  bool Node234<K>::isLeaf()  
{ 
   return !children[0] ? true : false;
}

template<typename K> inline Node234<K>::Node234(K small) : totalItems(1)
{ 
   keys[0] = small; 

   // We only really need to set children[0] to indicated that a node is a leaf, but we set all the children to zero.
   for (int i = 0; i < MAX; i++) {		
       children[i] = 0;
    }
}

template<typename K> inline Node234<K>::Node234(K small, K middle) : totalItems(2)
{ 
   keys[0] = small; 
   keys[1] = middle; 

   // We only really need to set children[0] to indicated that a node is a leaf, but we set all the children to zero.
   for (int i = 0; i < MAX; i++) {		
       children[i] = 0;
    }
}
template<typename K> inline Node234<K>::Node234(K small, K middle, K large) : totalItems(3)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   keys[3] = large; 
   // We only really need to set children[0] to indicated that a node is a leaf, but we set all the children to zero.
   for (int i = 0; i < MAX; i++) {		
       children[i] = 0;
    }
}

template<typename K> inline bool Node234<K>::find(K key, int& index)
{ 
   for(int i =0; i < totalItems; i++) {
   
           if (keys[i] == key) {
                   index = i;
                   return true;
           }
   }
   return false;
}

template<typename K> class Tree234 {
          
  protected:

    Node234<K> *root; 
    
    bool DoSearch(K key, Node234<K> *&location, int& index);
    template<typename Functor> void DoTraverse(Functor f, Node234<K> *root);
    Node234<K> *getNextChild(Node234<K> *current, K key);

  public:    
     Tree234() { root = 0; } 
     bool search(K key);
     bool remove(K key, Node234<K> *location=0);
     template<typename Functor> void traverse(Functor f);
     void insert(K key); // throw(duplicatekey) 
};
	

template<typename K> bool Tree234<K>::search(K key)
{
    // make sure tree has at least one element    
    if (root == 0) {
    
       return false;
        
    } else {
        int index;  
        Node234<K> *location;
        return DoSearch(key, location, index);
    }
}   
/*
 * Precondition: current is initially root.
 * Descends tree getting next child until key found or leaf encountered.
 * If key is found, additionally returns node and index within node
 */
template<typename K>  bool Tree234<K>::DoSearch(K key, Node234<K> *&location, int& index)
{
  Node234<K> *current = root;

  if (root == 0) {

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
 * Returns next child
 */
template<typename K> inline Node234<K> *Tree234<K>::getNextChild(Node234<K> *current, K key)
{
  int i = 0;
  
  for(; i < current->totalItems; i++) {        

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

template<typename K> template<typename Functor> void Tree234<K>::DoTraverse(Functor f, Node234<K> *current)
{     
   if (current == 0) {

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
Node234<K> *current = root;

   /* Descend until a leaf node is found, splitting four nodes as they are encountered */

    while(true) {

        if( current->isFull() )  {// if four node, split it, moving a value up to parent.

            split(current); 
      
            // resume search with parent.
            current = current->getParent(); //Q: is current correct here?

            current = getNextChild(current, key);

        } else if(current->isLeaf()) {

                /* done descending. */
	        break; 
	} else { 

            /* node is internal but not full, so descend, getting next in-order child. */ 
                              
            current = getNextChild(current, key);
        }
    } 

    // current is now a leaf and not full.
    current->insertItem(key); 
} 
/*
 * Preconditions: node is full, a four node.
 *
 * Pseudo code: The four node can be either: 
 * 1. root
 * 2. have a two node parent
 * 3. have a three node parent
 * 
 * If (node is root) { 
 *   put middle value in a new parent two node.
 *   save the large value temporarily.
 *   convert node into a two node, holding the samll value
 *   allocate a new two node to hold the large value. 
 *   set the node as left child of new parent. set the newly allocated node as the right child
 *   return 
 * } 
 * parent = parent of node
 *
 * if (parent is two node) {
 *
 *
 * } else { // parent is three node
 *
 *
 *
 * }
 *
 */
template<typename K> void split(Node234<K> *node)
{
    K  temB, itemC;

    Node234<K> *parent, *child2, *child3;

    int itemIndex;
    
    itemC = node.removeItem(); // remove items from node
    
    itemB = node.removeItem(); 
    
    child2 = node.disconnectChild(2); // remove children
    
    child3 = node.disconnectChild(3); // from this node
    
    Node newRight = new Node(); // make new node

    if(node == root) { // if this is the root,

	root = new Node(); // make new root
	parent = root;     // root is our parent
	root->connectChild(0, node); // connect to parent

    } else {    // this node not the root, get parent 
	parent = node->getParent(); 
    }

    // deal with parent
    itemIndex = parent->insertItem(itemB); // item B to parent
    
    int total = parent->totalItems; // total items?
    
    for(int j=total - 1; j > itemIndex; j--)  {// move parent's connections

        Node234<K> *temp = parent->disconnectChild(j); // one child

        parent->connectChild(j + 1, temp); // to the right
    }

    // connect newRight to parent
    parent->connectChild(itemIndex + 1, newRight);

    // deal with newRight
    newRight->insertItem(itemC); // item C to newRight

    newRight->connectChild(0, child2); // connect to 0 and 1

    newRight->connectChild(1, child3); // on newRight
}
#endif
