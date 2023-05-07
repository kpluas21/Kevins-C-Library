# Kevin's C Library

My implementation of popular data structures and programs in C. 
## How To Use
More information on the programs can be found in their respective folders. Each program was made to be as independent as possible. As a result, simply including the header and source file will be enough to use the module.

## Documentation

To view the most updated documentation, click on this [link](https://kpluas21.github.io/Kevins-C-Library/).  

Alternatively, if you have doxygen installed you can generate your own nice looking documentation using a single command.
From the main directory, simply type 
```
doxygen Doxyfile
```
A directory named _docs/_ will be generated and you can open up index.html with any browser to view all documentation created for this library.

## Tools Currently Implemented

* DynamiC : A generic dynamic array
* LinkC   : A generic linked list
* BstC    : A binary search tree using integers
* HashC   : A hash table using strings as keys and integers as their respective values
* GraphC  : An undirected, unweighted graph with chars as the main key. 
