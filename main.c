#include "file_utilities.h"

/**********************************************************************
 * Main function to run the game
 *
 *     Command to run program:
 *         $ make
 *         $ ./game files/<filename>
 *
 *     Loads the initial file specified at the command line
 *     Prints the initial file specified at the command line
 *     Provides a menu for the user to make selections from
 *     Takes input from the user for menu selections
 *
 * @author Brandon Conn
 * @version 2/12/2018
 *********************************************************************/

/**********************************************************************
 * Runs the Game of Life
 *
 * @param argc number of arguments
 * @param argv value of arguments
 * @return 0 to exit the game
 *********************************************************************/
int main(int argc, char** argv) {

    // Checks for user input of 2 arguments
    if (argc != 2) {
        printf("\n> Invalid Input!\n");
        printf("> Usage: ./<program name> files/<filename>\n\n");
        exit(1);
    }

    // Game menu for user input
    printf("\n****************************************************\n");
    printf("   1 : Continue Another Generation\n");
    printf("   2 : Continue a Specified Number of Generations\n");
    printf("   3 : Save to file\n");
    printf("   4 : Load from file\n");
    printf("   5 : Quit\n");
    printf("****************************************************\n\n");

    // Initializes the game board
    GAME* board = (GAME*) malloc(sizeof(GAME));

    // Opens the specified file from the command line and
    // prints the board from the file
    loadFile(argv[1], board);
    printBoard(board);

    // Receives user input until the user exits the game
    int input = -1;

    // Gives a good enough amount of space for a large file
    char* filename = (char*) malloc(128 * sizeof(char));

    // Number of generations that the user inputs
    int* numGen;
    numGen = 0;

    // Continues the game as long as the user doesn't exit
    while (input != 5) {
        printf("> Enter a number from the menu: ");

        // Checks if input is not an integer
        // Only acceptable input other than integer is return carriage
        if (scanf("%d", &input) != 1) {
            while(getchar() != '\n');
            input = -1;
        }

        switch (input) {

            // Processes one generation and prints it
            case 1:
                generation(board);
                printBoard(board);
                break;

            // Processes specified number of generations and prints them
            case 2:
                printf("\nHow many generations would you like to occur?\n");
                scanf("%d", (int*)&numGen);
                for (int i = 0; i < (int) numGen; i++){
                    generation(board);
                    printBoard(board);
                }
                break;

            // Saves the current board to a new file
            case 3:
                printf("\n> What would you like the file to be saved as? \n");
                scanf("%s", filename);
                saveFile(filename, board);
                break;

            // Loads the board from a specified file
            case 4:
                printf("\n> Enter the filename to load: ");
                scanf("%s", filename);
                printf("\n");
                loadFile(filename, board);
                printBoard(board);
                break;

            // Exits the game
            case 5:
                printf("\n~ EXITING THE GAME OF LIFE ... GOODBYE CRUEL WORLD!\n\n");
                free(board -> cells);
                return 0;

            // The input was not among those in the menu options
            default:
                printf("\n> That was not a valid input...try again.\n");
                break;
        }
        printf("\n****************************************************\n");
        printf("   1 : Continue Another Generation\n");
        printf("   2 : Continue a Specified Number of Generations\n");
        printf("   3 : Save to file\n");
        printf("   4 : Load from file\n");
        printf("   5 : Quit\n");
        printf("****************************************************\n\n");
    }
}
