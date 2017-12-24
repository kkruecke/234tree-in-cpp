Things TODO
===========

Improve and Correct remove(Key key)
-----------------------------------

Change code so that it does not return values using reference parameters anywhere in code. This happens only in the ::remove() code, which therfore needs to be redsigned from the ground up. Eliminate the use of references for return values.
Instead use either a pair, a struct or a tuple to return values using RVO.

Design. The pseudo code for remove is here:

* `2 3 4 Deletion Pseudo Code 1 <http://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf>`_
* `2 3 4 Deletion pseudo code 2 <http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf>`_  -- starting on page 63.
* Walls and Mirrors textbook.

To get rid of returning values in reference paramaters. Use either a pair, a struct or a tuple to return the value using RVO.

Look at the current getSucccessor() logic and some of the current getRemoveSuccessor() logic. Start with pseudocode overview and design.


Idea
----

Add range for loops by creating a container that can hold from one to three elements. This may eliminate the KeyValue class.

class key_value_container : private std::array<KeyValue, 3> {

    int totalItems;

  public:
          
  KeyValue& operator[](int i)
  {
     return std::array<...>::operator[i];
  } 
   
  class iterator : public std::iterator<std::random_iterator_tag, KeyValue> {
      key_value_container& cont;
      int index;
    public:
      KeyValue& opeator*() { return cont[index]; }
      operator++(int i);    
      operator+(int i);    
  };

 
};
