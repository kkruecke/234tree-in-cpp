

Printing tree in after insert of 20

current_level = 1 [20], 

Printing tree in after insert of 40

current_level = 1 [20, 40], 

Printing tree in after insert of 60

current_level = 1 [20, 40, 60], 

Printing tree in after insert of 70

current_level = 1  [40], 

current_level = 2 [20], [60, 70], 

Printing tree in after insert of 80

current_level = 1  [40], 

current_level = 2 [20], [60, 70, 80], 

Printing tree in after insert of 90

current_level = 1  [40, 70], 

current_level = 2 [20], [60], [80, 90], 

Printing tree in after insert of 100

current_level = 1  [40, 70], 

current_level = 2 [20], [60], [80, 90, 100], 

Printing tree in after insert of 120

current_level = 1   [70], 

current_level = 2  [40], [90], 

current_level = 3 [20], [60], [80], [100, 120], 
Test Completed


Printing tree in after insert of 20

current_level = 1 [20], 

Printing tree in after insert of 40

current_level = 1 [20, 40], 

Printing tree in after insert of 60

current_level = 1 [20, 40, 60], 

Printing tree in after insert of 41

current_level = 1  [40], 

current_level = 2 [20], [41, 60], 

Printing tree in after insert of 42

current_level = 1  [40], 

current_level = 2 [20], [41, 42, 60], 

Printing tree in after insert of 43

current_level = 1  [40, 42], 

current_level = 2 [20], [41], [43, 60], 

Printing tree in after insert of 44

current_level = 1  [40, 42], 

current_level = 2 [20], [41], [43, 44, 60], 
Test Completed


Printing tree in after insert of 20

current_level = 1 [20], 

Printing tree in after insert of 40

current_level = 1 [20, 40], 

Printing tree in after insert of 60

current_level = 1 [20, 40, 60], 

Printing tree in after insert of 0

current_level = 1  [40], 

current_level = 2 [0, 20], [60], 

Printing tree in after insert of 1

current_level = 1  [40], 

current_level = 2 [0, 1, 20], [60], 

Printing tree in after insert of 2

current_level = 1  [1, 40], 

current_level = 2 [0], [2, 20], [60], 

Printing tree in after insert of 3

current_level = 1  [1, 40], 

current_level = 2 [0], [2, 3, 20], [60], 
Test Completed

Printing the keys to be removed

5, 26, 33, 2, 1, 69, 51, 55, 97, 17, 23, 79, 92, 37, 87, 62, 27, 0, 90, 15, 80, 70, 40, 50, 20, 10, 30, 60, 
Tree size is 28 before removing item 5

item 5 successfully removed 
Tree size is 27 after attempting to remove item 5



=======Tree level order print =====================


current_level = 1   [23, 50, 70], 

current_level = 2  [1, 15], [30], [60], [87], 

current_level = 3 [0], [2, 10], [17, 20], [26, 27], [33, 37, 40], [51, 55], [62, 69], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 1 2 10 15 17 20 23 26 27 30 33 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 1, 2, 10, 15, 17, 20, 23, 26, 27, 30, 33, 37, 40, 50, 51, 55, 60, 62, 69, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 69, 62, 60, 55, 51, 50, 40, 37, 33, 30, 27, 26, 23, 20, 17, 15, 10, 2, 1, 0, 

Tree size is 27 before removing item 26

item 26 successfully removed 
Tree size is 26 after attempting to remove item 26



=======Tree level order print =====================


current_level = 1   [15, 50, 70], 

current_level = 2  [1], [23, 30], [60], [87], 

current_level = 3 [0], [2, 10], [17, 20], [27], [33, 37, 40], [51, 55], [62, 69], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 1 2 10 15 17 20 23 27 30 33 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 1, 2, 10, 15, 17, 20, 23, 27, 30, 33, 37, 40, 50, 51, 55, 60, 62, 69, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 69, 62, 60, 55, 51, 50, 40, 37, 33, 30, 27, 23, 20, 17, 15, 10, 2, 1, 0, 

Tree size is 26 before removing item 33

item 33 successfully removed 
Tree size is 25 after attempting to remove item 33



=======Tree level order print =====================


current_level = 1   [15, 50, 70], 

current_level = 2  [1], [23, 30], [60], [87], 

current_level = 3 [0], [2, 10], [17, 20], [27], [37, 40], [51, 55], [62, 69], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 1 2 10 15 17 20 23 27 30 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 1, 2, 10, 15, 17, 20, 23, 27, 30, 37, 40, 50, 51, 55, 60, 62, 69, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 69, 62, 60, 55, 51, 50, 40, 37, 30, 27, 23, 20, 17, 15, 10, 2, 1, 0, 

Tree size is 25 before removing item 2

item 2 successfully removed 
Tree size is 24 after attempting to remove item 2



=======Tree level order print =====================


current_level = 1   [23, 50, 70], 

current_level = 2  [1, 15], [30], [60], [87], 

current_level = 3 [0], [10], [17, 20], [27], [37, 40], [51, 55], [62, 69], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 1 10 15 17 20 23 27 30 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 1, 10, 15, 17, 20, 23, 27, 30, 37, 40, 50, 51, 55, 60, 62, 69, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 69, 62, 60, 55, 51, 50, 40, 37, 30, 27, 23, 20, 17, 15, 10, 1, 0, 

Tree size is 24 before removing item 1

item 1 successfully removed 
Tree size is 23 after attempting to remove item 1



=======Tree level order print =====================


current_level = 1   [23, 50, 70], 

current_level = 2  [10, 17], [30], [60], [87], 

current_level = 3 [0], [15], [20], [27], [37, 40], [51, 55], [62, 69], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 10 15 17 20 23 27 30 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 10, 15, 17, 20, 23, 27, 30, 37, 40, 50, 51, 55, 60, 62, 69, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 69, 62, 60, 55, 51, 50, 40, 37, 30, 27, 23, 20, 17, 15, 10, 0, 

Tree size is 23 before removing item 69

item 69 successfully removed 
Tree size is 22 after attempting to remove item 69



=======Tree level order print =====================


current_level = 1   [23, 50], 

current_level = 2  [10, 17], [30], [60, 70, 87], 

current_level = 3 [0], [15], [20], [27], [37, 40], [51, 55], [62], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 10 15 17 20 23 27 30 37 40 50 51 55 60 62 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 10, 15, 17, 20, 23, 27, 30, 37, 40, 50, 51, 55, 60, 62, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 62, 60, 55, 51, 50, 40, 37, 30, 27, 23, 20, 17, 15, 10, 0, 

Tree size is 22 before removing item 51

item 51 successfully removed 
Tree size is 21 after attempting to remove item 51



=======Tree level order print =====================


current_level = 1   [23, 50], 

current_level = 2  [10, 17], [30], [60, 70, 87], 

current_level = 3 [0], [15], [20], [27], [37, 40], [55], [62], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 10 15 17 20 23 27 30 37 40 50 55 60 62 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 10, 15, 17, 20, 23, 27, 30, 37, 40, 50, 55, 60, 62, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 62, 60, 55, 50, 40, 37, 30, 27, 23, 20, 17, 15, 10, 0, 

Tree size is 21 before removing item 55

item 55 successfully removed 
Tree size is 20 after attempting to remove item 55



=======Tree level order print =====================


current_level = 1   [23, 50], 

current_level = 2  [10, 17], [30], [70, 87], 

current_level = 3 [0], [15], [20], [27], [37, 40], [60, 62], [79, 80], [90, 92, 97], 

=================== Normal Tree Print =======================

0 10 15 17 20 23 27 30 37 40 50 60 62 70 79 80 87 90 92 97 

========== Test of iterator class ===================
0, 10, 15, 17, 20, 23, 27, 30, 37, 40, 50, 60, 62, 70, 79, 80, 87, 90, 92, 97, 


========== Test of reverse_iterator class ===================
97, 92, 90, 87, 80, 79, 70, 62, 60, 50, 40, 37, 30, 27, 23, 20, 17, 15, 10, 0, 

Tree size is 20 before removing item 97

item 97 successfully removed 
Tree size is 19 after attempting to remove item 97



=======Tree level order print =====================


current_level = 1   [23, 50], 

current_level = 2  [10, 17], [30], [70, 87], 

current_level = 3 [0], [15], [20], [27], [37, 40], [60, 62], [79, 80], [90, 92], 

=================== Normal Tree Print =======================

0 10 15 17 20 23 27 30 37 40 50 60 62 70 79 80 87 90 92 

========== Test of iterator class ===================
0, 10, 15, 17, 20, 23, 27, 30, 37, 40, 50, 60, 62, 70, 79, 80, 87, 90, 92, 


========== Test of reverse_iterator class ===================
92, 90, 87, 80, 79, 70, 62, 60, 50, 40, 37, 30, 27, 23, 20, 17, 15, 10, 0, 

Tree size is 19 before removing item 17

item 17 successfully removed 
Tree size is 18 after attempting to remove item 17



=======Tree level order print =====================


current_level = 1   [50], 

current_level = 2  [10, 23, 30], [70, 87], 

current_level = 3 [0], [15, 20], [27], [37, 40], [60, 62], [79, 80], [90, 92], 

=================== Normal Tree Print =======================

0 10 15 20 23 27 30 37 40 50 60 62 70 79 80 87 90 92 

========== Test of iterator class ===================
0, 10, 15, 20, 23, 27, 30, 37, 40, 50, 60, 62, 70, 79, 80, 87, 90, 92, 


========== Test of reverse_iterator class ===================
92, 90, 87, 80, 79, 70, 62, 60, 50, 40, 37, 30, 27, 23, 20, 15, 10, 0, 

Tree size is 18 before removing item 23

item 23 successfully removed 
Tree size is 17 after attempting to remove item 23



=======Tree level order print =====================


current_level = 1   [50], 

current_level = 2  [10, 27, 37], [70, 87], 

current_level = 3 [0], [15, 20], [30], [40], [60, 62], [79, 80], [90, 92], 

=================== Normal Tree Print =======================

0 10 15 20 27 30 37 40 50 60 62 70 79 80 87 90 92 

========== Test of iterator class ===================
0, 10, 15, 20, 27, 30, 37, 40, 50, 60, 62, 70, 79, 80, 87, 90, 92, 


========== Test of reverse_iterator class ===================
92, 90, 87, 80, 79, 70, 62, 60, 50, 40, 37, 30, 27, 20, 15, 10, 0, 

Tree size is 17 before removing item 79

item 79 successfully removed 
Tree size is 16 after attempting to remove item 79



=======Tree level order print =====================


current_level = 1   [50], 

current_level = 2  [10, 27, 37], [70, 87], 

current_level = 3 [0], [15, 20], [30], [40], [60, 62], [80], [90, 92], 

=================== Normal Tree Print =======================

0 10 15 20 27 30 37 40 50 60 62 70 80 87 90 92 

========== Test of iterator class ===================
0, 10, 15, 20, 27, 30, 37, 40, 50, 60, 62, 70, 80, 87, 90, 92, 


========== Test of reverse_iterator class ===================
92, 90, 87, 80, 70, 62, 60, 50, 40, 37, 30, 27, 20, 15, 10, 0, 

Tree size is 16 before removing item 92

item 92 successfully removed 
Tree size is 15 after attempting to remove item 92



=======Tree level order print =====================


current_level = 1   [50], 

current_level = 2  [10, 27, 37], [70, 87], 

current_level = 3 [0], [15, 20], [30], [40], [60, 62], [80], [90], 

=================== Normal Tree Print =======================

0 10 15 20 27 30 37 40 50 60 62 70 80 87 90 

========== Test of iterator class ===================
0, 10, 15, 20, 27, 30, 37, 40, 50, 60, 62, 70, 80, 87, 90, 


========== Test of reverse_iterator class ===================
90, 87, 80, 70, 62, 60, 50, 40, 37, 30, 27, 20, 15, 10, 0, 

Tree size is 15 before removing item 37

item 37 successfully removed 
Tree size is 14 after attempting to remove item 37



=======Tree level order print =====================


current_level = 1   [50], 

current_level = 2  [10, 27], [70, 87], 

current_level = 3 [0], [15, 20], [30, 40], [60, 62], [80], [90], 

=================== Normal Tree Print =======================

0 10 15 20 27 30 40 50 60 62 70 80 87 90 

========== Test of iterator class ===================
0, 10, 15, 20, 27, 30, 40, 50, 60, 62, 70, 80, 87, 90, 


========== Test of reverse_iterator class ===================
90, 87, 80, 70, 62, 60, 50, 40, 30, 27, 20, 15, 10, 0, 

Tree size is 14 before removing item 87

item 87 successfully removed 
Tree size is 13 after attempting to remove item 87



=======Tree level order print =====================


current_level = 1   [27], 

current_level = 2  [10], [50, 70], 

current_level = 3 [0], [15, 20], [30, 40], [60, 62], [80, 90], 

=================== Normal Tree Print =======================

0 10 15 20 27 30 40 50 60 62 70 80 90 

========== Test of iterator class ===================
0, 10, 15, 20, 27, 30, 40, 50, 60, 62, 70, 80, 90, 


========== Test of reverse_iterator class ===================
90, 80, 70, 62, 60, 50, 40, 30, 27, 20, 15, 10, 0, 

Tree size is 13 before removing item 62

item 62 successfully removed 
Tree size is 12 after attempting to remove item 62



=======Tree level order print =====================


current_level = 1   [27], 

current_level = 2  [10], [50, 70], 

current_level = 3 [0], [15, 20], [30, 40], [60], [80, 90], 

=================== Normal Tree Print =======================

0 10 15 20 27 30 40 50 60 70 80 90 

========== Test of iterator class ===================
0, 10, 15, 20, 27, 30, 40, 50, 60, 70, 80, 90, 


========== Test of reverse_iterator class ===================
90, 80, 70, 60, 50, 40, 30, 27, 20, 15, 10, 0, 

Tree size is 12 before removing item 27

item 27 successfully removed 
Tree size is 11 after attempting to remove item 27



=======Tree level order print =====================


current_level = 1   [30], 

current_level = 2  [10], [50, 70], 

current_level = 3 [0], [15, 20], [40], [60], [80, 90], 

=================== Normal Tree Print =======================

0 10 15 20 30 40 50 60 70 80 90 

========== Test of iterator class ===================
0, 10, 15, 20, 30, 40, 50, 60, 70, 80, 90, 


========== Test of reverse_iterator class ===================
90, 80, 70, 60, 50, 40, 30, 20, 15, 10, 0, 

Tree size is 11 before removing item 0

item 0 successfully removed 
Tree size is 10 after attempting to remove item 0



=======Tree level order print =====================


current_level = 1   [50], 

current_level = 2  [15, 30], [70], 

current_level = 3 [10], [20], [40], [60], [80, 90], 

=================== Normal Tree Print =======================

10 15 20 30 40 50 60 70 80 90 

========== Test of iterator class ===================
10, 15, 20, 30, 40, 50, 60, 70, 80, 90, 


========== Test of reverse_iterator class ===================
90, 80, 70, 60, 50, 40, 30, 20, 15, 10, 

Tree size is 10 before removing item 90

item 90 successfully removed 
Tree size is 9 after attempting to remove item 90



=======Tree level order print =====================


current_level = 1   [30], 

current_level = 2  [15], [50, 70], 

current_level = 3 [10], [20], [40], [60], [80], 

=================== Normal Tree Print =======================

10 15 20 30 40 50 60 70 80 

========== Test of iterator class ===================
10, 15, 20, 30, 40, 50, 60, 70, 80, 


========== Test of reverse_iterator class ===================
80, 70, 60, 50, 40, 30, 20, 15, 10, 

Tree size is 9 before removing item 15

item 15 successfully removed 
Tree size is 8 after attempting to remove item 15



=======Tree level order print =====================


current_level = 1   [50], 

current_level = 2  [20], [70], 

current_level = 3 [10], [30, 40], [60], [80], 

=================== Normal Tree Print =======================

10 20 30 40 50 60 70 80 

========== Test of iterator class ===================
10, 20, 30, 40, 50, 60, 70, 80, 


========== Test of reverse_iterator class ===================
80, 70, 60, 50, 40, 30, 20, 10, 

Tree size is 8 before removing item 80

item 80 successfully removed 
Tree size is 7 after attempting to remove item 80



=======Tree level order print =====================


current_level = 1  [20, 50], 

current_level = 2 [10], [30, 40], [60, 70], 

=================== Normal Tree Print =======================

10 20 30 40 50 60 70 

========== Test of iterator class ===================
10, 20, 30, 40, 50, 60, 70, 


========== Test of reverse_iterator class ===================
70, 60, 50, 40, 30, 20, 10, 

Tree size is 7 before removing item 70

item 70 successfully removed 
Tree size is 6 after attempting to remove item 70



=======Tree level order print =====================


current_level = 1  [20, 50], 

current_level = 2 [10], [30, 40], [60], 

=================== Normal Tree Print =======================

10 20 30 40 50 60 

========== Test of iterator class ===================
10, 20, 30, 40, 50, 60, 


========== Test of reverse_iterator class ===================
60, 50, 40, 30, 20, 10, 

Tree size is 6 before removing item 40

item 40 successfully removed 
Tree size is 5 after attempting to remove item 40



=======Tree level order print =====================


current_level = 1  [20, 50], 

current_level = 2 [10], [30], [60], 

=================== Normal Tree Print =======================

10 20 30 50 60 

========== Test of iterator class ===================
10, 20, 30, 50, 60, 


========== Test of reverse_iterator class ===================
60, 50, 30, 20, 10, 

Tree size is 5 before removing item 50

item 50 successfully removed 
Tree size is 4 after attempting to remove item 50



=======Tree level order print =====================


current_level = 1  [20], 

current_level = 2 [10], [30, 60], 

=================== Normal Tree Print =======================

10 20 30 60 

========== Test of iterator class ===================
10, 20, 30, 60, 


========== Test of reverse_iterator class ===================
60, 30, 20, 10, 

Tree size is 4 before removing item 20

item 20 successfully removed 
Tree size is 3 after attempting to remove item 20



=======Tree level order print =====================


current_level = 1  [30], 

current_level = 2 [10], [60], 

=================== Normal Tree Print =======================

10 30 60 

========== Test of iterator class ===================
10, 30, 60, 


========== Test of reverse_iterator class ===================
60, 30, 10, 

Tree size is 3 before removing item 10

item 10 successfully removed 
Tree size is 2 after attempting to remove item 10



=======Tree level order print =====================


current_level = 1 [30, 60], 

=================== Normal Tree Print =======================

30 60 

========== Test of iterator class ===================
30, 60, 


========== Test of reverse_iterator class ===================
60, 30, 

Tree size is 2 before removing item 30

item 30 successfully removed 
Tree size is 1 after attempting to remove item 30



=======Tree level order print =====================


current_level = 1 [60], 

=================== Normal Tree Print =======================

60 

========== Test of iterator class ===================
60, 


========== Test of reverse_iterator class ===================
60, 

Tree size is 1 before removing item 60

item 60 successfully removed 
Tree size is 0 after attempting to remove item 60



=======Tree level order print =====================


=================== Normal Tree Print =======================



========== Test of iterator class ===================



========== Test of reverse_iterator class ===================


==== Final Tree ========


