/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>

/*CHECKING IF A COLOR SELECTED BY USER IS TAKEN OR NOT*/
int sameColor(Player players[], int numPlayers){
        for (int i = 0; i < numPlayers; ++i){
            for (int j = i+1; j < numPlayers; ++j){
                if (players[j].col == players[i].col){
                    return 1;
                }
            }
        }
        return 0;
}

/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(Square board[NUM_ROWS][NUM_COLUMNS]){

    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4)
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].topOfStack = NULL;
        }
    }
}


 /*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(Player players[]){

    int numPlayers = 0;

    printf("\nHow many players? (Minimum 2, Maximum 6): ");
    scanf("%d", &numPlayers);


    while(numPlayers < 2 || numPlayers > 6){
        printf("Invalid amount of players");

        printf("\nHow many players? (Minimum 2, Maximum 6): ");
        scanf("%d", &numPlayers);
    }

    for(int i = 0; i < numPlayers; ++i){
        printf("\nPlayer %d, ", i+1); //player id
        printf("What is your name: ");

        char removeNewline;
        scanf("%c", &removeNewline);

        gets(players[i].name);

        printf("\nWhat color would you like to play with %s?\n\n"
               "Enter 0 for Red\n"
               "Enter 1 for Blue\n"
               "Enter 2 for Green\n"
               "Enter 3 for Yellow\n"
               "Enter 4 for Pink\n"
               "Enter 5 for Orange\n\n", players[i].name);
        //todo add input options
        scanf("%u", &players[i].col);
    }

    /*WHILE  COLOR SELECTED BY USER IS ALREADY TAKEN*/
    while(sameColor(players, numPlayers) == 1){
        printf("\nSome players have chosen the same color. Choose different colors.\n");
        for (int i = 0; i < numPlayers; ++i){
            printf("\nWhat color would you like to play with %s?\n\n"
                    "Enter 0 for Red\n"
                    "Enter 1 for Blue\n"
                    "Enter 2 for Green\n"
                    "Enter 3 for Yellow\n"
                    "Enter 4 for Pink\n"
                    "Enter 5 for Orange\n\n", players[i].name);

            scanf("%u", &players[i].col);
        }
    }
        return numPlayers;
}




