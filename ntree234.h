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

       Node234(K small) noexcept;
       Node234(K small, K larger) noexcept;
       Node234(K small, K middle, K large) noexcept;
       Node234& operator=(const Node234& rhs) noexcept;

       Node234 *parent; // parent is only used for navigation of the tree. It does not own the memory it points to.

       int totalItems; /* If 1, two node; if 2, three node; if 3, four node. */   

       std::array<K, 3> keys;

       /*
        * For 2-nodes, children[0] is left pointer and children[1] is right pointer.
        * For 3-nodes, children[0] is left pointer, children[1] the middle pointer, and children[2] the right pointer.
        * And so on for 4-nodes.
        */

       std::array< std::unique_ptr<Node234>, 4 > children;

       Node234 *getParent() noexcept; 

       /* 
        * Returns true if key is found in node and set index: this->keys[index] == key
        * Returns false if key is if not found; set next to the next in-order child.
        */
       bool searchNode(K key, int& index, Node234 *&next) noexcept;

       int insertKey(K key) noexcept;
       
       void connectChild(int childNum, std::unique_ptr<Node234>& child) noexcept;
       
       /*
        * Removes child node andshifts its children to fill the gap. Returns child pointer.
        */  
       std::unique_ptr<Node234> disconnectChild(int child_index) noexcept; 

       void insertChild(int childNum, std::unique_ptr<Node234> &pChild) noexcept;

       /* 
        * Called during remove(K key).
        * Merges the 2-node children of a parent 2-node into the parent, making a 4-node. 
        */
       
     public:
         
       const Node234 *getParent() const noexcept;

       int getTotalItems() const noexcept;
       int getChildCount() const noexcept;
       bool findKey(K key, int& index) const noexcept;
       bool isFull() const  noexcept;
       bool isLeaf() const noexcept; 
       bool isTwoNode() const noexcept;
       void nullAllChildren() noexcept;
    };  

    friend class DebugPrinter;
  
    std::unique_ptr<Node234>  root; 
    
    bool DoSearch(K key, Node234 *&location, int& index) noexcept;

    void split(Node234 *node) noexcept;  // called during insert to split 4-nodes
    void DestroyTree(std::unique_ptr<Node234> &root) noexcept; 

  public:

     Tree234() noexcept : root{nullptr} { } 

     Tree234(const Tree234& lhs) noexcept; 

     Tree234(std::initializer_list<K> list) noexcept; 

    ~Tree234(); 

    bool search(K key) noexcept;

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
template<typename K> inline  Tree234<K>::Node234::Node234(K small)  noexcept : totalItems(1), parent(nullptr)
{ 
   keys[0] = small; 
   children[0] = nullptr;
}

/*
 * TODO: 
 * error: non-const lvalue reference to type 'std::unique_ptr<Node234>' cannot bind to a temporary of type 'nullptr_t'
 */

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle)  noexcept : totalItems(2), parent(nullptr)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   children[0] = nullptr;
}
/*
 * TODO: 
 * error: non-const lvalue reference to type 'std::unique_ptr<Node234>' cannot bind to a temporary of type 'nullptr_t'
 */
template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle, K large)  noexcept : totalItems(3), parent(nullptr)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   keys[2] = large; 
   children[0] = nullptr;
}

template<typename K> inline void Tree234<K>::Node234::nullAllChildren()  noexcept
{
  for(auto i = 0; i <= totalItems; ++i) {

	children[i] = nullptr;
  }
}

template<typename K> typename Tree234<K>::Node234& Tree234<K>::Node234::operator=(const Node234& rhs)  noexcept
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

template<typename K> inline int Tree234<K>::Node234::getTotalItems() const noexcept
{
   return totalItems; 
}

template<typename K> inline bool Tree234<K>::Node234::findKey(K key, int& index) const noexcept
{
   for(index = 0; index < totalItems; ++index) {
       
       if (keys[index] == key) {
           return true;
       }
   }   
   
   return false;
}

template<typename K> inline int Tree234<K>::Node234::getChildCount() const noexcept
{
   return totalItems + 1; 
}

template<typename K> inline bool Tree234<K>::Node234::isTwoNode() const noexcept
{
   return (totalItems == 1) ? true : false;
}

 
template<typename K> inline Tree234<K>::Tree234(std::initializer_list<K> il) noexcept//: root(nullptr)
{
    for (auto x: il) {

        insert(x);
    }
}
/*
 * precondition: childIndex is within the range for the type of node.
 * child is not nullptr.
 */
template<typename K> inline void  Tree234<K>::Node234::connectChild(int childIndex, std::unique_ptr<Node234>& child)  noexcept
{
  children[childIndex] = std::move( child );
  
  if (child != nullptr) {

       child->parent = this; 
  }
}

/*
 * Returns true if key is found in node, and it set index so that this->keys[index] == key.
 * Returns false if key is if not found, and it sets next to point to next child with which to continue the search.
 */
template<typename K> inline bool Tree234<K>::Node234::searchNode(K value, int& index, Node234 *&next) noexcept
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

template<typename K> inline void Tree234<K>::Node234::insertChild(int childNum, std::unique_ptr<Node234> &pChild) noexcept
{
  // shift children right in order to insert pChild
  
  /*
   * When insertChild() is called, totalItems will reflect the number of keys after a new key was added by insertKey(K key), but before a new
   * child was inserted using insertChild(). Therefore, the index of the last child would be totalItems - 1. 
   *    For example, if the prior totalIems was 1, and we made the 2-node a 3-node by calling insertKey(key), then totalItmes would be 2, but the
   * last child index--before calling insertChild()--would still be 1, or "the new  totalItems" - 1.
   */
  for(auto i = totalItems - 1; i >= childNum ; i--) {

        children[i + 1] = std::move(children[i]); // shift child right. Calls operator=(Node234&&) 
   } 

  children[childNum] = std::move(pChild);

  if (!isLeaf()) {
      
     pChild->parent = this; // reset the child's parent pointer, too.
  }
  
  return;
}


/*
 * precondition: childIndex is within the range for the type of node.
 * returns child pointer.
 * Note: Always call disconnectChild() before removeItem(), or it will not work correctly because totalItems
 * will have been altered.
 */

template<typename K> inline std::unique_ptr<typename Tree234<K>::Node234> Tree234<K>::Node234::disconnectChild(int childIndex) noexcept
{
  std::unique_ptr<Node234> node{ children[childIndex] }; // invokes move constructor.

  // shift children (whose last 0-based index is totalItems) left to overwrite removed child i.
  for(auto i = childIndex; i < totalItems; ++i) {

       children[i] = std::move(children[i + 1]); // shift remaining children to the left. Calls operator=(Node234&&)
  } 

  return node;
}
/*
 * preconditions: node is not full, not a four node (full), and key is not already in node. It may or may not
 * be a leaf node.  Shifts keys in node as needed so that key will be inserted in sorted position. Returns index
 * of inserted key.
 */

template<typename K> inline int  Tree234<K>::Node234::insertKey(K key)  noexcept
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


template<typename K> inline  bool Tree234<K>::Node234::isFull() const  noexcept
{ 
   return totalItems == MAX_KEYS;
}

template<typename K> inline typename Tree234<K>::Node234 * Tree234<K>::Node234::getParent()   noexcept
{ 
   return parent;
}

template<typename K> inline const typename Tree234<K>::Node234 *Tree234<K>::Node234::getParent() const  noexcept
{ 
   return parent;
}


template<typename K> inline  bool Tree234<K>::Node234::isLeaf() const  noexcept
{ 
   return !children[0] ? true : false;
}

template<typename K> inline Tree234<K>::~Tree234()
{
  // DestroyTree(root); TODO: DestroyTree should call p.release() instead of delete p;
}

template<typename K> inline bool Tree234<K>::search(K key) noexcept
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

template<typename K>  bool Tree234<K>::DoSearch(K key, Node234 *&location, int& index) noexcept
{
  Node234 *current = root.get();
  Node234 *next;

  if (!root) { // <--> if (root.get() == nullptr)

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
    /*
     * TODO: reset() first deletes object current being managed before the new'ed pointer begins to be managed. 
     */
       root.reset( new Node234{key} ); 
       return; 
    } 

   Node234 *current = root.get();

   /* Descend until a leaf node is found, splitting four nodes as they are encountered */

   while(true) {
       
       if(current->isFull()) {// if four node, split it, moving a value up to parent.

            split(current); 
      
            // resume search with parent.
            current = current->getParent(); // TODO:  no operaotr= exists in unique_ptr. Should I call: current->getParent.get()?
                        
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
            current = next;  // can't copy assign a unique_ptr. You can only move-assign.
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
template<typename K> void Tree234<K>::split(Node234 *node) noexcept
{
    K  itemB, itemC;
    Node234 *parent;

    // remove two largest (of three total) keys...
        
    itemC = node->keys[2];
    itemB = node->keys[1]; 
    
    node->totalItems = 1; // ...by first setting totalItems to 1. 

    std::unique_ptr<Node234> newRight{ new Node234{itemC} }; // make new right child node from largest item

    /* set its left and right children to be the two right-most children of node */
    if (node->children[2] && node->children[3]) { // that is, if neither are nullptr
        
        newRight->connectChild(0, node->children[2]); // connect to 0 and 1

        newRight->connectChild(1, node->children[3]); // on newRight
    }

    /* we will covert node into a two node whose left and right children will be the two left most children
       This occurs by default. We only need adjust totalItems  */
    
    node->children[2] = std::move(std::unique_ptr<Node234>()); 
    node->children[3] = std::move(std::unique_ptr<Node234>()); 

    // if this is the root,
    if(node == root.get()) { 

        /* make new root two node using node's middle value */  
        std::unique_ptr<Node234> p{ new Node234{itemB} };
        
        root = std::move(p); // TODO: Is this what I intend? Does this cause root to leak?
        
        // TODO: This line doesn't seem to do anything?
        //--parent = root;          // root is parent of node 
        
        // TODO: change to do move() and then set the parent.)
        // root is newly allocated Node.
        root->connectChild(0, node); // TODO: node is a raw pointer and not a unique_ptr<Node234>
        
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
