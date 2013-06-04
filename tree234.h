#ifndef  TREE23_H
#define	TREE23_H
/*
 * Based on http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt
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
       bool isLeaf(); 

       Node234<K> *parent;
       /*  If totalItems is 1, then two node; if 2, then three node, if 3, then four node. */
 
       int totalItems;    

       K values[3];
          
       Node234<K> *children[3];
       bool find(K key, int& index);
};  

template<typename K> inline  bool Node234<K>::isLeaf()  
{ 
   !children[0] ? true : false;
   
}

template<typename K> inline Node234<K>::Node234(K small) : totalItems(1)
{ 
   values[0] = small; 
}

template<typename K> inline Node234<K>::Node234(K small, K middle) : totalItems(2)
{ 
   values[0] = small; 
   values[1] = middle; 
}
template<typename K> inline Node234<K>::Node234(K small, K middle, K large) : totalItems(3)
{ 
   values[0] = small; 
   values[1] = middle; 
   values[3] = large; 
}

template<typename K> inline bool Node234<K>::find(K key, int& index)
{ 
   for(int i =0; i < totalItems; i++) {
   
           if (values[i] == key) {
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
     Node234<K> *insert(K key, Node234<K> *location=0) throw(duplicatekey);
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
 *
 */
template<typename K> inline Node234<K> *Tree234<K>::getNextChild(Node234<K> *current, K key)
{
  int i = 0;
  
  for(; i < current->totalItems; i++) {        

     // Are we less?
     if (key < current->values[i]) {

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

                 f(current->values[0]);

                 DoTraverse(f, current->children[1]);
                 break;

        case 2: // three node
                 DoTraverse(f, current->children[0]);

                 f(current->values[0]);

                 DoTraverse(f, current->children[1]);
 
                 f(current->values[1]);

                 DoTraverse(f, current->children[2]);
                 break;

        case 3: // four node
                 DoTraverse(f, current->children[0]);

                 f(current->values[0]);

                 DoTraverse(f, current->children[1]);
 
                 f(current->values[1]);

                 DoTraverse(f, current->children[2]);

                 f(current->values[2]);

                 DoTraverse(f, current->children[3]);
 
                 break;
   }
}
#endif
