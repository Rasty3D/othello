Otello
======

Otello game


Compiling
---------

To compile the program, please run the following commands:

    othello$ mkdir build
    othello$ cd build
    othello/build$ ../scripts/cmake.sh
    othello/build$ make
    
You can clean the make files with:

    othello/build$ make clean
    
Or you can clean completely the build folder just deleting the files:

    othello/build$ rm -rf *
    
After this command you have to regenerate the cmake (see above).


Executing a program
-------------------

The executable files are placed in the build/bin folder. You can launch the programs from the build folder like this:

    othello/build$ ./bin/othello_text
    

Testing
-------

If the testing is enable, you can run the tests with:

    othello/build$ make test
