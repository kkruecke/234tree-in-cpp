/* 
 * File:   DebugPrinter.h
 * Author: kurt
 *
 * Created on May 11, 2013, 8:21 PM
 */

#ifndef DEBUGPRINTER_H
#define	DEBUGPRINTER_H
#include <iosfwd>

//template<typename K> Tree234<K>;// fwd reference

class DebugPrinter {
    
    std::ostream& ostr_;
    
public:
    DebugPrinter(std::ostream& ostr) : ostr_(ostr) {}
    DebugPrinter(const DebugPrinter& tp) : ostr_(tp.ostr_) {}
    template<class K> std::ostream& operator()(K k, int index, const typename Tree234<K>::Node234 *current);
};

template<class K> inline std::ostream& DebugPrinter::operator()(K k, int index, const typename Tree234<K>::Node234 *current)
{

    switch (current->getTotalItems()) {
    
      case 1: // 2-node
              ostr_ << "\nTwo node   (" << current << "): key[" << index << "]: " << k << " parent:[" << current->getParent() << "] \n";
              break;
    
      case 2: // 3-node

              ostr_ << "\nThree node (" << current << "): key[" << index << "]: " << k << " parent:[" << current->getParent() << "] \n";
              break;
    
      case 3: // 4-node
              ostr_ << "\nFour node  (" << current << "): key[" << index << "]: " << k << " parent:[" << current->getParent() << "] \n";
              break;
    }

    return ostr_;
}
#endif	/* DEBUGRINTER_H */
