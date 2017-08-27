#ifndef DEBUGPRINTER_H
#define	DEBUGPRINTER_H
#include <iosfwd>
#include <string>
#include <sstream>

// TODO: Scrap this in preference to something like the debugPrinter for tree23.

template<typename K> class Tree234;// fwd reference

class DebugPrinter {
    // TODO: Add tree depth capability somehow. 
    
    std::ostream& ostr_;
    
public:
    DebugPrinter(std::ostream& ostr) : ostr_(ostr) {}

    DebugPrinter(const DebugPrinter& tp) : ostr_(tp.ostr_) {}

    template<class K> std::ostream& operator()(const K& k, int index, const typename Tree234<K>::Node234 *current,
                                                               const typename Tree234<K>::Node234 *const root);
};

template<class K> inline std::ostream& DebugPrinter::operator()(const K& key, int index, const typename Tree234<K>::Node234 *current,
                                                                                  const typename Tree234<K>::Node234 *const root)
{
    const typename Tree234<K>::Node234 *parent = current->getParent();

    // Get current's child index in its parent.
    int child_index; 
    
    if (parent != nullptr) {
    
        for (child_index = 0; child_index <= parent->getTotalItems(); ++child_index) {
       
             if (current == parent->children[child_index].get()) { 
                 break;
            }  
        }
    } 
    
    std::ostringstream oss;
    
    std::string strLeaf = (current->isLeaf()) ? " <-- is Leaf " : "";

    strLeaf += std::string("\n");
    
    if (parent != nullptr) {

        oss << " address(" << current << "): key[" << index << "] = " << key << ": parent[";

        if (parent == root) {

            oss << " root ";

        } else {

          oss << parent;
        }

        oss << "]->children[" << child_index << "]->keys[" << index << "] = " << key;

    } else {

        oss << " address(" << current << "): key[" << index << "] = " << key << ": {Root}";
    }
       
    std::string suffix = oss.str();

    suffix += strLeaf; 
  
    switch (current->getTotalItems()) {
    
      case 1: // 2-node
              ostr_ << "\nTwo node:  " << suffix;
              break;
    
      case 2: // 3-node

              ostr_ << "\nThree node:" << suffix; 
              break;
    
      case 3: // 4-node
              ostr_ << "\nFour node: " << suffix; 
              break;
    }

    return ostr_;
}

#endif	/* DEBUGRINTER_H */
