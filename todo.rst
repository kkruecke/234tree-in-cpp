Things TODO
===========

Latest code in in ~/4/include/ntree234.h. The new remove() code works in part. It need correct pseudo code, then re-implemnt it, then debug it.
After both split_find() and remove()/conrt_find() are working, use the newer descent_transform() method instead. Make sure it is working. Then make the changes below.

Improve and Correct remove(Key key)
-----------------------------------

Design. The pseudo code for remove is here:

* `2 3 4 Deletion Pseudo Code 1 <http://www.cs.ubc.ca/~liorma/cpsc320/files/B-trees.pdf>`_
* `2 3 4 Deletion pseudo code 2 <http://www2.thu.edu.tw/~emtools/Adv.%20Data%20Structure/2-3,2-3-4%26red-blackTree_952.pdf>`_  -- starting on page 63.
* Walls and Mirrors textbook.

To get rid of returning values in reference paramaters. Use either a pair, a struct or a tuple to return the value using RVO.

Look at the current getSucccessor() logic and some of the current getRemoveSuccessor() logic. Start with pseudocode overview and design.


Idea
----


