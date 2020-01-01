TODO 
====

BUG: Code blows up when we try to remove from a tree that has a 2-node root and only one child is a 2-node. Prospective code in ~/w/test/include and ./src. 

Use the animations at http://www.cs.armstrong.edu/liang/animation/web/24Tree.html and https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree.

See Caranno and https://en.wikipedia.org/wiki/2%E2%80%933%E2%80%934_tree. 

.. code-block:: cpp

    tree234<int, int> stree = { {5, 5}, {40, 40}, {70, 70}, {120, 120}};
    stree.remove(40);
    cout << stree;
    stree.remove(70); 

