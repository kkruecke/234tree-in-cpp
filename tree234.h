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
/*
 * See www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt  
 * and http://web.njit.edu/~wl256/download/cs610/n1561011.pdf
 for pseudo code
 */

template<typename K> class Tree234 {
    
  protected:
   class Node234 { // nested node class
       
       friend class Tree234<K>;             
       friend class DebugPrinter;
       static const int MAX_KEYS;   

       enum class NodeMaxItems : int { two_node=1, three_node=2, four_node=3 };
    
       int to_int(const NodeMaxItems x) const { return static_cast<int>(x); }
       
   private: 

       Node234 *parent; /* parent is only used for navigation of the tree. It does not own the memory
                           it points to. */

       int totalItems; /* If 1, two node; if 2, three node; if 3, four node. */   

       std::array<K, 3> keys;

       /*
        * For 2-nodes, children[0] is left pointer and children[1] is right pointer.
        * For 3-nodes, children[0] is left pointer, children[1] the middle pointer, and children[2] the right pointer.
        * And so on for 4-nodes.
        */

       std::array<std::unique_ptr<Node234>, 4> children;
       
       constexpr Node234 *getParent() noexcept; 

       /* 
        * Returns true if key is found in node and sets index so this->keys[index] == key
        * Returns false if key is if not found; sets next to the next in-order child if key not found.
        */
       bool NodeDescentSearch(K key, int& index, Node234 *&next) noexcept;

       int insertKey(K key) noexcept;
       
       void connectChild(int childNum, std::unique_ptr<Node234>& child) noexcept;
       
       // Remove key, if found, from node, shifting remaining keys to fill its gap.
       K removeKey(int index) noexcept;

       /*
        * Removes child node (implictly using move ctor) and shifts its children to fill the gap. Returns child pointer.
        */  
       std::unique_ptr<Node234> disconnectChild(int child_index) noexcept; 

       void insertChild(int childNum, std::unique_ptr<Node234> &pChild) noexcept;

       /* 
        * Called during remove(K key).
        * Merges the 2-node children of a parent 2-node into the parent, making a 4-node. 
        */
       Node234 *fuseWithChildren() noexcept; 
       
     public:
         
       Node234() noexcept;
       Node234(K small) noexcept;
       Node234(K small, K large) noexcept;
       Node234(K small, K middle, K large) noexcept;  
       constexpr const Node234 *getParent() const noexcept;

       constexpr int getTotalItems() const noexcept;
       constexpr int getChildCount() const noexcept;

       bool findKey(K key, int& index) const noexcept;
       constexpr bool isFull() const  noexcept;
       constexpr bool isLeaf() const noexcept; 
       constexpr bool isTwoNode() const noexcept;
       constexpr bool isThreeNode() const noexcept;
       constexpr bool isFourNode() const noexcept;
    };  

    friend class DebugPrinter;
  
    int to_int(const typename Tree234<K>::Node234::NodeMaxItems x) const { return static_cast<int>(x); }

    std::unique_ptr<Node234>  root; 
    
    bool DoSearch(K key, Node234 *&location, int& index) noexcept;

    template<typename Functor> void DoInorderTraverse(Functor f, Node234 *root) noexcept;
    template<typename Functor> void DoPostOrderTraverse(Functor f, Node234 *root) noexcept;
    template<typename Functor> void DoPreOrderTraverse(Functor f, Node234 *root) noexcept;
    template<typename Functor> void DoPostOrder4Debug(Functor f, Node234 *root) noexcept;

    void split(Node234 *node) noexcept;  // called during insert to split 4-nodes
    void DestroyTree(std::unique_ptr<Node234> &root) noexcept; 

    void CloneTree(const Node234 *pNode2Copy, std::unique_ptr<Node234> &pNodeCopy) noexcept; // called by copy ctor

    // These methods are called during remove(K key)
    bool remove(K key, Node234 *location); 

    // Convert two-node to three- or four-node
    Node234 *convertTwoNode(Node234 *node) noexcept;

    Node234 *fuseSiblings(Node234 *parent, int node2_id, int sibling_id) noexcept;
    
    Node234 *doRotation(Node234 *parent, int node2_id, int sibling_id) noexcept;

    Node234 *leftRotation(Node234 *p2node, Node234 *psibling, Node234 *parent, int parent_key_index) noexcept;

    Node234 *rightRotation(Node234 *p2node, Node234 *psibling, Node234 *parent, int parent_key_index) noexcept;

  public:

     Tree234() noexcept : root{} { } 

     Tree234(const Tree234& lhs) noexcept; 
     Tree234(Tree234&& lhs) noexcept;     // move constructor

     Tree234& operator=(const Tree234& lhs) noexcept; 
     Tree234& operator=(Tree234&& lhs) noexcept;    // move assignment

     Tree234(std::initializer_list<K> list) noexcept; 
     Tree234(std::vector<K> vec) noexcept; 

    ~Tree234(); 

    template<typename Functor> void inOrderTraverse(Functor f) noexcept;
    template<typename Functor> void postOrderTraverse(Functor f) noexcept;
    template<typename Functor> void preOrderTraverse(Functor f) noexcept;

    template<typename Functor> void debug_dump(Functor f) noexcept;

    bool search(K key) noexcept;

    void insert(K key) noexcept; 

    bool remove(K key);
};

template<typename K> const int  Tree234<K>::Node234::MAX_KEYS = 3; 
/*
 * Node234 constructors. Note: While all children are initialize to nullptr, this is not really necessary. 
 * Instead your can simply set children[0] = nullptr, since a Node234 is a leaf if and only if children[0] == 0
 */
template<typename K> inline  Tree234<K>::Node234::Node234()  noexcept : totalItems(0), parent(nullptr), children()
{ 
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small)  noexcept : totalItems(1), parent(nullptr), children()
{ 
   keys[0] = small; 
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle)  noexcept : totalItems(2), parent(nullptr), children()
{ 
   keys[0] = small; 
   keys[1] = middle; 
}

template<typename K> inline  Tree234<K>::Node234::Node234(K small, K middle, K large)  noexcept : totalItems(3), parent(nullptr), children()
{ 
   keys[0] = small; 
   keys[1] = middle; 
   keys[2] = large; 
}

template<typename K> inline constexpr int Tree234<K>::Node234::getTotalItems() const noexcept
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

template<typename K> inline constexpr int Tree234<K>::Node234::getChildCount() const noexcept
{
   return totalItems + 1; 
}

template<typename K> inline constexpr bool Tree234<K>::Node234::isTwoNode() const noexcept
{
   return (totalItems == to_int(NodeMaxItems::two_node)) ? true : false;
}

template<typename K> inline constexpr bool Tree234<K>::Node234::isThreeNode() const noexcept
{
   return (totalItems == to_int(NodeMaxItems::three_node)) ? true : false;
}

template<typename K> inline constexpr bool Tree234<K>::Node234::isFourNode() const noexcept
{
   return (totalItems == to_int(NodeMaxItems::four_node)) ? true : false;
}

template<typename K> inline Tree234<K>::Tree234(const Tree234<K>& lhs) noexcept
{
    Tree234<K>::Node234 *src =  lhs.root.get();
    
    CloneTree(src, root);
}
 
// move constructor
template<typename K> inline Tree234<K>::Tree234(Tree234&& lhs) noexcept : root{std::move(lhs.root)} 
{
    root->parent = nullptr;
}

template<typename K> inline Tree234<K>::Tree234(std::initializer_list<K> il) noexcept : root(nullptr) 
{
    for (K& x: il) { // simply call insert(x)
          insert(x);
    }
}

template<typename K> inline Tree234<K>::Tree234(std::vector<K> vec) noexcept : root(nullptr) 
{
    for (K& x: vec) { // simply call insert(x)
          insert(x);
    }
}

// copy assignment
template<typename K> inline Tree234<K>& Tree234<K>::operator=(const Tree234& lhs) noexcept 
{
  if (root == lhs.root) { // are they the same?

       return *this;
  }

  DestroyTree(root); // free all nodes and then clone lhs.

  const Tree234<K>::Node234 *src =  lhs.root.get();
            
  CloneTree(src, root);

  return *this;
}

// move assignment
template<typename K> inline Tree234<K>& Tree234<K>::operator=(Tree234&& lhs) noexcept 
{
    root = std::move(lhs.root);
    root->parent = nullptr;
}

template<typename K> template<typename Functor> inline void Tree234<K>::inOrderTraverse(Functor f) noexcept
{
   DoInorderTraverse(f, root.get());
}

template<typename K> template<typename Functor> inline void Tree234<K>::postOrderTraverse(Functor f) noexcept
{
   DoPostOrderTraverse(f, root.get());
}

template<typename K> template<typename Functor> inline void Tree234<K>::preOrderTraverse(Functor f) noexcept
{
   DoPreOrderTraverse(f, root.get());
}

template<typename K> template<typename Functor> inline void Tree234<K>::debug_dump(Functor f) noexcept
{
   DoPostOrder4Debug(f, root.get());
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
            DoPostOrderTraverse(f, current->children[0].get());

            DoPostOrderTraverse(f, current->children[1].get());

            f(current->keys[0]);
            break;

      case 2: // three node
            DoPostOrderTraverse(f, current->children[0].get());

            DoPostOrderTraverse(f, current->children[1].get());

            f(current->keys[0]);

            DoPostOrderTraverse(f, current->children[2].get());

            f(current->keys[1]);
            break;

      case 3: // four node
            DoPostOrderTraverse(f, current->children[0].get());

            DoPostOrderTraverse(f, current->children[1].get());

            f(current->keys[0]);

            DoPostOrderTraverse(f, current->children[2].get());

            f(current->keys[1]);

            DoPostOrderTraverse(f, current->children[3].get());

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

            DoPreOrderTraverse(f, current->children[0].get());

            DoPreOrderTraverse(f, current->children[1].get());

            break;

      case 2: // three node
            f(current->keys[0]);

            DoPreOrderTraverse(f, current->children[0].get());

            DoPreOrderTraverse(f, current->children[1].get());

            f(current->keys[1]);

            DoPreOrderTraverse(f, current->children[2].get());

            break;

      case 3: // four node
            f(current->keys[0]);

            DoPreOrderTraverse(f, current->children[0].get());

            DoPreOrderTraverse(f, current->children[1].get());

            f(current->keys[1]);

            DoPreOrderTraverse(f, current->children[2].get());

            f(current->keys[2]);

            DoPreOrderTraverse(f, current->children[3].get());

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
            DoPostOrder4Debug(f, current->children[0].get());

            DoPostOrder4Debug(f, current->children[1].get());

            f(current->keys[0], 0, current, root.get());
            break;

      case 2: // three node
            DoPostOrder4Debug(f, current->children[0].get());

            DoPostOrder4Debug(f, current->children[1].get());

            f(current->keys[0], 0, current, root.get());

            DoPostOrder4Debug(f, current->children[2].get());

            f(current->keys[1], 1, current, root.get());
            break;

      case 3: // four node
            DoPostOrder4Debug(f, current->children[0].get());

            DoPostOrder4Debug(f, current->children[1].get());

            f(current->keys[0], 0, current, root.get());

            DoPostOrder4Debug(f, current->children[2].get());

            f(current->keys[1], 1, current, root.get());

            DoPostOrder4Debug(f, current->children[3].get());

            f(current->keys[2], 2, current, root.get());
 
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
            DoInorderTraverse(f, current->children[0].get());

            f(current->keys[0]);

            DoInorderTraverse(f, current->children[1].get());
            break;

      case 2: // three node
            DoInorderTraverse(f, current->children[0].get());

            f(current->keys[0]);

            DoInorderTraverse(f, current->children[1].get());
 
            f(current->keys[1]);

            DoInorderTraverse(f, current->children[2].get());
            break;

      case 3: // four node
            DoInorderTraverse(f, current->children[0].get());

            f(current->keys[0]);

            DoInorderTraverse(f, current->children[1].get());
 
            f(current->keys[1]);

            DoInorderTraverse(f, current->children[2].get());

            f(current->keys[2]);

            DoInorderTraverse(f, current->children[3].get());
 
            break;
   }
}

/*
 * pre-order traversal
 */

template<typename K>  void Tree234<K>::CloneTree(const Node234 *pNode2Copy, std::unique_ptr<Node234> &pNodeCopy) noexcept
{
 if (pNode2Copy != nullptr) { 
                              
   // copy node
   switch (pNode2Copy->totalItems) {

      case 1: // two node
      {    
            std::unique_ptr<Node234> tmp = std::make_unique<Node234>(pNode2Copy->keys[0]);
            
            pNodeCopy = std::move(tmp); 
             
            pNodeCopy->parent = pNode2Copy->parent;
            
            const Node234 *src = pNode2Copy->children[0].get();
            
            CloneTree(src, pNodeCopy->children[0]); 
            
            src = pNode2Copy->children[1].get();

            CloneTree(src, pNodeCopy->children[1]); 

            break;

      }   // end case
      case 2: // three node
      {
            std::unique_ptr<Node234> tmp = std::make_unique<Node234>( pNode2Copy->keys[0], pNode2Copy->keys[1]); 
            
            pNodeCopy = std::move( tmp ); 

            pNodeCopy->parent = pNode2Copy->parent;
            
            const Node234 *src = pNode2Copy->children[0].get();

            CloneTree(src, pNodeCopy->children[0]);
            
            src = pNode2Copy->children[1].get();

            CloneTree(src, pNodeCopy->children[1]);
            
            src = pNode2Copy->children[2].get();
 
            CloneTree(src, pNodeCopy->children[2]);

            break;
      } // end case
      case 3: // four node
      {

            std::unique_ptr<Node234> tmp = std::make_unique<Node234>( pNode2Copy->keys[0], pNode2Copy->keys[1], pNode2Copy->keys[2]); 

            pNodeCopy = std::move( tmp );

            pNodeCopy->parent = pNode2Copy->parent;
            
            const Node234 *src = pNode2Copy->children[0].get();

            CloneTree(src, pNodeCopy->children[0]);
            
            src = pNode2Copy->children[1].get();

            CloneTree(src, pNodeCopy->children[1]);
            
            src = pNode2Copy->children[2].get();
 
            CloneTree(src, pNodeCopy->children[2]);
            
            src = pNode2Copy->children[3].get();

            CloneTree(src, pNodeCopy->children[3]);
 
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
  children[childIndex] = std::move( child ); // Note: If children[childIndex] currently holds a managed pointer , it will be freed.
  
  if (children[childIndex] != nullptr) { 

       children[childIndex]->parent = this; 
  }
}

/*
 * Returns true if key is found in node, and it set index so that this->keys[index] == key.
 * Returns false if key is if not found, and it sets next to point to next child with which to continue the descent search downward (toward a leaf node).
 */
template<typename K> inline bool Tree234<K>::Node234::NodeDescentSearch(K value, int& found_index, Node234 *&next) noexcept
{
  for(auto i = 0; i < totalItems; ++i) {

     if (value < keys[i]) {
            
         next = children[i].get(); 
         return false;

     } else if (keys[i] == value) {

         found_index = i;
         return true;
     }
  }

  // it must be greater than the last key (because it is not less than or equal to it).
  next = children[totalItems].get(); 

  return false;
}

template<typename K> inline void Tree234<K>::Node234::insertChild(int childNum, std::unique_ptr<Node234> &pChild) noexcept
{
  // shift children right in order to insert pChild
  
  /*
   * When insertChild() is called, totalItems will reflect the number of keys after a new key was added by insertKey(K key),
   * but before a new child was inserted using insertChild(). Therefore, the index of the last child would be totalItems - 1. 
   *    For example, if the prior totalIems was 1, and we made the 2-node a 3-node by calling insertKey(key), then totalItmes
   * would be 2, but the last child index--before calling insertChild()--would still be 1, or "the new  totalItems" - 1.
   */
  for(auto i = totalItems - 1; i >= childNum ; i--) {

        children[i + 1] = std::move(children[i]); // shift child right. Calls operator=(Node234&&) 
   } 

  children[childNum] = std::move(pChild);

  if (!isLeaf()) {
      
     children[childNum]->parent = this; // reset the child's parent pointer, too.
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
  std::unique_ptr<Node234> node = std::move(children[childIndex] ); // invokes move assignment.

  // shift children (whose last 0-based index is totalItems) left to overwrite removed child i.
  for(auto i = childIndex; i < totalItems; ++i) {

       children[i] = std::move(children[i + 1]); // shift remaining children to the left. Calls operator=(Node234&&)
  } 

  return node; // invokes move constructor since node is an rvalue.
}
/*
 * preconditions: node is not full, not a four node (full), and key is not already in node. It may or may not
 * be a leaf node.  Shifts keys in node as needed so that key will be inserted in sorted position. Returns index
 * of inserted key.
 */

template<typename K> inline int  Tree234<K>::Node234::insertKey(K key)  noexcept
{ 
    
  // start on right, examine items
  for(auto i = totalItems - 1; i >= 0 ; --i) {

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

template<typename K> inline K Tree234<K>::Node234::removeKey(int index) noexcept
{
  K key = keys[index]; 

  // shift to the left all keys to the right of index to the left
  for(auto i = index; i < totalItems - 1; ++i) {

      keys[i] = keys[i + 1]; 
  } 

  totalItems--;

  return key;
}

template<typename K> inline constexpr  bool Tree234<K>::Node234::isFull() const  noexcept
{ 
   return totalItems == MAX_KEYS;
}

template<typename K> inline constexpr typename Tree234<K>::Node234 * Tree234<K>::Node234::getParent()   noexcept
{ 
   return parent;
}

template<typename K> inline constexpr const typename Tree234<K>::Node234 *Tree234<K>::Node234::getParent() const  noexcept
{ 
   return parent;
}

template<typename K> inline constexpr  bool Tree234<K>::Node234::isLeaf() const  noexcept
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

   for(auto i = 0; i < current->totalItems; ++i) {

        DestroyTree(current->children[i]);
   }

   current.reset();
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
 
      if (current->NodeDescentSearch(key, index, next)) {  

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
 * Rather than search down the tree and then possibly promote and break up 4-nodes on the way back up, we split 4 nodes as we call NodeDescentSearch()
 * on the way down.
 * Insertion based on pseudo code at:
 * http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt
 */
template<typename K> void Tree234<K>::insert(K key) noexcept
{
    if (root == nullptr) {
           
       root = std::make_unique<Node234>(key); 
       return; 
    } 

   Node234 *current = root.get();

   // Descend until a leaf node is found, splitting four nodes as they are encountered 

   while(true) {
       
       if(current->isFull()) {// if four node encountered, split it, moving a value up to parent.

            split(current); 
      
            // resume search with parent.
            current = current->getParent(); 
                        
       }  else if( current->isLeaf() )  {

            // done descending. 
            break;

       } else { // internal node encountered

            Node234 *next;
            int index;
            
            if (current->NodeDescentSearch(key, index, next) ) {// return if key is already in tree
                
                return;
            } 

            // set current to next   
            current = next;  
       }
    }

    // Make sure key is not in a leaf node that is 2- or 3-node.
    //--if (current->keys[0] == key || (current->totalItems == 2 && current->keys[1] == key)) {
    if ((!current->isFourNode() && current->keys[0] == key) || (current->isThreeNode() && current->keys[1] == key)) {

        return;
    } 
 
    // current node is now a leaf and it is not full (because we split all four nodes while descending).
    current->insertKey(key); 
}
/* 
 *  Split pseudocode: 
 *  
 *  Upon encountering a full node (searching for a place to insert…):
 *  
 *  1. We move the largest key into a newly allocated 2-node
 *  2. We convert *pnode into a 2-node, holding its smallest key, by setting totalItems to 1. 
 *  3. We move the middle key up to the parent( which we know is not a 4-node; else it too would have been split)
 *  4. The two left-most children of the former 4-node become the left and right children of the 2-node holding the smallest key.
 *  5. The two right-most children of the former 4-node are move to become the left and right children of the 2-node holding the largest key.
 *  6. Insert new data item into the original leaf node.
 *  
 */ 
template<typename K> void Tree234<K>::split(Node234 *pnode) noexcept
{
    // remove two largest (of three total) keys...
        
    K itemC = pnode->keys[2];
    K itemB = pnode->keys[1]; 
    
    pnode->totalItems = 1; // This effective removes all but the smallest key from node.
    
    std::unique_ptr<Node234> newRight{std::make_unique<Node234>(itemC) }; // Move largest key to what will be the new right child of split node.

    /* Note: The "bool operator()" of unique_ptr tests whether a pointer is being managed, whether get() == nullptr. */
    if (pnode->children[2] && pnode->children[3]) { // If neither are nullptr
       
        /* connectChild() same as:
         *
         * newRight->children[0] = std::move(node->children[2]);
         * newRight->children[0]->parent = newRight; 
         * newRight->children[1] = std::move(node->children[3]);
         * newRight->children[1]->parent = newRight; 
         *
         */  
        newRight->connectChild(0, pnode->children[2]); // set its left child to the 3rd child of node 

        newRight->connectChild(1, pnode->children[3]); // set its right child to the 4th child of node
                  
        pnode->children[2] = nullptr;
        pnode->children[3] = nullptr;
    }

    /* node's left and right children will be the two left most children of the node being split. 
     * but first set node's two rightmost children to nullptr */

    // if this is the root,
    if(pnode == root.get()) { 

        /* make new root two node using node's middle value */  
        
       /*
        * Since the move version of operator=(unique_ptr<t>&&) deletes the managed pointer, we must first call release(); 
        * otherwise, node, which is root, the soon-to-be prior root, will be deleted. 
        */ 
        Node234 *prior_root = root.release(); // This sets root to zero.
      
        root = std::move(std::make_unique<Node234>(itemB)); 
         
        /* make new root two node using node's middle value, which we make root's left-most child */  
        root->children[0] = std::move(std::unique_ptr<Node234>{pnode}); 
        root->children[0]->parent = root.get(); 
        
        root->children[1] = std::move(newRight); 
        root->children[1]->parent = root.get(); 

    }  else {       

        Node234 *parent = pnode->getParent(); 
    
        int insert_index = parent->insertKey(itemB); // insert itemB into parent, and using its inserted index...
    
        int last_index = parent->totalItems - 1;
    
        // ...move parent's connections right, starting from its last child index and stopping just before insert_index.
        for(auto i = last_index; i > insert_index; i--)  {
    
            parent->connectChild(i + 1, parent->children[i]);       
        }
    
        /* 
         * ...and make newRight the 
         */ 
    
        parent->connectChild(insert_index + 1,  newRight);
    }

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

         bool found = root->NodeDescentSearch(key, index, next);

         if (found) { 

           // *
           // * Remove key from root, when root is a leaf. This will also shift the in-order successor into
           // * its location.
            
            root->removeKey(index);

            if (root->totalItems == 0) {

                root.reset(); // delete root 
                root  = nullptr;
            }  
         }
 
         return found;

   } else {
 
       return remove(key, root.get()); 
  }
}
/*
 * This pseudo code is taken from pages 50-53 of: www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *
 * Deletion is similar to 2-3 trees: We "swap" the item to be deleted with its in-order successor, which
 * is always in a leaf node. "Swap" means we overwrite the item to be deleted with its in-order successor and then
 * remove the in-order successor from the leaf node.
 *
 * There is a problem, however: if the in-order successor is a 2-node leaf, this leaves an empty leaf node, resulting in an
 * unbalanced tree. To prevent this, as we descend the tree we turn 2-nodes (other than the root) into 3-nodes or
 * 4-nodes. 
 *
 * There are two cases to consider:  
 *
 * Case 1: If an adjacent sibling has 2 or 3 items (and the parent is a 3- or 4-node), we "steal" an item from sibling by
 * rotating items and moving subtree. See slide #51 at www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *         
 * Case 2: If each adjacent sibling (there are at most two) has only one item (and parent is a 3- or 4-node),
 * we fuse together the two, plus an item from parent, forming a 4-node and shifting the children appropriately. See
 * slide 52 of www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 * 
 * This technique is also explained and illustrated with several examples at pages 64-66 of
 * http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf 
 *
 * and at:
 * 
 * http://www.cs.toronto.edu/~krueger/cscB63h/lectures/tut04.txt 
 * http://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf
 *
 */

// TODO: Can this be simplified. It is quite convoluted because side effects of other member functions need to be checked, and this is done in way
// that is not very readable. There are lots of checks, like that of checking the node's keys and setting lots of flags to track these checks.
template<typename K> bool Tree234<K>::remove(K key, Node234 *current) 
{
   Node234 *next = nullptr;
   Node234 *found_node = nullptr;
   int found_index;

   /* Search, looking for key, converting 2-nodes to 3- or 4-nodes as encountered */

   while(true) {

       if (current == nullptr) {
              
            return false;

       } else if (current != root.get() && current->isTwoNode()) {

            // convert 2-node into 3- or 4-node 
            current = convertTwoNode(current); 
      
       } else if (current->NodeDescentSearch(key, found_index, next)) { // ...search for item in current node. 

              found_node = current;
              break; // we found it.  

       } else {
          // ... If not found, continue to descend. 
           current = next; 
       }
    }

    // Invariant checking: this should never happen. 
    if (found_index + 1 > found_node->totalItems) {

         throw std::logic_error(std::string("Bug found: There is a logic error in Tree234<K?::remove(Key k, Node234 *current"));
    }

    // using found_index and node type, get the child pointer to follow in the search for the in-order
    // successor 
    Node234 *in_order_successor;
    
    if (!found_node->isLeaf()) {// If key found in an internal node, search for in order successor. 
    
         // The next largest item with be the smallest item, the left most left node, in the subtree rooted at
         // found_node->children[found_index + 1].
         Node234 *prospective_in_order_successor = found_node->children[found_index + 1].get(); 
        
         /* 
          * Traverse down the left-most branch until we find a leaf.
          *  
          *  Note: if prospective_in_order_successor is a 2-node, the key (in found_node->keys[found_index]) may get moved down
          *  (from the parent) to the child after the 2-node has been converted to a 3- or 4-node by doRotation(), or the key may
          *  have shifted within found_node (to keys[1]) if fuseWithChildren() gets called. 
          */ 
         bool check_if_key_moved = true; // TODO: Try to get rid of this flag!!
         
         while (prospective_in_order_successor != nullptr) { 

             in_order_successor = prospective_in_order_successor;
        
             if (in_order_successor->isTwoNode()) {

                   Node234 *convertedNode = convertTwoNode(in_order_successor);

                   int index;
                                  
                   if (convertedNode == found_node) { // fuseWithSiblings() was called. This only happens when leaves are fused with root.
                             
                         found_node->findKey(key, found_index);

                         if (found_node->isLeaf()) { // This should always be true...

                            in_order_successor = found_node;
                            break;

                         } else { //..but this is extra insurance.

                             prospective_in_order_successor = found_node->children[found_index + 1].get();   
                         }

                    /*
                     * else Check if key moved.
		     */
                   } else if (!check_if_key_moved || (found_index < found_node->totalItems && found_node->keys[found_index] == key) )  { 

                        // We no longer need check if the key moved to 
                       check_if_key_moved  = false;
                       prospective_in_order_successor = convertedNode->children[0].get();
                   
             /* 
              * If a rotation occurred, the key may have moved to the converted 2-node (now a 3-node). Also, if a fusion of the 2-node
              * with its adjacent sibling 2-node sibling, together with a parent key, it again may have moved to the converted node.
              */      
                   } else if ( convertedNode->findKey(key, index) )  { /* It is either in the converted node ...
                                                                                 ... or in its parent, found_node. */
                        found_node = convertedNode;
                        found_index = index;
                        prospective_in_order_successor = convertedNode->children[index + 1].get(); // root of subtree with next largest key 
                   }         

             } else {

                  check_if_key_moved = false; 
                  prospective_in_order_successor = in_order_successor->children[0].get(); // it was not converted, so take smallest child.
             } 
         }

    } else { // else we are at a leaf and the in_order_successor is in the same node.

         in_order_successor = found_node;
    }
    
    // We are now at the in-order successor leaf node. 

    // Remove in-order successor from leaf and overwrite key to be deleted with it. 
    // First, check if found_node is internal node
    if (!found_node->isLeaf() && found_node != in_order_successor) { // <-- the found_node may be the only node

	    found_node->keys[found_index] = in_order_successor->removeKey(0);  // <-- wrong

    } else if (found_index < found_node->totalItems) { 

            // The in-order in_order_successor is in same leaf node, so simply remove it, which will also overwrite its position by
            // shifting all keys to right of it one position left.
            in_order_successor->removeKey(found_index);

            /* 
             * Note: The line above is equivalent to doing:
             *   found_node->keys[found_index] = in_order_successor->keys[found_index + 1];
             *   found_node->totalItems--;  
             */
    } 

    // Note, we did not need to disconnect a child because we are at a leaf node.
        
    return true;  
}
/*
 * input preconditions: node is 2-node.
 * output: node is converted into either a 3- or a 4-node.
 *
 * Code follows pages 51-53 of: www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 * and pages 64-66 of http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf
 *
 * Case 1: If an adjacent sibling--there are at most two--has 2 or 3 items, "steal" an item from the sibling by
 * rotating items and shifting children. See slide 51 of www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *         
 * Case 2: If each adjacent sibling has only one item (and parent is a 3- or 4-node), we take its sole item together with an item from
 * parent and fuse them into the 2-node, making a 4-node. If the parent is also a 2-node (this only happens in the case of the root),
 * we fuse the three together into a 4-node. In either case, we shift the children as required.
 * 
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::convertTwoNode(Node234 *node)  noexcept
{                                                                         
   Node234 *convertedNode;
   Node234 *parent = node->getParent();

   int parentKeyTotal = parent->totalItems;
   int parentChildrenTotal = parentKeyTotal + 1;
   
   // First, we find the index of the 2-node such that parent->children[node2_index] == node, by comparing node's key to its
   // parent's keys.
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

   if (has3or4NodeSibling == false) { // All adjacent siblings are also 2-nodes...

       // Determine, based on whether the parent is a two node, whether to rotate or fuse. 
       // Check if its parent 2-node (or 3- or 4-node).
       
       if (parent->isTwoNode()) { //... as is the parent, which must be root; otherwise, it would have already been converted.
         
	     convertedNode = parent->fuseWithChildren();

        } else { // parent is 3- or 4-node and there a no 3- or 4-node adjacent siblings 

             convertedNode = fuseSiblings(parent, node2_index, sibling_index);
        }

   } else { // it has a 3- or 4-node sibling.

        convertedNode = doRotation(parent, node2_index, sibling_index);
   }
   
   return convertedNode;
}
/*
 * precondition: node is a 2-node. Its children are both 2-nodes.
 * output: 4-node resulting from fusing of the two 2-nodes. 
 * pseudo code: 
 * 1. Absorbs its children's keys as its own. 
 * 2. Makes its grandchildren its children and deletes its former, now orphaned child nodes.
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::Node234::fuseWithChildren() noexcept
{
  // move key of 2-node 
  keys[1] = keys[0];

  // absorb children's keys
  keys[0] = children[0]->keys[0];    
  keys[2] = children[1]->keys[0];       

  totalItems = 3;
  
  std::unique_ptr<Node234> leftOrphan = std::move(children[0]); // so we can delete them later
  std::unique_ptr<Node234> rightOrphan = std::move(children[1]); // so we can delete them later
    
  // make grandchildren the children.
  connectChild(0, leftOrphan->children[0]); // connectChild() will also reset parent pointer of right parameter.
  connectChild(1, leftOrphan->children[1]);
  connectChild(2, rightOrphan->children[0]); 
  connectChild(3, rightOrphan->children[1]);
    
  return this;  
  
}// <-- automatic deletion of leftOrphan and rightOrphan because they are managed unique_ptr<Node234> pointers
/*
 * preconditions:
 * 1. sibling_id is a 3- or 4-node of parent. 
 * 2. node2_id is the node to convert from a 2-node to a 3-node
 * Returns:
 * A parent key is stolen and inserted into parent->children[node2_id], making it a 3-node. A key from the sibling replaces
 * the stolen parent key.
 * The siblings orphaned child is adopted by the converted 2- now 3-node. 
 * The converted 2-node is returned.
 */
template<typename K> inline typename Tree234<K>::Node234 * Tree234<K>::doRotation(Node234 *parent, int node2_id, int sibling_id) noexcept
{
  Node234 *psibling = parent->children[sibling_id].get();

  Node234 *p2node = parent->children[node2_id].get();

  /* 
   * First we get the index of the parent's key value such that either 
   *
   *   parent->children[node2_index]->keys[0]  <  parent->keys[index] <  parent->children[sibling_id]->keys[0] 
   *     
   *  or  
   *
   *    parent->children[sibling_id]->keys[0]  <  parent->keys[index] <  parent->children[node2_index]->keys[0]
   *
   * by taking the minimum of the indecies.
   */

  int parent_key_index = std::min(node2_id, sibling_id); 

  if (node2_id > sibling_id) { /* If sibling is to the left, then
                                *
                                *  parent->children[sibling_id]->keys[0] < parent->keys[index] < parent->children[node2_index]->keys[0]
                                * 
                                * and we do a right rotation
                                */ 

      return rightRotation(p2node, psibling, parent, parent_key_index);

  } else { /* else sibling is to the right and 
            *    parent->children[node2_index]->keys[0]  <  parent->keys[index] <  parent->children[sibling_id]->keys[0] 
            * therefore do a left rotation
  	    */ 

      return leftRotation(p2node, psibling, parent, parent_key_index);
  }
}
/* 
 * Sibling is to the left, therefore: parent->children[sibling_id]->keys[0] < parent->keys[index] < parent->children[node2_index]->keys[0]
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::rightRotation(Node234 *p2node, Node234 *psibling, Node234 *parent, int parent_key_index) noexcept
{    
  // Add the parent's key to 2-node, making it a 3-node

  // 1. But first shift the 2-node's sole key right one position
  p2node->keys[1] = p2node->keys[0];      

  p2node->keys[0] = parent->keys[parent_key_index];  // 2. Now bring down parent key

  p2node->totalItems = to_int(Tree234<K>::Node234::NodeMaxItems::three_node); // 3. increase total items

  int total_sibling_keys = psibling->totalItems; 

  // 4. disconnect right-most child of sibling
  std::unique_ptr<Node234> pchild_of_sibling = psibling->disconnectChild(total_sibling_keys); 

  K largest_sibling_key = psibling->removeKey(total_sibling_keys - 1); // remove the largest, the right-most, sibling's key.

  parent->keys[parent_key_index] = largest_sibling_key;  // 5. overwrite parent item with largest sibling key

  p2node->insertChild(0, pchild_of_sibling); // add former right-most child of sibling as its first child

  return p2node;
}
/* sibling is to the right therefore: parent->children[node2_index]->keys[0]  <  parent->keys[index] <  parent->children[sibling_id]->keys[0] 
 * Do a left rotation
 */ 
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::leftRotation(Node234 *p2node, Node234 *psibling, Node234 *parent, int parent_key_index) noexcept
{
  // pnode2->keys[0] doesn't change.
  p2node->keys[1] = parent->keys[parent_key_index];  // 1. insert parent key making 2-node a 3-node

  p2node->totalItems = to_int(Tree234<K>::Node234::NodeMaxItems::three_node);// 3. increase total items

  std::unique_ptr<Node234> pchild_of_sibling = psibling->disconnectChild(0); // disconnect first child of sibling.

  // Remove smallest key in sibling
  K smallest_sibling_key = psibling->removeKey(0);

  parent->keys[parent_key_index] = smallest_sibling_key;  // overwrite parent item with it.

  // add former first child of silbing as right-most child of our 3-node.
  p2node->insertChild(p2node->totalItems, pchild_of_sibling); 

  return p2node;
}
/*
 * Preconditions: 
 * 1. parent is a 3- or 4-node. 
 * 2. parent->children[sibling_index] is the 2-node sibling to be fused, along with a parent key,
 *    into the 2-node, to make a 4-node.
 * 3. parent->childen[node2_id] is the 2-node being converted (into a 3- or 4-node).
 *
 * Returns: node2_id is converted into 4-node by adding sibling's sole key together with a key "stolen" from the parent. The 
 * siblings children are connected to the former 2- now 4-node. The parent becomes a 2-node, if it was a 3-node; or a 3-node, if it 
 * was a 4-node.
 */
template<typename K> typename Tree234<K>::Node234 *Tree234<K>::fuseSiblings(Node234 *parent, int node2_index, int sibling_index) noexcept
{
  Node234 *psibling;

  Node234 *p2node = parent->children[node2_index].get();

  // First get the index of the parent's key value to be stolen and added into the 2-node
  int parent_key_index = std::min(node2_index, sibling_index); 

  if (node2_index > sibling_index) { // sibling is to the left: 

      /* Adjust parent:
         1. Remove parent key (and shift its remaining keys and reduce its totalItems)
         2. Reset parent's children pointers after removing sibling.
       * Note: There is a potential insidious bug: disconnectChild depends on totalItems, which removeKey() reduces. Therefore,
       * disconnectChild() must always be called before removeKey().
       */
      std::unique_ptr<Node234> psibling = parent->disconnectChild(sibling_index); // This will do #2. 
      
      K parent_key = parent->removeKey(parent_key_index); //this will do #1

      // Now, add both the sibling's and parent's key to 2-node

      // 1. But first shift the 2-node's sole key right two positions
      p2node->keys[2] = p2node->keys[0];      

      p2node->keys[1] = parent_key;  // 2. bring down parent key

      p2node->keys[0] = psibling->keys[0]; // 3. insert adjacent sibling's sole key. 
 
      p2node->totalItems = 3; // 3. increase total items

      // Add sibling's children to the former 2-node, now 4-node...
           
      p2node->children[3] = std::move(p2node->children[1]);  // ... but first shift its children right two positions
      p2node->children[2] = std::move(p2node->children[0]);

      // Insert sibling's first two child. Note: connectChild() will also reset the parent pointer of these children (to be p2node). 
      p2node->connectChild(1, psibling->children[1]); 
      p2node->connectChild(0, psibling->children[0]); 

   // <-- automatic deletion of psibling in above after } immediately below
  } else { // sibling is to the right:

      
      /* Next adjust parent:
         1. Remove parent key (and shift its remaining keys and reduce its totalItems)
         2. Reset its children pointers 
       * Note: There is a potential insidious bug: disconnectChild depends on totalItems, which removeKey reduces. Therefore,
       * disconnectChild() must always be called before removeKey(), or children will not be shifted correctly.
       */
      std::unique_ptr<Node234> psibling = parent->disconnectChild(sibling_index); // this does #2
      
      K parent_key = parent->removeKey(parent_key_index); // this will #1

      // p2node->key[0] is already in the correct position
      p2node->keys[1] = parent_key;  // 1. bring down parent key

      p2node->keys[2] = psibling->keys[0];// 2. insert sibling's sole key.
 
      p2node->totalItems = 3; // 3. make it a 4-node

      // Insert sibling's last two child. Note: connectChild() will also reset the parent pointer of these children (to be p2node). 

      p2node->connectChild(3, psibling->children[1]);  // Add sibling's children
      p2node->connectChild(2, psibling->children[0]);  
      
  } // <-- automatic deletion of psibling

  //delete psibling; // delete orphaned sibling. NOW NOT needed due to unique_ptr

  return p2node;
} 
#endif
