Printing tree in level order


level = 1     [ 50 ] 

level = 2    [ 23 ]  [ 70 ] 

level = 3   [ 2, 15 ]  [ 30 ]  [ 60 ]  [ 90, 97 ] 

level = 4  [ 1 ]  [ 5, 10 ]  [ 17, 20 ]  [ 26, 27 ]  [ 33, 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100, 150, 201 ] 
======================

Printing actual tree in order

1 2 5 10 15 17 20 23 26 27 30 33 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 150 201 

Printing copy of tree

1 2 5 10 15 17 20 23 26 27 30 33 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 150 201 
tree.find(60) returns:  success.
tree.find(-60) returns:  failure.
tree.find(30) returns:  success.
tree.find(-30) returns:  failure.
tree.find(10) returns:  success.
tree.find(-10) returns:  failure.
tree.find(20) returns:  success.
tree.find(-20) returns:  failure.
tree.find(50) returns:  success.
tree.find(-50) returns:  failure.
tree.find(40) returns:  success.
tree.find(-40) returns:  failure.
tree.find(70) returns:  success.
tree.find(-70) returns:  failure.
tree.find(80) returns:  success.
tree.find(-80) returns:  failure.
tree.find(15) returns:  success.
tree.find(-15) returns:  failure.
tree.find(90) returns:  success.
tree.find(-90) returns:  failure.
tree.find(100) returns:  success.
tree.find(-100) returns:  failure.
tree.find(27) returns:  success.
tree.find(-27) returns:  failure.
tree.find(62) returns:  success.
tree.find(-62) returns:  failure.
tree.find(87) returns:  success.
tree.find(-87) returns:  failure.
tree.find(37) returns:  success.
tree.find(-37) returns:  failure.
tree.find(92) returns:  success.
tree.find(-92) returns:  failure.
tree.find(79) returns:  success.
tree.find(-79) returns:  failure.
tree.find(23) returns:  success.
tree.find(-23) returns:  failure.
tree.find(17) returns:  success.
tree.find(-17) returns:  failure.
tree.find(97) returns:  success.
tree.find(-97) returns:  failure.
tree.find(55) returns:  success.
tree.find(-55) returns:  failure.
tree.find(51) returns:  success.
tree.find(-51) returns:  failure.
tree.find(69) returns:  success.
tree.find(-69) returns:  failure.
tree.find(1) returns:  success.
tree.find(-1) returns:  failure.
tree.find(201) returns:  success.
tree.find(-201) returns:  failure.
tree.find(2) returns:  success.
tree.find(-2) returns:  failure.
tree.find(33) returns:  success.
tree.find(-33) returns:  failure.
tree.find(26) returns:  success.
tree.find(-26) returns:  failure.
tree.find(150) returns:  success.
tree.find(-150) returns:  failure.
tree.find(5) returns:  success.
tree.find(-5) returns:  failure.

Using traverse methods to print tree in-order:
1, 2, 5, 10, 15, 17, 20, 23, 26, 27, 30, 33, 37, 40, 50, 51, 55, 60, 62, 69, 70, 79, 80, 87, 90, 92, 97, 100, 150, 201, 
Using traverse methods to print tree post order:
1, 5, 10, 2, 17, 20, 15, 26, 27, 33, 37, 40, 30, 23, 51, 55, 62, 69, 60, 79, 80, 87, 92, 90, 100, 150, 201, 97, 70, 50, 
Using traverse methods to print tree pre-order:
50, 23, 2, 1, 5, 10, 15, 17, 20, 30, 26, 27, 33, 37, 40, 70, 60, 51, 55, 62, 69, 90, 79, 80, 87, 92, 97, 100, 150, 201, 
Tree size is 30 before removing item 5

item 5 successfully removed 
Tree size is 29 after attempting to remove item 5



=======Tree level order print =====================


level = 1    [ 23, 50, 70 ] 

level = 2   [ 2, 15 ]  [ 30 ]  [ 60 ]  [ 90, 97 ] 

level = 3  [ 1 ]  [ 10 ]  [ 17, 20 ]  [ 26, 27 ]  [ 33, 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100, 150, 201 ] 

=================== Normal Tree Print =======================

1 2 10 15 17 20 23 26 27 30 33 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 150 201 
Tree size is 29 before removing item 150

item 150 successfully removed 
Tree size is 28 after attempting to remove item 150



=======Tree level order print =====================


level = 1    [ 23, 50, 70 ] 

level = 2   [ 2, 15 ]  [ 30 ]  [ 60 ]  [ 90, 97 ] 

level = 3  [ 1 ]  [ 10 ]  [ 17, 20 ]  [ 26, 27 ]  [ 33, 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100, 201 ] 

=================== Normal Tree Print =======================

1 2 10 15 17 20 23 26 27 30 33 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 201 
Tree size is 28 before removing item 26

item 26 successfully removed 
Tree size is 27 after attempting to remove item 26



=======Tree level order print =====================


level = 1    [ 15, 50, 70 ] 

level = 2   [ 2 ]  [ 23, 30 ]  [ 60 ]  [ 90, 97 ] 

level = 3  [ 1 ]  [ 10 ]  [ 17, 20 ]  [ 27 ]  [ 33, 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100, 201 ] 

=================== Normal Tree Print =======================

1 2 10 15 17 20 23 27 30 33 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 201 
Tree size is 27 before removing item 33

item 33 successfully removed 
Tree size is 26 after attempting to remove item 33



=======Tree level order print =====================


level = 1    [ 15, 50, 70 ] 

level = 2   [ 2 ]  [ 23, 30 ]  [ 60 ]  [ 90, 97 ] 

level = 3  [ 1 ]  [ 10 ]  [ 17, 20 ]  [ 27 ]  [ 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100, 201 ] 

=================== Normal Tree Print =======================

1 2 10 15 17 20 23 27 30 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 201 
Tree size is 26 before removing item 2

item 2 successfully removed 
Tree size is 25 after attempting to remove item 2



=======Tree level order print =====================


level = 1    [ 23, 50, 70 ] 

level = 2   [ 10, 17 ]  [ 30 ]  [ 60 ]  [ 90, 97 ] 

level = 3  [ 1 ]  [ 15 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100, 201 ] 

=================== Normal Tree Print =======================

1 10 15 17 20 23 27 30 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 201 
Tree size is 25 before removing item 201

item 201 successfully removed 
Tree size is 24 after attempting to remove item 201



=======Tree level order print =====================


level = 1    [ 23, 50, 70 ] 

level = 2   [ 10, 17 ]  [ 30 ]  [ 60 ]  [ 90, 97 ] 

level = 3  [ 1 ]  [ 15 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100 ] 

=================== Normal Tree Print =======================

1 10 15 17 20 23 27 30 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 
Tree size is 24 before removing item 1

item 1 successfully removed 
Tree size is 23 after attempting to remove item 1



=======Tree level order print =====================


level = 1    [ 23, 50, 70 ] 

level = 2   [ 17 ]  [ 30 ]  [ 60 ]  [ 90, 97 ] 

level = 3  [ 10, 15 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 51, 55 ]  [ 62, 69 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 17 20 23 27 30 37 40 50 51 55 60 62 69 70 79 80 87 90 92 97 100 
Tree size is 23 before removing item 69

item 69 successfully removed 
Tree size is 22 after attempting to remove item 69



=======Tree level order print =====================


level = 1    [ 23, 50, 90 ] 

level = 2   [ 17 ]  [ 30 ]  [ 60, 70 ]  [ 97 ] 

level = 3  [ 10, 15 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 51, 55 ]  [ 62 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 17 20 23 27 30 37 40 50 51 55 60 62 70 79 80 87 90 92 97 100 
Tree size is 22 before removing item 51

item 51 successfully removed 
Tree size is 21 after attempting to remove item 51



=======Tree level order print =====================


level = 1    [ 23, 50, 90 ] 

level = 2   [ 17 ]  [ 30 ]  [ 60, 70 ]  [ 97 ] 

level = 3  [ 10, 15 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 55 ]  [ 62 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 17 20 23 27 30 37 40 50 55 60 62 70 79 80 87 90 92 97 100 
Tree size is 21 before removing item 55

item 55 successfully removed 
Tree size is 20 after attempting to remove item 55



=======Tree level order print =====================


level = 1    [ 23, 50, 90 ] 

level = 2   [ 17 ]  [ 30 ]  [ 70 ]  [ 97 ] 

level = 3  [ 10, 15 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 60, 62 ]  [ 79, 80, 87 ]  [ 92 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 17 20 23 27 30 37 40 50 60 62 70 79 80 87 90 92 97 100 
Tree size is 20 before removing item 97

item 97 successfully removed 
Tree size is 19 after attempting to remove item 97



=======Tree level order print =====================


level = 1    [ 23, 50 ] 

level = 2   [ 17 ]  [ 30 ]  [ 70, 90 ] 

level = 3  [ 10, 15 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 60, 62 ]  [ 79, 80, 87 ]  [ 92, 100 ] 

=================== Normal Tree Print =======================

10 15 17 20 23 27 30 37 40 50 60 62 70 79 80 87 90 92 100 
Tree size is 19 before removing item 17

item 17 successfully removed 
Tree size is 18 after attempting to remove item 17



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 23, 30 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 27 ]  [ 37, 40 ]  [ 60, 62 ]  [ 79, 80, 87 ]  [ 92, 100 ] 

=================== Normal Tree Print =======================

10 15 20 23 27 30 37 40 50 60 62 70 79 80 87 90 92 100 
Tree size is 18 before removing item 23

item 23 successfully removed 
Tree size is 17 after attempting to remove item 23



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 27, 37 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 30 ]  [ 40 ]  [ 60, 62 ]  [ 79, 80, 87 ]  [ 92, 100 ] 

=================== Normal Tree Print =======================

10 15 20 27 30 37 40 50 60 62 70 79 80 87 90 92 100 
Tree size is 17 before removing item 79

item 79 successfully removed 
Tree size is 16 after attempting to remove item 79



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 27, 37 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 30 ]  [ 40 ]  [ 60, 62 ]  [ 80, 87 ]  [ 92, 100 ] 

=================== Normal Tree Print =======================

10 15 20 27 30 37 40 50 60 62 70 80 87 90 92 100 
Tree size is 16 before removing item 92

item 92 successfully removed 
Tree size is 15 after attempting to remove item 92



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 27, 37 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 30 ]  [ 40 ]  [ 60, 62 ]  [ 80, 87 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 20 27 30 37 40 50 60 62 70 80 87 90 100 
Tree size is 15 before removing item 37

item 37 successfully removed 
Tree size is 14 after attempting to remove item 37



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 27 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 30, 40 ]  [ 60, 62 ]  [ 80, 87 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 20 27 30 40 50 60 62 70 80 87 90 100 
Tree size is 14 before removing item 87

item 87 successfully removed 
Tree size is 13 after attempting to remove item 87



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 27 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 30, 40 ]  [ 60, 62 ]  [ 80 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 20 27 30 40 50 60 62 70 80 90 100 
Tree size is 13 before removing item 62

item 62 successfully removed 
Tree size is 12 after attempting to remove item 62



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 27 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 30, 40 ]  [ 60 ]  [ 80 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 20 27 30 40 50 60 70 80 90 100 
Tree size is 12 before removing item 27

item 27 successfully removed 
Tree size is 11 after attempting to remove item 27



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 30 ]  [ 70, 90 ] 

level = 3  [ 10 ]  [ 20 ]  [ 40 ]  [ 60 ]  [ 80 ]  [ 100 ] 

=================== Normal Tree Print =======================

10 15 20 30 40 50 60 70 80 90 100 
Tree size is 11 before removing item 100

item 100 successfully removed 
Tree size is 10 after attempting to remove item 100



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 15, 30 ]  [ 70 ] 

level = 3  [ 10 ]  [ 20 ]  [ 40 ]  [ 60 ]  [ 80, 90 ] 

=================== Normal Tree Print =======================

10 15 20 30 40 50 60 70 80 90 
Tree size is 10 before removing item 90

item 90 successfully removed 
Tree size is 9 after attempting to remove item 90



=======Tree level order print =====================


level = 1    [ 30 ] 

level = 2   [ 15 ]  [ 50, 70 ] 

level = 3  [ 10 ]  [ 20 ]  [ 40 ]  [ 60 ]  [ 80 ] 

=================== Normal Tree Print =======================

10 15 20 30 40 50 60 70 80 
Tree size is 9 before removing item 15

item 15 successfully removed 
Tree size is 8 after attempting to remove item 15



=======Tree level order print =====================


level = 1    [ 50 ] 

level = 2   [ 20 ]  [ 70 ] 

level = 3  [ 10 ]  [ 30, 40 ]  [ 60 ]  [ 80 ] 

=================== Normal Tree Print =======================

10 20 30 40 50 60 70 80 
Tree size is 8 before removing item 80

item 80 successfully removed 
Tree size is 7 after attempting to remove item 80



=======Tree level order print =====================


level = 1   [ 20, 50 ] 

level = 2  [ 10 ]  [ 30, 40 ]  [ 60, 70 ] 

=================== Normal Tree Print =======================

10 20 30 40 50 60 70 
Tree size is 7 before removing item 70

item 70 successfully removed 
Tree size is 6 after attempting to remove item 70



=======Tree level order print =====================


level = 1   [ 20, 50 ] 

level = 2  [ 10 ]  [ 30, 40 ]  [ 60 ] 

=================== Normal Tree Print =======================

10 20 30 40 50 60 
Tree size is 6 before removing item 40

item 40 successfully removed 
Tree size is 5 after attempting to remove item 40



=======Tree level order print =====================


level = 1   [ 20, 50 ] 

level = 2  [ 10 ]  [ 30 ]  [ 60 ] 

=================== Normal Tree Print =======================

10 20 30 50 60 
Tree size is 5 before removing item 50

item 50 successfully removed 
Tree size is 4 after attempting to remove item 50



=======Tree level order print =====================


level = 1   [ 20 ] 

level = 2  [ 10 ]  [ 30, 60 ] 

=================== Normal Tree Print =======================

10 20 30 60 
Tree size is 4 before removing item 20

item 20 successfully removed 
Tree size is 3 after attempting to remove item 20



=======Tree level order print =====================


level = 1   [ 30 ] 

level = 2  [ 10 ]  [ 60 ] 

=================== Normal Tree Print =======================

10 30 60 
Tree size is 3 before removing item 10

item 10 successfully removed 
Tree size is 2 after attempting to remove item 10



=======Tree level order print =====================


level = 1  [ 30, 60 ] 

=================== Normal Tree Print =======================

30 60 
Tree size is 2 before removing item 30

item 30 successfully removed 
Tree size is 1 after attempting to remove item 30



=======Tree level order print =====================


level = 1  [ 60 ] 

=================== Normal Tree Print =======================

60 
Tree size is 1 before removing item 60

item 60 successfully removed 
Tree size is 0 after attempting to remove item 60



=======Tree level order print =====================


=================== Normal Tree Print =======================


==== Final Tree ========


