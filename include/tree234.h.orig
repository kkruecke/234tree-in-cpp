#ifndef TREE234_H
#define	TREE234_H
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <array>
#include <queue>
#include <stack>
#include <sstream>
#include <exception>
#include <iosfwd>
#include <string>
#include <iostream>
#include "level-order-invariant-report.h"
#include "level-order-display.h"

// fwd declarations
template<typename Key, typename Value> class tree234;    
template<typename Key, typename Value> class Node; 

class DebugPrinter; 
    
template<typename Key, typename Value> class tree234 {
    
   union KeyValue { // A union is used to hold to two types of pairs, one of which (pair) has a non-const Key; the other has a const Key.
       friend class tree234<Key, Value>;
   
       std::pair<Key, Value>        _pair;  // ...this eliminates constantly casting of const_cast<Key>(p.first) = some_noconst_key;
       std::pair<const Key, Value>  _constkey_pair;  // but always return this member of the union.

       KeyValue() {} 
       KeyValue(Key key, const Value& value) : _pair{key, value} {}
       
       KeyValue(const KeyValue& lhs) : _pair{lhs._pair.first, lhs._pair.second} {}
       
       KeyValue(Key k, Value&& v) : _pair{k, std::move(v)} {} 
   
       KeyValue(KeyValue&& lhs) :  _pair{move(lhs._pair)} {}
   
       KeyValue& operator=(const KeyValue& lhs) noexcept;  
       KeyValue& operator=(KeyValue&& lhs) noexcept; 

       constexpr const Key&  key()  { return _pair.first; }
       constexpr const Key& key() const { return _constkey_pair.first; }

       constexpr Value&  value()  { return _pair.second; }
       constexpr const Value& value() const { return _constkey_pair.second; }

     public:    
       constexpr const std::pair<Key, Value>& pair() const { return _pair; }
       constexpr std::pair<Key, Value>& pair() { return _pair; }
        
       constexpr const std::pair<const Key, Value>& constkey_pair() const { return _constkey_pair; }
       constexpr       std::pair<const Key, Value>& constkey_pair() { return _constkey_pair; }

       friend std::ostream& operator<<(std::ostream& ostr, const KeyValue& key_value)
       {
          ostr << "{" << key_value._pair.first << ',' <<  key_value._pair.second <<  "}, ";
          return ostr;
       }
   };
 
  public:
      
   class Node { // public nested node class Tree<Key, Value>::Node
     private:  
       friend class tree234<Key, Value>;             
       friend class DebugPrinter;
       static const int MAX_KEYS;   

       enum class NodeType : int { two_node=1, three_node=2, four_node=3 };
    
       Node *parent; /* parent is only used for navigation of the tree. It does not own the memory
                           it points to. */
    
       int totalItems; /* If 1, two node; if 2, three node; if 3, four node. */   
    
       std::array<KeyValue, 3> keys_values; // This implementation does not have an associated value for the key.
       
       /*
        * For 2-nodes, children[0] is left pointer, children[1] is right pointer.
        * For 3-nodes, children[0] is left pointer, children[1] the middle pointer, and children[2] the right pointer.
        * And so on for 4-nodes.
        */
    
       std::array<std::unique_ptr<Node>, 4> children;
       
       constexpr Node *getParent() noexcept; 
       int getChildIndex() const noexcept;
    
       /* 
        * Returns true if key is found in node and sets index so pNode->keys_values[index] == key
        * Returns false if key is if not found, and sets next to the next in-order child.
        */
       bool SearchNode(Key key, int& index, int& child_index, const Node *&next) const noexcept;
    
       void insert(KeyValue&& key_value, std::unique_ptr<Node>& newChild) noexcept;

       int insertKeyValue(Key key, const Value& value) noexcept;
       
       // Remove key, if found, from node, shifting remaining keys_values to fill its gap.
       KeyValue removeKeyValue(int index) noexcept; 
    
       void connectChild(int childNum, std::unique_ptr<Node>& child) noexcept;
       /*
        * Removes child node (implictly using move ctor) and shifts its children to fill the gap. Returns child pointer.
        */  
       std::unique_ptr<Node> disconnectChild(int child_index) noexcept; 
    
       void insertChild(int childNum, std::unique_ptr<Node> &pChild) noexcept;
    
       /* 
        * Called during remove(Key keym, Node *).
        * Merges the 2-node children of a parent 2-node into the parent, making the parent a 4-node. The parent, then, adopts the "grand children", and the children
        * after having been adopted by the parent are deallocated. 
        */
       Node *fuseWithChildren() noexcept; 

       public:
             
           Node() noexcept;

           explicit Node(Key small, const Value& value, Node *parent=nullptr) noexcept;

           explicit Node(const KeyValue& key_value, Node *parent=nullptr) noexcept;

           explicit Node(const KeyValue&, const KeyValue&, Node *parent=nullptr) noexcept;
           
           explicit Node(const KeyValue&, const KeyValue&,  const KeyValue&, Node *parent=nullptr) noexcept;

           explicit Node(KeyValue&& key_value) noexcept; 
           
           constexpr const Node *getParent() const noexcept;
    
           constexpr int getTotalItems() const noexcept;
           constexpr int getChildCount() const noexcept;

           constexpr const Node *getRightMostChild() const noexcept { return children[getTotalItems()].get(); }

           // method to help in debugging
           void printKeys(std::ostream&);

           constexpr Key& key(int i ) { return keys_values[i].key(); } 

           constexpr const Key& key(int i ) const { return keys_values[i].key(); } 

           int getIndexInParent() const;

           constexpr Value& value(int i ) { return keys_values[i].value(); } 
           const Value& value(int i ) const { return keys_values[i].value(); } 
    
           bool findKey(Key key, int& index) const noexcept;
           constexpr Key getKey(int i) const;
           constexpr bool isLeaf() const noexcept; 
           constexpr bool isTwoNode() const noexcept;
           constexpr bool isThreeNode() const noexcept;
           constexpr bool isFourNode() const noexcept;
           constexpr bool isEmpty() const noexcept; 

           std::ostream& print(std::ostream& ostr) const noexcept;
   
           friend std::ostream& operator<<(std::ostream& ostr, const Node& node234)
           { 
             return node234.print(ostr);
           }
  }; // end class Tree<Key, Value>::Node  

 private:

   friend class DebugPrinter;

    std::unique_ptr<Node>  root; 

    int  tree_size; // adjusted by insert(), remove(), operator=(const tree234...), move ctor

    bool DoSearch(Key key, const Node *&location, int& index) noexcept;

    // implementations of the public depth-frist traversal methods    
    template<typename Functor> void DoInOrderTraverse(Functor f, const std::unique_ptr<Node>& root) const noexcept;

    template<typename Functor> void DoPostOrderTraverse(Functor f,  const std::unique_ptr<Node>& root) const noexcept;

    template<typename Functor> void DoPreOrderTraverse(Functor f, const std::unique_ptr<Node>& root) const noexcept;

    void DestroyTree(std::unique_ptr<Node> &root) noexcept; 

    void CloneTree(const std::unique_ptr<Node>& src_node, std::unique_ptr<Node> &dest_node, const Node *parent) noexcept; // called by copy ctor

    void split(Node *node) noexcept;  // called during insert(Key key) to split 4-nodes encountered.

    // Called during remove(Key key)
    bool remove(Key key, const Node *location); 

    // Called during remove(Key key, Node *) to convert two-node to three- or four-node during descent of tree.
    Node *convertTwoNode(Node *node) noexcept;

    // These methods are called by convertTwoNode()
    Node *fuseSiblings(Node *parent, int node2_id, int sibling_id) noexcept;

    Node *leftRotation(Node *p2node, Node *psibling, Node *parent, int parent_key_index) noexcept;

    Node *rightRotation(Node *p2node, Node *psibling, Node *parent, int parent_key_index) noexcept;

    // Non recursive in order traversal of tree methods
    std::pair<const Node *, int> getSuccessor(const Node *current, int key_index) const noexcept;
    std::pair<const Node *, int> getPredecessor(const Node *current, int key_index) const noexcept;

    std::pair<const Node *, int> getInternalNodeSuccessor(const Node *pnode,  int index_of_key) const noexcept;
    std::pair<const Node *, int> getInternalNodePredecessor(const Node *pnode,  int index_of_key) const noexcept;

    std::pair<const Node *, int> getLeafNodeSuccessor(const Node *pnode, int key_index) const;
    std::pair<const Node *, int> getLeafNodePredecessor(const Node *pnode, int key_index) const;
   
    // Returns node with smallest value of tree whose root is 'root'
    const Node *min(const Node* root) const noexcept; 
    const Node *max(const Node* root) const noexcept; 
    
    std::pair<const Node *, int> getRemoveSuccessor(Key key, const Node *&pfound_node, int& key_index) noexcept;

    int  height(const Node *pnode) const noexcept;
    
    int  depth(const Node *pnode) const noexcept;
    bool isBalanced(const Node *pnode) const noexcept;

  public:

    using value_type      = std::pair<const Key, Value>; 
    using difference_type = long int;
    using pointer         = value_type*; 
    using reference       = value_type&; 
    using node_type       = Node; 

     explicit tree234() noexcept : root{}, tree_size{0} { } 

     tree234(const tree234& lhs) noexcept; 
     tree234(tree234&& lhs) noexcept;     // move constructor

     tree234& operator=(const tree234& lhs) noexcept; 
     tree234& operator=(tree234&& lhs) noexcept;    // move assignment

     tree234(std::initializer_list<std::pair<Key, Value>> list) noexcept; 
     
     void test_invariant() const noexcept; 
 
     constexpr int size() const;
     int getHeight() const noexcept; // get depth of tree from root to leaf.

    ~tree234() noexcept; 

    // Breadth-first traversal
    template<typename Functor> void levelOrderTraverse(Functor f) const noexcept;

    // Depth-first traversals
    template<typename Functor> void inOrderTraverse(Functor f) const noexcept;

    template<typename Functor> void iterativeInOrderTraverse(Functor f) const noexcept;

    template<typename Functor> void postOrderTraverse(Functor f) const noexcept;
    template<typename Functor> void preOrderTraverse(Functor f) const noexcept;
   
    // Used during development and testing 
    template<typename Functor> void debug_dump(Functor f) noexcept;

    bool find(Key key) noexcept;

    void insert(Key key, const Value &) noexcept; 
    
    void insert(const value_type& pair) noexcept { insert(pair.first, pair.second); } 

    bool remove(Key key);

    void printlevelOrder(std::ostream&) const noexcept;
    
    void printInOrder(std::ostream&) const noexcept;
    
    void printPreOrder(std::ostream&) const noexcept;
    
    void printPostOrder(std::ostream&) const noexcept;

    void test(Key key);

    bool isEmpty() const noexcept;

    class iterator : public std::iterator<std::bidirectional_iterator_tag, typename tree234<Key, Value>::value_type> { 
                                                 
       friend class tree234<Key, Value>;   

      private:
         tree234<Key, Value>& tree; 

         const Node *current;
         const Node *cursor;
	 int key_index;
         
         int getChildIndex(const typename tree234<Key, Value>::Node *p) const noexcept;

         std::pair<const typename tree234<Key, Value>::Node *, int> findLeftChildAncestor() noexcept;

         iterator& increment() noexcept; 

         iterator& decrement() noexcept;

         iterator(tree234<Key, Value>& lhs, int i);  // called by end()
      public:

         explicit iterator(tree234<Key, Value>&); 

         iterator(const iterator& lhs); // What does explicit do?

         iterator(iterator&& lhs); 
 
         bool operator==(const iterator& lhs) const;
         
         constexpr bool operator!=(const iterator& lhs) const { return !operator==(lhs); }
         
         constexpr reference dereference() noexcept 
         { 
             return cursor->keys_values[key_index].constkey_pair(); 
         } 

         constexpr const std::pair<const Key, Value>& dereference() const noexcept 
         { 
             return cursor->keys_values[key_index].constkey_pair(); 
         }
         
         iterator& operator++() noexcept; 
         iterator operator++(int) noexcept;

         iterator& operator--() noexcept;
         iterator operator--(int) noexcept;
         
         std::pair<const Key, Value>& operator*() noexcept { return dereference(); } 

         const std::pair<const Key, Value>& operator*() const noexcept { return dereference(); }
         
         typename tree234<Key, Value>::KeyValue *operator->() noexcept;
    };

    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const value_type> {

       friend class tree234<Key, Value>;   

      private:
        iterator iter; 
         explicit const_iterator(const tree234<Key, Value>& lhs, int i);
      public:
         
         explicit const_iterator(const tree234<Key, Value>& lhs);

         const_iterator(const const_iterator& lhs);
         const_iterator(const_iterator&& lhs); 

         const_iterator(const typename tree234<Key, Value>::iterator& lhs); // this ctor provide implicit conversion from iterator to const_iterator     

         bool operator==(const const_iterator& lhs) const;
         bool operator!=(const const_iterator& lhs) const;
         
         const_iterator& operator++() noexcept;
         const_iterator operator++(int) noexcept;
         const_iterator& operator--() noexcept;
         const_iterator operator--(int) noexcept;

         const std::pair<const Key,Value>&  operator*() const noexcept 
         {
           return iter.dereference(); 
         } 

         const std::pair<const Key, Value> *operator->() const noexcept { return &this->operator*(); } 
    };

    iterator begin() noexcept;  
    iterator end() noexcept;  
  
    const_iterator begin() const noexcept;  
    const_iterator end() const noexcept;  
  
    using  reverse_iterator       = std::reverse_iterator<typename tree234<Key, Value>::iterator>; 
    using  const_reverse_iterator = std::reverse_iterator<typename tree234<Key, Value>::const_iterator>;

    reverse_iterator rbegin() noexcept;  
    reverse_iterator rend() noexcept;  
 
    const_reverse_iterator rbegin() const noexcept;  
    const_reverse_iterator rend() const noexcept;    

    int  height() const noexcept;
    bool isBalanced() const noexcept;
};

template<class Key, class Value> inline bool tree234<Key, Value>::isEmpty() const noexcept
{
  return root == nullptr ? true : false;
}

template<typename Key, typename Value> inline typename tree234<Key, Value>::KeyValue& tree234<Key, Value>::KeyValue::operator=(const KeyValue& lhs) noexcept
{
  if (this != &lhs) { 

    pair() = lhs.pair();

  }
  return *this;
}

template<typename Key, typename Value> inline typename tree234<Key, Value>::KeyValue& tree234<Key, Value>::KeyValue::operator=(KeyValue&& lhs) noexcept
{
  if (this != &lhs) { 

    pair() = std::move(lhs.pair());

  }
  return *this;
}

template<typename Key, typename Value> const int  tree234<Key, Value>::Node::MAX_KEYS = 3; 
/*
 * Node constructors. Note: While all children are initialized to nullptr, this is not really necessary. 
 * Instead your can simply set children[0] = nullptr, since a Node is a leaf if and only if children[0] == 0'
 */
template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node()  noexcept : totalItems(0), parent(nullptr), children()
{ 
}

template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node(Key small, const Value& value, Node *parent_in)  noexcept : totalItems(1), parent(parent_in), children()
{ 
   keys_values[0].key() = small; 
   keys_values[0].value() = value;
}

template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node(const KeyValue& kv1, Node *parent_in)  noexcept : totalItems(1), parent(parent_in), children()
{ 
   keys_values[0] = kv1; 
}


template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node(const KeyValue& kv1, const KeyValue& kv2, Node *parent_in)  noexcept : totalItems(2), parent(parent_in), children()
{ 
   keys_values[0] = kv1; 
   keys_values[1] = kv2;
}

template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node(const KeyValue& kv1, const KeyValue& kv2, const KeyValue& kv3, Node *parent_in)  noexcept : totalItems(3), parent(parent_in), children()
{ 
   keys_values[0] = kv1; 
   keys_values[1] = kv2;
   keys_values[2] = kv3;
}

template<class Key, class Value> std::ostream& tree234<Key, Value>::Node::print(std::ostream& ostr) const noexcept
{
   ostr << "[";

   if (totalItems == 0) { // remove() situation when merge2Nodes() is called

       ostr << "empty"; 

   } else {

        for (auto i = 0; i < totalItems; ++i) {

            ostr << keys_values[i].key(); // or to print both keys and values do: ostr << keys_values[i];

            if (i + 1 == totalItems)  {
                continue;

            } else { 
                ostr << ", ";
            }
        }
   }

   ostr << "]";
   return ostr;
}

template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node(KeyValue&& key_value) noexcept : parent{nullptr}, totalItems{1}
{
   keys_values[0] = std::move(key_value); 
}

template<class Key, class Value> int tree234<Key, Value>::Node::getIndexInParent() const 
{
  for (int child_index = 0; child_index <= parent->totalItems; ++child_index) { // Check the address of each of the children of the parent with the address of "this".

       if (this == parent->children[child_index].get()) {
           return  child_index;
       }
  }

  throw std::logic_error("Cannot find the parent child index of the node. The node may be the tree's root or the invariant may have been violated.");
}

template<typename Key, typename Value> inline tree234<Key, Value>::tree234(const tree234<Key, Value>& lhs) noexcept 
{
 if (root == lhs.root) { // are they the same?

      return;
  }

  DestroyTree(root); // free all the nodes of the current tree 

  tree_size = lhs.tree_size;
  
  CloneTree(lhs.root, root, nullptr);
}
 
// move constructor
template<typename Key, typename Value> inline tree234<Key, Value>::tree234(tree234&& lhs) noexcept : root{std::move(lhs.root)}, tree_size{lhs.tree_size}  
{
    root->parent = nullptr;
    lhs.tree_size = 0;
}

template<typename Key, typename Value> inline tree234<Key, Value>::tree234(std::initializer_list<std::pair<Key, Value>> il) noexcept : root(nullptr), tree_size{0} 
{
    for (auto& x: il) { // simply call insert(x)
         
         insert(x.first, x.second);
    }
}

template<typename Key, typename Value> inline tree234<Key, Value>::~tree234() noexcept 
{
  DestroyTree(root);
}
/*
Finding the successor of a given node 
-------------------------------------
Requires:
    1. If position is beg, current and key_index MUST point to first key in tree. 
    2. If position is end,  current and key_index MUST point to last key in tree.
      
    3. If position is in_between, current and key_index do not point to either the first key in the tree or last key in tree. If the tree has only one node,
       the state can only be in_between if the first node is a 3-node.
    Returns:
    pair<const Node *, int>, where the Node pointer is the node with the next key and value in in-order sequence. key_index is the index into Node::keys_values[].
    Note, if the last key has already been visited, the pointer returned will be nullptr.
    Pseudo code for getting successor (from: http://ee.usc.edu/~redekopp/cs104/slides/L19_BalancedBST_23.pdf):
    If left child exists, predecessor is the right most node of the left subtree. Internal node's of a 2 3 tree always have a right branch because 2 3 trees are  balanced.
    Else walk up the ancestor chain until you traverse the first right child pointer (find  the first node who is a right child of his parent...that parent is the predecessor)
    If you get to the root w/o finding a node who is a right child, there is no predecessor
    Side effects. May set:
    1. current
    2. key_index
    3. position
 */
template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::getSuccessor(const Node *current, int key_index) const noexcept
{
  if (current->isLeaf()) { // If leaf node
     
     if (current == root.get()) { // special case: root is leaf      
 
         if (!root->isTwoNode() && key_index != (root->getTotalItems() - 1)) { 

             return std::make_pair(current, key_index + 1);
         } 
                  
         return std::make_pair(nullptr, 0); // There is no successor
 
     } else {

        return getLeafNodeSuccessor(current, key_index);
     }

  } else { // else internal node

      return getInternalNodeSuccessor(current, key_index);
  }
}

/* 
   Requires:
   1. pnode is an internal node not a leaf node.
   2. If pnode is a 3-node, key_index is 1 not 0.
   Returns:
   pointer to successor node.
Note: When a 2 3 tree node is a 3-node, it has two "right" chidren from the point of view of its first key and two "left" children from the point of view of its
second key.
 */
template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::getInternalNodeSuccessor(const typename tree234<Key, Value>::Node *pnode, int key_index) const noexcept	    
{
 // Get next right child node of pnode based on key_index.

 // Question: Does it take into account that fact that a node may have already been visited in order?
 // Get the smallest node in the subtree rooted at the rightChild, i.e., its left most node...
 for (const Node *cursor =  pnode->children[key_index + 1].get(); cursor != nullptr; cursor = cursor->children[0].get()) { // TODO: This has not been checked/ported for tree234

    pnode = cursor;
 }

 return std::make_pair(const_cast<Node *>(pnode), 0);
}
/*
 Requires:
 1. pnode is a leaf node, either a 2 or 3-node
 2. If pnode is 3-node, then key_index, the key index into pnode->keys_values[].key() must be 1, the second key. It can never be 0, the first key.
 */
template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::getLeafNodeSuccessor(const Node *pnode, int key_index) const 
{
  // Handle the easy case: a 3- or 4-node in which key_index is not the right most value in the node.
  if (!pnode->isTwoNode() && (pnode->getTotalItems() - 1) != key_index) { 

      return std::make_pair(pnode, key_index + 1); 
  }

  Node *successor = nullptr;

  int child_index = pnode->getChildIndex();
  
  int current_key = pnode->keys_values[key_index].key();

  if (pnode->parent->children[child_index].get() == pnode->parent->getRightMostChild()) { // Is pnode the right-most child of its parent? 

  /*
   pnode is the right-most child of its parent, so we must find the first ancestor--parent, grandparent, great grandparent, etc--that is in a "greater than" node.key(i), i.e., an ancestor->key(j) that is to the right of node.key(i). 
   Note: We know that if it is a 3- or 4-node, then key_index is the right most value in the node. Since a 2-node only has one value, it is by default the "right most".
   To find this ancester, we ascend the tree until we encounter the first ancestor that is not a right-most child.  We select its left-most value since it is the smallest value that is larger than pnode->key(key_index).
   */
       const Node *parent = pnode->parent;
       
       // Ascend the parent pointer as long as the node continues to be the right most child (of its parent). 
       for(;pnode == parent->getRightMostChild(); parent = parent->parent)  { 
       
           // pnode is still the right most child, but if it is also the root, then, there is no successor (because pnode was the largest node in the tree). 
           if (parent == root.get()) {
              
               return std::make_pair(nullptr, 0);  // To indicate "no-successor" we return the pair: {nullptr, 0}.
           }
       
           pnode = parent;
       }
       // We select its left-most value since it is the smallest value that is larger than pnode->key(key_index).
       int successor = 0;

       for (; successor < parent->getTotalItems() && current_key > parent->keys_values[successor].key(); ++successor);
         
       return std::make_pair(parent, successor);
       

  } else { 
      /* 
        ...otherwise, we know that pnode that for 2, 3 and 4-nodes pnode is NOT the right most child of its parent (and it is a leaf). We know that if it is a 2, 3, or 4-node, it is not the right most. 
        We also know that key_index is the right most value of pnode--right? So need to ascertain the index next_index such that pnode->parent->key(next_index) > pnode->key(key_index). How can next_index be calculated
        from the input parameters and this use-case?
        Comment: We can view a 3-node as two catenated 2-nodes in which the the middle child is shared between these two "2-nodes", like this
      
           [3,       5]  
           /  \     / \
          /    \   /   \
        [1, 2]  [3, 4]  [6]
        While a 4-node can be viewed as three catenated 2-nodes in which the two middle child are shared
          
           [2,   4,   6]  
          /  \  / \  / \
        [1]  [3]   [5]  [7] 
        If the leaft node is a 3- or 4-node, we already know (from the first if-test) that the current key is the last, ie, pnode->getTotalItems() - 1. So the we simply go up on level to find the in order successor.    
        We simply need to determine the index in the parent to choose.
      */

     if (child_index > static_cast<int>(Node::NodeType::four_node)) {

         throw std::logic_error("child_index was not between 0 and 3 in getLeafNodeSuccessor()");
     }

     return std::make_pair(pnode->parent, child_index);
  }  
}


// copy assignment
template<typename Key, typename Value> inline tree234<Key, Value>& tree234<Key, Value>::operator=(const tree234& lhs) noexcept 
{
  if (root == lhs.root) { // are they the same?

       return *this;
  }

  DestroyTree(root); // free all nodes and then clone lhs.

  tree_size = lhs.tree_size;         

  CloneTree(lhs.root, root, nullptr);

  return *this;
}


template<typename Key, typename Value> inline void tree234<Key, Value>::Node::printKeys(std::ostream& ostr)
{
  ostr << "["; 

  for(auto i = 0; i < getTotalItems(); ++i) {

      ostr << getKey(i);

      if (i < getTotalItems() - 1)       {

         ostr << ", ";
      } 
  }

  ostr << "]";
}

template<typename Key, typename Value> inline constexpr int tree234<Key, Value>::Node::getTotalItems() const noexcept
{
   return totalItems; 
}

template<typename Key, typename Value> inline constexpr Key tree234<Key, Value>::Node::getKey(int i) const 
{
    if (0 <= i && i < getTotalItems()) {
        
        return keys_values[i].key();
    }
    
    throw std::range_error{"key of Node not in range"};     
}

template<typename Key, typename Value> inline bool tree234<Key, Value>::Node::findKey(Key key, int& index) const noexcept
{
   for(index = 0; index < totalItems; ++index) {
       
       if (keys_values[index].key() == key) {
           
           return true;
       }
   }   

   return false;
}

template<typename Key, typename Value> inline constexpr int tree234<Key, Value>::Node::getChildCount() const noexcept
{
   return totalItems + 1; 
}

template<typename Key, typename Value> inline constexpr bool tree234<Key, Value>::Node::isTwoNode() const noexcept
{
   return (totalItems == static_cast<int>(NodeType::two_node)) ? true : false;
}

template<typename Key, typename Value> inline constexpr bool tree234<Key, Value>::Node::isThreeNode() const noexcept
{
   return (totalItems == static_cast<int>(NodeType::three_node)) ? true : false;
}

template<typename Key, typename Value> inline constexpr bool tree234<Key, Value>::Node::isFourNode() const noexcept
{
   return (totalItems == static_cast<int>(NodeType::four_node)) ? true : false;
}

template<typename Key, typename Value> inline constexpr bool tree234<Key, Value>::Node::isEmpty() const noexcept
{
   return (totalItems == 0) ? true : false;
}

template<typename Key, typename Value> inline constexpr int tree234<Key, Value>::size() const
{
  return tree_size;
}
             
template<typename Key, typename Value> inline int tree234<Key, Value>::getHeight() const noexcept
{
  int depth = 0;

  for (auto current = root.get(); current != nullptr; current = current->children[0].get()) {

       ++depth;
  }

  return depth;
}
// move assignment
template<typename Key, typename Value> inline tree234<Key, Value>& tree234<Key, Value>::operator=(tree234&& lhs) noexcept 
{
    tree_size = lhs.tree_size;

    lhs.tree_size = 0;

    root = std::move(lhs.root);

    root->parent = nullptr;
}
/*
 * F is a functor whose function call operator takes two parameters: a Node * and an int indicating the depth of the node from the root, which has depth 1.
 */
template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::levelOrderTraverse(Functor f) const noexcept
{
   if (root.get() == nullptr) return;
   
   // pair of: 1. Node pointer and 2. level of tree.
   std::queue<std::pair<const Node*, int>> q; 

   auto level = 1;

   q.push(std::make_pair(root.get(), level));

   while (!q.empty()) {

        std::pair<const Node *, int> pair_ = q.front();

        const Node *current = pair_.first;

        int tree_level = pair_.second;

        f(current, tree_level); // For example: print out all the keys_values in current.
         
        if (!current->isLeaf()) {
            
            for(auto i = 0; i < current->getChildCount(); ++i) {

               q.push(std::make_pair(current->children[i].get(), tree_level + 1));  
            }
        }
        q.pop(); 
   }
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::inOrderTraverse(Functor f) const noexcept
{
   DoInOrderTraverse(f, root);
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::iterativeInOrderTraverse(Functor f) const noexcept
{
   const Node *current = min(root.get());
   int key_index = 0;

   while (current != nullptr)  {
 
      f(current->keys_values[key_index].pair());

      std::pair<const Node *, int> pair = getSuccessor(current, key_index);   

      current = pair.first;
      key_index = pair.second;
  }
}

template<typename Key, typename Value> inline const typename tree234<Key, Value>::Node *tree234<Key, Value>::min(const Node *current) const noexcept
{
   while (current->children[0].get() != nullptr) {

        current = current->children[0].get();
   }
   return current;
}

template<typename Key, typename Value> inline const typename tree234<Key, Value>::Node *tree234<Key, Value>::max(const Node *current) const noexcept
{
   while (current->getRightMostChild() != nullptr) {

        current = current->getRightMostChild();
   }
   return current;
}


template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::postOrderTraverse(Functor f) const noexcept
{
   DoPostOrderTraverse(f, root);
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::preOrderTraverse(Functor f) const noexcept
{
   DoPreOrderTraverse(f, root);
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::debug_dump(Functor f) noexcept
{
   DoPostOrder4Debug(f, root);
}
/*
 * post order traversal 
 */
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::DoPostOrderTraverse(Functor f, const std::unique_ptr<Node>& current) const noexcept
{  
   if (current == nullptr) {

        return;
   }

   switch (current->totalItems) {

      case 1: // two node
            DoPostOrderTraverse(f, current->children[0]);

            DoPostOrderTraverse(f, current->children[1]);

            f(current->keys_values[0].pair());
            break;

      case 2: // three node
            DoPostOrderTraverse(f, current->children[0]);

            DoPostOrderTraverse(f, current->children[1]);

            f(current->keys_values[0].pair());

            DoPostOrderTraverse(f, current->children[2]);

            f(current->keys_values[1].pair());
            break;

      case 3: // four node
            DoPostOrderTraverse(f, current->children[0]);

            DoPostOrderTraverse(f, current->children[1]);

            f(current->keys_values[0].pair());

            DoPostOrderTraverse(f, current->children[2]);

            f(current->keys_values[1].pair());

            DoPostOrderTraverse(f, current->children[3]);

            f(current->keys_values[2].pair());
 
            break;
   }
}
/*
 * pre order traversal 
 */
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::DoPreOrderTraverse(Functor f, const std::unique_ptr<Node>& current) const noexcept
{  

  if (current == nullptr) {

        return;
   }

   switch (current->totalItems) {

      case 1: // two node
            f(current->keys_values[0].pair());

            DoPreOrderTraverse(f, current->children[0]);

            DoPreOrderTraverse(f, current->children[1]);

            break;

      case 2: // three node
            f(current->keys_values[0].pair());

            DoPreOrderTraverse(f, current->children[0]);

            DoPreOrderTraverse(f, current->children[1]);

            f(current->keys_values[1].pair());

            DoPreOrderTraverse(f, current->children[2]);

            break;

      case 3: // four node
            f(current->keys_values[0].pair());

            DoPreOrderTraverse(f, current->children[0]);

            DoPreOrderTraverse(f, current->children[1]);

            f(current->keys_values[1].pair());

            DoPreOrderTraverse(f, current->children[2]);

            f(current->keys_values[2].pair());

            DoPreOrderTraverse(f, current->children[3]);

            break;
   }
}

/*
 * In order traversal
 */
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::DoInOrderTraverse(Functor f, const std::unique_ptr<Node>& current) const noexcept
{     
   if (current == nullptr) return;

   switch (current->getTotalItems()) {

      case 1: // two node
            DoInOrderTraverse(f, current->children[0]);

            f(current->keys_values[0].pair());

            DoInOrderTraverse(f, current->children[1]);
            break;

      case 2: // three node
            DoInOrderTraverse(f, current->children[0]);

            f(current->keys_values[0].pair());

            DoInOrderTraverse(f, current->children[1]);
 
            f(current->keys_values[1].pair());

            DoInOrderTraverse(f, current->children[2]);
            break;

      case 3: // four node
            DoInOrderTraverse(f, current->children[0]);

            f(current->keys_values[0].pair());

            DoInOrderTraverse(f, current->children[1]);
 
            f(current->keys_values[1].pair());

            DoInOrderTraverse(f, current->children[2]);

            f(current->keys_values[2].pair());

            DoInOrderTraverse(f, current->children[3]);
 
            break;
   }
}
/*
 * post order traversal for debugging purposes
 */
/*
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::DoPostOrder4Debug(Functor f, const std::unique_ptr<Node>& current) noexcept
{     
   
   if (current == nullptr) {
 return;
   }
   switch (current->totalItems) {
      case 1: // two node
            DoPostOrder4Debug(f, current->children[0]);
            DoPostOrder4Debug(f, current->children[1]);
            f(current->keys_values[0], 0, current, root);
            break;
      case 2: // three node
            DoPostOrder4Debug(f, current->children[0]);
            DoPostOrder4Debug(f, current->children[1]);
            f(current->keys_values[0], 0, current, root);
            DoPostOrder4Debug(f, current->children[2]);
            f(current->keys_values[1], 1, current, root);
            break;
      case 3: // four node
            DoPostOrder4Debug(f, current->children[0]);
            DoPostOrder4Debug(f, current->children[1]);
            f(current->keys_values[0], 0, current, root);
            DoPostOrder4Debug(f, current->children[2]);
            f(current->keys_values[1], 1, current, root);
            DoPostOrder4Debug(f, current->children[3]);
            f(current->keys_values[2], 2, current, root);
 
            break;
   }
}
*/
/*
 * pre-order traversal
 */
template<typename Key, typename Value>  void tree234<Key, Value>::CloneTree(const std::unique_ptr<Node>& src_node, std::unique_ptr<Node> &dest_node, const Node *parent) noexcept
{
 if (src_node != nullptr) { 
                              
   // copy node
   switch (src_node->totalItems) {

      case 1: // two node
      {    
            dest_node = std::make_unique<Node>(src_node->keys_values[0],  const_cast<Node*>(parent));
           
            CloneTree(src_node->children[0], dest_node->children[0], dest_node.get()); 
            
            CloneTree(src_node->children[1], dest_node->children[1], dest_node.get()); 

            break;

      } 
      case 2: // three node
      {
            dest_node = std::make_unique<Node>( src_node->keys_values[0], src_node->keys_values[1], const_cast<Node*>(parent)); 
            
            CloneTree(src_node->children[0], dest_node->children[0], dest_node.get());
            
            CloneTree(src_node->children[1], dest_node->children[1], dest_node.get());
            
            CloneTree(src_node->children[2], dest_node->children[2], dest_node.get());

            break;
      } 
      case 3: // four node
      {
            dest_node = std::make_unique<Node>( src_node->keys_values[0], src_node->keys_values[1], src_node->keys_values[2], const_cast<Node*>(parent)); 
            
            CloneTree(src_node->children[0], dest_node->children[0], dest_node.get());
            
            CloneTree(src_node->children[1], dest_node->children[1], dest_node.get());
            
            CloneTree(src_node->children[2], dest_node->children[2], dest_node.get());
            
            CloneTree(src_node->children[3], dest_node->children[3], dest_node.get());
 
            break;
      } 
   }
 } else {

    dest_node = nullptr;
 } 
}

/*
 * Requires: childIndex is within the range for the type of node.
 * child is not nullptr.
 * connectChild() is equivalent to doing:
 *
 * newRight->children[0] = std::move(node->children[2]);
 * newRight->children[0]->parent = newRight; 
 * newRight->children[1] = std::move(node->children[3]);
 * newRight->children[1]->parent = newRight; 
 *
 */
template<typename Key, typename Value> inline void  tree234<Key, Value>::Node::connectChild(int childIndex, std::unique_ptr<Node>& child)  noexcept
{
  children[childIndex] = std::move( child ); // Note: If children[childIndex] currently holds a managed pointer , it will be freed.
  
  if (children[childIndex] != nullptr) { 

       children[childIndex]->parent = this; 
  }
}

/*
 * Returns true if key is found in node, and it set index so that this->keys_values[index] == key.
 * Returns false if key is if not found, and it sets next to point to next child with which to continue the descent search downward (toward a leaf node), and
 * it sets child_index such that next->parent->children[child_index] == next.
 */
template<typename Key, typename Value> inline bool tree234<Key, Value>::Node::SearchNode(Key key, int& index, int& child_index, const Node *&next) const noexcept 
{
  for(auto i = 0; i < totalItems; ++i) {

     if (key < keys_values[i].key()) {
            
         next = children[i].get(); 
         child_index = i;  // new code. index is such that: this->children[index] == next
         return false;

     } else if (keys_values[i].key() == key) {

         index = i;
         return true;
     }
  }

  // It must be greater than the last key (because it is not less than or equal to it).
  child_index = totalItems; // new: see 'new code' comment just above.
  next = children[totalItems].get(); 

  return false;
}

/*
 * Require: childIndex is within the range for the type of node.
 * Returns: child pointer.
 * Note: Always call disconnectChild() before removeItem(), or it will not work correctly because totalItems
 * will have been altered.
 */

template<typename Key, typename Value> inline std::unique_ptr<typename tree234<Key, Value>::Node> tree234<Key, Value>::Node::disconnectChild(int childIndex) noexcept // ok
{
  std::unique_ptr<Node> node = std::move(children[childIndex] ); // invokes unique_ptr<Node> move assignment.

  // shift children (whose last 0-based index is totalItems) left to overwrite removed child i.
  for(auto i = childIndex; i < totalItems; ++i) {

       children[i] = std::move(children[i + 1]); // shift remaining children to the left. Calls unique_ptr<Node>::operator=(unique_ptr<Node>&&)
  } 

  return node; // invokes unique_ptr<Node> move constructor since node is an rvalue.
}
/*
 * Preconditions: node is not full, not a four node, and key is not present in node, which may or may not
 * be a leaf node.  Shifts keys_values in node as needed so that key will be inserted in sorted position. Returns index
 * of inserted key.
 */

template<typename Key, typename Value> int  tree234<Key, Value>::Node::insertKeyValue(Key key, const Value& value)  noexcept // ok. Maybe add a move version, too: insertKey(Key, Value&&)
{ 
  // start on right, examine items
  for(auto i = totalItems - 1; i >= 0 ; --i) {

      if (key < keys_values[i].key()) { // if key[i] is bigger

          keys_values[i + 1] = std::move(keys_values[i]); // shift it right

      } else {

          keys_values[i + 1].key() = key; // insert new item
          keys_values[i + 1].value() = value;  
        ++totalItems;        // increase the total item count
          return i + 1;      // return index of inserted key.
      } 
    } 

    // key is smaller than all keys_values, so insert it at position 0
    keys_values[0].key() = key;  
    keys_values[0].value() = value; 
  ++totalItems; // increase the total item count
    return 0;
}

template<typename Key, typename Value> void tree234<Key, Value>::Node::insert(KeyValue&& key_value, std::unique_ptr<Node>& largerNode) noexcept 
{ 
  // start on right, examine items
  for(auto i = totalItems - 1; i >= 0 ; --i) {

      if (key_value.key() < keys_values[i].key()) { // if key[i] is bigger

          keys_values[i + 1] = std::move(keys_values[i]); // shift it right...

      } else {

          keys_values[i + 1] = std::move(key_value);

        ++totalItems;        // increase the total item count

          insertChild(i + 2, largerNode); // TODO: Is i + 1 correct?
          return;      // return index of inserted key.
      } 
    } 

    // key is smaller than all keys_values, so insert it at position 0
    keys_values[0] = std::move(key_value); 

  ++totalItems; // increase the total item count

    insertChild(1, largerNode); // TODO: Is 1 correct--I believe it is?
    return;
}
/*
 Input: A new child to insert at child index position insert_index. The current number of children currently is given by children_num.
 */
template<typename Key, typename Value> void tree234<Key, Value>::Node::insertChild(int insert_index, std::unique_ptr<Node>& newChild) noexcept
{
   int last_index = totalItems - 1;  // While totalItems reflects the correct number of keys, the number of children currently is also equal to the number of keys.
 

   // ...move its children right, starting from its last child index and stopping just before insert_index.
   for(auto i = last_index; i >= insert_index; i--)  {

       connectChild(i + 1, children[i]);       
   }

   // Then insert the new child whose key is larger than key_value.key().
   connectChild(insert_index,  newChild);
}
template<typename Key, typename Value> inline typename tree234<Key, Value>::KeyValue tree234<Key, Value>::Node::removeKeyValue(int index) noexcept 
{
  KeyValue key_value = std::move(keys_values[index]); 

  // shift to the left all keys_values to the right of index to the left
  for(auto i = index; i < totalItems - 1; ++i) {

      keys_values[i] = std::move(keys_values[i + 1]); 
  } 

  --totalItems;

  return key_value;
}


template<typename Key, typename Value> inline constexpr typename tree234<Key, Value>::Node * tree234<Key, Value>::Node::getParent()   noexcept // ok
{ 
   return parent;
}

template<typename Key, typename Value> inline constexpr const typename tree234<Key, Value>::Node *tree234<Key, Value>::Node::getParent() const  noexcept // ok
{ 
   return parent;
}
/*
  Input: 
   Assumes that "this" is never the root. The parent of the root is nullptr.
 */
template<class Key, class Value> int tree234<Key, Value>::Node::getChildIndex() const noexcept
{
  // Determine child_index such that this == this->parent->children[child_index]
  int child_index = 0;

  for (; child_index <= parent->getTotalItems(); ++child_index) {

       if (this == parent->children[child_index].get())
          break;
  }

  return child_index;
}
template<typename Key, typename Value> inline constexpr  bool tree234<Key, Value>::Node::isLeaf() const  noexcept // ok
{ 
   return !children[0] ? true : false;
}

/*
 * Recursively delete nodes, starting with children.
 */
template<typename Key, typename Value> void tree234<Key, Value>::DestroyTree(std::unique_ptr<Node> &current) noexcept 
{
  if (current == nullptr) {

      return;
  }
  
  for(auto i = 0; i < current->totalItems; ++i) {

      DestroyTree(current->children[i]);
   }

   current.reset(); // deletes the pointer owned by unique_ptr<Node>.
}

template<typename Key, typename Value> inline bool tree234<Key, Value>::find(Key key) noexcept
{
    // make sure tree has at least one element    
    if (root == nullptr) return false;

    else {
        int index;  
        const Node *location;
        return DoSearch(key, location, index);
    }
}   

template<typename Key, typename Value>  bool tree234<Key, Value>::DoSearch(Key key, const Node *&location, int& index) noexcept // ok
{
  if (!root) { // <--> if (root.get() == nullptr)

     return false;
  }

  const Node *next;
  int child_index;
  const Node *current = root.get();
  
  for(; !current->SearchNode(key, index, child_index, next); current = next) {  

      if (current->isLeaf()) { 

          return false; // wasn't found
      } 
  }

  location = current;
  return true;
}
/*
 * Insertion based on pseudo code at:

 1. http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt
 2. http://www.serc.iisc.ernet.in/~viren/Courses/2010/SE286/Lecture16.pdf 

 * 4-nodes as the are encountered are split into two 2-nodes, one holding the smallest key, the other the largest. The middle key is inserted into the parent
 * The two left most children of the former 4-node are assigned to the smaller 2-node, and the two right most children, likewise, are assigned to the larger 
 * two node. The parent of the former 4-node adopts the two new 2-nodes. Note: the smaller 2-node is simply the original 4-node downsized to a 2-node.
 */
template<typename Key, typename Value> void tree234<Key, Value>::insert(Key key, const Value& value) noexcept 
{ 
   if (root == nullptr) {
           
      root = std::make_unique<Node>(key, value); 
      ++tree_size;
      return; 
   } 

   const Node *current = root.get();

   // Descend until a leaf node is found, splitting four nodes as they are encountered 
   int child_index;

    while(true) {
      
       // TODO: Do we need to resume the search with the parent? Doesn't this result sometimes in splitting the parent, too, when we don't need to?
 
       if(current->isFourNode()) {// if four node encountered, split it, moving a value up to parent.

          split(const_cast<Node *>(current)); // split needs to modify the tree.
          current = current->parent;
       } 

       const Node *next;
       int index;

       if (current->SearchNode(key, index, child_index, next) ) {// return if key is already in tree
             
          return;

       } else if (current->isLeaf()) {

          break;
       } 

       // set current to next   
       current = next;  
    }
 
    // current node is now a leaf and it is not full (because we split all four nodes while descending). We cast away constness in order to change the node.
    const_cast<Node *>(current)->insertKeyValue(key, value); 
    ++tree_size;
}
/* Orig
template<typename Key, typename Value> void tree234<Key, Value>::insert(Key key, const Value& value) noexcept 
{ 
   if (root == nullptr) {
           
      root = std::make_unique<Node>(key, value); 
      ++tree_size;
      return; 
   } 

   const Node *current = root.get();

   // Descend until a leaf node is found, splitting four nodes as they are encountered 
   int child_index;

    while(true) {
      
       // TODO: Do we need to resume the search with the parent? Doesn't this result sometimes in splitting the parent, too, when we don't need to?
 
       if(current->isFourNode()) {// if four node encountered, split it, moving a value up to parent.

          split(const_cast<Node *>(current)); // split needs to modify the tree.

          // resume search with parent.
          current = current->getParent(); 
                        
       } else {

          const Node *next;
          int index;

          if (current->SearchNode(key, index, child_index, next) ) {// return if key is already in tree
                
             return;

          } else if (current->isLeaf()) {

             break;
          } 

          // set current to next   
          current = next;  
       }
    }
 
    // current node is now a leaf and it is not full (because we split all four nodes while descending). We cast away constness in order to change the node.
    const_cast<Node *>(current)->insertKeyValue(key, value); 
    ++tree_size;
}
*/

/* 
 *  Split pseudocode: 
 *  
 *  Upon encountering a four node: split it into a 2-node
 *  
 *  1. We move the largest key into a newly allocated 2-node and connect the two right most children of the input 3-node to it.
 *  2. We convert pnode into a 2-node by setting totalItems to 1, but keeping its smallest key and its two left-most chidren, 
 *  3. We move the middle key up to the parent( which we know is not a 4-node; else it too would have been split already), and we connect the node step #1 to it as a new child.
 *  Note: if pnode is the root, we special case this by creating a new root above the current root.
 *  
 */ 

template<typename Key, typename Value> void tree234<Key, Value>::split(Node *pnode) noexcept
{
   // 1. create a new node from largest key and adopt pnode's tworight most children
   std::unique_ptr<Node> largestNode = std::make_unique<Node>(std::move(pnode->keys_values[2]));
   
   largestNode->connectChild(0, pnode->children[2]); 
   largestNode->connectChild(1, pnode->children[3]);
   
   // 2. Make pnode a 2-node. Note: It stoll retains its two left-most children becoming 
   pnode->totalItems = 1;
   
   // 3. Insert middle value into parent, or if pnode is the root, create a new root above pnode and 
   // adopt pnode and largest as children.
   
   if (root.get() == pnode) {
   
     std::unique_ptr<Node> new_root = std::make_unique<Node>(std::move(pnode->keys_values[1])); // Middle value will become new root

     root.release(); // We don't want the current root's underlying member, to which pnode points, to be freed when root is assigned below. 

     std::unique_ptr<Node> tmp{pnode};  

     new_root->connectChild(0, tmp); 
     new_root->connectChild(1, largestNode); 
     
     root = std::move(new_root); // reset the root.

   } else {

     // The parent will retain pnode, now downgraded to a 2-node, as its child in its current child position. It will insert the new key value and connect/insert largeNode
     pnode->parent->insert(std::move(pnode->keys_values[1]), largestNode); 
   }
}

/*
 * Deletion based on pseudo code from pages 50-53 of: 
 *
 * www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 *
 * We reduce deletion of an internal node's key to deletion of a leaf node's key by swapping the deleted key
 * with its in-order successor.
 */

template<typename Key, typename Value> bool tree234<Key, Value>::remove(Key key)  // ok
{
   if (root == nullptr) return false; 

   else if (root->isLeaf()) { 
       
         int index = 0;
         
         for (; index < root->getTotalItems(); ++index) {

             if (root->keys_values[index].key() == key ) {

                // Remove key from root and puts its in-order successor (if it exists) into its place. 
                root->removeKeyValue(index); 
                              
                if (root->isEmpty()) {

                   root.reset(); // delete root if tree now empty. 
               }  

                --tree_size;
                return true;
             } 
         }

         return false;

   } else { // there are more nodes than just the root.
 
       return remove(key, root.get()); 
  }
}
 
/*
 * Pseudo code is from slides 50-53 of: www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
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
 * we fuse together the two siblings, plus an item we bring down from parent, forming a 4-node and shifting all children effected appropriately. 
 *
 * See slide 52 at:
 *     www.serc.iisc.ernet.in/~viren/Courses/2009/SE286/2-3Trees-Mod.ppt 
 * 
 * An even more thorough explanationed illustrated with a several working examples is at pages 64-66 of
 *    http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf 
 * http://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf
 New untested prospective code for remove(Key key, Node *). This is the remove code for the case when the root is not a leaf node.
 */
template<typename Key, typename Value> bool tree234<Key, Value>::remove(Key key, const Node *current) 
{
   const Node *pfound_node = nullptr; 
   int key_index;
   int child_index;

   // Search, looking for key, converting 2-nodes encountered into 3- or 4-nodes. After the conversion, the node is searched for the key and, if not found,
   // We continue down the tree. 
   while(true) {

       // We know the root is not a leaf. That was handled in calling code. So we don't convert a 2-node root.
       if (current != root.get() && current->isTwoNode()) { 

           // If not the root, convert 2-nodes encountered while descending into 3- or 4-nodes... 
           current = convertTwoNode(const_cast<Node *>(current)); // ..and resume the key search with the now converted node.
       } 

       const Node *next = nullptr;

       if (current->SearchNode(key, key_index, child_index, next)) { // ...search for item in current node. 

           pfound_node = const_cast<Node *>(current); // We found it.  

           std::pair<const Node *, int> pr = getRemoveSuccessor(key, pfound_node, key_index);
           current = pr.first;
           
           break;

       } else if (current->isLeaf()) { // Are we done? 

           return false; 
       } 

       current = next; 
       continue;
  } 

  if (!pfound_node->isLeaf()) { 

      // We have the item found in pfound_node->keys_values[key_index], which is an internal node. We have current->keys_values[0] as in order successor leaf node, and we know
      // current it is not a leaf node.  So we "swap" the in order successor and the key at pfound_node->keys_values[key_index]. 
    
      // Note: We simply delete the former in-order
      // successor key. 
      const_cast<Node *>(pfound_node)->keys_values[key_index] = current->keys_values[0]; 
    
      const_cast<Node *>(current)->removeKeyValue(0); // Since current is not a 2-node, it does not need to be freed. Since it is a leaf, its children are all nullptr. 

   } else { 

      // pfound_node is a leaf that has already been converted, if necessary. We therefore do not need to free the node, and we can
      // simply call removeKeyValue(key_index).

      const_cast<Node *>(pfound_node)->removeKeyValue(key_index); 
   }

   --tree_size;
   return true;
}
/*
 * Returns the in-order successor of pfound_node->keys(key_index). If pfound_node is an internal node, the in order successor is the left-most leaf node in the subtree rooted
 * at found_node->children[key_index + 1]. If pfound_node is a leaf, the successor is within the leaf itself.
 *
 * It converts any 2-nodes encountered into 3-nodes, and re-searches for the key if it was moved during the 2-node conversion and re-sets pfound_node and key_index, which were
 * are reference paramters.
 * 
 */
template<typename Key, typename Value>
std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::getRemoveSuccessor(Key key, const Node *&pfound_node, int& key_index) noexcept
{
int child_index = 0;

   if (pfound_node->isLeaf()) {  // Is pfound_node already a leaf node.
     
       DoSearch(key, pfound_node, key_index);
       return std::make_pair(pfound_node, key_index);
   } 

   // The in-order successor, the left-most leaf node in the subtree rooted at found_node->children[key_index + 1].
   const Node *current = pfound_node->children[key_index + 1].get(); 

   while (true) {

     if (current->isTwoNode()) { 
 
          current = convertTwoNode(const_cast<Node*>(current));

          // Check if key moved as a result of conversion.
          // Comments:
          // pfound_node is never a 2-node since remove( Key key, Node *) first converts any 2-nodes to 3- or 4-nodes before calling
         
          if (pfound_node->getTotalItems() - 1 < key_index || pfound_node->keys_values[key_index].key() != key) { // Did key move?

              // Re-find the node and the key_index of key
              DoSearch(key, pfound_node, key_index);

              return getRemoveSuccessor(key, pfound_node, key_index);
          } 
     } 

     if (current->isLeaf()) { // At in order successor?

         break;  
     } 
     
     current = current->children[child_index].get(); // set current to left most child of current.
  }

  return std::make_pair(current, child_index);
}

/*
 * Requires: node is 2-node.
 * Promises: node is converted into either a 3- or a 4-node. 
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
template<typename Key, typename Value> typename tree234<Key, Value>::Node *tree234<Key, Value>::convertTwoNode(Node *node)  noexcept
{                                                                         
  
   Node *convertedNode;
   Node *parent = node->getParent();

   int parentKeyTotal = parent->getTotalItems();
   int parentChildrenTotal = parent->getChildCount();
   
   // First, we find the index of the 2-node such that parent->children[node2_index] == node, by comparing node's key to its
   // parent's keys_values.
   int node2_index = 0;
   
   for (; node2_index < parentKeyTotal; ++node2_index) {
       //
       // If we never break, then node->keys_values[0] is greater than the last key of its parent, which means
       // node == parent->children[parent->totalItems], the last child. 
       //

       if (node->keys_values[0].key() < parent->keys_values[node2_index].key() ) { 
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

   } else if (left_adjacent >= 0 && !parent->children[left_adjacent]->isTwoNode()) {

        has3or4NodeSibling = true;
        sibling_index = left_adjacent;  

   } else if (right_adjacent < parentChildrenTotal) { // There are no 3- or 4-nodes siblings. Therefore the all siblings 
                                                      // are 2-node(s).

        sibling_index = right_adjacent; 

   } else { // sibling is to the left.

        sibling_index = left_adjacent; 
   }

   // Determine, based on whether the parent is a two node, whether to rotate or fuse. 
   // Check if its parent 2-node (or 3- or 4-node).

   if (has3or4NodeSibling == false) { // All adjacent siblings are also 2-nodes...

        if (parent->isTwoNode()) { //... as is the parent, which must be root; otherwise, it would have already been converted.

            convertedNode = parent->fuseWithChildren();

        } else { // parent is 3- or 4-node and there a no 3- or 4-node adjacent siblings 

           convertedNode = fuseSiblings(parent, node2_index, sibling_index);
        }

   } else { // it has a 3- or 4-node sibling.

      Node *psibling = parent->children[sibling_index].get();
    
      Node *p2node = parent->children[node2_index].get();
    
      
      // First we get the index of the parent's key value such that either 
      // 
      //   parent->children[node2_index]->keys_values[0]  <  parent->keys_values[index] <  parent->children[sibling_id]->keys_values[0] 
      // 
      // or 
      // 
      //   parent->children[sibling_id]->keys_values[0]  <  parent->keys_values[index] <  parent->children[node2_index]->keys_values[0]
      //
      // by taking the minimum of the indecies.
      
    
      int parent_key_index = std::min(node2_index, sibling_index); 

      if (node2_index > sibling_index) { /* If sibling is to the left, then
                                    *
                                    *  parent->children[sibling_id]->keys_values[0] < parent->keys_values[index] < parent->children[node2_index]->keys_values[0]
                                    * 
                                    * and we do a right rotation
                                    */ 
    
          convertedNode = rightRotation(p2node, psibling, parent, parent_key_index);
    
      } else { /* else sibling is to the right and 
                *    parent->children[node2_index]->keys_values[0]  <  parent->keys_values[index] <  parent->children[sibling_id]->keys_values[0] 
                * therefore do a left rotation
           */ 
    
          convertedNode = leftRotation(p2node, psibling, parent, parent_key_index);
      }
   }
   
   return convertedNode;
}

/*
 * Requirements: 
 * 1. Parent node is a 2-node, and its two children are also both 2-nodes. Parent must be the tree's root (this is an inherent property of the
 *    2 3 4 tree insertion algorithm).
 *
 * Promises: 
 * 1. 4-node resulting from fusing of the two 2-nodes' keys_values into the parent. 
 * 2. Deletion of the 2-node children from the tree
 * 3. Adoption of the 2-node children's children as children of parent.
 *
 * Pseudo code: 
 *
 * 1. Absorbs its children's keys_values as its own. 
 * 2. Makes its grandchildren its children and deletes its former, now orphaned child nodes.
 */
template<typename Key, typename Value> typename tree234<Key, Value>::Node *tree234<Key, Value>::Node::fuseWithChildren() noexcept
{
  // move key of 2-node 
  keys_values[1] = std::move(keys_values[0]);

  // absorb children's keys_values
  keys_values[0] = std::move(children[0]->keys_values[0]);    
  keys_values[2] = std::move(children[1]->keys_values[0]);       

  totalItems = 3;
  
  std::unique_ptr<Node> leftOrphan = std::move(children[0]); 
  std::unique_ptr<Node> rightOrphan = std::move(children[1]); 
    
  // make grandchildren the children of this.
  connectChild(0, leftOrphan->children[0]); 
  connectChild(1, leftOrphan->children[1]);
  connectChild(2, rightOrphan->children[0]); 
  connectChild(3, rightOrphan->children[1]);
    
  return this;  
}// <-- Note: leftOrphan and rightOrphan are automatically deleted here when their unique_ptr<Node> go out of scope.

/* 
 * Requires: sibling is to the left, therefore: parent->children[sibling_id]->keys_values[0] < parent->keys_values[index] < parent->children[node2_index]->keys_values[0]
 */
template<typename Key, typename Value> typename tree234<Key, Value>::Node *tree234<Key, Value>::rightRotation(Node *p2node, Node *psibling, Node *parent, int parent_key_index) noexcept
{    
  // Add the parent's key to 2-node, making it a 3-node

  // 1. But first shift the 2-node's sole key right one position
  p2node->keys_values[1] = p2node->keys_values[0];      

  p2node->keys_values[0] = parent->keys_values[parent_key_index];  // 2. Now bring down parent key

  p2node->totalItems = static_cast<int>(tree234<Key, Value>::Node::NodeType::three_node); // 3. increase total items

  int total_sibling_keys_values = psibling->totalItems; 

  // 4. disconnect right-most child of sibling
  std::unique_ptr<Node> pchild_of_sibling = psibling->disconnectChild(total_sibling_keys_values); 
  
  parent->keys_values[parent_key_index] = std::move(psibling->removeKeyValue(total_sibling_keys_values - 1)); // remove the largest, the right-most, sibling's key, and, then, overwrite parent item with largest sibling key ++

  p2node->insertChild(0, pchild_of_sibling); // add former right-most child of sibling as its first child

  return p2node;
}
/* Requires: sibling is to the right therefore: parent->children[node2_index]->keys_values[0]  <  parent->keys_values[index] <  parent->children[sibling_id]->keys_values[0] 
 * Do a left rotation
 */ 
template<typename Key, typename Value> typename tree234<Key, Value>::Node *tree234<Key, Value>::leftRotation(Node *p2node, Node *psibling, Node *parent, int parent_key_index) noexcept
{
  // pnode2->keys_values[0] doesn't change.
  p2node->keys_values[1] = parent->keys_values[parent_key_index];  // 1. insert parent key making 2-node a 3-node

  p2node->totalItems = static_cast<int>(tree234<Key, Value>::Node::NodeType::three_node);// 3. increase total items

  std::unique_ptr<Node> pchild_of_sibling = psibling->disconnectChild(0); // disconnect first child of sibling.

  // Remove smallest key in sibling
  parent->keys_values[parent_key_index] = std::move(psibling->removeKeyValue(0)); 

  // add former first child of silbing as right-most child of our 3-node.
  p2node->insertChild(p2node->totalItems, pchild_of_sibling); 

  return p2node;
}
/*
 * Requirements: 
 *
 * 1. parent is a 3- or 4-node. 
 * 2. parent->children[node2_index] and parent->children[sibling_index] are both 2-nodes
 * 
 * Promises:
 * 
 * 1. The 2-node at parent->children[node2_index] is converted into a 4-node by fusing it with the 2-node at parent->children[sibling_index] along with
 *    a key from the parent located at parent->keys_values[parent_key_index]
 *
 * 2. The 2-node sibling at parent->children[silbing_index] is then deleted from the tree, and its children are connected to the converted 2-node (into a 4-node)
 *
 * 3. parent->childen[node2_id] is the 2-node being converted (into a 3- or 4-node).
 *
 * 4. The parent becomes either a 2-node, if it was a 3-node, or a 2-node if it was a 4-node?
 *
 */
template<typename Key, typename Value> typename tree234<Key, Value>::Node *tree234<Key, Value>::fuseSiblings(Node *parent, int node2_index, int sibling_index) noexcept
{
  //--Node *psibling;

  Node *p2node = parent->children[node2_index].get();

  // First get the index of the parent's key value to be stolen and added into the 2-node
  int parent_key_index = std::min(node2_index, sibling_index); 

  if (node2_index > sibling_index) { // sibling is to the left: 

      /* Adjust parent:
         1. Remove parent key (and shift its remaining keys_values and reduce its totalItems)
         2. Reset parent's children pointers after removing sibling.
       * Note: There is a potential insidious bug: disconnectChild depends on totalItems, which removeKey() reduces. Therefore,
       * disconnectChild() must always be called before removeKey().
       */
      std::unique_ptr<Node> psibling = parent->disconnectChild(sibling_index); // This will do #2. 
      
      //--Key parent_key = parent->removeKey(parent_key_index); //this will do #1
      KeyValue parent_key_value = parent->removeKeyValue(parent_key_index); //this will do #1

      // Now, add both the sibling's and parent's key to 2-node

      // 1. But first shift the 2-node's sole key right two positions
      p2node->keys_values[2] = p2node->keys_values[0];      

      p2node->keys_values[1] = std::move(parent_key_value);  // 2. bring down parent key and value, ie, its pair<Key, Value>, so a move assignment operator must be invoked. 

      p2node->keys_values[0] = psibling->keys_values[0]; // 3. insert adjacent sibling's sole key. 
 
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
         1. Remove parent key (and shift its remaining keys_values and reduce its totalItems)
         2. Reset its children pointers 
       * Note: There is a potential insidious bug: disconnectChild depends on totalItems, which removeKey reduces. Therefore,
       * disconnectChild() must always be called before removeKey(), or children will not be shifted correctly.
       */
      std::unique_ptr<Node> psibling = parent->disconnectChild(sibling_index); // this does #2
      
      // TODO: Should move() be called?
      p2node->keys_values[1] = parent->removeKeyValue(parent_key_index); // this will #1 // 1. bring down parent key 

      p2node->keys_values[2] = std::move(psibling->keys_values[0]);// 2. insert sibling's sole key and value. 
 
      p2node->totalItems = 3; // 3. make it a 4-node

      // Insert sibling's last two child. Note: connectChild() will also reset the parent pointer of these children (to be p2node). 

      p2node->connectChild(3, psibling->children[1]);  // Add sibling's children
      p2node->connectChild(2, psibling->children[0]);  
      
  } // <-- automatic deletion of psibling's underlying raw memory

  return p2node;
} 

template<typename Key, typename Value> inline void tree234<Key, Value>::printlevelOrder(std::ostream& ostr) const noexcept
{
  levelOrderDisplay<tree234<Key, Value>> tree_printer(*this, ostr);  
  
  levelOrderTraverse(tree_printer);
  
  ostr << std::flush;
}

template<typename Key, typename Value> inline void tree234<Key, Value>::printInOrder(std::ostream& ostr) const noexcept
{
  auto lambda = [&](const std::pair<Key, Value>& pr) { ostr << pr.first << ' '; };
  inOrderTraverse(lambda); 
}
	
/*
 TODO: The comments here sometimes be confuse predecessor with successor; likewise, the comments for iterator::getSuccessor confuse the successor with the predecessor!
Two cases are possible: 1.) when current is an internal node and 2.) when current is a leaf node.
case 2:
If current is a leaf node, and if it is a a 3-node and key-index is 1, then the predecessor is trivial: the first key is the predecessor. If, however, the key_index is 0, we ascend the parent
chain until we enounter the first parent that is not a left most-child (of its parent). If the root is enounter before such a parent is found, then there is no predecessor.
 nodes as long as the parent is the right-most (or left-most???) child (of its parent). If we reach the root, there is no predecessor.
Else upon reaching a parent (before the root) that is a middle or left-most child (of its parent), we find the smallest key in the parent's "right" subtree.
 */
template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::getPredecessor(const typename  tree234<Key, Value>::Node *current, int key_index) const noexcept
{
  if (current->isLeaf()) { // If leaf node

     if (current == root.get()) { // root is leaf      

         if (key_index != 0) {
                  
             return std::make_pair(current, key_index - 1);
         } 
         return std::make_pair(nullptr, 0);
            
     } else {

        return getLeafNodePredecessor(current, key_index);
     }

  } else { // else internal node

      return getInternalNodePredecessor(current, key_index);
  }
}

template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::getInternalNodePredecessor(\
     const typename tree234<Key, Value>::Node *pnode, int key_index) const noexcept	    
{
 // Get next left child node of pnode based on key_index. This will be the child at pnode->children[index]. 
 const Node *leftChild = pnode->children[key_index].get();

 for (const Node *cursor = leftChild; cursor != nullptr; cursor = cursor->children[cursor->totalItems].get()) {

    pnode = cursor;
 }

 return std::make_pair(pnode, pnode->totalItems - 1); 
}
/* 
Finding the predecessor of a given node 
---------------------------------------
  If left child exists, predecessor is the right most node of the left subtree
  Else we walk up the ancestor chain until you traverse the first right child pointer (find the first node that is a right child of its 
  parent...that parent is the predecessor)
  If you get to the root w/o finding a node that is a right child, there is no predecessor
*/

template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::getLeafNodePredecessor(const Node *pnode, int index) const 
{
  // Handle trivial case: if the leaf node is not a 2-node (it is a 3-node or 4-node, and key_index is not the first key), simply set index of predecessor to index - 1. 
  if (!pnode->isTwoNode() && index != 0) {

      return std::make_pair(pnode, index - 1); 
  }

  // Determine child_index such that pnode == pnode->parent->children[child_index]
  int child_index = pnode->getChildIndex();

  int pred_key_index;

  if (child_index != 0) { // IF pnode is not the left-most child, the predecessor is in the parent

      return  std::make_pair(pnode->parent, child_index - 1); 

  } else {

   /* 
    To find the next smallest node the logic is identical: We walk up the parent chain until we traverse the first parent that is not a left-most child 
    of its parent. That parent is the predecessor. If we get to the root without finding a node that is a right child, there is no predecessor.
    Note: In a 2 3 tree, a "right" child pointer will be either the second child of a 2-node or the second, the middle, or the third child of a 3-node. "right" child
    pointer means a pointer to a subtree with larger keys. In a 2 3 tree, the middle child pointer of a 3-node parent is a "right child pointer" of the 1st key
    because all the keys of the subtree whose root is the second (or middle) child pointer are greater than 1st key of the subtree's parent. 
    So when we walk up the ancestor chain as long as the parent is the first child. For example, in the tree portion shown below
              [5,   10]  
              /   |   \                              
          ...    ...  [27,       70]  
                       /       |     \
                      /        |      \   
                   [20]       [45]    [80, 170]
                   /   \      /  \     /  |  \
                [15]  [25]  [30] [60]  <-- pnode points to leaf node [20]. 
                / \   / \   / \  / \   
               0   0 0   0 0   0 0  0  ... 
     
    if [15] is the pnode leaf node, the predecessor of [15] is the second key of the 3-node [5, 10] because when we walk up the parent chain from [15], the first
    right child pointer we encounter is the parent of [27, 70], which is [5, 10]. So [10] is the next smallest key. In this example
              [5,   10]  
              /   |   \                              
          ...    ...  [27,       70]  
                       /       |     \
                      /        |      \   
                   [20]       [45]     [80, 170]
                  /   \       /  \      /  |  \
                [15]  [25]  [30] [60]  <-- pnode points to leaf node [20]. 
                / \   / \   / \  / \   
               0   0 0   0 0   0 0  0  ... 
     
      if [30] is the pnode leaf node, the predecessor of [30] is the first key of the 3-node [27, 70] because when we walk up the parent chain from [30], the first
      non-first child pointer we encounter is the parent of [45], which is [27, 70]. So the key at index 0, which is [27], is the next smallest key. Therefore, if our
      loop above terminates without encountering the root, we must determine the child index of prior_node in pnode. If pnode is a 2-node, it is trivial: the child
      index is one. If pnode is a three node, the child index is either one or two:
      int child_index = 1; // assume pnode is a 2-node.
      if (pnode->isThreeNode()) { // if it is a 3-nodee, compare prior_node to children[1]
          child_index = prior_node == pnode->children[1].get() ? 1 : 2;
      }
  
      Now that we know the child_index such that
            pnode->children[child_index] == prior_node;
      
      Determine which key is the predecessor. If child_index is one, the middle child, then the predecessor is pnode->keys_values[0]. If child_index is two, then
      the predecessor is pnode->keys_values[1].key(). Thus, the predecessor is the key at child_index - 1.
      */
      const Node *parent = pnode->parent;
      
      Key current_key = pnode->keys_values[index].key();

      // Ascend the parent pointer chain as long as pnode is the left most child of its parent.
      for(; pnode == parent->children[0].get();  parent = parent->parent)  {
      
          // pnode is still the left most child, but if its is the root, we cannot ascend further and there is no predecessor.  
          if (parent == root.get()) {
                
              return std::make_pair(nullptr, 0);  // To indicate this we set current, the member of the pair, to nullptr and key_index, the second member, to 0.
          }
          pnode = parent;
      }

      // The predecessor will be the first key, starting with the right most key, that is less than current_key. 
      for (int pred_index = parent->getTotalItems() - 1; pred_index >= 0; --pred_index) {

           if (current_key > parent->keys_values[pred_index].key()) {

               return std::make_pair(parent, pred_index);
           } 
      } 

     throw std::logic_error("Error in getLeafNodePredecessor");
  } // end else
}

template<class Key, class Value> tree234<Key, Value>::iterator::iterator(tree234<Key, Value>& lhs_tree) : tree{lhs_tree} 
{
  // If the tree is empty, there is nothing over which to iterate...
   if (!tree.isEmpty()) {

      current = tree.min(tree.root.get());
  } else {

      current = nullptr;
  }

  cursor = current;
  key_index = 0;  
}

template<class Key, class Value> inline tree234<Key, Value>::iterator::iterator(const iterator& lhs) : tree{lhs.tree}, current{lhs.current},\
        cursor{lhs.cursor}, key_index{lhs.key_index}
{
}

// non const tree234<Key, Value>& passed to ctor. Called only by end()
template<class Key, class Value> inline tree234<Key, Value>::iterator::iterator(tree234<Key, Value>& lhs_tree, int i) :  tree{lhs_tree} 
{
  // If the tree is empty, there is nothing over which to iterate...
   if (!tree.isEmpty()) {

      cursor = tree.max(tree.root.get()); // Go to largest node.
      key_index = cursor->getTotalItems() - 1;

      current = nullptr; 

  } else {

      cursor = current = nullptr;
      key_index = 0;  
  }
}

template<class Key, class Value> inline typename tree234<Key, Value>::iterator tree234<Key, Value>::begin() noexcept
{
  return iterator{*this};
}

template<class Key, class Value> inline typename tree234<Key, Value>::const_iterator tree234<Key, Value>::begin() const noexcept
{
  return const_iterator{*this};
}

template<class Key, class Value> inline typename tree234<Key, Value>::iterator tree234<Key, Value>::end() noexcept
{
   return iterator(const_cast<tree234<Key, Value>&>(*this), 0);
}

template<class Key, class Value> inline typename tree234<Key, Value>::const_iterator tree234<Key, Value>::end() const noexcept
{
   return const_iterator(const_cast<tree234<Key, Value>&>(*this), 0);
}

template<class Key, class Value> inline typename tree234<Key, Value>::reverse_iterator tree234<Key, Value>::rbegin() noexcept
{
   return reverse_iterator{ end() }; 
}

template<class Key, class Value> inline typename tree234<Key, Value>::const_reverse_iterator tree234<Key, Value>::rbegin() const noexcept
{
    return const_reverse_iterator{ end() }; 
}

template<class Key, class Value> inline typename tree234<Key, Value>::reverse_iterator tree234<Key, Value>::rend() noexcept
{
    return reverse_iterator{ begin() }; 
}

template<class Key, class Value> inline typename tree234<Key, Value>::const_reverse_iterator tree234<Key, Value>::rend() const noexcept
{
    return const_reverse_iterator{ begin() }; 
}

template<class Key, class Value> typename tree234<Key, Value>::iterator& tree234<Key, Value>::iterator::increment() noexcept	    
{
  if (tree.isEmpty()) {

     return *this;  // If tree is empty or we are at the end, do nothing.
  }

  std::pair<const Node *, int> pair = tree.getSuccessor(cursor, key_index);

  if (pair.first == nullptr) { // nullptr implies there is no successor to cursor->keys_values[key_index].key().
                               // Therefore cached_cursor already points to last key/value in tree.

       current = nullptr; // We are now at the end. 

  } else {

      cursor = current = pair.first;
      key_index = pair.second;
  }

  return *this;
}

template<class Key, class Value> typename tree234<Key, Value>::iterator& tree234<Key, Value>::iterator::decrement() noexcept	    
{
  if (tree.isEmpty()) {

     return *this; 
  }
   
  if (current == nullptr) { // If already at the end, then simply return the cached value and don't call getPredecessor()
      current = cursor; 
      return *this;
  }
  
  std::pair<const Node *, int> pair = tree.getPredecessor(cursor, key_index);

  if (pair.first != nullptr) { // nullptr implies there is no predecessor cursor->keys_values[key_index].key().
      
      cursor = current = pair.first;
      key_index = pair.second;
  }

  return *this;
}

template<class Key, class Value> inline tree234<Key, Value>::iterator::iterator(iterator&& lhs) : \
             tree{lhs.tree}, current{lhs.current}, cursor{lhs.cursor}, key_index{lhs.key_index}  
{
   lhs.cursor = lhs.current = nullptr; 
}
/*
 */
template<class Key, class Value> bool tree234<Key, Value>::iterator::operator==(const iterator& lhs) const
{
 if (&lhs.tree == &tree) {
   /*
     The first if-test, checks for "at end".
     If current is nullptr, that signals the iterator is "one past the end.". If current is not nullptr, then current will equal cached_cursor.fist. current is either nullptr or cursor. cached_cursor never 
     becomes nullptr.
     In the else-if block block, we must check 'current == lhs.current' and not 'cursor == lhs.cursor' because 'cursor' never signals the end of the range, it never becomes nullptr,
     but the iterator returned by tree234::end()'s iterator always sets current to nullptr (to signal "one past the end").
     current to nullptr.
   */

   if (current == nullptr && lhs.current == nullptr) return true; 
   else if (current == lhs.current && key_index == lhs.key_index) { 
       
       return true;
   }    
 } 
 return false;
}

/*
 int getChildIndex(Node *cursor)
 Requires: cursor is not root, and  cursor is a node in the tree for which we want child_index such that
      current->parent->children[child_index] == current
 Returns: child_index as shown above. 
 */

template<class Key, class Value> int tree234<Key, Value>::iterator::getChildIndex(const typename tree234<Key, Value>::Node *p) const noexcept
{
  // Determine child_index such that current == current->parent->children[child_index]
  int child_index = 0;

  for (; child_index <= current->parent->getTotalItems(); ++child_index) {

       if (current == current->parent->children[child_index].get())
              break;
  }

  return child_index;
}

/*
 tree234<Key, Value>::const_iterator constructors
 */
template<class Key, class Value> inline tree234<Key, Value>::const_iterator::const_iterator(const tree234<Key, Value>& lhs) : iter{const_cast<tree234<Key, Value>&>(lhs)} 
{
}

template<class Key, class Value> inline tree234<Key, Value>::const_iterator::const_iterator(const tree234<Key, Value>& lhs, int i) : iter{const_cast<tree234<Key, Value>&>(lhs), i} 
{
}


template<class Key, class Value> inline tree234<Key, Value>::const_iterator::const_iterator::const_iterator(const typename tree234<Key, Value>::const_iterator& lhs) : iter{lhs.iter}
{
}

template<class Key, class Value> inline tree234<Key, Value>::const_iterator::const_iterator::const_iterator(typename tree234<Key, Value>::const_iterator&& lhs) : iter{std::move(lhs.iter)}
{
}
/*
 * This constructor also provides implicit type conversion from a iterator to a const_iterator
 */
template<class Key, class Value> inline tree234<Key, Value>::const_iterator::const_iterator::const_iterator(const typename tree234<Key, Value>::iterator& lhs) : iter{lhs}
{
}

template<class Key, class Value> inline bool tree234<Key, Value>::const_iterator::operator==(const const_iterator& lhs) const 
{ 
  return iter.operator==(lhs.iter); 
}

template<class Key, class Value> inline  bool tree234<Key, Value>::const_iterator::operator!=(const const_iterator& lhs) const
{ 
  return iter.operator!=(lhs.iter); 
}
     
template<class Key, class Value> inline typename tree234<Key, Value>::const_iterator& tree234<Key, Value>::const_iterator::operator++() noexcept	    
{
  iter.increment();
  return *this;
}

template<class Key, class Value> inline typename tree234<Key, Value>::const_iterator tree234<Key, Value>::const_iterator::operator++(int) noexcept	    
{
 const_iterator tmp{*this};

 iter.increment(); 

 return *this;
}

template<class Key, class Value> inline typename tree234<Key, Value>::const_iterator& tree234<Key, Value>::const_iterator::operator--() noexcept	    
{
   iter.decrement();
   return *this;
}

template<class Key, class Value> inline typename tree234<Key, Value>::const_iterator tree234<Key, Value>::const_iterator::operator--(int) noexcept	    
{
 const_iterator tmp{*this};

 iter.decrement(); 

 return *this;
}

/*
 * Returns -1 is pnode not in tree
 * Returns: 0 for root
 *          1 for level immediately below root
 *          2 for level immediately below level 1
 *          3 for level immediately below level 2
 *          etc. 
 */
template<class Key, class Value> int tree234<Key, Value>::depth(const Node *pnode) const noexcept
{
    if (pnode == nullptr) return -1;

    int depth = 0;
      
    for (const Node *current = root; current != nullptr; ++depth) {

      if (current->key() == pnode->key()) {

          return depth;

      } else if (pnode->key() < current->key()) {

          current = current->left;

      } else {

          current = current->right;
      }
    }

    return -1; // not found
}

template<class Key, class Value> inline int tree234<Key, Value>::height() const noexcept
{
   return height(root);
}

template<class Key, class Value> int tree234<Key, Value>::height(const Node* pnode) const noexcept
{
   if (pnode == nullptr) {

       return -1;

   } else {
       
      std::array<int, 4> heights;
      
      int num_children = pnode->getChildCount();
      
      for (auto i = 0; i < num_children; ++i) {
          
         heights[i] = height(pnode->children[i].get());
      }
      
      int max = *std::max_element(heights.begin(), heights.begin() + num_children);
      
      return 1 + max;
   }
}

/*
  Input: pnode must be in tree
 */
template<class Key, class Value> bool tree234<Key, Value>::isBalanced(const Node* pnode) const noexcept
{
    if (pnode == nullptr) return false; 

    std::array<int, 4> heights; // four is max number of children.
    
    int child_num = pnode->getChildCount();
    
    for (auto i = 0; i < child_num; ++i) {

         heights[i] = height(pnode->children[i].get());
    }
    
    int minHeight = *std::min_element(heights.begin(), heights.begin() + child_num);
    
    int maxHeight = *std::max_element(heights.begin(), heights.begin() + child_num);

    // Get absolute value of difference between max height and min of height of children.
    int diff = std::abs(maxHeight - minHeight);

    return (diff == 1 || diff ==0) ? true : false; // return true is absolute value is 0 or 1.
}

// Visits each Node in level order, testing whether it is balanced. Returns false if any node is not balanced.
template<class Key, class Value> bool tree234<Key, Value>::isBalanced() const noexcept
{
    std::queue<const Node *> nodes;

    nodes.push(root.get());

    while (!nodes.empty()) {

       const Node *current = nodes.front();
       
       nodes.pop(); // remove first element
       
       if (isBalanced(current) == false)  return false; 

       // push its children onto the stack 
       for (auto i = 0; i < current->getChildCount(); ++i) {
          
           if (current->children[i] != nullptr) {
               
               nodes.push(current->children[i].get());
           }   
       }
    }
    return true; // All Nodes were balanced.
}
#endif
