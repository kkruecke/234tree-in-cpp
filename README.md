234tree-in-cpp
=============

A 2 3 4 implemented in C++14. Based on these slides on [2-3-4 trees](http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt).
There is a great step-by-step animation of 2 3 4 tree is at: http://cs.sou.edu/~harveyd/classes/cs511/docs/234Tree/tree.htm 

Code was compiled with  g++ version 5.3 using **-std=c++14** option. 

Everything seems to work, including the iterator classes, with the exeception that rbegin() seems to return an iterator that does not work properly
The version of tree2334.h is under developement. It has a new implementation of remove(K key). The prior working and tested verions of all the code is in tree234-orig.h.

Further documentations is at [Implementing a 2 3 4 Tree in C++14](http://cplusplus.kurttest.com/notes/tree234.html).
