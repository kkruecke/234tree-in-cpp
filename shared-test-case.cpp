#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
using namespace std;

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

   friend ostream& operator<<(ostream& ostr, const Test& lhs) 
   {
     ostr << "i = " << lhs.i << endl; 
     return ostr;
   }

  ~Test()
   {
     std::cout << "In ~Test() with i = " << i << " and this = " << this << std::endl;
   }
 
};

template<class Key> class Node;  // fwd ref.

template<class Key> std::shared_ptr<Node<Key>> buildTree(Key k1, Key k2, Key k3); // fwd ref.

template<class Key> class Node {

   friend std::shared_ptr<Node<Key>> buildTree<Key>(Key k1, Key k2, Key k3); 

    Key key;

    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

 public:
   Node(Key k) : key{k} {}

   Node(const Node<Key>& ) = default;

   Node(Node<Key>&& ) = default;

   Node<Key>& operator=(const Node<Key>&) = default;
   Node<Key>& operator=(Node<Key>&&) = default;
   

  ~Node()
   {
     std::cout << "In ~Node<Key> with key = " << key << " and this = " << this << std::endl;
   }
 
};

template<class Key> shared_ptr<Node<Key>> buildTree(Key k1, Key k2, Key k3)
{
  shared_ptr<Node<Key>> tree;

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

  tree = make_shared<Node<Key>>(mid);   

  tree->left =  make_shared<Node<Key>>(min);   

  tree->right =  make_shared<Node<Key>>(max);   

  return tree;
}


int main(int argc, char** argv) 
{
    shared_ptr<Node<Test>> root = buildTree(Test(0), Test{1}, Test{2});
   
    shared_ptr<Node<Test>> root2 = root;
    
    return 0;
}

