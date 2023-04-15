# DynamiC

An implementation of a generic dynamic array data structure in C. It supports fast insertion and dynamic memory allocation. It has support for other features in similar libraries such as _find, _remove, etc. It has support for four data types : int, char, float and double. It's meant to be analogous to vectors in C++.

## Installation
Everything needed is contained in the included header and source file. Simply add this line to the top of your file and you should be good to go!

    #include"DynamiC.h"
    
You can also use the following command to try out the library!
```
make -f DynamiCTestmake.mk
```
This will create an executable that tests all of the functions and ensure they work on your machine.

## How To Use
To start, call the _init() function and pass it the DataType of the array, a pointer to the initial data, and the size of the intial data. The function will take care of the rest for you.

        DynamiC *intVector = DynamiC(INT, intPtr, 5);

If done correctly, you should have a pointer to a dynamic array containing your initial data and of the typing of your choosing.
From there, call the functions as needed, passing the pointer to your array. More information on the functions and their use can be found in the source code.

        DynamiC_append(array, &elem);
        DynamiC_find(array, &elem);
        DynamiC_get(array, index);
        DynamiC_print(array);
Casting to the appropriate data type is a must when using certain functions such as _get. It is up to you to ensure the types match. For example :

```
//Retrieve an int at index 5 of our array
//Because _get returns void, we will need to cast to an int and dereference.

    int num;
    num = *(int*)DynamiC_get(intVector, 5);

```
Some functions will also return an int on success or failure.
```
//Using _find
    int numSearch = 10;
    if(DynamiC_find(intVector, &numSearch) == -1) {
        puts("Element not found!");
    }
    puts("Element found!");
```

As shown, you'll be using pointers quite a bit so make sure to call the provided delete function when you're done. Make sure you pass a reference to the pointer you've been working with. This will ensure that everything, including the pointer, is free'd and null'd safely!

	    //....
	    DynamiC_delete(&array);
        //array will be NULL at this point. 
	    return 0;
    }



