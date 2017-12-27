Things TODO
===========

Latest code in in ~/4/include/ntree234.h, in which the methods called remove(Node *, key) were reworked, causes a segementation fault. 

descent_transform() may or may not be useful.

See the TODOES in getSucessor() and convert_min.

Key References
--------------

Design. The pseudo code for remove is here:

* `2 3 4 Deletion Pseudo Code 1 <http://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf>`_
* `2 3 4 Deletion pseudo code 2 <http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf>`_  -- starting on page 63.
* ??????
* Walls and Mirrors textbook.

To get rid of returning values in reference paramaters. Use either a pair, a struct or a tuple to return the value using RVO.

Look at the current getSucccessor() logic and some of the current getRemoveSuccessor() logic. Start with pseudocode overview and design.



