#ifndef TREE234_H
#define	TREE234_H

#include <utility>
#include <algorithm>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <array>
#include <iosfwd>

// fwd declarations
template<typename T> class Tree234;    
template<typename K> class Node234; 
class DebugPrinter; 

template<typename K> class Tree234 {
      
  protected:
   /*
    * TODO: The default copy constructor won't work because....I believe...because of the default unique_ptr<> default copy ctor--which does what?
    */   
   class Node234 {
       
      private: 
       friend class Tree234<K>;             
       friend class DebugPrinter;
       static int MAX_KEYS;   

       Node234(K small);
       Node234(K small, K larger);
       Node234(K small, K middle, K large);
       Node234& operator=(const Node234& rhs);

       std::unique_ptr<Node234> &parent;

       int totalItems; /* If 1, two node; if 2, three node; if 3, four node. */   
  //-- K keys[3];

       std::array<K, 3> keys;

       /*
        * For 2-nodes, children[0] is left pointer and children[1] is right pointer.
        * For 3-nodes, children[0] is left pointer, children[1] the middle pointer, and children[2] the right pointer.
        * And so on for 4-nodes.
        */
//--   std::unique_ptr<Node234> children[4];

       std::array< std::unique_ptr<Node234>, 4 > children;

       std::unique_ptr<Node234> &getParent(); 

       /* 
        * Returns true if key is found in node and set index: this->keys[index] == key
        * Returns false if key is if not found; set next to the next in-order child.
        */
       bool searchNode(K key, int& index, Node234 *&next);

       int insertKey(K key);
       
       void connectChild(int childNum, std::unique_ptr<Node234> child);
       
       /*
        * Removes child node andshifts its children to fill the gap. Returns child pointer.
        */  
       std::unique_ptr<Node234> disconnectChild(int child_index); 

       void insertChild(int childNum, std::unique_ptr<Node234> &pChild);

       /* 
        * Called during remove(K key).
        * Merges the 2-node children of a parent 2-node into the parent, making a 4-node. 
        */
       
     public:
         
       const std::unique_ptr<Node234> &getParent() const;

       int getTotalItems() const;
       int getChildCount() const;
       bool findKey(K key, int& index) const;
       bool isFull() const;
       bool isLeaf() const; 
       bool isTwoNode() const;
       void nullAllChildren();
    };  

    friend class DebugPrinter;
  
    std::unique_ptr<Node234>  root; 
    
    bool DoSearch(K key, std::unique_ptr<Node234> &location, int& index);

    void split(std::unique_ptr<Node234> &node);  // called during insert to split 4-nodes
 
    void DestroyTree(std::unique_ptr<Node234> &root); 

  public:

     Tree234() : root{nullptr} { } 

     Tree234(const Tree234& lhs); 

     Tree234(std::initializer_list<K> list); 

    ~Tree234(); 

    bool search(K key);

    void insert(K key) noexcept; 
};

template<typename K> int  Tree234<K>::Node234::MAX_KEYS = 3; 
/*
 * Node234 constructors. Note: While all children are initialize to nullptr, this is not really necessary. 
 * Instead your can simply set children[0] = nullptr, since a Node234 is a leaf if and only if children[0] == 0
 */

/*
 * TODO: 
 * error: non-const lvalue reference to type 'std::unique_ptr<Node234>' cannot bind to a temporary of type 'nullptr_t'
 */
template<typename K> inline  Tree234<K>::Node234::Node234(K small) : totalItems(1), parent(nullptr)
{ 
   keys[0] = small; 
   children[0] = nullptr;
}

/*
 * TODO: 
 * error: non-const lvalue reference to type 'std::unique_ptr<Node234>' cannot bind to a temporary of type 'nullptr_t'
 */

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle) : totalItems(2), parent(nullptr)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   children[0] = nullptr;
}
/*
 * TODO: 
 * error: non-const lvalue reference to type 'std::unique_ptr<Node234>' cannot bind to a temporary of type 'nullptr_t'
 */
template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle, K large) : totalItems(3), parent(nullptr)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   keys[2] = large; 
   children[0] = nullptr;
}

template<typename K> inline void Tree234<K>::Node234::nullAllChildren()
{
  for(auto i = 0; i <= totalItems; ++i) {

	children[i] = nullptr;
  }
}

template<typename K> typename Tree234<K>::Node234& Tree234<K>::Node234::operator=(const Node234& rhs)
{
  if (this == &rhs) {
    return rhs;
  }

  parent = rhs.parent;
  totalItems = rhs.totalItems;

  auto i = 0;
  for(; i < rhs.totalItems; ++i) {
      keys[i] = rhs.keys[i];
      children[i] = rhs.children[i];
  }

  children[i] = rhs.children[i];
}

template<typename K> inline int Tree234<K>::Node234::getTotalItems() const
{
   return totalItems; 
}

template<typename K> inline bool Tree234<K>::Node234::findKey(K key, int& index) const
{
   for(index = 0; index < totalItems; ++index) {
       
       if (keys[index] == key) {
           return true;
       }
   }   
   
   return false;
}

template<typename K> inline int Tree234<K>::Node234::getChildCount() const
{
   return totalItems + 1; 
}

template<typename K> inline bool Tree234<K>::Node234::isTwoNode() const
{
   return (totalItems == 1) ? true : false;
}

 
template<typename K> inline Tree234<K>::Tree234(std::initializer_list<K> il) : root(nullptr)
{
    for (auto x: il) {
        insert(x);
    }
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

template<typename K> inline void Tree234<K>::Node234::insertChild(int childNum, std::unique_ptr<Node234> &pChild)
{
  // shift children right in order to insert pChild
  
  /*
   * When insertChild() is called, totalItems will reflect the number of keys after a new key was added by insertKey(K key), but before a new
   * child was inserted using insertChild(). Therefore, the index of the last child would be totalItems - 1. 
   *    For example, if the prior totalIems was 1, and we made the 2-node a 3-node by calling insertKey(key), then totalItmes would be 2, but the
   * last child index--before calling insertChild()--would still be 1, or "the new  totalItems" - 1.
   */
  for(auto i = totalItems - 1; i >= childNum ; i--) {

          // TODO: use std::move
          children[i + 1] = std::move(children[i]); // shift child right

   } 

//??  children[childNum] = pChild;
  children[childNum] = std::move(pChild);

  if (!isLeaf()) {
      
   pChild->parent = this; // reset the child's parent pointer, too.
  }
  
  return;
}


/*
 * precondition: childIndex is within the range for the type of node.
 * child is not nullptr.
 */
template<typename K> inline void  Tree234<K>::Node234::connectChild(int childIndex, std::unique_ptr<Node234> child)
{
  //--children[childIndex] = child; // no operator=
  children[childIndex].reset( child ); 
  
  if (child != nullptr) {
      /*
       * TODO:  error: no viable overloaded '='
       */ 
     //--child->parent = this; 
     child->parent.reset( this ); 
     
  }
}
/*
 * precondition: childIndex is within the range for the type of node.
 * returns child pointer.
 * Note: Always call disconnectChild() before removeItem(), or it will not work correctly because totalItems
 * will have been altered.
 */

template<typename K> inline std::unique_ptr<typename Tree234<K>::Node234> Tree234<K>::Node234::disconnectChild(int childIndex)
{
  std::unique_ptr<Node234> node{ children[childIndex] };

  // shift children (whose last 0-based index is totalItems) left to overwrite removed child i.
  for(auto i = childIndex; i < totalItems; ++i) {

       children[i] = std::move(children[i + 1]); // shift remaining children to the left
  } 

  return node;
}
/*
 * preconditions: node is not full, not a four node (full), and key is not already in node. It may or may not
 * be a leaf node.  Shifts keys in node as needed so that key will be inserted in sorted position. Returns index
 * of inserted key.
 */

template<typename K> inline int  Tree234<K>::Node234::insertKey(K key) 
{ 
  // start on right, examine items

  for(auto i = totalItems - 1; i >= 0 ; i--) {

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


template<typename K> inline  bool Tree234<K>::Node234::isFull() const 
{ 
   return totalItems == MAX_KEYS;
}

template<typename K> inline  std::unique_ptr< typename Tree234<K>::Node234 > &Tree234<K>::Node234::getParent()  
{ 
   return parent;
}

template<typename K> inline  const std::unique_ptr< typename Tree234<K>::Node234 > &Tree234<K>::Node234::getParent() const 
{ 
   return parent;
}


template<typename K> inline  bool Tree234<K>::Node234::isLeaf() const 
{ 
   return !children[0] ? true : false;
}

template<typename K> inline Tree234<K>::~Tree234()
{
  // DestroyTree(root);
}

template<typename K> inline bool Tree234<K>::search(K key)
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

template<typename K>  bool Tree234<K>::DoSearch(K key, std::unique_ptr<Node234> &location, int& index)
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
 * Insertion based on pseudo code at: http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt
 */
template<typename K> void Tree234<K>::insert(K key) noexcept
{
    if (root == nullptr) {

       root.reset( new Node234{key} ); 
       return; 
    } 

   std::unique_ptr<Node234> &current = root;

   /* Descend until a leaf node is found, splitting four nodes as they are encountered */

   while(true) {
       
       if(current->isFull()) {// if four node, split it, moving a value up to parent.

            split(current); 
      
            // resume search with parent.
            /*
             * TODO: Error message about: no operaotr= exists in unique_ptr. Should I call: current->getParent.get()?
             */
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
template<typename K> void Tree234<K>::split(std::unique_ptr<Node234> &node)
{
    K  itemB, itemC;
    Node234 *parent;

    // remove two largest (of three total) keys...
        
    itemC = node->keys[2];
    itemB = node->keys[1]; 
    node->totalItems = 1; // ...by first setting totalItems to 1. 

    // Remove its two right-most children. 
    Node234 *child2 = node->children[2]; // TODO:
    Node234 *child3 = node->children[3]; // TODO:

    Node234 *newRight = new Node234{itemC}; // make new right child node from largest item

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
        root = new Node234{itemB}; 
        parent = root;          // root is parent of node
        root->connectChild(0, node); // connect node to root as left child
        root->connectChild(1, newRight);
        return;
    }         

    parent = node->getParent(); 
    
    // deal with parent, moving itemB middle value to parent.

    int insert_index = parent->insertKey(itemB);
    int last_index = parent->totalItems - 1;
    
    for(auto i = last_index; i > insert_index; i--)  {// move parent's connections right, start from new last
                                                     // index up to insert_index
        parent->connectChild(i + 1, parent->children[i]);       // to the right
    }

    parent->connectChild(insert_index + 1,  newRight);

    /* 
     * By default, we do not need to insert node. It will be at the correct position. So we do not need to do:
     *     parent->connectChild(insert_index, node); 
     */
  
    return;
}
#endif
