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

int carrier     =   0;
int battleship  =   1;
int cruiser     =   2;
int submarine   =   3;
int destroyer   =   4;

int N = 1;
int E = 2;
int S = 3;
int W = 4;

#define carrier_size     5
#define battleship_size  4
#define cruiser_size     3
#define submarine_size   3
#define destroyer_size   2

#define WATER   '~'
#define SHIP    'O'
#define HIT     'H'
#define MISS    'X'
#define WIN_CONDITION 45

char array1 [ROWS][COLS];
char array2 [ROWS][COLS];

int player1_hit = 0;
int player2_hit = 1;

int player = 0;

typedef struct position{
        int x;
        int y;
}Position;

typedef struct ship{
    char name[15];
    int size;
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
