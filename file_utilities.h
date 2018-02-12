#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**********************************************************************
 * Basic header file for main.c to utilize file_utilities.c
 * 
 * @author Brandon Conn
 * @version 2-12-2018
 *********************************************************************/

/**********************************************************************
 * Structure holding the contents of the game board which is made up of
 *     cells arranged in rows and columns
 *********************************************************************/
struct board {

    /** Each cell is denoted by a 'O' for a living cell or ' ' (space)
            for a non-living cell **/
    char* cells;

    /** The number of rows of which the board is made **/
    int rows;

    /** The number of columns of which the board is made **/
    int cols;
};
typedef struct board GAME;

/**********************************************************************
 * Prints out the current board
 *
 * @param board the board that contains the cells
 *********************************************************************/
void printBoard(GAME *board);

/**********************************************************************
 * Saves the board to the specified file
 *
 * @param filename the name of the specified file
 * @param board the board that contains the cells
 *********************************************************************/
void saveFile(char* filename, GAME* board);

/**********************************************************************
 * Loads the board from the specified file
 * @param filename the name of the specified file
 * @param board the board that contains the cells
 *********************************************************************/
void loadFile(char* filename, GAME* board);

/**********************************************************************
 * Counts the number of neighbors around a cell
 *     8 possible positions
 *
 * @param board the board that contains the cells
 * @param pos the position of the cell
 * @return the number of living cells that neighbor a cell
 *********************************************************************/
int numNeighbors(GAME *board, int pos);

/**********************************************************************
 * Performs one generation of the board
 *
 * @param board the board that contains the cells
 *********************************************************************/
void generation(GAME *board);
