//Created by Max Reiver
#ifndef BATTLESHIPHEADER_H_INCLUDED
#define BATTLESHIPHEADER_H_INCLUDED

// board constants
#define ROWS 10
#define COLS 10
#define WATER '~'

// player constants
#define MANUAL 49
#define RANDOM 50
#define PLAYERS 2
#define PLAYER1 0
#define PLAYER2 1
#define PLAYERONE "Player 1"
#define PLAYERTWO "Player 2"

// ship constants
#define NUM_SHIPS 5
#define HORIZONTAL 'H'
#define VERTICAL 'V'

#define CARRIER 'C'
#define BATTLESHIP 'B'
#define CRUISER 'R'
#define SUBMARINE 'S'
#define DESTROYER 'D'

#define CARRIER_SZ 5
#define BATTLESHIP_SZ 4
#define CRUISER_SZ 3
#define SUBMARINE_SZ 3
#define DESTROYER_SZ 2


#define HIT 'X'
#define MISS '.'

//structs
typedef struct gameboard
{
    char board [ROWS] [COLS];
}GameBoard;

typedef struct Location
{
    int row;
    int column;
}Location ;

typedef struct Ship
{
    char name [11];
    char symbol;
    int length;
    bool sunk;
    Location start;
}Ship;

typedef struct Human
{
    char name [20];
    GameBoard gameBoard;
    Ship ships [NUM_SHIPS];
}Player;
// numerating function decleration
enum shiptype {battleship, carrier, cruiser, destroyer, submarine};


// function declaration global
void welcomeScreen();
void displayGameBoard(Player player);
void clearScreen();
int displayMenu();
void initializeBoard(Player * player);
void initializePlayer(Player *player, char *name);
void initializeShips(Player * player);
void displayShips(Player player);
void manualShipPlace(Player * player);
void randomShipPlace(Player * player);
bool isValid (Player player, int row, int col, int length, char orient);
void placeShip(Player * player, int row, int col, Ship ship, char orient);

//new global declarations
void playGame(Player * playerOne, Player * playerTwo);
int switchPlayer(int currentPlayer);
Location getTarget(Player player);
Location getRandomTarget();
void checkShot(Player * player, Location target);
void updatePlayerData(Player * player, Location location, char result, char ship);
void checkShips(Player * player, Location location, char ship);
void endGame(Player player);



#endif // BATTLESHIP_H_INCLUDED
