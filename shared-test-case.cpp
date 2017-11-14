#include <iostream>
#include <memory>
#include <utility>
#include <queue>
#include <stack>

// TODO: Implement print_tree()

template<class Key> class Node;  // fwd ref.

template<class Key> std::shared_ptr<Node<Key>> buildTree(Key k1, Key k2, Key k3); // fwd ref.

template<class Key> void print_tree(const Node<Key>& root); // fwd ref.

template<class Key> class Node {

   friend std::shared_ptr<Node<Key>> buildTree<Key>(Key k1, Key k2, Key k3); 
   friend void print_tree<Key>(const Node<Key>&); 

    Key key;

    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

 public:
   Node(Key k) : key{k} {}

   Node(const Node<Key>& ) = default;

   Node(Node<Key>&& ) = default;

   Node<Key>& operator=(const Node<Key>&) = default;
   Node<Key>& operator=(Node<Key>&&) = default;
   
   Key get_key() { return key; } 

  ~Node()
   {
     std::cout << "In ~Node<Key> with key = \n\t" << get_key() << "\n\t and this = " << this << '.' << std::endl;
   }
 
};

template<class Key> std::shared_ptr<Node<Key>> buildTree(Key k1, Key k2, Key k3)
{
  std::shared_ptr<Node<Key>> tree;

  Key min, mid, max;

  if (k1 < k2) {

     min = k1;
     max = k2;
  } else {

     min = k2;
     max = k1;
  }

  if (k3 < min) {

     mid = min;
     min = k3;

  } else if (k3 < max) {

     mid = k3;  

  } else {

     mid = max;
     max = k3;
  }

  tree = std::make_shared<Node<Key>>(mid);   

  tree->left =  std::make_shared<Node<Key>>(min);   

  tree->right =  std::make_shared<Node<Key>>(max);   

  return tree;
}

template<class Key, class Functor> void levelOrderTraverse(const Node<Key>& root, Functor f) 
{
   if (root == nullptr) return;
   
   // pair of: 1. Node pointer and 2. level of tree.
   std::queue<std::pair<const Node<Key>*, int>> q; 

   auto level = 1;

   q.push(std::make_pair(root.get(), level));

   while (!q.empty()) {

        std::pair<const Node<Key> *, int> pair_ = q.front();

        const Node<Key> *current = pair_.first;

        int tree_level = pair_.second;

        f(current, tree_level); // For example: print out all the keys_values in current.
         
        if (!current->isLeaf()) {
            
            q.push(std::make_pair(current->left.get(), tree_level + 1));  
            q.push(std::make_pair(current->right.get(), tree_level + 1));  
        }
        q.pop(); 
   }
}

template<class Key> void print_tree(const Node<Key>& root)
{
  // auto functor = [&](const Node *current, int level) { 

}


/*
 Object for testing trees implemented with shared_ptr's
 */

class Test {

   int i;

  public:

   bool operator <(const Test& lhs) { return i < lhs.i; }
   bool operator==(const Test& lhs) { return i == lhs.i; }

   Test() : i{0} {}
   Test(int in) : i{in} {}
   Test(const Test& ) = default;

   Test(Test&& ) = default;

   Test& operator=(const Test&) = default;
   Test& operator=(Test&&) = default;

   friend std::ostream& operator<<(std::ostream& ostr, const Test& lhs) 
   {
     ostr << "i = " << lhs.i << std::endl; 
     return ostr;
   }

  ~Test()
   {
     std::cout << "In ~Test() with i = " << i << " and this = " << this << std::endl;
   }
 
};

using namespace std;

int main(int argc, char** argv) 
{
    shared_ptr<Node<Test>> root = buildTree(Test(0), Test{1}, Test{2});

    cout << "\nTree built." << endl;
   
    shared_ptr<Node<Test>> root2 = root;
    
    cout << "\nroot2 = root done. Doing 'return 0'." << endl;
    return 0;
}

