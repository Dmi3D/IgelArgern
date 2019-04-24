/*PRINTS THE BOARD*/
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

/*COUNTS NUMBER OF TOKENS IN COLUMN 0*/
void checkingColumn(Square board[NUM_ROWS][NUM_COLUMNS], int colCord);

/*COUNTS NUMBER OF TOKENS PER SQUARE IN COLUMN 0*/
int tokensPerSquare(Square board[NUM_ROWS][NUM_COLUMNS], int rowCord, int colCord);

/*CHECKS IF PLAYER CHOOSING THEIR TOKEN IN SIDEWAYS MOVE*/
int isCorrectToken(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int i, int rowCord, int colCord);

/*CHECKING IF OBSTACLE SHOULD REMAIN OBSTACLE OR NOT*/
int obstacleCheck(Square board[NUM_ROWS][NUM_COLUMNS], int dice, int colCord);

/*MOVING TOKEN ON BOARD*/
void tokenTravel(Square board[][NUM_COLUMNS], int currentPosRow, int currentPosCol, int newPosRow, int newPostCol);

/*CHECKS IF THERE IS WINNER*/
int checkWinner(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers);

/*
 *  * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
int play_game(Square board[NUM_ROWS][NUM_COLUMNS], Player players[], int numPlayers);


