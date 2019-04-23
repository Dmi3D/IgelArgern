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

void play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers){
    //TO BE IMPLEMENTED
}



