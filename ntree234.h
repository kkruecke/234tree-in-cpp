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

    template<typename Functor> void DoInorderTraverse(Functor f, Node234 *root) noexcept;
    template<typename Functor> void DoPostOrderTraverse(Functor f, Node234 *root) noexcept;
    template<typename Functor> void DoPreOrderTraverse(Functor f, Node234 *root) noexcept;
    template<typename Functor> void DoPostOrder4Debug(Functor f, Node234 *root) noexcept;

    void split(Node234 *node) noexcept;  // called during insert to split 4-nodes
    void DestroyTree(std::unique_ptr<Node234> &root) noexcept; 
    void CloneTree(Node234 *pNode2Copy, Node234 *&pNodeCopy) noexcept; // called by copy ctor

  public:

     Tree234() noexcept : root{nullptr} { } 

     Tree234(const Tree234& lhs) noexcept; 

     Tree234(std::initializer_list<K> list) noexcept; 

    ~Tree234(); 

    template<typename Functor> void inOrderTraverse(Functor f) noexcept;
    template<typename Functor> void postOrderTraverse(Functor f) noexcept;
    template<typename Functor> void preOrderTraverse(Functor f) noexcept;

    bool search(K key) noexcept;

    void insert(K key) noexcept; 
};

template<typename K> int  Tree234<K>::Node234::MAX_KEYS = 3; 
/*
 * Node234 constructors. Note: While all children are initialize to nullptr, this is not really necessary. 
 * Instead your can simply set children[0] = nullptr, since a Node234 is a leaf if and only if children[0] == 0
 */

template<typename K> inline  Tree234<K>::Node234::Node234(K small)  noexcept : totalItems(1), parent(nullptr)
{ 
   keys[0] = small; 
   children[0] = nullptr;
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle)  noexcept : totalItems(2), parent(nullptr)
{ 
   keys[0] = small; 
   keys[1] = middle; 
   children[0] = nullptr;
}

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

template<typename K> inline Tree234<K>::Tree234(const Tree234<K>& lhs) noexcept
{
    //const Tree234<K>::Node234 *src =  const_cast<const Tree234<K>::Node234 *>( lhs.root.get() );
    Tree234<K>::Node234 *src =  lhs.root.get();
    
    Tree234<K>::Node234 *dest = root.get();
            
    CloneTree(src, dest);
}

template<typename K> template<typename Functor> inline void Tree234<K>::inOrderTraverse(Functor f) noexcept
{
   DoInorderTraverse(f, root);
}

template<typename K> template<typename Functor> inline void Tree234<K>::postOrderTraverse(Functor f) noexcept
{
   DoPostOrderTraverse(f, root);
}

template<typename K> template<typename Functor> inline void Tree234<K>::preOrderTraverse(Functor f) noexcept
{
   DoPreOrderTraverse(f, root);
}

/*
 * post order traversal 
 */
template<typename K> template<typename Functor> void Tree234<K>::DoPostOrderTraverse(Functor f, Node234 *current) noexcept
{  
   if (current == nullptr) {

        return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DoPostOrderTraverse(f, current->children[0]);

            DoPostOrderTraverse(f, current->children[1]);

            f(current->keys[0]);
            break;

      case 2: // three node
            DoPostOrderTraverse(f, current->children[0]);

            DoPostOrderTraverse(f, current->children[1]);

            f(current->keys[0]);

            DoPostOrderTraverse(f, current->children[2]);

            f(current->keys[1]);
            break;

      case 3: // four node
            DoPostOrderTraverse(f, current->children[0]);

            DoPostOrderTraverse(f, current->children[1]);

            f(current->keys[0]);

            DoPostOrderTraverse(f, current->children[2]);

            f(current->keys[1]);

            DoPostOrderTraverse(f, current->children[3]);

            f(current->keys[2]);
 
            break;
   }
}
/*
 * pre order traversal 
 */
template<typename K> template<typename Functor> void Tree234<K>::DoPreOrderTraverse(Functor f, Node234 *current) noexcept
{  

  if (current == nullptr) {

        return;
   }

   switch (current->totalItems) {

      case 1: // two node
            f(current->keys[0]);

            DoPreOrderTraverse(f, current->children[0]);

            DoPreOrderTraverse(f, current->children[1]);

            break;

      case 2: // three node
            f(current->keys[0]);

            DoPreOrderTraverse(f, current->children[0]);

            DoPreOrderTraverse(f, current->children[1]);

            f(current->keys[1]);

            DoPreOrderTraverse(f, current->children[2]);

            break;

      case 3: // four node
            f(current->keys[0]);

            DoPreOrderTraverse(f, current->children[0]);

            DoPreOrderTraverse(f, current->children[1]);

            f(current->keys[1]);

            DoPreOrderTraverse(f, current->children[2]);

            f(current->keys[2]);

            DoPreOrderTraverse(f, current->children[3]);

            break;
   }
}

/*
 * post order traversal for debugging purposes
 */
template<typename K> template<typename Functor> void Tree234<K>::DoPostOrder4Debug(Functor f, Node234 *current) noexcept
{     
   
   if (current == nullptr) {

	return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DoPostOrder4Debug(f, current->children[0]);

            DoPostOrder4Debug(f, current->children[1]);

            f(current->keys[0], 0, current, root);
            break;

      case 2: // three node
            DoPostOrder4Debug(f, current->children[0]);

            DoPostOrder4Debug(f, current->children[1]);

            f(current->keys[0], 0, current, root);

            DoPostOrder4Debug(f, current->children[2]);

            f(current->keys[1], 1, current, root);
            break;

      case 3: // four node
            DoPostOrder4Debug(f, current->children[0]);

            DoPostOrder4Debug(f, current->children[1]);

            f(current->keys[0], 0, current, root);

            DoPostOrder4Debug(f, current->children[2]);

            f(current->keys[1], 1, current, root);

            DoPostOrder4Debug(f, current->children[3]);

            f(current->keys[2], 2, current, root);
 
            break;
   }
}

/*
 * In order traversal
 */
template<typename K> template<typename Functor> void Tree234<K>::DoInorderTraverse(Functor f, Node234 *current) noexcept
{     
   if (current == nullptr) {

	return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DoInorderTraverse(f, current->children[0]);

            f(current->keys[0]);

            DoInorderTraverse(f, current->children[1]);
            break;

      case 2: // three node
            DoInorderTraverse(f, current->children[0]);

            f(current->keys[0]);

            DoInorderTraverse(f, current->children[1]);
 
            f(current->keys[1]);

            DoInorderTraverse(f, current->children[2]);
            break;

      case 3: // four node
            DoInorderTraverse(f, current->children[0]);

            f(current->keys[0]);

            DoInorderTraverse(f, current->children[1]);
 
            f(current->keys[1]);

            DoInorderTraverse(f, current->children[2]);

            f(current->keys[2]);

            DoInorderTraverse(f, current->children[3]);
 
            break;
   }
}


/*
 * pre-order traversal
 */

template<typename K>  void Tree234<K>::CloneTree(Node234 *pNode2Copy, Node234 *&pNodeCopy) noexcept
{
 if (pNode2Copy != nullptr) { 
                              
   // copy node
   switch (pNode2Copy->totalItems) {

      case 1: // two node
      {    

            pNodeCopy = new Node234(pNode2Copy->keys[0]); 
             
            pNodeCopy->parent = pNode2Copy->parent;
            
            pNodeCopy->nullAllChildren(); // necessary?
            
            /*
             * There is no implicit coversion from
             * 
             *      unique_ptr<Tree234<int>::Node234> 
             * to 
             *      Tree234<int>::Node234 *
             * 
             */
            Node234 *src = pNode2Copy->children[0].get();
            Node234* dest = pNodeCopy->children[0].get();
            
            CloneTree(src, dest); 
            
            src = pNode2Copy->children[1].get();
            dest = pNodeCopy->children[1].get();

            CloneTree(src, dest); 

            break;
      }   // end case
      case 2: // three node
      {
            pNodeCopy = new Node234(pNode2Copy->keys[0], pNode2Copy->keys[1]); 

            pNodeCopy->parent = pNode2Copy->parent;
            pNodeCopy->nullAllChildren();
            
            Node234 *src = pNode2Copy->children[0].get();
            Node234* dest =  pNodeCopy->children[0].get();

            CloneTree(src, dest);
            
            src = pNode2Copy->children[1].get();
            dest = pNodeCopy->children[1].get();

            CloneTree(src, dest);
            
            src = pNode2Copy->children[2].get();
            dest = pNodeCopy->children[2].get();
 
            CloneTree(src, dest);

            break;
      } // end case
      case 3: // four node
      {

            pNodeCopy = new Node234(pNode2Copy->keys[0], pNode2Copy->keys[1], pNode2Copy->keys[2]); 

            pNodeCopy->parent = pNode2Copy->parent;
            pNodeCopy->nullAllChildren();
            
            Node234 *src = pNode2Copy->children[0].get();
            Node234 *dest =  pNodeCopy->children[0].get();

            CloneTree(src, dest);
            
            src = pNode2Copy->children[1].get();
            dest =  pNodeCopy->children[1].get();

            CloneTree(src, dest);
            
            src = pNode2Copy->children[2].get();
            dest =  pNodeCopy->children[2].get();
 
            CloneTree(src, dest);
            
            src = pNode2Copy->children[3].get();
            dest =  pNodeCopy->children[3].get();

            CloneTree(src, dest);
 
            break;
      } // end case
   }
 } else {

    pNodeCopy = nullptr;
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
            
           next = children[i].get(); 
           break;

     } else if (keys[i] == value) {

         hit = true;
         index = i;
         break;

     } else if (i == totalItems - 1) { // it is greater than the last key
          
          next = children[totalItems].get(); 
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

  return node; // invokes move constructor since node.
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
  DestroyTree(root); 
}

/*
 * Post order traversal, deleting nodes
 */
template<typename K> void Tree234<K>::DestroyTree(std::unique_ptr<Node234> &current) noexcept 
{
  if (current == nullptr) {

	return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DestroyTree(current->children[0]);

            DestroyTree(current->children[1]);

            //delete current;
            current.reset();

            break;

      case 2: // three node
            DestroyTree(current->children[0]);

            DestroyTree(current->children[1]);
 
            DestroyTree(current->children[2]);

            //delete current;
            current.reset();

            break;

      case 3: // four node
            DestroyTree(current->children[0]);

            DestroyTree(current->children[1]);
 
            DestroyTree(current->children[2]);

            DestroyTree(current->children[3]);

            //delete current;
            current.reset();
 
            break;
   }
  
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
 *  Split pseudocode: 
 *  
 *  Upon encountering a full node (searching for a place to insert…):
 *  
 *  1.  split the node at that time. 
 *  2.  move highest data  item from the current (full) node into new node to the right.
 *  3.  move middle value of node undergoing the split up to parent node (Know we can do all this because parent node was not full) 
 *  4.  Retain lowest item in node.    
 *  
 *  5.  New node (to the right) only has one data item (the highest value) 
 *  6.  Original node (formerly full) node contains only the lowest of the three values.
 *  7.  Rightmost children of original full node are disconnected and connected to new children as appropriate 
 *	    (They must be disconnected, since their parent data is changed)
 *            New connections conform to linkage conventions, as expected. 
 *  8. Insert new data item into the original leaf node.
 *  
 */ 
template<typename K> void Tree234<K>::split(Node234 *node) noexcept
{
    // remove two largest (of three total) keys...
        
    K itemC = node->keys[2];
    K itemB = node->keys[1]; 
    
    node->totalItems = 1; // This effective removes all but the smallest key from node.

    std::unique_ptr<Node234> newRight{ new Node234{itemC} }; // Move largest key to what will be the new right child of split node.

    /* The "bool operator()" of unique_ptr tests whether a pointer is being managed, whether get() == nullptr. */
    if (node->children[2] && node->children[3]) { // If neither are nullptr
        
        newRight->connectChild(0, node->children[2]); // set its left child to the 3rd child of node 

        newRight->connectChild(1, node->children[3]); // set its right child to the 4th child of node
    }

    /* node's left and right children will be the two left most children of the node being split. */
    // I think these two lines can be deleted.  
    node->children[2] = std::move(std::unique_ptr<Node234>()); // First set node's two rightmost children to nullptr
    node->children[3] = std::move(std::unique_ptr<Node234>()); 

    // if this is the root,
    if(node == root.get()) { 

        /* make new root two node using node's middle value */  
        std::unique_ptr<Node234> p{ new Node234{itemB} };
        
       /*
         * Since the move version of operator=(unique_ptr<t>&&) deletes the managed pointer, we must first call release(); 
         * otherwise, node, which equals root, the soon-to-be prior root, will be deleted. 
         */ 
        root.release(); 
      
        root = std::move(p); 
        
        root->children[0] = std::move(std::unique_ptr<Node234>{node}); 
        root->children[0]->parent = root.get();
        
        root->children[1] = std::move(newRight); 
        root->children[1]->parent = root.get();
        
        return;
    }         

    Node234 *parent = node->getParent(); 
    
    // Move itemB, middle value, to parent (which we know has room).

    int insert_index = parent->insertKey(itemB);

    int last_index = parent->totalItems - 1;

    // move parent's connections right, starting from new last index, stopping before insert_index
    for(auto i = last_index; i > insert_index; i--)  {

        parent->connectChild(i + 1, parent->children[i]);       
    }

    // make newRight the right most child.
    parent->connectChild(insert_index + 1,  newRight);

    return;
}
#endif
