

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
0, terminate called after throwing an instance of 'std::logic_error'
  what():  iterator constructor called with wrong position paramater
