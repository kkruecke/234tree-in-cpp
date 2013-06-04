#ifndef  TREE23_H
#define	TREE23_H
// TODO: insertItem() is differs from java source. connectChild() is missing. 
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
       Node234(K small);
       Node234(K small, K middle);
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
/*
 * preconditions: node is not full. key is not already in node.
 * shifts keys in node as needed so that key will be inserted in sorted position
 */
template<typename K> inline int Node234<K>::insertItem(K key)
{ 
  // start on right, examine items
  for(int i = totalItems; i >=0 ; i--) {

        if(key < keys[i]) { // if it's bigger

            keys[i + 1] = keys[i]; // shift value[i] right

        } else {

            keys[i + 1] = key; // insert new item

            return i + 1; // return index to
        } 
    } // end for // shifted all items,

    keys[0] = key; // insert new item
  ++totalItems; // increase the total item count
    return 0;

  //TODO: shift pointers appropriately
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
}

template<typename K> inline Node234<K>::Node234(K small, K middle) : totalItems(2)
{ 
   keys[0] = small; 
   keys[1] = middle; 
}
template<typename K> inline Node234<K>::Node234(K small, K middle, K large) : totalItems(3)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   keys[3] = large; 
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
 * Precondition: current is initially root
 * returns true if found and sets location and index within location
 */
template<typename K>  bool Tree234<K>::DoSearch(K key, Node234<K> *&location, int& index)
{
  Node234<K> *current = root;

    while(true) {
 
        if (current->isLeaf()) {

            return false;

        } else if (current->find(key, index)) {

            location = current;
            return true; 

        } else {

	    current = getNextChild(current, key);	
        }  
    }
}
/* 
 * Precondition: assumes node is not empty, not full, not a leaf
 * Returns next descendent. 
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
   if (current->isLeaf()) {

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
/* loop until a leaf node is found, splitting four nodes as we descend */
    while(true) {

        if( current->isFull() )  {// if node full,

            split(current); // split it

            current = current->getParent(); // back up

            // search once again
            current = getNextChild(current, key);
        } 
        else if(current->isLeaf()) {

	        break; 
	} else { 
            /* node is not full, not a leaf; so go to lower level else */
            current = getNextChild(current, key);
        }
    } // end while

    current->insertItem(key); // insert new DataItem
} // end insert()
/*
 * Preconditions: node is full and must be split
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
