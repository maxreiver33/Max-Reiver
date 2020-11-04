//Created by Max Reiver
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "battleshipHeader.h"


// main function

int main()
{
	/***** variable declarations *****/

	// variables for player
	short player     = 0;	     /* 0 -> player1, 1 -> player2 */
	short shot       = 0;        /* holds temp value if ship has been shot */
	int   menuSelect = 0;        /* option for player to place ship manually or randomly */

	// variables for directions
	int   north = 0;             /* holds change of value when going north */
	int	  south = 0;             /* holds change of value when going south */
	int	  east  = 0;             /* holds change of value when going east */
	int	  west  = 0;             /* holds change of value when going west */

	// variables for counters
	int   i       = 0;
	int	  counter = 1;

    // variable for ship symbol
	char  shipSymbol = '\0';       /* temporary value to save character symbol of the ship */

	Player playerOne;
	Player playerTwo;

    srand(time(0));

    // call function welcomeScreen
    welcomeScreen();

    // clear the screen
    clearScreen();

    // initialize players
    initializePlayer(&playerOne, PLAYERONE);

    // clear the screen
    clearScreen();

    initializePlayer(&playerTwo, PLAYERTWO);

    // clear the screen
    clearScreen();

    // get the human player ship placement method
    menuSelect = displayMenu();

    // clear the screen
    clearScreen();

    // evaluate player 1's ship placement option
    switch(menuSelect)
    {
        case MANUAL:
            printf("%s selected to place ships manually\n", playerOne.name);
            manualShipPlace(&playerOne);
            break;
        case RANDOM:
            printf("%s selected to place ships randomly\n", playerOne.name);
            randomShipPlace(&playerOne);
            break;
    }

    randomShipPlace(&playerTwo);

    //displayGameBoard(playerOne);
    //displayGameBoard(playerTwo);


     playGame(&playerOne, &playerTwo);

    // end program
    return 0;
}

void clearScreen()
{
    // send the clear screen command Windows
    system("cls");
    // send the clear screen command for UNIX flavor operating systems
    // system("clear");
}

// welcomeScreen function
void welcomeScreen ()
{
	printf ("BBBBB   AAAA  TTTTTT TTTTTT LL     EEEEEE  SSSSS HH  HH II PPPP\n");
	printf ("BB  BB AA  AA   TT     TT   LL     EE     SS     HH  HH II PP  PP\n");
	printf ("BBBBB  AA  AA   TT     TT   LL     EEEE    SSSS  HHHHHH II PPPP\n");
	printf ("BB  BB AAAAAA   TT     TT   LL     EE         SS HH  HH II PP\n");
	printf ("BBBBB  AA  AA   TT     TT   LLLLLL EEEEEE SSSSS  HH  HH II PP\n");
	printf ("\n\n");
	printf ("RULES OF THE GAME:\n");
	printf ("1. This is a two player game.\n");
	printf ("2. Player 1 is you and Player 2 is the computer.\n");
	printf ("3. Player 1 will be prompted if user wants to manually input coordinates\n");
	printf ("   for the game board or have the computer randomly generate a game board\n");
	printf ("4. There are five types of ships to be placed by longest length to the\n");
	printf ("   shortest; [c] Carrier has 5 cells, [b] Battleship has 4 cells, [r] Cruiser\n");
	printf ("   has 3 cells, [s] Submarine has 3 cells, [d] Destroyer has 2 cells\n");
	printf ("5. The computer randomly selects which player goes first\n");
	printf ("6. The game begins as each player tries to guess the location of the ships\n");
	printf ("   of the opposing player's game board; [X] hit and [~] miss\n");
	printf ("7. First player to guess the location of all ships wins\n\n");

	printf("\t\t\t\tHit <ENTER> to continue!\n");

	char enter;
	scanf("%c", &enter );
}

int displayMenu()
{
    // variable for menu selection value
    int select;

    while(select != MANUAL && select != RANDOM)
    {
        // prompt the user
        printf ("Select the option for human player ship placement:\n");
        printf ("[1] Manually\n");
        printf ("[2] Randomly\n");
        printf ("Enter Option: ");

        select = getchar();

        if(select != MANUAL && select != RANDOM)
            printf("Invalid option, try again\n");

        fflush(stdin);
    }


	return select;
}

void displayGameBoard(Player player)
{
    int row;
    int col;

    printf("\n%s's Game Board\n\n", player.name);
    printf("---------------------------------------------\n");
    printf("|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
    printf("---------------------------------------------\n");

    for(row = 0; row < ROWS; row++)
    {
        // display the row number
        printf("| %d ", row);

        for(col = 0; col < COLS; col++)
        {
            printf("| %c ", player.gameBoard.board[row][col]);
        }

        printf("|\n");
    }

    printf("---------------------------------------------\n");
}

void initializePlayer(Player * player, char * name)
{
    char playerName[20];
    GameBoard playerBoard;
	Ship ships[NUM_SHIPS];

    printf("Enter %s's name\n", name);
    gets(playerName);

    strcpy(player->name, playerName);
    player->gameBoard = playerBoard;
    memcpy(player->ships, ships, NUM_SHIPS);

    // initialize player board
    initializeBoard(player);
  //  displayGameBoard(*player);
//    getchar();
    clearScreen();

    // initialize ships
    initializeShips(player);
   // displayShips(*player);
//    getchar();
}

void initializeBoard(Player * player)
{
    memset(player->gameBoard.board, WATER, sizeof(player->gameBoard.board));
}

void initializeShips(Player * player)
{
    int shipNum;

    for(shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {
        Ship s;

        switch(shipNum)
        {
            // BATTLESHIP
            case battleship:
                 strcpy(s.name, "BATTLESHIP");
                 s.length = BATTLESHIP_SZ;
                 s.symbol = BATTLESHIP;
                 break;
             // CARRIER
            case carrier:
                 strcpy(s.name, "CARRIER");
                 s.length = CARRIER_SZ;
                 s.symbol = CARRIER;
                 break;
             // CRUISER
            case cruiser:
                 strcpy(s.name, "CRUISER");
                 s.length = CRUISER_SZ;
                 s.symbol = CRUISER;
                 break;
             // DESTROYER
            case destroyer:
                 strcpy(s.name, "DESTROYER");
                 s.length = DESTROYER_SZ;
                 s.symbol = DESTROYER;
                 break;
             // SUBMARINE
            case submarine:
                 strcpy(s.name, "SUBMARINE");
                 s.length = SUBMARINE_SZ;
                 s.symbol = SUBMARINE;
                 break;
        }

        s.sunk = false;
        s.start.column = -1;
        s.start.row = -1;
        player->ships[shipNum] = s;
    }
}

void displayShips(Player player)
{
    int shipNum;

    printf("%s's Ship Data\n\n", player.name);

    for(shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {
        printf("Name: %s\n", player.ships[shipNum].name);
        printf("Length: %d\n", player.ships[shipNum].length);
        printf("Symbol: %c\n", player.ships[shipNum].symbol);
        printf("Is sunk: %s\n", ( (player.ships[shipNum].sunk) ? "True" : "False") );
        printf("Location: row: %d col: %d\n\n", player.ships[shipNum].start.row, player.ships[shipNum].start.column);
    }
}

bool isValid (Player player, int row, int col, int length, char orient)
{
	int r;
	int c;

	bool valid = true;

    if( (row < 0 || (( (row + length) > 9)&& orient == 'V') ) )
        return false;

    if( (col < 0 || ( ( (col + length) > 9) && orient == 'H' ) ))
        return false;

    if(orient != 'H' && orient != 'V')
        return false;

    switch(orient)
    {
        case HORIZONTAL:
            for(c = col; c < (length + col); c++)
            {
                if (player.gameBoard.board[row][c] != WATER)
                {
                    return false;
                }
            }
            break;
        case VERTICAL:
            for(r = row; r < (length + row); r++)
            {
                if (player.gameBoard.board[r][col] != WATER)
                {
                    return false;
                }
            }
            break;
    }

	return valid;
}


void placeShip(Player * player, int row, int col, Ship ship, char orient)
{
    int r;
    int c;

//    printf("Placing ship %s with %d cells, starting at row/column %d/%d orient %c\n ", ship.name, ship.length, row, col, orient);

    switch(orient)
    {
        case HORIZONTAL:
            for(c = col; c < (ship.length + col); c++)
            {
                player->gameBoard.board[row][c] = ship.symbol;
            }
            break;
        case VERTICAL:
            for(r = row; r < (ship.length + row); r++)
            {
                player->gameBoard.board[r][col] = ship.symbol;
            }
            break;
    }
}

void manualShipPlace (Player * player)
{
	int shipNum;
    int row;
    int col;
    char orient;

	bool valid = false;

	for (shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {
		while (valid == false)
        {
			displayGameBoard (*player);

			printf ("Enter the row and col (e.g. 0 0) for the first cell of ship %s:\n", player->ships[shipNum].name);
			printf ("Row col ");
			scanf("%d %d", &row, &col);

			fflush(stdin);

			printf("What is the orientation for this ship? Enter H for horizontal, V for vertical\n");
			scanf("%c", &orient);
			orient = toupper(orient);

			printf("Checking row %d col %d orient %c...\n", row, col, orient);

			valid = isValid(*player, row, col, player->ships[shipNum].length, orient);

			if (valid)
            {
                placeShip(player, row, col, player->ships[shipNum], orient);
			}
			else
			{
				valid = false;
				printf ("Invalid, try again\n");
			}
        }

        valid = false;
	}
}

//code to randomize
void randomShipPlace (Player * player)
{
	int shipNum;
    int row;
    int col;
    int const DIR = 2;
    int const H = 0;
    int const V = 1;
    char orient;
    int o;

	bool valid = false;

	fflush (stdin);

	for (shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {
		while (valid == false)
        {
			row = (rand() % ROWS);
			col = (rand() % COLS);

			o = (rand() % DIR);

			if(o == H)
                orient = HORIZONTAL;
            else if(o == V)
                orient = VERTICAL;

			valid = isValid(*player, row, col, player->ships[shipNum].length, orient);

			if (valid)
            {
                placeShip(player, row, col, player->ships[shipNum], orient);
			}
			else
			{
				valid = false;
			}
        }

        valid = false;
	}
}

void playGame(Player * playerOne, Player * playerTwo){
        int currentPlayer = PLAYER1;
        Location target;
    while(true)
{


 switch(currentPlayer)
    {
        case PLAYER1:
            printf("%s turn",playerOne->name);
            displayGameBoard(*playerOne);
            target=getTarget(*playerOne);
            checkShot(playerTwo, target);
            break;

        case PLAYER2:
            printf("%s turn",playerTwo->name);
            target=getRandomTarget ();
            checkShot(playerOne, target);
            break;
        }

    currentPlayer=switchPlayer(currentPlayer);
    clearScreen();
    }
}


int switchPlayer(int currentPlayer){

   if(currentPlayer == PLAYER1)
    {
       return PLAYER2;
   }
   else if(currentPlayer == PLAYER2)
    {
       return PLAYER1;
   }
}

//registers
Location getTarget(Player player){

    Location target;
    fflush(stdin);
    printf("%s enter Target as row and col (ex. 3 4):",player.name);
    scanf("%d %d", &target.row, &target.column);
    fflush(stdin);
    return target;
}

//location of the row and column
Location getRandomTarget(){

    Location target;
    target.row = (rand() % ROWS);
    target.column = (rand() % COLS);
    return target;
}
// checks the shot as a hit or a miss
void checkShot(Player* player, Location target){

    char symbol = player->gameBoard.board[target.row][target.column];
    switch(symbol)
    {
        case WATER:
            printf("row %d col %d was a miss!", target.row, target.column);
            getchar();
            updatePlayerData(player, target, MISS, symbol);
            break;
        case CARRIER:
        case BATTLESHIP:
        case CRUISER:
        case SUBMARINE:
        case DESTROYER:
            printf("row %d col %d was a hit!", target.row, target.column);
            getchar();
            updatePlayerData(player, target, HIT, symbol);
            break;
        case HIT:
        case MISS:
        default:
            printf("Already guessed that location, lost turn! \n");
            getchar();
            break;

    }
}
//updates and checks the location of the ship as a hit
void updatePlayerData(Player * player, Location location, char result, char ship)
{
    player->gameBoard.board[location.row][location.column] = result;
    if(result == HIT)
    {
    checkShips(player, location, ship);
    }
}




//code to check the ships length and tells the user if it has sunk
void checkShips(Player * player, Location location, char ship)
{
    const int battleshipIdx=0;
    const int carrierIdx=1;
    const int cruiserIdx=2;
    const int destroyerIdx=3;
    const int submarineIdx=4;

    int sunkCount = 0;
    int shipNum;


    switch(ship)
    {
        case BATTLESHIP:
            player->ships[battleshipIdx].length --;
            if(player -> ships[battleshipIdx].length == 0)
            {
                printf("%s's BATTLESHIP is sunk!",player->name);
            }
            getchar();
            break;
        case CARRIER:
            player->ships[carrierIdx].length --;
            if(player -> ships[carrierIdx].length == 0)
            {
                printf("%s's CARRIER is sunk!",player->name);
            }
            getchar();
            break;
        case CRUISER:
            player->ships[cruiserIdx].length --;
            if(player -> ships[cruiserIdx].length == 0)
            {
                printf("%s's CRUISER is sunk!",player->name);
            }
            getchar();
            break;
        case DESTROYER:
            player->ships[destroyerIdx].length --;
            if(player -> ships[destroyerIdx].length == 0)
            {
                printf("%s's DESTROYER is sunk!",player->name);
            }
            getchar();
            break;
        case SUBMARINE:
            player->ships[submarineIdx].length --;
            if(player -> ships[submarineIdx].length == 0)
            {
                printf("%s's SUBMARINE is sunk!",player->name);
            }
            getchar();
            break;
    }


    for(shipNum = 0; shipNum < NUM_SHIPS; shipNum ++)
    {
        if(player -> ships [shipNum].length == 0)
            sunkCount++;
    }


    if (sunkCount == NUM_SHIPS)
    {
        endGame(*player);
    }
}





//code to print if the user has lost the game
void endGame(Player player)
{
    printf("%s HAS LOST THE GAME!",player.name);
    getchar();
    exit(0);
}
