#ifndef	TREE234_H
#define	TREE234_H
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <array>
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <exception>
#include <iosfwd>
#include <string>
#include <iostream>
#include "value-type.h"

template<typename Key, typename Value> class tree234;  // Forward declaration

template<typename Key, typename Value> class tree234 {

   public:
  
      // Basic STL-required types:
      // Container typedef's used by STL.
      using key_type   = Key;
      using mapped_type = Value;
  
      using value_type = __value_type<Key, Value>::value_type;// = std::pair<const Key, Value>;  
      using difference_type = long int;
      using pointer         = value_type*; 
      using reference       = value_type&; 


   /*
   * This union eliminates repetitive const_cast<Node*>: const_cast<Key>(p.first) = some_noconst_key;
   * by holding two different types of pairs: _constkey_pair, where member first is 'const Key'; and _pair, where  
   * first is 'Key'.
   *
   * Note 1: Since anonymous unions do not implicitly destruct their members, we must explicitly call their destructors in 
   *         KeyValue::~KeyValue().
   * Note 2: Defining a user-declared destructor causes the default move constructor and move assignment to be created, so
   *         we explictily declare and defined them.
   */
   
  
   class Node; // Forward feference. 
   
   class Node { 
      /*
      Note: Node depends on both of tree234's template parameters, Key and Value, so we can 
      make it a nested class.
      */
      private:  
      friend class tree234<Key, Value>;             
      static const int MAX_KEYS;   
      
      enum class NodeType : int { two_node=1, three_node=2, four_node=3 };
      
      Node *parent; /* parent is only used for navigation of the tree. It never owns the memory
		      it points to. */
      
      int totalItems; /* If 1, two node; if 2, three node; if 3, four node. */   
      
      //--std::array<value_type, 3> keys_values; 
      std::array<__value_type<Key, Value>, 3> keys_values; 
      
      /*
      * For 2-nodes, children[0] is left pointer, children[1] is right pointer.
      * For 3-nodes, children[0] is left pointer, children[1] the middle pointer, and children[2] the right pointer.
      * For 4-nodes, children[0] is left pointer, children[1] the left middle pointer, and children[2] is the right middle pointer,
      * and children[3] is the right pointer.
      */
      std::array<std::unique_ptr<Node>, 4> children;
      
      constexpr Node *getParent() noexcept { return parent; }
      
      int getChildIndex() const noexcept;
      
      /* 
      * Returns {true, Node * pnode, int index} if key is found and pnode->keys_values[index] == found_key
      * Returns {false, Node * pnode, int index} if key is not found, and sets pnode and index so is the next prospective node and key
      * one level lower in the tree.
      */
      std::tuple<bool, typename tree234<Key, Value>::Node *, int>  find(Key key) const noexcept;
      
      int insert(Key key, const Value& value) noexcept;
      
      // Take ownership of child, inserting it a childNum. 
      void insertChild(int childNum, std::shared_ptr<Node>& pChild) noexcept;

      void connectChild(int childNum, std::unique_ptr<Node>& child) noexcept;

      Node *makeRoot4Node() noexcept;
      
      /*
      * Removes child node (implictly using move ctor) and shifts its children to fill the gap. Returns child pointer.
      */  
      std::shared_ptr<Node> disconnectChild(int child_index) noexcept; 

      std::pair<bool, int> chooseSibling(int child_index) const noexcept;
            
      public:
           
         Node() noexcept;
         
        ~Node() // For debug purposes only
         { 
            // std::cout << "~Node(): " << *this << std::endl; 
         }
          
         explicit Node(const Key& small, const Value& value, Node *in_parent=nullptr) noexcept : parent{in_parent}
         {
            keys_values[0] = {small, value};      
            // TODO: Does this implicitly set children to nullptr 
         } 
      
         explicit Node(const Node& node) noexcept; 
    
         // This constructor is called by copy_tree()
         Node(const std::array<value_type, 3>& lhs, Node *const lhs_parent, int lhs_totalItems) noexcept;             

         constexpr const Node *getParent() const noexcept;
      
         constexpr int getTotalItems() const noexcept;
         constexpr int getChildCount() const noexcept;
      
         constexpr const Node *getRightMostChild() const noexcept { return children[getTotalItems()].get(); }
      
         // Helps in debugging
         void printKeys(std::ostream&);

        /*
            TODO: Changes some of these, as needed (after thinking it through) to call keys_values[i].__ref() instead of keys_values[i].__get_value()
            I can even reimplement them as:
 
              constexpr const Key& key(int i) const noexcept 
              {
                 return keys_values[i]._cc.first; //  'template<typename _Key, typename _Value> struct keys_values[i].__value_type' does not have members first and second.
              } 
      
              constexpr Key& key(int i) noexcept 
              {
                 return const_cast<Key&>(keys_values[i]._cc).first; //  'template<typename _Key, typename _Value> struct keys_values[i].__value_type' does not have members first and second.
              } 
      
              constexpr const Value& value(int i) const noexcept 
              { 
                 return keys_values[i]._cc.second;
              }  
      
              constexpr Value& value() noexcept 
              {
                 return keys_values[i]._cc.second;
              } 
      
    
           */ 
        

        constexpr const Key& key(int i) const noexcept 
        {
           return keys_values[i].__get_value().first; //  'template<typename _Key, typename _Value> struct keys_values[i].__value_type' does not have members first and second.
        } 

        constexpr Key& key(int i) noexcept 
        {
           return const_cast<Key&>(keys_values[i].__get_value().first); //  'template<typename _Key, typename _Value> struct keys_values[i].__value_type' does not have members first and second.
        } 

        constexpr const Value& value(int i) const noexcept 
        { 
           return keys_values[i].__get_value().second; 
        }  

        constexpr Value& value(int i) noexcept 
        {
           return keys_values[i].__get_value().second; 
        } 

        int getIndexInParent() const;
      
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

        std::ostream& debug_print(std::ostream& ostr) const noexcept;
      
     }; // end class Tree<Key, Value>::Node  
   
   class NodeLevelOrderPrinter {
   
      std::ostream& ostr;
      int current_level;
      int height;

      std::ostream& (Node::*pmf)(std::ostream&) const noexcept;

      void display_level(std::ostream& ostr, int level) const noexcept
      {
        ostr << "\n\n" << "current_level = " <<  current_level << ' '; 
         
        // Provide some basic spacing to tree appearance.
        std::size_t num = height - current_level + 1;
      
        std::string str( num, ' ');
      
        ostr << str; 
      }
      
      public: 
      
      NodeLevelOrderPrinter (int height_in,  std::ostream& (Node::*pmf_)(std::ostream&) const noexcept, std::ostream& ostr_in):  ostr{ostr_in}, current_level{0}, height{height_in}, pmf{pmf_} {}
          
      NodeLevelOrderPrinter (const NodeLevelOrderPrinter& lhs): ostr{lhs.ostr}, current_level{lhs.current_level}, height{lhs.height}, pmf{lhs.pmf} {}
      
      void operator ()(const Node *pnode, int level)
      { 
          // Did current_level change?
          if (current_level != level) { 
         
              current_level = level;
         
              display_level(ostr, level);       
          }
         
          (pnode->*pmf)(std::cout);
         
          std::cout << ' ' << std::flush;
      }
   };
   
   private:
   
   std::unique_ptr<Node>  root; 
   
   int tree_size; // adjusted by insert(), remove(), operator=(const tree234...), move ctor
   
   // Implementations of the public depth-frist traversal methods    
   template<typename Functor> void DoInOrderTraverse(Functor f, const Node *proot) const noexcept;
   
   template<typename Functor> void DoPostOrderTraverse(Functor f,  const Node *proot) const noexcept;
   
   template<typename Functor> void DoPreOrderTraverse(Functor f, const Node *proot) const noexcept;
   
   Node *split(Node *node, Key new_key) noexcept;  // called during insert(Key key) to split 4-nodes when encountered.
   
   // Returns node with smallest value of tree whose root is 'root'
   const Node *min(const Node* root) const noexcept; 
   const Node *max(const Node* root) const noexcept; 
   
   int  height(const Node *pnode) const noexcept;
   
   int  depth(const Node *pnode) const noexcept;
   bool isBalanced(const Node *pnode) const noexcept;
   
   bool find(const Node *current, Key key) const noexcept; 
   
   std::tuple<bool, Node *, int> find_insert_node(Node *pnode, Key new_key) noexcept;  // Called during insert

   Node *get_successor_node(Node *pnode, int child_index) noexcept; // Called during remove()

   std::tuple<Node *, int, Node *> get_delete_successor(Node *pdelete, Key delete_key, int delete_key_index) noexcept;

 public:
   
   using node_type = Node; 
   
   void debug() noexcept;  // As an aid in writting any future debug code.
 
   explicit tree234() noexcept : root{}, tree_size{0} { } 
   
   tree234(const tree234& lhs) noexcept; 
   tree234(tree234&& lhs) noexcept;     // move constructor
   
   tree234& operator=(const tree234& lhs) noexcept; 
   tree234& operator=(tree234&& lhs) noexcept;    // move assignment
   
   tree234(std::initializer_list<std::pair<Key, Value>> list) noexcept; 
   
   constexpr int size() const;

   ~tree234() = default; 
   
   // Breadth-first traversal
   template<typename Functor> void levelOrderTraverse(Functor f) const noexcept;
   
   // Depth-first traversals
   template<typename Functor> void inOrderTraverse(Functor f) const noexcept;
   
   template<typename Functor> void iterativeInOrderTraverse(Functor f) const noexcept;
   
   template<typename Functor> void postOrderTraverse(Functor f) const noexcept;
   template<typename Functor> void preOrderTraverse(Functor f) const noexcept;
   
   // Used during development and testing 
   template<typename Functor> void debug_dump(Functor f) noexcept;
   
   bool find(Key key) const noexcept;
   
   void insert(Key key, const Value &) noexcept; 
   
   void insert(const value_type& pair) noexcept { insert(pair.first, pair.second); } 
   
   void printlevelOrder(std::ostream&) const noexcept;
   
   void debug_printlevelOrder(std::ostream& ostr) const noexcept;

   void printInOrder(std::ostream&) const noexcept;
   
   void printPreOrder(std::ostream&) const noexcept;
   
   void printPostOrder(std::ostream&) const noexcept;
   
   bool isEmpty() const noexcept;
   
   int  height() const noexcept;
   
   bool isBalanced() const noexcept;
   
   friend std::ostream& operator<<(std::ostream& ostr, const tree234<Key, Value>& tree)
   {
      tree.printlevelOrder(ostr);
      return ostr;
   }
   
   // Bidirectional stl-compatible constant iterator
   class iterator { 
					       
      public:
      using difference_type  = std::ptrdiff_t; 
      using value_type       = tree234<Key, Value>::value_type; 
      using reference        = value_type&; 
      using pointer          = value_type*;
      
      using iterator_category = std::bidirectional_iterator_tag; 
				          
      friend class tree234<Key, Value>; 
      
      private:
       tree234<Key, Value>& tree; 
      
       const Node *current;
       const Node *cursor; //  points to "current" node.
       int key_index;

       std::stack<int> child_indexes; 
       
       std::pair<const typename tree234<Key, Value>::Node *, int> findLeftChildAncestor() noexcept;
      
       iterator& increment() noexcept; 
      
       iterator& decrement() noexcept;
      
       iterator(tree234<Key, Value>& lhs, int i);  // called by end()   

       std::pair<const Node *, int> getSuccessor(const Node *current, int key_index) noexcept;
       std::pair<const Node *, int> getPredecessor(const Node *current, int key_index) noexcept;
       
       // Subroutines of the two methods above.
       std::pair<const Node *, int> getInternalNodeSuccessor(const Node *pnode,  int index_of_key) noexcept;
       std::pair<const Node *, int> getInternalNodePredecessor(const Node *pnode,  int index_of_key) noexcept;
       
       std::pair<const Node *, int> getLeafNodeSuccessor(const Node *pnode, int key_index);
       std::pair<const Node *, int> getLeafNodePredecessor(const Node *pnode, int key_index);

       const Node *get_min() noexcept;

       const Node *get_max() noexcept;

       void push(int child_index)
       {
           child_indexes.push(child_index);
       }

       int pop()
       {
          if (child_indexes.empty()) {
              throw(std::logic_error("iterator popping empty stack"));
          }
          auto i = child_indexes.top();
          child_indexes.pop();
          return i; 
       }

       constexpr reference dereference() noexcept 
       { 
           return const_cast<Node *>(cursor)->constkey_pair(key_index); 
       } 
   
      public:

       iterator(const iterator& lhs) = default; 
      
       iterator(iterator&& lhs); 

       explicit iterator(tree234<Key, Value>&); 
      
       bool operator==(const iterator& lhs) const;
       
       constexpr bool operator!=(const iterator& lhs) const { return !operator==(lhs); }

       iterator& operator++() noexcept 
       {
          increment();
          return *this;
       } 
      
       iterator operator++(int) noexcept
       {
          iterator tmp(*this);
          increment();
          return tmp;
       } 
       
       iterator& operator--() noexcept 
       {
          decrement();
          return *this;
       } 
      
       iterator operator--(int) noexcept
       {
          iterator tmp(*this);
          decrement();
          return tmp;
       } 
       
       reference operator*() noexcept 
       { 
           return dereference(); 
       } 
      
       const std::pair<const Key, Value>& operator*() const noexcept 
       { 
           return dereference(); 
       }
       
       typename tree234<Key, Value>::value_type *operator->() noexcept;
       
       friend std::ostream& operator<<(std::ostream& ostr, const iterator& iter)
       {
          return iter.print(ostr);  
       } 

       std::ostream& print(std::ostream& ostr) const noexcept;
   };
   
   class const_iterator {
					    
      public:
      using difference_type   = std::ptrdiff_t; 
      using value_type        = tree234<Key, Value>::value_type; 
      using reference	      = const value_type&; 
      using pointer           = const value_type*;
      
      using iterator_category = std::bidirectional_iterator_tag; 
				          
      friend class tree234<Key, Value>;   
      
      private:
       iterator iter; 
      
       const_iterator(const tree234<Key, Value>& lhs, int i); // called by end()
          
       constexpr const std::pair<const Key, Value>& dereference() const noexcept 
       { 
           return iter.cursor->constkey_pair(iter.key_index); 
       }
       
      public:
       
       explicit const_iterator(const tree234<Key, Value>& lhs);
      
       const_iterator(const const_iterator& lhs);
       
       const_iterator(const_iterator&& lhs); 
      
       // Provides the implicit conversion from iterator to const_iterator     
       const_iterator(const typename tree234<Key, Value>::iterator& lhs); 
      
       bool operator==(const const_iterator& lhs) const;
       bool operator!=(const const_iterator& lhs) const;
       
       const_iterator& operator++() noexcept 
       {
          iter.increment();
          return *this;
       } 
      
       const_iterator operator++(int) noexcept
       {
          const_iterator tmp(*this);
          iter.increment();
          return tmp;
       } 
       
       const_iterator& operator--() noexcept 
       {
          iter.decrement();
          return *this;
       } 
      
       const_iterator operator--(int) noexcept
       {
          const_iterator tmp(*this);
          iter.decrement();
          return tmp;
       }
      
       const std::pair<const Key,Value>&  operator*() const noexcept 
       {
         return dereference(); 
       } 
      
       const std::pair<const Key, Value> *operator->() const noexcept { return &this->operator*(); } 
       
       friend std::ostream& operator<<(std::ostream& ostr, const const_iterator& it)
       {
          return it.iter.print(ostr);  
       } 

   };
   
   iterator begin() noexcept;  
   iterator end() noexcept;  
   
   const_iterator begin() const noexcept;  
   const_iterator end() const noexcept;  
   
   using reverse_iterator = std::reverse_iterator<iterator>;
   using const_reverse_iterator = std::reverse_iterator<const_iterator>;
   
   reverse_iterator rbegin() noexcept;  
   reverse_iterator rend() noexcept;  
   
   const_reverse_iterator rbegin() const noexcept;  
   const_reverse_iterator rend() const noexcept;    
};

template<class Key, class Value> inline bool tree234<Key, Value>::isEmpty() const noexcept
{
   return root == nullptr ? true : false;
}

template<typename Key, typename Value> const int  tree234<Key, Value>::Node::MAX_KEYS = 3; 

/*
* Node constructors. Note: While all children are initialized to nullptr, this is not really necessary. 
* Instead your can simply set children[0] = nullptr, since a Node is a leaf if and only if children[0] == 0'
*/
template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node()  noexcept : parent{nullptr}, totalItems{0}
{
 // TODO: Use default member construction for keys_values and children 
}

template<typename Key, typename Value> inline  tree234<Key, Value>::Node::Node(const Node& lhs)  noexcept : keys_values{lhs.keys_values}, totalItems{lhs.totalItems} 
{
  if (lhs.parent == nullptr) // If lhs is the root, then set parent to nullptr.
      parent = nullptr;

  if (lhs.isLeaf()) { // A leaf node's children are all nullptr
      for (auto i = 0; i < lhs.getChildCount(); ++i) 
            children[i] = nullptr;
       
  } else {

      // The make_unique<Node> calls will in turn recursively invoke the constructor again, resulting in the entire tree rooted at
      // lhs being copied.
      for (auto i = 0; i < lhs.getChildCount(); ++i) { 
           children[i] = std::make_unique<Node>(lhs.children[i]);     
           children[i]->parent = this;
      }  
  }
}

template<class Key, class Value> std::ostream& tree234<Key, Value>::Node::print(std::ostream& ostr) const noexcept
{
   ostr << "[";
   
   if (getTotalItems() == 0) { // remove() situation when merge2Nodes() is called
   
       ostr << "empty"; 
   
   } else {
   
       for (auto i = 0; i < getTotalItems(); ++i) {
       
           ostr << key(i); // or to print both keys and values do: ostr << keys_values[i];
       
           if (i + 1 == getTotalItems())  {
               continue;
       
           } else { 
               ostr << ", ";
           }
       }
   }
   
   ostr << "]";
   return ostr;
}

template<class Key, class Value> int tree234<Key, Value>::Node::getIndexInParent() const 
{
   for (int child_index = 0; child_index <= parent->getTotalItems(); ++child_index) { // Check the address of each of the children of the parent with the address of "this".
   
       if (this == parent->children[child_index].get()) {
          return  child_index;
       }
   }
       
   throw std::logic_error("Cannot find the parent child index of the node. The node may be the tree's root or the invariant may have been violated.");
}
 
/*
 * Does a post order tree traversal, using recursion and deleting nodes as they are visited.
 */

template<typename Key, typename Value> inline tree234<Key, Value>::tree234(const tree234<Key, Value>& lhs) noexcept
{ 
   root = std::make_unique<Node>(*lhs.root); 
   tree_size = lhs.tree_size;
/*
   destroy_tree(root); 
   copy_tree(lhs.root, root);
 */
}
// move constructor
template<typename Key, typename Value> inline tree234<Key, Value>::tree234(tree234&& lhs) noexcept : root{std::move(lhs.root)}, tree_size{lhs.tree_size}  
{
    root->parent = nullptr;
    lhs.tree_size = 0;
}

template<typename Key, typename Value> inline tree234<Key, Value>::tree234(std::initializer_list<std::pair<Key, Value>> il) noexcept : root(nullptr), tree_size{0} 
{
    for (auto&& [key, value]: il) { 
                    
         insert(key, value);
    }
}

/*
Finding the successor of a given node 
-------------------------------------
Requires:
    1. If position is beg, Node *current and key_index MUST point to first key in tree. 
    2. If position is end, Node *current and key_index MUST point to last key in tree.
      
    3. If position is in_between, current and key_index do not point to either the first key in the tree or last key. If the tree has only one node,
       the state can only be in_between if the first node is a 3-node.
    Returns:
    pair<const Node *, int>, where pnode->key(key_index) is next in-order key. Note, if the last key has already been visited, the pointer returned will be nullptr.
    The pseudo code for getting the successor is from: http://ee.usc.edu/~redekopp/cs104/slides/L19_BalancedBST_23.pdf:
*/
template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::iterator::getSuccessor(const Node *current, int key_index) noexcept
{
  if (current->isLeaf()) { // If leaf node

     const auto& root = tree.root; 

     if (current == root.get()) { // special case: current is root, which is a leaf      

         // If root has more than one value--it is not a 2-node--and key_index is not the right-most key/value pair in the node,
         // return the key--the index of the key--immediately to the right. 
         if (!root->isTwoNode() && key_index != (root->getTotalItems() - 1)) { 

             return {current, key_index + 1};
         } 
                  
         return {nullptr, 0}; // There is no successor because key_index is the right-most index.
 
     } else {

        return getLeafNodeSuccessor(current, key_index);
     }

  } else { // else internal node successor

      return getInternalNodeSuccessor(current, key_index);
  }
}

/* 
   Requires: pnode is an internal node not a leaf node.
   Returns:  pointer to successor of internal node.
 */
template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::iterator::getInternalNodeSuccessor(const typename tree234<Key, Value>::Node *pnode, int key_index) noexcept	    
{
 auto child_index = key_index + 1;

 // Get first right subtree of pnode, and descend to its left most left node.
 for (const Node *pcurrent =  pnode->children[child_index].get(); pcurrent != nullptr; pcurrent = pcurrent->children[child_index].get()) {  

    push(child_index);

    pnode = pcurrent;

    child_index = 0; // Set only after push(child_index)
 }

 return {pnode, 0};
}

/*
 Requires: pnode is a leaf node other than the root.
 */
template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::iterator::getLeafNodeSuccessor(const Node *pnode, int key_index) 
{
 const auto& root = tree.root;

  // Handle the easy case: a 3- or 4-node in which key_index is not the right most value in the node.
  if (!pnode->isTwoNode() && (pnode->getTotalItems() - 1) != key_index) { 

      return {pnode, key_index + 1};  
  }

  // Handle the harder case: pnode is a leaf node and pnode->keys_values[key_index] is the right-most key/value in this node.

  // Get child_index such that parent->children[child_index] == pnode.
  auto child_index = pop();
  
  auto current_key = pnode->key(key_index);
  
  // Handle the case: pnode is the right-most child of its parent... 
  if (pnode->parent->children[child_index].get() == pnode->parent->getRightMostChild()) { 

  /*
   pnode is a leaf node, and pnode is the right-most child of its parent, and key_index is the right-most index or last index into pnode->keys(). To find the successor, we need the first ancestor node that contains
   a value great than current_key. To find this ancester, we ascend the tree until we encounter the first ancestor node that is not a right-most child of its parent, that is, where
   ancester != ancestor->parent->getRightMostChild(). If the ancestor becomes equal to the root before this happens, there is no successor: pnode is the right most node in the tree and key_index is its right-most key.
   */
     const Node *parent = pnode->parent;

     // Ascend upward the parent pointer as long as the child continues to be the right most child (of its parent). 
     for(;child_index == parent->getTotalItems(); parent = pnode->parent)  { 
        
         // If child is still the right most child, and if it is also the root, then, there is no successor. pnode holds the largest key in the tree. 
         if (parent == root.get()) {
          
             return {nullptr, 0};  // To indicate "no-successor" we return the pair: {nullptr, 0}. 
         }

         child_index = pop();
         pnode = parent;
     }
     /* 
        We know that pnode now is NOT the right most child of its parent. 
        We need to ascertain the next index, next_index, such that parent->key(next_index) > current_key. We know 'pnode == parent->children[child_index]'. child_index is therefore
        also the index of the successor key in the parent: successor-key == parent->key(child_index). We can see this by looking these possiblities. First, a 3-node. 
        If we ascende from the leaf node of the right-most subtree of key 5,then 36 is the successor, and 36 == parent->key(child_index)
           [3,       36]  
           /        / \
          /        /   \
        [1, 2]  [4, 5]  [47]
        /   \   / | \   / \
        and a 4-node can be viewed as three catenated 2-nodes in which the two middle child are shared
          
           [2,   4,   36]  
          /     / \     \
        [1]  [3]   [5]  [37] 
        / \  / \   / \   / \
        Again, if ascend, say, the leaf of the right subtree root at key 3, then 4 is the successor; and if ascend, say, the leaf of the right subtree whose root is key 5, then 36 is the successor, and
        36 = parent->key(child_index);
      */

     return {parent, child_index};

  } else { // Handle the case: pnode is not the right-most child of its parent. 
      /* 
        ...else we know that pnode is NOT the right most child of its parent (and it is a leaf). We also know that key_index is the right most value of pnode (and in the case of a 2-node, key_index can only be zero, which is 
        also the "right-most" index).
        We need to ascertain the next index, next_index, such that pnode->parent->key(next_index) > pnode->key(key_index). To determine next_index, we can view a 3-node as two catenated 2-nodes in which the the middle child is
        shared between these two "2-nodes", like this
      
           [3,       6]  
           /  \     / \
          /    \   /   \
        [1, 2]  [4, 5]  [7]
        and a 4-node can be viewed as three catenated 2-nodes in which the two middle child are shared
          
           [2,   4,   6]  
          /  \  / \  / \
        [1]  [3]   [5]  [7] 
        If the leaft node is a 3- or 4-node, we already know (from the first if-test) that the current key is the last, current_key == pnode->getTotalItems() - 1. So the we simply go up on level to find the in order successor.    
        We know pnode == parent->children[child_index]. child_index also is index of the successor key in the parent: successor-key == parent->key(child_index).
      */

     if (child_index > static_cast<int>(Node::NodeType::four_node)) {

         throw std::logic_error("child_index was not between 0 and 3 in getLeafNodeSuccessor()");
     }

     return {pnode->parent, child_index};
  }  
}

template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::iterator::getPredecessor(const typename  tree234<Key, Value>::Node *current, int key_index) noexcept
{
 const auto& root = tree.root;

  if (current->isLeaf()) { // If leaf node

     if (current == root.get()) { // root is leaf      

         if (key_index != 0) {
                  
             return {current, key_index - 1};
         } 
         return {nullptr, 0};
            
     } else {

        return getLeafNodePredecessor(current, key_index);
     }

  } else { // else internal node

      return getInternalNodePredecessor(current, key_index);
  }
}

template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::iterator::getInternalNodePredecessor(\
     const typename tree234<Key, Value>::Node *pnode, int key_index) noexcept	    
{
 auto child_index = key_index;

 for (const Node *pcurrent = pnode->children[key_index].get(); pcurrent != nullptr; pcurrent = pcurrent->children[child_index].get()) {

    push(child_index);

    pnode = pcurrent;

    child_index = pcurrent->getTotalItems(); // Must do after push() 
 }

 return {pnode, pnode->totalItems - 1}; 
}
/* 
Finding the predecessor of a given node 
---------------------------------------
  If left child exists, predecessor is the right most node of the left subtree
  Else we walk up the ancestor chain until you traverse the first right child pointer (find the first node that is a right child of its 
  parent...that parent is the predecessor)
  If you get to the root w/o finding a node that is a right child, there is no predecessor
*/

template<class Key, class Value> std::pair<const typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::iterator::getLeafNodePredecessor(const Node *pnode, int index)
{
  // Handle trivial case: if the leaf node is not a 2-node (it is a 3-node or 4-node, and key_index is not the first key), simply set index of predecessor to index - 1. 
  if (!pnode->isTwoNode() && index != 0) {

      return {pnode, index - 1}; 
  }

  // Get child_index such that pnode == pnode->parent->children[child_index]
  auto child_index = pop();

  if (child_index != 0) { // If pnode is not the left-most child, the predecessor is in the parent

      return  {pnode->parent, child_index - 1}; 

  } else {

   /* 
    To find the next smallest node the logic is similar to finding the successor: We walk up the parent chain until we traverse the first parent that
    is not a left-most child of its parent. That parent is the predecessor. If we get to the root without finding a node that is a right child, there is no predecessor.
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
      the predecessor is pnode->key(1). Thus, the predecessor is the key at child_index - 1.
      */
      const Node *parent = pnode->parent;

     // Ascend upward the parent pointer as long as the child continues to be the left most child (of its parent). 
     for(;child_index == 0; parent = pnode->parent)  { 
        
         // child is still the left most child, but if it is also the root, then, there is no predecessor. child holds the smallest key in the tree. 
         if (parent == tree.root.get()) {
          
             return {nullptr, 0};  //  {nullptr, 0} indicates "no predecessor".
         }

         child_index = pop();
         pnode = parent;
     }

     // The predecessor will be the first key, starting with the right most key, that is less than current_key. 
     return {parent, child_index - 1}; 

  } // end else
}

// copy assignment
template<typename Key, typename Value> inline tree234<Key, Value>& tree234<Key, Value>::operator=(const tree234& lhs) noexcept 
{
  if (this == &lhs)  {
      
      return *this;
  }
  
  destroy_tree(root); // free all the nodes of the current tree 

  tree_size = lhs.tree_size;

  copy_tree(lhs.root, root);

  return *this;
}


template<typename Key, typename Value> inline void tree234<Key, Value>::Node::printKeys(std::ostream& ostr)
{
  ostr << "["; 

  for(auto i = 0; i < getTotalItems(); ++i) {

      ostr << key(i);

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
             
template<typename Key, typename Value> inline int tree234<Key, Value>::height() const noexcept
{
  int depth = 0;

  for (auto current = root.get(); current != nullptr; current = current->children[0].get()) {

       ++depth;
  }

  return depth;
}
// Move assignment operator
template<typename Key, typename Value> inline tree234<Key, Value>& tree234<Key, Value>::operator=(tree234&& lhs) noexcept 
{
    tree_size = lhs.tree_size;

    lhs.tree_size = 0;

    root = std::move(lhs.root);

    root->parent = nullptr;
}
/*
 * F is a functor whose function call operator takes a 1.) const Node * and an 2.) int, indicating the depth of the node from the root,
 * which has depth 1.
 */
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::levelOrderTraverse(Functor f) const noexcept
{
   if (root.get() == nullptr) return;
   
   // pair of: 1. const Node * and 2. level of tree.
   std::queue<std::pair<const Node*, int>> queue; 

   auto level = 1;

   queue.push({root.get(), level});

   while (!queue.empty()) {

        auto& [pnode, tree_level] = queue.front(); 

        f(pnode, tree_level); // Call functor 
         
        if (!pnode->isLeaf()) { // If it was not a leaf node, push its children onto the queue
            
            for(auto i = 0; i < pnode->getChildCount(); ++i) {

               queue.push({pnode->children[i].get(), tree_level + 1});  
            }
        }

        queue.pop(); // Remove the node used in the call to functor f above.
   }
}
/*
 * This method allows the tree to be traversed in-order step-by-step
 */
template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::iterativeInOrderTraverse(Functor f) const noexcept
{
   const Node *current = min(root.get());
   int key_index = 0;

   while (current != nullptr)  {
 
      f(current->pair(key_index)); 

      //std::pair<const Node *, int> pair = getSuccessor(current, key_index);  
      auto &&[next_pnode, next_index] = getSuccessor(current, key_index);  
  
      current = next_pnode; 
      key_index = next_index;
  }
}
/*
 * Return the node with the "smallest" key in the tree, the left most left node.
 */
template<typename Key, typename Value> inline const typename tree234<Key, Value>::Node *tree234<Key, Value>::min(const Node *current) const noexcept
{
   while (current->children[0].get() != nullptr) {

        current = current->children[0].get();
   }
   return current;
}
/*
 * Return the node with the largest key in the tree, the right most left node.
 */
template<typename Key, typename Value> inline const typename tree234<Key, Value>::Node *tree234<Key, Value>::max(const Node *current) const noexcept
{
   while (current->getRightMostChild() != nullptr) {

        current = current->getRightMostChild();
   }
   return current;
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::inOrderTraverse(Functor f) const noexcept
{
   DoInOrderTraverse(f, root.get());
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::postOrderTraverse(Functor f) const noexcept
{
   DoPostOrderTraverse(f, root.get());
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::preOrderTraverse(Functor f) const noexcept
{
   DoPreOrderTraverse(f, root.get());
}

template<typename Key, typename Value> template<typename Functor> inline void tree234<Key, Value>::debug_dump(Functor f) noexcept
{
   DoPostOrder4Debug(f, root.get());
}
/*
 * Calls functor on each node in post order. Uses recursion.
 */
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::DoPostOrderTraverse(Functor f, const Node *current) const noexcept
{  
   if (current == nullptr) return;

   switch (current->getTotalItems()) {

      case 1: // two node
            DoPostOrderTraverse(f, current->children[0].get());

            DoPostOrderTraverse(f, current->children[1].get());

            f(current->constkey_pair(0));
            break;

      case 2: // three node
            DoPostOrderTraverse(f, current->children[0].get());

            DoPostOrderTraverse(f, current->children[1].get());

            f(current->constkey_pair(0));

            DoPostOrderTraverse(f, current->children[2].get());

            f(current->constkey_pair(1));
            break;

      case 3: // four node
            DoPostOrderTraverse(f, current->children[0].get());

            DoPostOrderTraverse(f, current->children[1].get());

            f(current->constkey_pair(0));

            DoPostOrderTraverse(f, current->children[2].get());

            f(current->constkey_pair(1));

            DoPostOrderTraverse(f, current->children[3].get());

            f(current->constkey_pair(1));
 
            break;
   }
}

/* 
 * Calls functor on each node in pre order. Uses recursion.
 */
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::DoPreOrderTraverse(Functor f, const Node *current) const noexcept
{  

   if (current == nullptr) return;

   f(current->constkey_pair(0)); // Visit keys_values[0] 

   switch (current->getTotalItems()) {

      case 1: // two node

        DoPreOrderTraverse(f, current->children[0].get());

        DoPreOrderTraverse(f, current->children[1].get());

        break;

      case 2: // three node

        DoPreOrderTraverse(f, current->children[0].get());

        DoPreOrderTraverse(f, current->children[1].get());

        f(current->constkey_pair(1));// Visit Node::keys_values[1]

        DoPreOrderTraverse(f, current->children[2].get());

        break;

      case 3: // four node

        DoPreOrderTraverse(f, current->children[0].get());

        DoPreOrderTraverse(f, current->children[1].get());

        f(current->constkey_pair(1));// Visit Node::keys_values[1]

        DoPreOrderTraverse(f, current->children[2].get());

        f(current->constkey_pair(2));// Visit Node::keys_values[2]

        DoPreOrderTraverse(f, current->children[3].get());

        break;
   }
}

/*
 * Calls functor on each node in in-order traversal. Uses recursion.
 */
template<typename Key, typename Value> template<typename Functor> void tree234<Key, Value>::DoInOrderTraverse(Functor f, const Node *current) const noexcept
{     
   if (current == nullptr) return;

   switch (current->getTotalItems()) {

      case 1: // two node
        DoInOrderTraverse(f, current->children[0].get());

        f(current->constkey_pair(0));

        DoInOrderTraverse(f, current->children[1].get());
        break;

      case 2: // three node
        DoInOrderTraverse(f, current->children[0].get());

        f(current->constkey_pair(0));

        DoInOrderTraverse(f, current->children[1].get());
 
        f(current->constkey_pair(1));

        DoInOrderTraverse(f, current->children[2].get());
        break;

      case 3: // four node
        DoInOrderTraverse(f, current->children[0].get());

        f(current->constkey_pair(0));

        DoInOrderTraverse(f, current->children[1].get());
 
        f(current->constkey_pair(1));

        DoInOrderTraverse(f, current->children[2].get());

        f(current->constkey_pair(2));

        DoInOrderTraverse(f, current->children[3].get());
 
        break;
   }
}

/*
 * Preconditionss: childIndex is within the range for the type of node, and child is not nullptr.
 *  
 * connectChild() adopts input child node as its (childIndex + 1)th child by doing:
 *
 *    children[childIndex] = std::move(child);
 *    children[childIndex]->parent = this; 
 *  
 */
template<typename Key, typename Value> inline void  tree234<Key, Value>::Node::connectChild(int childIndex, std::unique_ptr<Node>& child)  noexcept
{
  children[childIndex] = std::move( child ); 
  
  if (children[childIndex] != nullptr) { 

       children[childIndex]->parent = this; 
  }
}
/*
 * Returns tuple of three values: <bool, Node *, int>. 
 * If key found n this Node, we return this tuple: {true, pointer to node containing key, the index into Node::key_values of the key}.
 * If key is not found, we return this tuple: {false, pointer to next child with which to continue the downward search of the tree, 0}. 
 */
template<class Key, class Value> inline std::tuple<bool, typename tree234<Key, Value>::Node *, int> tree234<Key, Value>::Node::find(Key lhs_key) const noexcept 
{
  for(auto i = 0; i < getTotalItems(); ++i) {

     if (lhs_key < key(i)) {
            
         return {false, children[i].get(), 0}; 

     } else if (key(i) == lhs_key) {

         return {true, const_cast<Node *>(this), i};
     }
  }

  // lhs_key must be greater than the last key (because it is not less than or equal to it).
  // next = children[totalItems].get(); 
  return {false, children[getTotalItems()].get(), 0};
}
/*
 * Require: childIndex is within the range for the type of node.
 * Returns: child pointer.
 * Note: disconnectChild() must always be called before removeItem(); otherwise, it will not work correctly (because totalItems
 * will have been altered).
 */
template<typename Key, typename Value> inline std::shared_ptr<typename tree234<Key, Value>::Node> tree234<Key, Value>::Node::disconnectChild(int childIndex) noexcept // ok
{
  std::shared_ptr<Node> node{ std::move(children[childIndex] ) }; // invokes shared_ptr<Node> move ctor.

  // shift children (whose last 0-based index is totalItems) left to overwrite removed child i.
  for(auto i = childIndex; i < getTotalItems(); ++i) {

       children[i] = std::move(children[i + 1]); // shift remaining children to the left. Calls shared_ptr<Node>::operator=(shared_ptr<Node>&&)
  } 

  return node; // invokes shared_ptr<Node> move constructor since node is an rvalue.
}

/*
 * Preconditions: node is not a four node, and key is not present in node.
 * Purpose: Shifts keys_values needed so key can be inserted in sorted position. Returns index of inserted key.
 */
template<typename Key, typename Value> int  tree234<Key, Value>::Node::insert(Key lhs_key, const Value& lhs_value)  noexcept // ok. Maybe add a move version, too: insertKey(Key, Value&&)
{ 
  // start on right, examine items
  for(auto i = getTotalItems() - 1; i >= 0 ; --i) {

      if (lhs_key < key(i)) { // if key[i] is bigger
          
          keys_values[i + 1] = std::move(keys_values[i]); // shift it right
          
      } else {

          key(i + 1) = lhs_key; // insert new item
          value(i + 1) = lhs_value;  
        ++totalItems;        // increase the total item count
          return i + 1;      // return index of inserted key.
      } 
    } 

    // key is smaller than all keys_values, so insert it at position 0
   keys_values[0].__ref() = {lhs_key, lhs_value};  

    /*
    key(0) = lhs_key;  
    value(0) = lhs_value; 
     */
  ++totalItems; // increase the total item count
    return 0;
}
/*
 * Inserts key_value pair into its sorted position in this Node and makes largerNode its right most child.
 */
/*++
template<typename Key, typename Value> void tree234<Key, Value>::Node::insert(typename tree234<Key, Value>::value_type&& key_value, std::unique_ptr<Node>& largerNode) noexcept 
{ 
  // start on right, examine items
  for(auto i = getTotalItems() - 1; i >= 0 ; --i) {

      if (key_value.key() < key(i)) { // if key[i] is bigger

          keys_values[i + 1] = std::move(keys_values[i]); // shift it right...

      } else {

          keys_values[i + 1] = std::move(key_value);

        ++totalItems;        // increase the total item count

          insertChild(i + 2, largerNode); 
          return;      // return index of inserted key.
      } 
    } 

    // key is smaller than all keys_values, so insert it at position 0
    keys_values[0] = std::move(key_value); 

  ++totalItems; // increase the total item count

    insertChild(1, largerNode); 
    return;
}
++*/ 
/*
 Input: A new child to insert at child index position insert_index. The current number of children currently is given by children_num.
 */
template<typename Key, typename Value> void tree234<Key, Value>::Node::insertChild(int insert_index, std::shared_ptr<Node>& newChild) noexcept
{
   int last_index = getTotalItems() - 1;  // While totalItems reflects the correct number of keys, the number of children currently is also equal to the number of keys.

   // ...move its children right, starting from its last child index and stopping just before insert_index.
   for(auto i = last_index; i >= insert_index; i--)  {

       connectChild(i + 1, children[i]);       
   }

   // Then insert the new child whose key is larger than key_value.key().
   connectChild(insert_index,  newChild);
}

template<typename Key, typename Value> inline constexpr const typename tree234<Key, Value>::Node *tree234<Key, Value>::Node::getParent() const  noexcept // ok
{ 
   return parent;
}

/*
 * Input: Assumes that "this" is never the root (because the parent of the root is always the nullptr).
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
 * Recursive version of find
 */
template<typename Key, typename Value> inline bool tree234<Key, Value>::find(Key key) const noexcept
{
    return find(root.get(), key); 
} 
/*
 * find helper method.
 */
template<typename Key, typename Value> bool tree234<Key, Value>::find(const Node *pnode, Key key) const noexcept
{
   if (pnode == nullptr) return false;
   
   auto i = 0;
   
   for (;i < pnode->getTotalItems(); ++i) {

      if (key < pnode->key(i)) 
         return find(pnode->children[i].get(), key); 
    
      else if (key == pnode->key(i)) 
         return true;
   }

   return find(pnode->children[i].get(), key);
}

/*
 * Insersion algorithm is based on https://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf   
 *
 * Other helpful links are:
 *
 * https://www.cs.usfca.edu/~galles/visualization/BTree.html       <-- Best manually insert/delete animation
 * https://www.educative.io/page/5689413791121408/80001            <-- Top notch animation of insert and delete.
 * https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap13a.pdf    <-- Has good illustrations
 * https://www.cs.mcgill.ca/~cs251/ClosestPair/2-4trees.html
 * https://algorithmtutor.com/Data-Structures/Tree/2-3-4-Trees/    <-- Introduces reb-black trees, too
 *
 * Insertion Algorithm 
 *
 * The insert algorithm is based on the this description of `B-Trees <https://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf>`_.  New keys are inserted at leaf nodes.
 * If the leaf node is a 4-node, we must first split it by pushing its middle key up a level to make room for the new key. To ensure the parent can always accomodate a
 * key, we must first split the parent if it is a 4-node. And to ensure the parent's parent can accomodate a new key, we split all 4-nodes as we descend the tree. 
 *
 * If the root must be split (because it is the parent of the leaf or is itself a leaf), the tree will grows upward when a new root node is inserted above the old.
 *
 * The split algorithm converts the fromer 4-node into 2-node that containing only its left key. This downsized node retains it two left-most children. The middle key is
 * pushed into the parent, and the right key is moved into a new 2-node. This newly created 2-node takes ownership of the two right-most children of the former 4-node, and
 * this newly created 2-node is made a child of the parent. The child indexes in the parent are adjusted to properly reflect the new relationships between these nodes.
 *
 */
template<typename Key, typename Value> void tree234<Key, Value>::insert(Key new_key, const Value& value) noexcept 
{ 
   if (root == nullptr) {
           
      root = std::make_unique<Node>(new_key, value); 
                                                    
    ++tree_size;
      return; 
   } 
   
   auto [bool_found, current, index] = find_insert_node(root.get(), new_key);  
   
   if (bool_found) return;

   // current node is now a leaf and it is not full (because we split all four nodes while descending). We cast away constness in order to change the node.
   current->insert(new_key, value); 
   ++tree_size;
}

/*
 * Called by insert(Key key, const Value& value) to determine if key exits or not.
 * Precondition: pnode is never nullptr.
 *
 * Purpose: Recursive method that searches the tree for 'new_key', splitting 4-nodes when encountered. If key is not found, the tree descent terminates at
 * the leaf node where the new 'new_key' should be inserted, and it returns the pair {false, pnode_leaf_where_key_should_be_inserted}. If key was found,
 * it returns the pair {true, Node *pnode_where_key_found}.
 */
template<class Key, class Value> std::tuple<bool, typename tree234<Key, Value>::Node *, int>  tree234<Key, Value>::find_insert_node(Node *pcurrent, Key new_key) noexcept
{
   if (pcurrent->isFourNode()) { 

       if (pcurrent->key(1) == new_key) // First check the middle key because split() will move it into its parent.
            return {true, pcurrent, 1}; 

       // split pcurrent into two 2-nodes and set pcurrent to the Node to examine next(int the loop below).
       pcurrent = split(pcurrent, new_key); 
   }

   auto i = 0;

   for(; i < pcurrent->getTotalItems(); ++i) {

       if (new_key < pcurrent->key(i)) {

           if (pcurrent->isLeaf())
               return {false, pcurrent, i};
 
           return find_insert_node(pcurrent->children[i].get(), new_key); // Recurse left subtree of pcurrent->key(i)
       } 

       if (new_key == pcurrent->key(i)) {

           return {true, pcurrent, i};  // key located at std::pair{pcurrent, i};  
       }
   }

   if (pcurrent->isLeaf()) {
      return {false, pcurrent, 0};
   } 

   return find_insert_node(pcurrent->children[i].get(), new_key); // key is greater than all values in pcurrent, search right-most subtree.
}

/* 
 *  split pseudocode: 
 *  
 *  Input: pnode is a 4-node that is is split follows:
 *  Output:  
 *  1. A new 2-node containing pnode's largest key(the 3rd key) is created, it adopts pnode's two right-most children.
 *  2. pnode is downsized to a 2-node (by setting totalItems to 1) containing its smallest key and its two left-most chidren, 
 *  3. pnode's middle key moves up to its parent (which we know is not a 4-node, since, if it were, it has already been split), and we connect the new
 *    2-node step from #1 to it as its right most child.
 *
 *  Special case: if pnode is the root, we special case this and create a new root above the current root.
 *
 */ 
template<typename Key, typename Value> typename tree234<Key, Value>::Node *tree234<Key, Value>::split(Node *pnode, Key new_key) noexcept
{
   Key middle_key = pnode->key(1);
   
   // 1. create a new node from largest key of pnode and adopt pnode's two right-most children
   auto largestNode = std::make_unique<Node>(std::move(pnode->keys_values[2])); 
   
   largestNode->connectChild(0, pnode->children[2]); 
   largestNode->connectChild(1, pnode->children[3]);
   
   // 2. Make pnode a 2-node. Note: It still retains its two left-most children, 
   pnode->totalItems = 1;
   
   Node *pLargest = largestNode.get();
   
   // 3. Insert middle value into parent, or if pnode is the root, create a new root above pnode and 
   // adopt 'pnode' and 'largest' as children.
   if (root.get() == pnode) {
   
     auto new_root = std::make_unique<Node>(std::move(pnode->keys_values[1])); // Middle value will become new root
     
     new_root->connectChild(0, root); 
     new_root->connectChild(1, largestNode); 
    
     // Since root was moved above, we can safely move into it. 
     root = std::move(new_root); 

   } else {

     // Insert pnode's middle KeyValue pair into its parent, and make largestNode its child.
     pnode->parent->insert(std::move(pnode->keys_values[1]), largestNode); 
   }

  // Since we already did 'if (new_key == middle_key)' in the caller ( in find_insert_node() ), we only need to check if 'new_key < middle_key' in order to set pnext to the node
  // to for find_insert_node() to examine.
  Node *pnext = (new_key < middle_key) ? pnode : pLargest;

  return pnext;
}

/*
 *  Converts 2-nodes to 3- or 4-nodes as it descends to the left-most leaf node of the substree rooted at pnode.
 *  Returns: min leaf node in subtree rooted at pnode.
 */
template<class Key, class Value> inline typename tree234<Key, Value>::Node *tree234<Key, Value>::get_successor_node(Node *pnode, int child_index) noexcept
{
  if (pnode->isTwoNode()) 
      convert2Node(pnode, child_index);

  if (pnode->isLeaf())
      return pnode;

  return get_successor_node(pnode->children[0].get(), 0);
}

template<typename Key, typename Value> inline void tree234<Key, Value>::printlevelOrder(std::ostream& ostr) const noexcept
{
  NodeLevelOrderPrinter tree_printer(height(), (&Node::print), ostr);  
  
  levelOrderTraverse(tree_printer);
 
  ostr << std::flush;
}

template<typename Key, typename Value> void tree234<Key, Value>::debug_printlevelOrder(std::ostream& ostr) const noexcept
{
  ostr << "\n--- First: tree printed ---\n";
  
  ostr << *this;  // calls tree.printlevelOrder(ostr);

  ostr << "\n--- Second: Node relationship info ---\n";
  
  NodeLevelOrderPrinter tree_printer(height(), &Node::debug_print, ostr);  
  
  levelOrderTraverse(tree_printer);
  
  ostr << std::flush;
}


template<typename Key, typename Value> inline void tree234<Key, Value>::printInOrder(std::ostream& ostr) const noexcept
{
  auto lambda = [&](const std::pair<Key, Value>& pr) { ostr << pr.first << ' '; };
  inOrderTraverse(lambda); 
}
	
template<class Key, class Value> tree234<Key, Value>::iterator::iterator(tree234<Key, Value>& lhs_tree) : tree{lhs_tree} 
{
  current = (!tree.isEmpty()) ? get_min() : nullptr;

  cursor = current;
  key_index = 0;  
}

template<class Key, class Value> std::ostream& tree234<Key, Value>::iterator::print(std::ostream& ostr) const noexcept
{
   ostr << "\n-------------------------------------\niterator settings:\ncurrent = " << current << "\n" << "cursor =  " << cursor <<  '\n';
   ostr << *cursor;      // print the node
   ostr << "\nkey_index = " << key_index << '\n';

   ostr << "stack = { "; 
   std::deque<int> deque;

   //tree234<Key, Value>::iterator& nonconst = const_cast<iterator&>(*this);
   tree234<int, int>::iterator& non_const = const_cast<tree234<Key, Value>::iterator&>(*this);
   
   while(!non_const.child_indexes.empty()) {

       auto top = non_const.child_indexes.top();

       ostr << top << ", ";

       deque.push_back(top);

       non_const.child_indexes.pop(); 
   }

   ostr << " } " << '\n' << std::flush;

   // Push elements back onto stack in opposite order they were pop()'ed
   while(!deque.empty()) {

       int i = deque.back();
       
        non_const.child_indexes.push(i);

        deque.pop_back();
   }
   
   return ostr;
}


template<typename Key, typename Value> inline const typename tree234<Key, Value>::Node *tree234<Key, Value>::iterator::get_max() noexcept
{
   const Node *pnode = tree.root.get();

   for (auto child_index = pnode->getTotalItems(); pnode->children[child_index] != nullptr; child_index = pnode->getTotalItems()) {

        push(child_index);
        pnode = pnode->children[child_index].get();
   }
   
   return pnode;
}

template<typename Key, typename Value> inline const typename tree234<Key, Value>::Node *tree234<Key, Value>::iterator::get_min() noexcept
{
   const Node *pnode = tree.root.get();

   for(auto child_index = 0; pnode->children[child_index].get() != nullptr; pnode = pnode->children[child_index].get()) {

        push(child_index);
   }

   return pnode;
}

// non const tree234<Key, Value>& passed to ctor. Called only by end()
template<class Key, class Value> inline tree234<Key, Value>::iterator::iterator(tree234<Key, Value>& lhs_tree, int i) :  tree{lhs_tree} 
{
  // If the tree is empty, there is nothing over which to iterate...
   if (!tree.isEmpty()) {

      cursor = get_max(); // Go to largest node.
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

  auto [successor, index] = getSuccessor(cursor, key_index);

  if (successor == nullptr) { // nullptr implies cursor->keys_values[key_index].key() is the max key,
                              // the last key/value in tree.

       current = nullptr; // We are now at the end. 

  } else {

      cursor = current = successor; 
      key_index = index;
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
  
  auto [predecessor, index] = getPredecessor(cursor, key_index);

  if (predecessor != nullptr) { // nullptr implies there is no predecessor cursor->key(key_index).
      
      cursor = current = predecessor; 
      key_index = index;

  } else {
    // TODO: Do we need an else statement like in iterator::increment() that sets current to nullptr? I need to create a test case for this.
     current = nullptr; // TODO: New else-block. Untested.
  }
  return *this;
}

template<class Key, class Value> inline tree234<Key, Value>::iterator::iterator(iterator&& lhs) : \
             tree{lhs.tree}, current{lhs.current}, cursor{lhs.cursor}, key_index{lhs.key_index}  
{
   lhs.cursor = lhs.current = nullptr; 
   child_indexes = std::move(lhs.child_indexes);
}
/*
 */

template<class Key, class Value> bool tree234<Key, Value>::iterator::operator==(const iterator& lhs) const
{
   //
   // The first if-test, checks for "at end".
   // If current is nullptr, that signals the iterator is "one past the end.". If current is not nullptr, then current will equal cursor.current is either nullptr or cursor. cursor never 
   // becomes nullptr.
   // In the else-if block block, we must check 'current == lhs.current' and not 'cursor == lhs.cursor' because 'cursor' never signals the end of the range, it never becomes nullptr,
   // but the iterator returned by tree234::end()'s iterator always sets current to nullptr (to signal "one past the end").
   // current to nullptr.
   //

   if (current == nullptr && lhs.current == nullptr) return true; 
   else if (current == lhs.current && key_index == lhs.key_index) { 
       return true;
   } else return false;
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

template<class Key, class Value> int tree234<Key, Value>::height(const Node* pnode) const noexcept
{
   if (pnode == nullptr) {

       return -1;

   } else {
       
      std::array<int, 4> heights;
      
      int num_children = pnode->getChildCount();
     
      // Get the max height of each child subtree.
      for (auto i = 0; i < num_children; ++i) {
          
         heights[i] = height(pnode->children[i].get());
      }

      int max = *std::max_element(heights.begin(), heights.begin() + num_children);
      
      return 1 + max; // add one to it.
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
    if (root ==nullptr) return true;
    
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
