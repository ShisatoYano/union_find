# union_find

* The optimization to naive method is Path Compression.  
* To flatten the tree when find() id called.  
* When find() is called for an element x, root of tree is returned.  
* To make the found root as parent of x so that we don't have to traverse all intermediate nodes again.  
* If x is root of a subtree, then path from all nodes under x also compress.  
