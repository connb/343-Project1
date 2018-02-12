# 343-Project1
C Implementation of Conway's Game of Life

To run this program from the command line:  

> $ make  
> $ ./game files/\<filename\>  

Using make will properly compile the program using the Makefile.  

The names of files that can be used is under the "files" folder  

The files contain one long string. The first two integers correlate with the number of rows and columns (In that order). The remainder of the string contains only spaces and O's. The O's denote a live cell. The string is read left to right, where every # of characters equal to # of columns is printed as one row.   

The following string:

7 &nbsp; 4O &nbsp; &nbsp; &nbsp; &nbsp; O &nbsp; O &nbsp; OO &nbsp; O &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; OOOOO &nbsp; O &nbsp; &nbsp; O

Would generate like this:

|   |   |   |   |
|---|---|---|---|
| O |   |   |   |
|   | O |   | O |
|   | O | O |   |
| O |   |   |   |
|   |   | O | O |
| O | O | O |   |
| O |   |   | O |
|   |   |   |   |
