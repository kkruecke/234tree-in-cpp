234tree-in-cpp
=============

A 2 3 4 implemented in C++. Based on these slides on [2-3-4 trees](http://www.unf.edu/~broggio/cop3540/Chapter%2010%20-%202-3-4%20Trees%20-%20Part%201.ppt).
Code was compiled with clang++ compiler using **-std=c11++** option. If you encounter a compiler error in main.cpp on 

    tree.traverse([](int x){ cout << x << ' '; }); 

you use this code instead
    TreePrinter tree_printer;
    tree.traverse(tree_printer);
 
