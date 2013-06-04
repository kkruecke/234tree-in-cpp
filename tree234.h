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
       bool isLeafNode(); 

       Node234<K> *parent,
           
       K values[3];
     // enum  indecies {leftChild = 0, leftmidChild = 1, rightmidChild = 2 , rightChild =3}; 
       Node234<K> *children[3];
       bool find(K key, Node234<K>*pnode, int& index);
};  

template<typename K> inline  bool Node234<K>::isLeafNode()  
{ 
   return  !leftChild; 
}

template<typename K> inline Node234<K>::Node234(K small) : maxIndex(0)
{ 
   values[0] = small; 
}

template<typename K> inline Node234<K>::Node234(K small, K middle) : maxIndex(1)
{ 
   values[0] = small; 
   values[1] = middle; 
}
template<typename K> inline Node234<K>::Node234(K small, K middle, K large) : maxIndex(2)
{ 
   values[0] = small; 
   values[1] = middle; 
   values[3] = large; 
}

template<typename K> inline bool Node234<K>::find(K key, int& index);
{ 
   for(int i =0; i <= maxIndex; i++) {
   
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
    Node234<K> *getNextChild(Node234<K> *current);

  public:    
     Tree234() { root = 0; } 
     bool search(K key);
     bool remove(K key, Node234<K> *location=0);
     Node234<K> *insert(K key, Node234<K> *location=0) throw(duplicatekey);
};
	

template<typename K> bool Tree234<K>::search(K key)
{
    // make sure tree has at least one element    
    if (root == 0) {
    
        location = 0;
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
  for(int i = 0; j <= maxIndex; i++) {        

     // Are we less?
     if( theValue < current->values[i]) {

           return current->children[i];  
     }
  }

  // we're greater, so return right-most child
  return current->children[i];   
}
#endif
