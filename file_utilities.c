#include "file_utilities.h"

/**********************************************************************
 * Helper functions for main.c
 *     Prints out the board
 *     Saves the current board to a new file
 *     Loads in a file from a previously created board
 *     Counts the number of neighbors
 *     Uses the number of neighbors to determine what to do on the
 *         next generation of the board
 *
 * @author Brandon Conn
 * @version 2-12-2018
 *********************************************************************/

/**********************************************************************
 * Prints out the current board
 *
 * @param board the board that contains the cells in the rows & columns
 *********************************************************************/
void printBoard(GAME *board) {

    /** The rows of which the board is made **/
    int row;

    printf("\n");

    for (row = 0; row < board -> rows; row++) {

        printf("   ");

        /** The columns of which the board is made **/
        int col;

        for (col = 0; col < board -> cols; col++) {

            printf(" %c ", board -> cells[row * board -> cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}

/**********************************************************************
 * Saves the board to the specified file
 *
 * @param filename the name of the specified file
 * @param board the board that contains the cells
 *********************************************************************/
void saveFile(char* filename, GAME* board) {

    // Creates a file that can be written to
    FILE* out;
    out = fopen(filename, "w");

    // Error saving the file
    if (out == NULL) {
        printf("\n> File \"%s\" could not be saved.\n", filename);
        printf(" >******EXITING PROGRAM******\n");
        exit(0);
    }

    // Writes two integers to the file to represent rows & columns
    fprintf(out, "%d %d", board -> rows, board -> cols);

    // Writes each character of each cell to the file
    int size = board -> rows * board -> cols;
    int i;
    for (i = 0; i < size; i++) {
        fprintf(out, "%c", board -> cells[i]);
    }

    printf("> The board has been saved to \"%s\" file.\n", filename);
    fclose(out);
}

/**********************************************************************
 * Loads the board from the specified file
 * @param filename the name of the specified file
 * @param board the board that contains the cells
 *********************************************************************/
void loadFile(char* filename, GAME* board) {

    // Reads in from a file
    FILE* in;
    in = fopen(filename, "r");

    // For input error when wrong or non-existent file is input
    if (in == NULL) {
        printf("> File \"%s\" could not be opened.\n", filename);
        printf("> ******EXITING PROGRAM******\n\n");
        exit(0);
    }

    // Uses the first two integers of the file for the rows and columns
    int rows;
    int cols;
    fscanf(in,"%d %d", &rows, &cols);

    // Creates rows and columns consisting of cells
    int size = rows * cols;
    board -> rows = rows;
    board -> cols = cols;
    board -> cells = (char*) malloc (size * sizeof(char));

    // Assigns the corresponding characters from the file to the cells
    int i;
    for (i = 0; i < size; i++) {
        fscanf(in, "%c", &(board -> cells[i]));
    }

    fclose(in);
}

/**********************************************************************
 * Counts the number of neighbors around a cell
 *     8 possible positions
 *
 * @param board the board that contains the cells
 * @param pos the position of the cell
 * @return the number of living cells that neighbor a cell
 *********************************************************************/
int numNeighbors(GAME *board, int pos) {

    /** Number of living neighbors **/
    int numNeighbors = 0;

    /** The size of the board **/
    int size = board -> rows * board -> cols;

    /** 8 positions of possible living neighbors **/
    int neighbor[8];

    /** Above Left **/
    neighbor[0] = pos - board -> cols - 1;

    /** Left **/
    neighbor[1] = pos - 1;

    /** Below Left **/
    neighbor[2] = pos + board -> cols - 1;

    /** Above **/
    neighbor[3] = pos - board -> cols;

    /** Below **/
    neighbor[4] = pos + board -> cols;

    /** Above Right **/
    neighbor[5] = pos - board -> cols + 1;

    /** Right **/
    neighbor[6] = pos + 1;

    /** Below Right **/
    neighbor[7] = pos + board -> cols + 1;

    int begin = 0;
    int end = 7;

    // Denotes a cell at the left edge of the board
    if (pos % board -> cols == 0) {
        begin = 3;
    }

    // Denotes a cell at the right edge of the board
    if (pos % board -> cols == board -> cols - 1) {
        end = 4;
    }

    // Loops through all the neighbors and increments when one is found
    for (; begin <= end; begin++) {

        // Is the the neighbor within the board?
        if (neighbor[begin] >= 0 && neighbor[begin] < size) {

            // Is the neighbor living?
            if (board -> cells[neighbor[begin]] == 'O') {
                numNeighbors++;
            }
        }
    }
    return numNeighbors;
}

/**********************************************************************
 * Performs one generation of the board
 *
 * @param board the board that contains the cells
 *********************************************************************/
void generation(GAME *board) {

    /** The size of the board **/
    int size = board -> rows * board -> cols;

    GAME* tmp = (GAME*) malloc(sizeof(GAME));

    // Makes a temporary copy of the board
    tmp -> rows = board -> rows;
    tmp -> cols = board -> cols;
    tmp -> cells = (char*) malloc (size * sizeof(char));
    memcpy(tmp -> cells, board -> cells, size * sizeof(char));

    // Loops through the cells so changes can be made to the new board
    int i;
    for (i = 0; i < size; i++) {

        // count alive neighbors
        int livingNeighbors = numNeighbors(tmp, i);

        // Check if the cell is living
        if(tmp -> cells[i] == 'O') {

            // Checks for underpopulation and overcrowding
            if (livingNeighbors < 2 || livingNeighbors > 3) {
                board -> cells[i] = ' ';
            }
        }

        // Otherwise the cell is not living (i.e. dead)
        // so check if it is able to become living
        else {

            // If a cell has 3 living neighbors, it becomes alive
            if (livingNeighbors == 3) {
                board -> cells[i] = 'O';
            }
        }
    }
    free(tmp -> cells);
    free(tmp);
}
