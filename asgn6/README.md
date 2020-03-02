#Program

This program is takes in words that you input and gives an output of words that you shouldn't use or if that word has another translation. From stdin, you type in -s if you want statistics of program. -h for manual hash table size, -f for manual bloom filter size, -m to indicate move to front rule, -b to indicate no move to front rule. If a file was not inputted, then you must type in words at comman line and then press CTRL + D to end. Program should run afterwards and you should see something if you used bad words.

#Makefile
Type make or make all to build all the required files to run.
Type ./newspeak should run the program. (you can also use flags -s, -f (#) , -h(#) ,-b,-m.
Type make clean should clear out all .o files + infer-out.
Type make infer should detect errors.

#ERRORS
In my make infer, it gives me dereference errors for some of my arrays. It says that there is a chance that it can be NULL. In my program, however, I made sure that my pointers won't assign a null into it.

