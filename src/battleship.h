/*
 * battleship.h
 *
 *  Created on: Oct 1, 2018
 *      Author: user
 */

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

char array1 [ROWS][COLS];
char array2 [ROWS][COLS];

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

int check_hit(int x , int y , char *array, ship *ships);
int ask_hit(int *turn);
int check_ships(int x,int y, ship *ships);


#endif /* BATTLESHIP_H_ */
