#Program

This program is suppose to encode and decode a file or from standard input. To use this program, you must either run ./encode or ./decode. There are flags in which you can place after which are, -v (prints compression stats). -i: infile , -o: outfile. If you dont specify a -i flag follow by input file, then it will read from standard input. If you don't specify a -o file follow by an output file, it will write to standard output.

#MAKEFILE

type make or make all to make encode and decode
type make encode to make only encode
type make decode to make only decode
type make clean to clear out .o and infer-out
type make infer to check for errors

#ERRORS

My program indicates that there could possibly be a null dereferenced at a pointer, but I made sure that it wouldn't get to that point if it's NULL
