/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 *
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char printToken(Token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(Square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){

        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].topOfStack != NULL){
                c = printToken(board[i][j].topOfStack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");
}

/*COUNTS NUMBER OF TOKENS IN COLUMN 0*/
void checkingColumn(Square board[NUM_ROWS][NUM_COLUMNS], int colCord){
    int tokenCount[6] = {0, 0, 0, 0, 0, 0};

    for(int i = 0; i < NUM_ROWS; ++i){
        Token *token = board[i][colCord].topOfStack;

        while (token != NULL){
            tokenCount[i] += 1;
            token = (*token).under;
        }
    }

    smallestTokenStack = tokenCount[0];

    for(int i = 0; i < NUM_ROWS; ++i){
        if (tokenCount[i] < smallestTokenStack){
            smallestTokenStack = tokenCount[i];
        }
    }
}

/*COUNTS NUMBER OF TOKENS PER SQUARE IN COLUMN 0*/
int tokensPerSquare(Square board[NUM_ROWS][NUM_COLUMNS], int rowCord, int colCord){
    int amountOfTokens = 0;

    Token *token = board[rowCord][colCord].topOfStack;

    while(token != NULL){
        amountOfTokens++;
        token = (*token).under;
    }
    return amountOfTokens;
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers){
    /*FOR ALL 4 TOKENS OF EACH PLAYER*/
    for (int t = 0; t < 4; ++t){
        for (int p = 0; p < numPlayers; ++p){
            checkingColumn(board, 0);

            int row;

            printf("\n%s, place Token %d on row (0 to 5): ", players[p].name, t + 1);
            scanf("%d", &row);

            /*WHILE INVALID PLACEMENT*/
            while(smallestTokenStack < tokensPerSquare(board, row, 0)){
                printf("\nERROR: You have to place tokens on smallest stacks\n");

                printf("\n%s, place Token %d on row (0 to 5): ", players[p].name, t + 1);
                scanf("%d", &row);
            }

            Token *newToken = malloc(sizeof(Token));
            newToken->col = players[p].col;
            newToken->under = board[row][0].topOfStack;
            board[row][0].topOfStack = newToken;

            printToken(board[row][0].topOfStack);
            print_board(board);
        }
    }
}

/*RETURNING COLOR NAME RELATING TO ENUM*/
char *color_name(enum Color color){
    switch(color){
        case 0: return "Red";
        case 1: return "Blue";
        case 2: return "Green";
        case 3: return "Yellow";
        case 4: return "Pink";
        case 5: return "Orange";
        default: return "color blind"; //change
    }
}

/*CHECKS IF PLAYER CHOOSING THEIR TOKEN IN SIDEWAYS MOVE*/
int isCorrectToken(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int i, int rowCord, int colCord){
    if (players[i].col == board[rowCord][colCord].topOfStack->col){
        return 1;
    }
    return 0;
}

/*CHECKING IF OBSTACLE SHOULD REMAIN OBSTACLE OR NOT*/
int obstacleCheck(Square board[NUM_ROWS][NUM_COLUMNS], int dice, int colCord){
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < colCord; ++j){
            if (board[i][j].topOfStack != NULL){
                return 0;
            }
        }
    }

    return 1;
}

/*MOVING TOKEN ON BOARD*/
void tokenTravel(Square board[][NUM_COLUMNS], int currentPosRow, int currentPosCol, int newPosRow, int newPostCol){
    Token *Token = board[currentPosRow][currentPosCol].topOfStack;
    board[currentPosRow][currentPosCol].topOfStack = Token->under;

    Token->under = board[newPosRow][newPostCol].topOfStack;
    board[newPosRow][newPostCol].topOfStack = Token;
}

void play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers){
    int rowCord, colCord, upOrDown;

    srand(time(NULL));

    for(int i = 0; i < numPlayers; ++i){
        printf("\nPlayer's turn: %s (%s)\n", players[i].name, color_name(players[i].col));

        int dice = rand()%6;
        printf("\nYou rolled: %d: ", dice);

        int answer;
        printf("\nDo you want to move sideways? \n1 for yes and 0 for no: ");
        scanf("%d", &answer);

        if (answer == 1){
            printf("\n%s, choose which %s token you would like to move sideways.", players[i].name, color_name(players[i].col));

            printf("\nEnter row number: ");
            scanf("%d", &rowCord);

            printf("\nEnter column number: ");
            scanf("%d", &colCord);

            while(board[rowCord][colCord].topOfStack == NULL){
                printf("\nERROR: Empty Square\n");

                printf("\n%s, choose which %s token you would like to move sideways.\n", players[i].name, color_name(players[i].col));

                printf("\nEnter row number: ");
                scanf("%d", &rowCord);

                printf("\nEnter column number: ");
                scanf("%d", &colCord);
            }

            /*RETURNS 0 IF WRONG TOKEN, RETURNS 1 IF CORRECT TOKEN*/
            int correctToken = isCorrectToken(board, players, i, rowCord, colCord);

            /*WHILE ITS NOT THEIR TOKEN OR IN AN OBSTACLE*/
            while (correctToken != 1 || board[rowCord][colCord].type == OBSTACLE){
                /*TELL THEM TO ENTER TOKEN AGAIN*/
                /*IF IN OBSTACLE, PRINT ERROR*/
                if(board[rowCord][colCord].type == OBSTACLE){
                    if (obstacleCheck(board, rowCord, colCord) == 0){
                    printf("\nERROR: You are in an obstacle. You can't move this token out until all tokens have reached column %d", colCord);
                    }
                }

                /*IF INCORRECT TOKEN, PRINT ERROR*/
                if(correctToken != 1){
                    printf("\nERROR: You can only move your %s tokens.\n", color_name(players[i].col));
                }

                /*ASK USER FOR CO ORDINATES AGAIN*/
                printf("\n%s, choose which %s token you would like to move sideways.\n", players[i].name, color_name(players[i].col));

                printf("\nEnter row number: ");
                scanf("%d", &rowCord);

                printf("\nEnter column number: ");
                scanf("%d", &colCord);

                while(board[rowCord][colCord].topOfStack == NULL){
                    printf("\nERROR: Empty Square\n");

                    printf("\n%s, choose which %s token you would like to move sideways.\n", players[i].name, color_name(players[i].col));

                    printf("\nEnter row number: ");
                    scanf("%d", &rowCord);

                    printf("\nEnter column number: ");
                    scanf("%d", &colCord);
                }


                /*IF CORRECT TOKEN AND NORMAL SQUARE, BREAK*/
                if (obstacleCheck(board, rowCord, colCord) == 1){
                    board[rowCord][colCord].type = NORMAL; //set square to normal
                    correctToken = isCorrectToken(board, players, i, rowCord, colCord); //set correct token to true
                }
            }

            if(correctToken == 1 && board[rowCord][colCord].type == NORMAL){
                printf("\nEnter 1 to go up OR Enter 2 to go down: ");
                scanf("%d", &upOrDown);

                if(upOrDown == 1){
                    tokenTravel(board, rowCord, colCord, rowCord-1, colCord);
                    printToken(board[rowCord-1][colCord].topOfStack);
                    print_board(board);
                }

                else if(upOrDown == 2){
                    tokenTravel(board, rowCord, colCord, rowCord+1, colCord);
                    printToken(board[rowCord+1][colCord].topOfStack);
                    print_board(board);
                }

                printf("\n%s, please move token from row %d forwards"
                        "\nWhich column is the token which you would like to move: ", players[i].name, dice);
                scanf("%d", &colCord);

                if(board[dice][colCord].topOfStack == NULL){
                     printf("\nEmpty Square\n");
                }

                if (board[dice][colCord].type == OBSTACLE && board[dice][colCord].topOfStack != NULL){
                    if (obstacleCheck(board, dice, colCord) == 0){
                        printf("\nYou are in an obstacle. You can't move this token out until all tokens have reached column %d", colCord);
                        print_board(board);
                    }

                    else if (obstacleCheck(board, dice, colCord) == 1){
                        tokenTravel(board, dice, colCord, dice, colCord+1);
                        printToken(board[dice][colCord+1].topOfStack);
                        print_board(board);
                    }
                }

                if(board[dice][colCord].type == NORMAL && board[dice][colCord].topOfStack != NULL){

                    tokenTravel(board, dice, colCord, dice, colCord+1);
                    printToken(board[dice][colCord+1].topOfStack);
                    print_board(board);
                }
            }
        }

        else if(answer == 0){
            printf("\n%s, please move token from row %d forwards\n"
                   "\nWhich column is the token which you would like to move: ", players[i].name, dice);
            scanf("%d", &colCord);

            if(board[dice][colCord].topOfStack == NULL){
                 printf("\nEmpty Square\n");
                }

            if (board[dice][colCord].type == OBSTACLE && board[dice][colCord].topOfStack != NULL){
                if (obstacleCheck(board, dice, colCord) == 0){
                    printf("\nYou are in an obstacle. You can't move this token out until all tokens have reached column %d", colCord);
                    print_board(board);
                }

                else if (obstacleCheck(board, dice, colCord) == 1){
                    tokenTravel(board, dice, colCord, dice, colCord+1);
                    printToken(board[dice][colCord+1].topOfStack);
                    board[dice][colCord].type = NORMAL;
                    print_board(board);
                }
            }

            if(board[dice][colCord].type == NORMAL && board[dice][colCord].topOfStack != NULL){

                tokenTravel(board, dice, colCord, dice, colCord+1);
                printToken(board[dice][colCord+1].topOfStack);
                print_board(board);
            }

            /*RESETING PLAYER*/
            if (i == numPlayers - 1){
                i = -1;
            }
        }
    }
}






