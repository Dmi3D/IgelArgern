
/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(Square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */

void place_tokens(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers);

int smallestTokenStack;

void checkingColumn(Square board[NUM_ROWS][NUM_COLUMNS], int colCord);

int tokensPerSquare(Square board[NUM_ROWS][NUM_COLUMNS], int rowCord, int colCord);

int isCorrectToken(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int i, int rowCord, int colCord);

int obstacleCheck(Square board[NUM_ROWS][NUM_COLUMNS], int dice, int colCord);

void tokenTravel(Square board[][NUM_COLUMNS], int currentPosRow, int currentPosCol, int newPosRow, int newPostCol);

/*
 *  * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
int play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers);


