/**********************************************************************
 * Makefile for Game of Life
 *
 * @author Brandon Conn
 * @version 2-12-2018
 *********************************************************************/

main : main.o file_utilities.o
	clang -o game main.o file_utilities.o

main.o : main.c file_utilities.h
	clang -c main.c

file_utilities.o : file_utilities.c file_utilities.h
	clang -c file_utilities.c

clean:
	rm -f *.o program 
