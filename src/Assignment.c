/*
 ============================================================================
 Name        : Assignment.c
 Author      : Zhong Ming Tan
 Version     :
 Copyright   : Zhong Ming Tan @ 2018
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "battleship.h"

ship ships1[15] =
{
    {"Carrier",carrier_size},
    {"Battleship1",battleship_size},
    {"Battleship2",battleship_size},
    {"Cruiser1",cruiser_size},{"Cruiser2",cruiser_size},{"Cruiser3",cruiser_size},
    {"Submarine1",submarine_size},{"Submarine2",submarine_size},{"Submarine3",submarine_size},{"Submarine4",submarine_size},
    {"Destroyer1",destroyer_size},{"Destroyer2",destroyer_size},{"Destroyer3",destroyer_size},{"Destroyer4",destroyer_size},{"Destroyer5",destroyer_size}
  };

ship ships2[15] =
{
        {"Carrier",carrier_size},
        {"Battleship1",battleship_size},
        {"Battleship2",battleship_size},
        {"Cruiser1",cruiser_size},{"Cruiser2",cruiser_size},{"Cruiser3",cruiser_size},
        {"Submarine1",submarine_size},{"Submarine2",submarine_size},{"Submarine3",submarine_size},{"Submarine4",submarine_size},
        {"Destroyer1",destroyer_size},{"Destroyer2",destroyer_size},{"Destroyer3",destroyer_size},{"Destroyer4",destroyer_size},{"Destroyer5",destroyer_size}
};

int main(void)
{
    fullscreen();
    system("COLOR 0A");

    setvbuf(stderr,NULL,_IONBF,0);
    setvbuf(stdout,NULL,_IONBF,0);

    initialize_grid(&array1[0][0]);
    initialize_grid(&array2[0][0]);

    //ask player 1 to deploy the ship
    for (int turn = 0; turn < 15; turn++){
        player = 1;
        setShip(&player,&turn);
        print_ships(&ships1[turn]);
        getchar();
        system("cls");
        printf("===================================================\n");
    }

    system("cls");
    print_grid(&array1[0][0]);


    for(int turn = 0; turn < 100; turn++){
        ask_hit(&turn);
        system("cls");
        print_grid(&array1[0][0]);
    }

}

void fullscreen()/* function definition for
                                                         fullscreen */
{  keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
}


void print_ships (ship *ships){
        for(int k = 0; k < 5; k++){
            printf("%s ",ships->name);
            printf("x = %i ",ships->position[k].x);
            printf("y = %i ",ships->position[k].y);
            printf("\n");
        }

}

int check_hit(int x , int y , char *array, ship *ships){
    int position = x * ROWS + y;
    switch(array[position]){
        case WATER:
            printf("Miss Shot\n");
            array[position] = MISS;
            break;
        case SHIP:
            printf("HIT!");
            array[position] = HIT;
            break;
        case MISS:
        case HIT:
            printf("This place is shot before\n");
            return 1;
            break;
        default:
            printf("Shot error\n");
            return 1;
            break;
    }
    return 0;
}

int ask_hit(int *turn){
    int player = 0;
    ship *ships;
    char *array;
    *turn %= 2;

    switch(*turn){
        case 0:
            player = 1;
            array = &array1[0][0];
            ships = &ships1[*turn];
            break;
        case 1:
            player = 2;
            array = &array1[0][0];
            ships = &ships1[*turn];
            break;
        default:
            printf("Invalid player\n");

    }

    //initialize...
    askinput: setvbuf(stdout,NULL,_IONBF,0);
    int counter = 0;

    int start_x = 0; char input_y;
    int start_y = 0;

       do{
           //display error message
           if(counter > 0){
               printf("Invalid input\n");
           }

           printf("Player%i: Please select a coordinate to hit !!! Eg = A5\n",player);
           scanf("%c%i",&input_y,&start_x);
           fflush(stdin);

           //convert character to uppercase
           input_y = toupper(input_y);

           //minus 1 for array
           start_x -= 1;

           //calculate the y value from character in aschii table
           //Example B - A = 1;
           start_y = input_y - 65;

           counter ++;
       }while((start_x < 0 || start_x > 9) || (start_y < 0 || start_y > 9 ));// if (0 - 9) and if (A - Z)

       switch(check_hit(start_x,start_y,array,ships)){
           case 0:
               return 0;
           case 1:
               goto askinput;
           default:
               printf("Check hit error\n");
       }
    return 0;
}


//Function: Initialize the array in pointer
//Parameter: &array[0][0];
void initialize_grid (char *array){
    int counter = 0;
    for (int i = 0; i < ROWS * COLS; i++)    {
        *(array + i) = WATER ;
        //printf("%c\n",*(array + i));
        counter++;
    }

    for(int j = 0; j < 15; j++){
        for(int k = 0; k < 5; k++){
            ships1[j].position[k].x = 0;
            ships1[j].position[k].y = 0;
            ships2[j].position[k].x = 0;
            ships2[j].position[k].y = 0;
        }
    }
    //printf("%i",counter);
}

//Function: Display the grid and content
//Parameter: &array[0][0];
void print_grid (char *array){

    printf("\t|");
    for (int i = 65; i < 75; i++){
        printf(" %c |",i);
    }
        printf("\n--------|---|---|---|---|---|---|---|---|---|---|\n");
    for(int i = 0; i < ROWS; i++ ){
        printf("%i \t|" , i + 1 );
        for(int j = 0 ; j < COLS; j++){
            printf(" %c |",*(array + i * COLS + j));
        }
        printf("\n--------|---|---|---|---|---|---|---|---|---|---|\n");
    }
        printf("===================================================\n");
}

//Function: Deploy the starting point of ship and display the grid
//Parameter: x set by user  , y set by user , array defined
int set_starting_point (int x, int y,char *array,ship *ships){
    array[x * COLS + y] = SHIP;
    //system("cls");
    print_grid(array);

    return 0;
}

//Function: Check the avability of array
//Parameter: x set by user , y set by user , array defined
//return : userinput function
int check_starting_point(int x, int y,char *array){

    if(array[x * COLS + y] == WATER)
        set_starting_point(x, y, array,ships1);
    else
        return 1;

    return 0;
}

//Function: Check the direction for array
//parameter: x and y is initialpoint set by user, array defined, type of ship, direction
//Return:  ask direction
int checkDirection (int x, int y, char *array, int*shipType ,int *direction, ship *ships){
    //initialize
    int x_backup = x, y_backup = y;
    int shipSize = 0;
    //define the size of ship
    switch(*shipType){
        case 0:
            shipSize = carrier_size - 1;
            break;
        case 1:
            shipSize = battleship_size - 1;
            break;
        case 2:
            shipSize = cruiser_size - 1;
            break;
        case 3:
            shipSize = submarine_size - 1;
            break;
        case 4:
            shipSize = destroyer_size - 1;
            break;
        default:
            return 1;
    }
    //printf("shipsize = %i\n",shipSize);

    int pos = x * ROWS + y;
    int endPoint = (x * ROWS + y) + shipSize;
    int diff = endPoint - pos + 1;
    //printf("pos = %i endPoint = %i\n",pos,endPoint);
    //printf("Diffr = %i\n",diff);

    if(*direction == N) {
        int col = (x * ROWS + y)%10;
        for(int i = 0; i < shipSize; i ++){
            x--;
            if(col != (x * ROWS + y)%10){
                //printf("Invalid");
                return 1;
            }
        }
            if(shipSize < diff  && diff >= 0){
                    //printf("Valid\n");
                }

            else{
                    //printf("Invalid Diffr = %i\n",diff);
                    return 1;
                }
    }

    x = x_backup; y = y_backup;
    int valid = 0;

    if(*direction == N){
        for (int i = 0; i < shipSize; i++){
            x--;
            //printf("i = %i x = %i\n",i,x);
                if(array[ x * ROWS + y] != WATER){
                   //printf("%i\n",x * ROWS + y);
                    valid = 1 ;
                    return 1;
                }
                else{
                    valid = 0;
                }
        }
        if (valid == 0){
            x = x_backup; y = y_backup;
            for (int i = 0; i < shipSize; i++){
                x--;
                array [ x * ROWS + y] = SHIP;
                ships->position[i+1].x = x;
                ships->position[i+1].y = y;
            }
        }
        else {
            return 1;
        }
    }

    else if (*direction == S){
        valid = 0;
        for (int i = 0; i < shipSize; i++){
            x++;
            //printf("shipsize = %i i = %i  pos = %i\n",shipSize,i,x * ROWS + y);
                if(array[ x * ROWS + y] != WATER){
                    //printf("%i\n",x * ROWS + y);
                    valid = 1 ;
                    return 1;
                }
                else
                {
                    valid = 0;
                }
        }
        if (valid == 0){
            x = x_backup; y = y_backup;
            for (int i = 0; i < shipSize; i++){
                        x++;
                        array [ x * ROWS + y ] = SHIP;
                        ships->position[i+1].x = x;
                        ships->position[i+1].y = y;
                    }
        }
        else {
            return 1;
        }
    }
    else if(*direction == W) {
        int col = (x * ROWS + y)/10;
        for (int j = 0; j < shipSize; j++){
            y--;
            if((col - (x * ROWS + y)/10 )!= 0){
                return 1;
            }
        }
        y = y_backup;
        for (int i = 0; i < shipSize; i++) {
            y--;
            if(col == (x * ROWS + y)/10) {
                if(array[ x * ROWS + y] == WATER) {
                    x = x_backup; y = y_backup;
                    for(int i  = 0; i < shipSize; i++) {
                        y--;
                        array [ x * ROWS + y ] = SHIP;
                        ships->position[i+1].x = x;
                        ships->position[i+1].y = y;
                    }
                }
            }
            else{
                return 1;
            }
        }
    }
    else if(*direction == E) {
        int col = (x * ROWS + y)/10;
        for (int j = 0; j < shipSize; j++){
            y++;
            if((col - (x * ROWS + y)/10 )!= 0){
                return 1;
            }
        }
        y = y_backup;
        for (int i = 0; i < shipSize; i++) {
            y++;
            if(col == (x * ROWS + y)/10) {
                if(array[ x * ROWS + y] == WATER) {
                    x = x_backup; y = y_backup;
                    for(int i  = 0; i < shipSize; i++) {
                        y++;
                        array [ x * ROWS + y ] = SHIP;
                        ships->position[i+1].x = x;
                        ships->position[i+1].y = y;
                    }
                }
            }
            else{
                return 1;
            }
        }
    }

    else{
        return 1;
    }

    return 0;
}

//Ask user to input the direction
//parameter: initial x and y set by user,array and type of ship
//return: user input function
int askDirection (int x, int y, char* array, int*shipType,ship *ships){

    setvbuf(stdout,NULL,_IONBF,0);

    //initialize
    char direction;

    int counter = 0, valid = 0;

    //do until direction set by user is N,E,S,W
    do{
        //Display error message
        if(counter > 0)
            printf("Invalid input\n");

        printf("Enter direction (N = north, E = east, S = south, W = west)\n");
        scanf("%c",&direction);
        fflush(stdin);

        // choose direction and verify the direction
        //call function check direction
        switch(toupper(direction)){
                    case 'N':
                        valid = checkDirection(x,y,array,shipType,&N,ships);
                        break;
                    case 'E':
                         valid = checkDirection(x,y,array,shipType,&E,ships);
                        break;
                    case 'S':
                        valid = checkDirection(x,y,array,shipType,&S,ships);
                        break;
                    case 'W':
                        valid = checkDirection(x,y,array,shipType,&W,ships);
                        break;
                    default:
                        printf("Invalid direction\n");
                        direction = 'F';
                }
       // printf("dir_code = %i\n");
    }while(direction == 'F');

    if(valid == 1){
        printf("The ship was blocked please choose direction again\n");
        askDirection (x, y, array,shipType,ships);
    }
    return 0;
}

//Function: Ask the input from user
//Parameter: player and type of ship
int userinput (int *player,int *shipType, char *array ,ship *ships){

    //initialize...
    int counter = 0;

    int start_x = 0; char input_y;
    int start_y = 0;

   do{
        setvbuf(stdout,NULL,_IONBF,0);
        //display error message
        if(counter > 0){
            printf("Invalid input\n");
        }

        printf("Player%i: Please enter a staring point Eg = A5\n",*player);
        scanf("%c%i",&input_y,&start_x);
        fflush(stdin);

        //convert character to uppercase
        input_y = toupper(input_y);

        //minus 1 for array
        start_x -= 1;

        //calculate the y value from character in aschii table
        //Example B - A = 1;
        start_y = input_y - 65;

        counter ++;
    }while((start_x < 0 || start_x > 9) || (start_y < 0 || start_y > 9 ));// if (0 - 9) and if (A - Z)

    //printf("x = %i y = %i", start_x, start_y);

    if(check_starting_point(start_x, start_y, array) != 0){
        printf("The place was occupied\n");
        userinput (player,shipType, array ,ships);
    }else{
        ships->position[0].x = start_x;
        ships->position[0].y = start_y;
        //ask direction
        askDirection(start_x,start_y,array,shipType,ships);
    }

    return 0;
}

//Function :Ask user to input the ship
//Parameter: player, number of turn
int setShip (int *player, int*turn){

    char *array;
    ship *ships;

     switch(*player){
        case 1:
            array = &array1[0][0];
            ships = &ships1[0];
            break;
        case 2:
            array = &array2[0][0];
            ships = &ships2[0];
            break;
    }

     print_grid(array);

    //Display the rule
    printf("Player%i: You will have:\n",*player);
    printf("Class of ship \t Size \t Number\n");
    printf("Carrier \t 5  \t 1\n");
    printf("Battleship \t 4 \t 2\n");
    printf("Cruiser \t 3\t 3\n");
    printf("Submarine \t 3 \t 4\n");
    printf("Destroyer \t 2 \t 5\n");
    printf("Please deploy your %s\n",ships[*turn].name);

    //Determine the type of ship by turn
    //and ask user to deploy the ship
    switch (*turn){
        case 0:
            userinput(player,&carrier,array,&ships[*turn]);
            break;
        case 1 ... 2:
            userinput(player,&battleship,array,&ships[*turn]);
            break;
        case 3 ... 6:
            userinput(player,&cruiser,array,&ships[*turn]);
            break;
        case 7 ... 10:
            userinput(player,&submarine,array,&ships[*turn]);
            break;
        case 11 ... 15:
            userinput(player,&destroyer,array,&ships[*turn]);
            break;
        default:
            printf("Invalid setShip\n");
            setShip(player,turn);
    }
    return 0;
}
