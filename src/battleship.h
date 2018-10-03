/*==============================================================================
 | Filename: battleship.h
 | Programmer: Tan Zhong Ming
 | Programming Assignment Introduction to Programming 2018: Battleship in Standard C
 | Date: October 10, 2018
 +------------------------------------------------------------------------------
 | Description: Thie file contains all the function definition of the prototypes
 |              listed in battleship.h These are the functions necessary to run
 |              the game of Battleship.
 ==============================================================================*/

#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#define ROWS 10
#define COLS 10

//Define the ship code for type of ship
int carrier     =   0;
int battleship  =   1;
int cruiser     =   2;
int submarine   =   3;
int destroyer   =   4;

//Define the code for orrientation
int N = 1; // NORTH
int E = 2; // EAST
int S = 3; // SOUTH
int W = 4; // WEST


//Define the size of type of ship
#define carrier_size     5 // size of carrier    is 5
#define battleship_size  4 // size of battleship is 4
#define cruiser_size     3 // size of cruiser    is 3
#define submarine_size   3 // size of submarine  is 3
#define destroyer_size   2 // size of destroyer  is 2

//Define the pattern for the grid
#define WATER   '~' // Define '~' to representing WATER
#define SHIP    'O' // Define 'O' to representing SHIP
#define HIT     'H' // Define 'H' to representing HIT
#define MISS    'X' // Define 'X' to representing MISS

// Total size of ship is 45 so that player require to hit
// 45 times in order to win
#define WIN_CONDITION 45

char array1 [ROWS][COLS];
char array2 [ROWS][COLS];

// Conter for each player
int player1_hit = 0;
int player2_hit = 1;

// number of player
int player = 0;

//struct that store the position to determine
// ship sunk
typedef struct position{
        int x;
        int y;
}Position;

// struct that define the type of ship
typedef struct ship{
    char name[15]; // name of ship
    int size; // size of ship
    Position position[5];
}ship;

void initialize_grid (char *array);
void print_grid (char *array);
int setShip (int *player, int*turn);
int userinput (int *player,int *shipType, char *array ,ship *ships);
int set_starting_point (int x, int y,char *array,ship *ships);
int check_starting_point(int x, int y,char *array);
int askDirection (int x, int y, char* array, int*shipType,ship *ships);
int checkDirection (int x, int y, char *array, int*shipType ,int *direction,ship *ships);

void fullscreen();
void print_ships (ship *ships);

int check_hit(int x , int y , char *array, ship *ships,int player);
int ask_hit(int *turn);
int check_ships(int x,int y, ship *ships);
void count_to_win (int player);

void print_win(int *player);


#endif /* BATTLESHIP_H_ */
