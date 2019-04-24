#include "game_init.h"
#include "game_logic.h"

int main(void) {

    //the board is defined as a 2-Dimensional array of squares
    Square board[NUM_ROWS][NUM_COLUMNS];

    //an array containing the players (MAX 6 players)
    Player players[6];

    //the number of players
    int numPlayers =0;

    //creates the squares of the board
    initialize_board(board);

    //prints the board
    print_board(board);

    //creates the players
    numPlayers = initialize_players(players);

    //asks each player to place their tokens
    //on the first column of the board
    place_tokens(board, players, numPlayers);

    //manages the turns of the game and identifies a winner
    while(play_game(board, players, numPlayers) != 1);

    return 0;

}

