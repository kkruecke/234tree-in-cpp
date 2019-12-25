

Printing tree in after insert of 20

current_level = 1  [20] 

Printing tree in after insert of 40

current_level = 1  [20, 40] 

Printing tree in after insert of 60

current_level = 1  [20, 40, 60] 

Printing tree in after insert of 70

current_level = 1   [40] 

current_level = 2  [20] [60, 70] 

Printing tree in after insert of 80

current_level = 1   [40] 

current_level = 2  [20] [60, 70, 80] 

Printing tree in after insert of 90

current_level = 1   [40, 70] 

current_level = 2  [20] [60] [80, 90] 

Printing tree in after insert of 100

current_level = 1   [40, 70] 

current_level = 2  [20] [60] [80, 90, 100] 

Printing tree in after insert of 120

current_level = 1   [40, 70, 90] 

current_level = 2  [20] [60] [80] [100, 120] 
Test Completed


Printing tree in after insert of 20

current_level = 1  [20] 

Printing tree in after insert of 40

current_level = 1  [20, 40] 

Printing tree in after insert of 60

current_level = 1  [20, 40, 60] 

Printing tree in after insert of 41

current_level = 1   [40] 

current_level = 2  [20] [41, 60] 

Printing tree in after insert of 42

current_level = 1   [40] 

current_level = 2  [20] [41, 42, 60] 

Printing tree in after insert of 43

current_level = 1   [40, 42] 

current_level = 2  [20] [41] [43, 60] 

Printing tree in after insert of 44

current_level = 1   [40, 42] 

current_level = 2  [20] [41] [43, 44, 60] 
Test Completed


Printing tree in after insert of 20

current_level = 1  [20] 

Printing tree in after insert of 40

current_level = 1  [20, 40] 

Printing tree in after insert of 60

current_level = 1  [20, 40, 60] 

Printing tree in after insert of 0

current_level = 1   [40] 

current_level = 2  [0, 20] [60] 

Printing tree in after insert of 1

current_level = 1   [40] 

current_level = 2  [0, 1, 20] [60] 

Printing tree in after insert of 2

current_level = 1   [1, 40] 

current_level = 2  [0] [2, 20] [60] 

Printing tree in after insert of 3

current_level = 1   [1, 40] 

current_level = 2  [0] [2, 3, 20] [60] 
Test Completed
Printing tree in level order


current_level = 1     [23, 50] 

current_level = 2    [5, 17] [30] [70, 87] 

current_level = 3   [1] [15] [20] [27] [37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [2, 3] [6, 10, 11] [16] [18] [21] [24, 26] [28] [31, 33, 34] [38, 40, 41] [51, 52] [56] [61] [63, 69] [71] [80, 81] [88, 90, 91] [93, 97, 98] 
======================

Printing actual tree in order

0 1 2 3 5 6 10 11 15 16 17 18 20 21 23 24 26 27 28 30 31 33 34 37 38 40 41 50 51 52 55 56 60 61 62 63 69 70 71 79 80 81 87 88 90 91 92 93 97 98 

Printing copy of tree

0 1 2 3 5 6 10 11 15 16 17 18 20 21 23 24 26 27 28 30 31 33 34 37 38 40 41 50 51 52 55 56 60 61 62 63 69 70 71 79 80 81 87 88 90 91 92 93 97 98 

Using traverse methods to print tree in-order:
0, 1, 2, 3, 5, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 26, 27, 28, 30, 31, 33, 34, 37, 38, 40, 41, 50, 51, 52, 55, 56, 60, 61, 62, 63, 69, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 
Printing the keys to be removed

5, 26, 33, 2, 1, 69, 51, 55, 97, 17, 23, 79, 92, 37, 87, 62, 27, 0, 90, 15, 80, 70, 40, 50, 20, 10, 30, 60, 
Tree size is 50 before removing item 5

item 5 successfully removed 
Tree size is 49 after attempting to remove item 5



=======Tree level order print =====================


current_level = 1     [23, 50] 

current_level = 2    [6] [30] [70, 87] 

current_level = 3   [1] [15, 17, 20] [27] [37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [2, 3] [10, 11] [16] [18] [21] [24, 26] [28] [31, 33, 34] [38, 40, 41] [51, 52] [56] [61] [63, 69] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 1 2 3 6 10 11 15 16 17 18 20 21 23 24 26 27 28 30 31 33 34 37 38 40 41 50 51 52 55 56 60 61 62 63 69 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 1, 2, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 26, 27, 28, 30, 31, 33, 34, 37, 38, 40, 41, 50, 51, 52, 55, 56, 60, 61, 62, 63, 69, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 69, 63, 62, 61, 60, 56, 55, 52, 51, 50, 41, 40, 38, 37, 34, 33, 31, 30, 28, 27, 26, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 2, 1, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 49 before removing item 26

item 26 successfully removed 
Tree size is 48 after attempting to remove item 26



=======Tree level order print =====================


current_level = 1     [23, 70] 

current_level = 2    [6] [50] [87] 

current_level = 3   [1] [15, 17, 20] [27, 30, 37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [2, 3] [10, 11] [16] [18] [21] [24] [28] [31, 33, 34] [38, 40, 41] [51, 52] [56] [61] [63, 69] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 1 2 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 33 34 37 38 40 41 50 51 52 55 56 60 61 62 63 69 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 1, 2, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 33, 34, 37, 38, 40, 41, 50, 51, 52, 55, 56, 60, 61, 62, 63, 69, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 69, 63, 62, 61, 60, 56, 55, 52, 51, 50, 41, 40, 38, 37, 34, 33, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 2, 1, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 48 before removing item 33

item 33 successfully removed 
Tree size is 47 after attempting to remove item 33



=======Tree level order print =====================


current_level = 1     [23] 

current_level = 2    [6] [50, 70, 87] 

current_level = 3   [1] [15, 17, 20] [27, 30, 37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [2, 3] [10, 11] [16] [18] [21] [24] [28] [31, 34] [38, 40, 41] [51, 52] [56] [61] [63, 69] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 1 2 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 51 52 55 56 60 61 62 63 69 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 1, 2, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 51, 52, 55, 56, 60, 61, 62, 63, 69, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 69, 63, 62, 61, 60, 56, 55, 52, 51, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 2, 1, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 47 before removing item 2

item 2 successfully removed 
Tree size is 46 after attempting to remove item 2



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 23] [70, 87] 

current_level = 3   [1, 6] [17, 20] [27, 30, 37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [3] [10, 11] [16] [18] [21] [24] [28] [31, 34] [38, 40, 41] [51, 52] [56] [61] [63, 69] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 1 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 51 52 55 56 60 61 62 63 69 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 1, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 51, 52, 55, 56, 60, 61, 62, 63, 69, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 69, 63, 62, 61, 60, 56, 55, 52, 51, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 1, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 46 before removing item 1

item 1 successfully removed 
Tree size is 45 after attempting to remove item 1



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 23] [70, 87] 

current_level = 3   [3, 10] [17, 20] [27, 30, 37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [6] [11] [16] [18] [21] [24] [28] [31, 34] [38, 40, 41] [51, 52] [56] [61] [63, 69] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 51 52 55 56 60 61 62 63 69 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 51, 52, 55, 56, 60, 61, 62, 63, 69, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 69, 63, 62, 61, 60, 56, 55, 52, 51, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 45 before removing item 69

item 69 successfully removed 
Tree size is 44 after attempting to remove item 69



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 23] [70, 87] 

current_level = 3   [3, 10] [17, 20] [27, 30, 37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [6] [11] [16] [18] [21] [24] [28] [31, 34] [38, 40, 41] [51, 52] [56] [61] [63] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 51 52 55 56 60 61 62 63 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 51, 52, 55, 56, 60, 61, 62, 63, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 63, 62, 61, 60, 56, 55, 52, 51, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 44 before removing item 51

item 51 successfully removed 
Tree size is 43 after attempting to remove item 51



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 23] [70, 87] 

current_level = 3   [3, 10] [17, 20] [27, 30, 37] [55, 60, 62] [79] [92] 

current_level = 4  [0] [6] [11] [16] [18] [21] [24] [28] [31, 34] [38, 40, 41] [52] [56] [61] [63] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 52 55 56 60 61 62 63 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 52, 55, 56, 60, 61, 62, 63, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 63, 62, 61, 60, 56, 55, 52, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 43 before removing item 55

item 55 successfully removed 
Tree size is 42 after attempting to remove item 55



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 23] [70, 87] 

current_level = 3   [3, 10] [17, 20] [27, 30, 37] [56, 62] [79] [92] 

current_level = 4  [0] [6] [11] [16] [18] [21] [24] [28] [31, 34] [38, 40, 41] [52] [60, 61] [63] [71] [80, 81] [88, 90, 91] [93, 97, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 52 56 60 61 62 63 70 71 79 80 81 87 88 90 91 92 93 97 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 97, 98, 


========== Test of reverse_iterator class ===================
98, 97, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 42 before removing item 97

item 97 successfully removed 
Tree size is 41 after attempting to remove item 97



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 23] [70] 

current_level = 3   [3, 10] [17, 20] [27, 30, 37] [56, 62] [79, 87, 92] 

current_level = 4  [0] [6] [11] [16] [18] [21] [24] [28] [31, 34] [38, 40, 41] [52] [60, 61] [63] [71] [80, 81] [88, 90, 91] [93, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 17 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 52 56 60 61 62 63 70 71 79 80 81 87 88 90 91 92 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 17, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 17, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 41 before removing item 17

item 17 successfully removed 
Tree size is 40 after attempting to remove item 17



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 23] [70] 

current_level = 3   [3, 10] [18] [27, 30, 37] [56, 62] [79, 87, 92] 

current_level = 4  [0] [6] [11] [16] [20, 21] [24] [28] [31, 34] [38, 40, 41] [52] [60, 61] [63] [71] [80, 81] [88, 90, 91] [93, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 23 24 27 28 30 31 34 37 38 40 41 50 52 56 60 61 62 63 70 71 79 80 81 87 88 90 91 92 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 23, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 23, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 40 before removing item 23

item 23 successfully removed 
Tree size is 39 after attempting to remove item 23



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 24] [70] 

current_level = 3   [3, 10] [18] [30, 37] [56, 62] [79, 87, 92] 

current_level = 4  [0] [6] [11] [16] [20, 21] [27, 28] [31, 34] [38, 40, 41] [52] [60, 61] [63] [71] [80, 81] [88, 90, 91] [93, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 24 27 28 30 31 34 37 38 40 41 50 52 56 60 61 62 63 70 71 79 80 81 87 88 90 91 92 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 79, 80, 81, 87, 88, 90, 91, 92, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 92, 91, 90, 88, 87, 81, 80, 79, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 39 before removing item 79

item 79 successfully removed 
Tree size is 38 after attempting to remove item 79



=======Tree level order print =====================


current_level = 1     [24] 

current_level = 2    [15] [50, 70] 

current_level = 3   [3, 10] [18] [30, 37] [56, 62] [80, 87, 92] 

current_level = 4  [0] [6] [11] [16] [20, 21] [27, 28] [31, 34] [38, 40, 41] [52] [60, 61] [63] [71] [81] [88, 90, 91] [93, 98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 24 27 28 30 31 34 37 38 40 41 50 52 56 60 61 62 63 70 71 80 81 87 88 90 91 92 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 80, 81, 87, 88, 90, 91, 92, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 92, 91, 90, 88, 87, 81, 80, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 38 before removing item 92

item 92 successfully removed 
Tree size is 37 after attempting to remove item 92



=======Tree level order print =====================


current_level = 1     [24] 

current_level = 2    [15] [50, 70] 

current_level = 3   [3, 10] [18] [30, 37] [56, 62] [80, 87, 93] 

current_level = 4  [0] [6] [11] [16] [20, 21] [27, 28] [31, 34] [38, 40, 41] [52] [60, 61] [63] [71] [81] [88, 90, 91] [98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 24 27 28 30 31 34 37 38 40 41 50 52 56 60 61 62 63 70 71 80 81 87 88 90 91 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 27, 28, 30, 31, 34, 37, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 80, 81, 87, 88, 90, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 90, 88, 87, 81, 80, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 37, 34, 31, 30, 28, 27, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 37 before removing item 37

item 37 successfully removed 
Tree size is 36 after attempting to remove item 37



=======Tree level order print =====================


current_level = 1     [24] 

current_level = 2    [15] [50, 70] 

current_level = 3   [3, 10] [18] [30, 38] [56, 62] [80, 87, 93] 

current_level = 4  [0] [6] [11] [16] [20, 21] [27, 28] [31, 34] [40, 41] [52] [60, 61] [63] [71] [81] [88, 90, 91] [98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 24 27 28 30 31 34 38 40 41 50 52 56 60 61 62 63 70 71 80 81 87 88 90 91 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 27, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 80, 81, 87, 88, 90, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 90, 88, 87, 81, 80, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 27, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 36 before removing item 87

item 87 successfully removed 
Tree size is 35 after attempting to remove item 87



=======Tree level order print =====================


current_level = 1     [24] 

current_level = 2    [15] [50, 70] 

current_level = 3   [3, 10] [18] [30, 38] [56, 62] [80, 88, 93] 

current_level = 4  [0] [6] [11] [16] [20, 21] [27, 28] [31, 34] [40, 41] [52] [60, 61] [63] [71] [81] [90, 91] [98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 24 27 28 30 31 34 38 40 41 50 52 56 60 61 62 63 70 71 80 81 88 90 91 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 27, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 62, 63, 70, 71, 80, 81, 88, 90, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 90, 88, 81, 80, 71, 70, 63, 62, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 27, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 35 before removing item 62

item 62 successfully removed 
Tree size is 34 after attempting to remove item 62



=======Tree level order print =====================


current_level = 1     [24] 

current_level = 2    [15] [50, 70] 

current_level = 3   [3, 10] [18] [30, 38] [56, 61] [80, 88, 93] 

current_level = 4  [0] [6] [11] [16] [20, 21] [27, 28] [31, 34] [40, 41] [52] [60] [63] [71] [81] [90, 91] [98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 24 27 28 30 31 34 38 40 41 50 52 56 60 61 63 70 71 80 81 88 90 91 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 27, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 63, 70, 71, 80, 81, 88, 90, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 90, 88, 81, 80, 71, 70, 63, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 27, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 34 before removing item 27

item 27 successfully removed 
Tree size is 33 after attempting to remove item 27



=======Tree level order print =====================


current_level = 1     [24] 

current_level = 2    [15] [50, 70] 

current_level = 3   [3, 10] [18] [30, 38] [56, 61] [80, 88, 93] 

current_level = 4  [0] [6] [11] [16] [20, 21] [28] [31, 34] [40, 41] [52] [60] [63] [71] [81] [90, 91] [98] 

=================== Normal Tree Print =======================

0 3 6 10 11 15 16 18 20 21 24 28 30 31 34 38 40 41 50 52 56 60 61 63 70 71 80 81 88 90 91 93 98 

========== Print of tree using for loop ===================
0, 3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 63, 70, 71, 80, 81, 88, 90, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 90, 88, 81, 80, 71, 70, 63, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 0, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 33 before removing item 0

item 0 successfully removed 
Tree size is 32 after attempting to remove item 0



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [15, 24] [70] 

current_level = 3   [10] [18] [30, 38] [56, 61] [80, 88, 93] 

current_level = 4  [3, 6] [11] [16] [20, 21] [28] [31, 34] [40, 41] [52] [60] [63] [71] [81] [90, 91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 15 16 18 20 21 24 28 30 31 34 38 40 41 50 52 56 60 61 63 70 71 80 81 88 90 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 63, 70, 71, 80, 81, 88, 90, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 90, 88, 81, 80, 71, 70, 63, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 32 before removing item 90

item 90 successfully removed 
Tree size is 31 after attempting to remove item 90



=======Tree level order print =====================


current_level = 1     [24] 

current_level = 2    [15] [50, 70] 

current_level = 3   [10] [18] [30, 38] [56, 61] [80, 88, 93] 

current_level = 4  [3, 6] [11] [16] [20, 21] [28] [31, 34] [40, 41] [52] [60] [63] [71] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 15 16 18 20 21 24 28 30 31 34 38 40 41 50 52 56 60 61 63 70 71 80 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 15, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 63, 70, 71, 80, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 80, 71, 70, 63, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 15, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 31 before removing item 15

item 15 successfully removed 
Tree size is 30 after attempting to remove item 15



=======Tree level order print =====================


current_level = 1     [50] 

current_level = 2    [16, 30] [70] 

current_level = 3   [10] [20, 24] [38] [56, 61] [80, 88, 93] 

current_level = 4  [3, 6] [11] [18] [21] [28] [31, 34] [40, 41] [52] [60] [63] [71] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 16 18 20 21 24 28 30 31 34 38 40 41 50 52 56 60 61 63 70 71 80 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 63, 70, 71, 80, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 80, 71, 70, 63, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 30 before removing item 80

item 80 successfully removed 
Tree size is 29 after attempting to remove item 80



=======Tree level order print =====================


current_level = 1     [30] 

current_level = 2    [16] [50, 70] 

current_level = 3   [10] [20, 24] [38] [56, 61] [81, 93] 

current_level = 4  [3, 6] [11] [18] [21] [28] [31, 34] [40, 41] [52] [60] [63] [71] [88, 91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 16 18 20 21 24 28 30 31 34 38 40 41 50 52 56 60 61 63 70 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 63, 70, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 70, 63, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 29 before removing item 70

item 70 successfully removed 
Tree size is 28 after attempting to remove item 70



=======Tree level order print =====================


current_level = 1     [30] 

current_level = 2    [16] [50, 71] 

current_level = 3   [10] [20, 24] [38] [56, 61] [88, 93] 

current_level = 4  [3, 6] [11] [18] [21] [28] [31, 34] [40, 41] [52] [60] [63] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 16 18 20 21 24 28 30 31 34 38 40 41 50 52 56 60 61 63 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 40, 41, 50, 52, 56, 60, 61, 63, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 63, 61, 60, 56, 52, 50, 41, 40, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 28 before removing item 40

item 40 successfully removed 
Tree size is 27 after attempting to remove item 40



=======Tree level order print =====================


current_level = 1     [30] 

current_level = 2    [16] [56, 71] 

current_level = 3   [10] [20, 24] [38, 50] [61] [88, 93] 

current_level = 4  [3, 6] [11] [18] [21] [28] [31, 34] [41] [52] [60] [63] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 16 18 20 21 24 28 30 31 34 38 41 50 52 56 60 61 63 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 41, 50, 52, 56, 60, 61, 63, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 63, 61, 60, 56, 52, 50, 41, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 27 before removing item 50

item 50 successfully removed 
Tree size is 26 after attempting to remove item 50



=======Tree level order print =====================


current_level = 1     [30] 

current_level = 2    [16] [56, 71] 

current_level = 3   [10] [20, 24] [38] [61] [88, 93] 

current_level = 4  [3, 6] [11] [18] [21] [28] [31, 34] [41, 52] [60] [63] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 16 18 20 21 24 28 30 31 34 38 41 52 56 60 61 63 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 16, 18, 20, 21, 24, 28, 30, 31, 34, 38, 41, 52, 56, 60, 61, 63, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 63, 61, 60, 56, 52, 41, 38, 34, 31, 30, 28, 24, 21, 20, 18, 16, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 26 before removing item 20

item 20 successfully removed 
Tree size is 25 after attempting to remove item 20



=======Tree level order print =====================


current_level = 1     [56] 

current_level = 2    [16, 30] [71] 

current_level = 3   [10] [21] [38] [61] [88, 93] 

current_level = 4  [3, 6] [11] [18] [24, 28] [31, 34] [41, 52] [60] [63] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 10 11 16 18 21 24 28 30 31 34 38 41 52 56 60 61 63 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 10, 11, 16, 18, 21, 24, 28, 30, 31, 34, 38, 41, 52, 56, 60, 61, 63, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 63, 61, 60, 56, 52, 41, 38, 34, 31, 30, 28, 24, 21, 18, 16, 11, 10, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 25 before removing item 10

item 10 successfully removed 
Tree size is 24 after attempting to remove item 10



=======Tree level order print =====================


current_level = 1     [56] 

current_level = 2    [30] [71] 

current_level = 3   [6, 16, 21] [38] [61] [88, 93] 

current_level = 4  [3] [11] [18] [24, 28] [31, 34] [41, 52] [60] [63] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 11 16 18 21 24 28 30 31 34 38 41 52 56 60 61 63 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 11, 16, 18, 21, 24, 28, 30, 31, 34, 38, 41, 52, 56, 60, 61, 63, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 63, 61, 60, 56, 52, 41, 38, 34, 31, 30, 28, 24, 21, 18, 16, 11, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 24 before removing item 30

item 30 successfully removed 
Tree size is 23 after attempting to remove item 30



=======Tree level order print =====================


current_level = 1    [21, 56, 71] 

current_level = 2   [6, 16] [31, 38] [61] [88, 93] 

current_level = 3  [3] [11] [18] [24, 28] [34] [41, 52] [60] [63] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 11 16 18 21 24 28 31 34 38 41 52 56 60 61 63 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 11, 16, 18, 21, 24, 28, 31, 34, 38, 41, 52, 56, 60, 61, 63, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 63, 61, 60, 56, 52, 41, 38, 34, 31, 28, 24, 21, 18, 16, 11, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

Tree size is 23 before removing item 60

item 60 successfully removed 
Tree size is 22 after attempting to remove item 60



=======Tree level order print =====================


current_level = 1    [21, 56, 88] 

current_level = 2   [6, 16] [31, 38] [71] [93] 

current_level = 3  [3] [11] [18] [24, 28] [34] [41, 52] [61, 63] [81] [91] [98] 

=================== Normal Tree Print =======================

3 6 11 16 18 21 24 28 31 34 38 41 52 56 61 63 71 81 88 91 93 98 

========== Print of tree using for loop ===================
3, 6, 11, 16, 18, 21, 24, 28, 31, 34, 38, 41, 52, 56, 61, 63, 71, 81, 88, 91, 93, 98, 


========== Test of reverse_iterator class ===================
98, 93, 91, 88, 81, 71, 63, 61, 56, 52, 41, 38, 34, 31, 28, 24, 21, 18, 16, 11, 6, 3, 


========== Test of isBalanced() ===================

tree.isBalanced() == true

==== Final Tree ========



current_level = 1    [21, 56, 88] 

current_level = 2   [6, 16] [31, 38] [71] [93] 

current_level = 3  [3] [11] [18] [24, 28] [34] [41, 52] [61, 63] [81] [91] [98] In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
==================
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 
In samle_value::~sample_value() 

