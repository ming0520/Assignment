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

//a struct type ships for player 1 and player 2
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

int main(int argc, char* argv[])
{
    setvbuf(stderr,NULL,_IONBF,0);
    setvbuf(stdout,NULL,_IONBF,0);


    if (toupper(*argv[1]) == 'f'){
        fullscreen();
    }
    else{
        printf("Game must run in command promt with full screen (f)");
    }

    system("COLOR 0A");

    initialize_grid(&array1[0][0]);
    initialize_grid(&array2[0][0]);

    //ask player 1 to deploy the ship
    for (int turn = 0; turn < 15; turn++){
        player = 1;
        setShip(&player,&turn);
        system("cls");
        printf("===================================================\n");
    }
    for (int turn = 0; turn < 15; turn++){
        player = 2;
        setShip(&player,&turn);
        system("cls");
        printf("===================================================\n");
    }

    system("cls");

    for(int turn = 0; turn < 200; turn++){
        switch(turn % 2){
            case 0:
                printf("                 Player2 BOARD\n");
                printf("===================================================\n");
                print_grid(&array2[0][0]);
                break;
            case 1:
                printf("                 Player 1 BOARD\n");
                printf("===================================================\n");
                print_grid(&array1[0][0]);
                break;
            default:
                printf("Attack print grid problem\n");
        }
        ask_hit(&turn);
        system("cls");
    }


}

/**
 * Function name : fullscreen()
 * Date Created  : 12 October 2018
 * Usage         : welcomeScreen ();
 * Definition    : Display in full screen
 * Parameter     : void
 * return        : void
 */
void fullscreen()
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
    //print the array position of particular ship (testing purpose)
        for(int k = 0; k < ships->size; k++){
            printf("%s ",ships->name);// display name of ship
            printf("x = %i ",ships->position[k].x); // display value x of ship
            printf("y = %i ",ships->position[k].y); // display value y of ship
            printf("\n");
        }

}

/**
 * Function name : check_ships()
 * Date Created  : 10 October 2018
 * Usage         : int check_ships(int ,int , ship* )
 * Definition    : DISPLAY when ship is sunk
 * Pre-condition : void
 * Post-condition: Display the grid
 * Parameter     : int x,int y, ship *ships
 * Return        : return TRUE (0) or FALSE(1) to check_hit()
 */
int check_ships(int x,int y, ship *ships){

    //check the position array through the array of the struct ship
    for (int i = 0; i < 15; i++ ){
        for(int j = 0; j < ships->size; j++){
            if(ships[i].position[j].x == x && ships[i].position[j].y == y){
                ships[i].position[j].x = 0;
                ships[i].position[j].y = 0;
                //print_ships(&ships[i]); // to display ships coordinate in struct (testing purpose)
                break;
            }
        }
    }

    //DISPLAY SUNK
    for (int i = 0; i < 15; i++){
        if(ships[i].position[0].x == 0 && ships[i].position[1].x == 0 && ships[i].position[2].x == 0  && ships[i].position[3].x == 0  && ships[4].position[4].x == 0){
            if(ships[i].position[0].y == 0 && ships[i].position[1].y == 0 && ships[i].position[2].y == 0 && ships[i].position[3].y == 0 && ships[i].position[4].y == 0){
                printf("%s\tSUNK!\n",ships[i].name);
            }
        }
    }
    return 0;
}

/**
 * Function name : check_hit()
 * Date Created  : 10 October 2018
 * Usage         : check_hit(int , int, char*, ship*,int);
 * Definition    : Incraese the counter of player 1 or player 2 when HIT
 * Pre-condition : MISS && HIT & WATERare defined as constant macros
 * Post-condition: Display the grid
 * Parameter     : int x , int y , char *array, ship *ships,int player
 * Return        : return TRUE (0) or FALSE(1) to ask_hit()
 */
int check_hit(int x , int y , char *array, ship *ships,int player){

    int position = x * ROWS + y;
    system("cls");

    switch(array[position]){
        case WATER:
            system("color 07");
            array[position] = MISS;
            print_grid(array);
            printf("Miss Shot\n");
            break;
        case SHIP:
            array[position] = HIT;
            count_to_win(player);
            print_grid(array);
            system("color 0B");
            printf("HIT!\n\n");
            check_ships(x, y, ships);
            break;
        case MISS:
        case HIT:
            print_grid(array);
            printf("This place is shot before\n");
            return 1;
            break;
        default:
            print_grid(array);
            printf("Shot error\n");
            return 1;
            break;
    }
    printf("Press <ENTER> to continue...\n");
    getchar();
    system("color 0A");
    return 0;
}


/**
 * Function name : ask_hit()
 * Date Created  : 10 October 2018
 * Usage         : ask_hit (int*);
 * Definition    : Get the x and y value from user
 * Pre-condition : void
 * Post-condition: void
 * Parameter     : int *player
 * Return        : check_hit()
 */
int ask_hit(int *turn){
    int player = 0;
    ship *ships;
    char *array;
    *turn %= 2;

    switch(*turn){
        case 0:
            player = 1;
            array = &array2[0][0];
            ships = &ships2[0];
            break;
        case 1:
            player = 2;
            array = &array1[0][0];
            ships = &ships1[0];
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

       switch(check_hit(start_x,start_y,array,ships,player)){
           case 0:
               return 0;
           case 1:
               goto askinput;
           default:
               printf("Check hit error\n");
       }
    return 0;
}

/**
 * Function name : count_to_win()
 * Date Created  : 10 October 2018
 * Usage         : count_to_win (int);
 * Definition    : Incraese the counter of player 1 or player 2 when HIT
 * Pre-condition : WIN_CONDITION are defined as constant macros
 * Post-condition: Display the win screen
 * Parameter     : int player
 * Return        : void
 */
void count_to_win (int player){
    switch(player){
        // player 1
        case 1:
            // player 1 counter increase by 1
            player1_hit++;
            printf("Player 1 %i hit\n",player1_hit);
            break;
        default:
            // player 2 counter increase by 1
            printf("Player 2 %i hit\n",player2_hit);
            player2_hit++;
    }

//Display the win screen when is WIN_CONDITION all the ship sunk
    if(player1_hit == WIN_CONDITION || player2_hit == WIN_CONDITION)
        print_win(&player);
}

void print_win(int *player){
    system("color 0c");
    printf("Player%i WIN!",*player);
    printf("Press <ENTER> to quit\n");
    getchar();
    system("exit");
}

/**
 * Function name : initialize_grid()
 * Date Created  : 10 October 2018
 * Usage         : initialize_grid (char* );
 * Definition    : Initialize the array in pointer .
 * Pre-condition : ROWS & COLS & WATER are defined as constant macros
 * Post-condition: Array initialize to (~) tilde representing water
 * Parameter     : &array[0][0]; <- create a pointer to the array
 * Return        : void
 */
void initialize_grid (char *array){
    int counter = 0;
    for (int i = 0; i < ROWS * COLS; i++)    {
        *(array + i) = WATER ;
        //printf("%c\n",*(array + i));
        counter++;
    }

    //initialize the array position in struct ship to 0;
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

/**
 * Function name : print_grid()
 * Date Created  : 10 October 2018
 * Usage         : print_grid(char* );
 * Definition    : This function prints the game board on the console
 *                 screen with an option of showing or not showing the pegs
 * Pre-condition : ROWS & COLS are defined as constant macros
 * Post-condition: Array initialize to (~) tilde representing water
 * Parameter     : &array[0][0]; <- create a pointer to the array
 * Return        : void
 */
void print_grid (char *array){

    //Tab for the first row of character
    printf("\t|");
    //Display the character by aschii table
    for (int i = 65; i < 75; i++){
        printf(" %c |",i);
    }
    // Display seperate line
        printf("\n--------|---|---|---|---|---|---|---|---|---|---|\n");
        //Display the first rows of the array
    for(int i = 0; i < ROWS; i++ ){
        printf("%i \t|" , i + 1 );
        for(int j = 0 ; j < COLS; j++){
            //Display the first cols of the array for each rows
            printf(" %c |",*(array + i * COLS + j));
        }
        printf("\n--------|---|---|---|---|---|---|---|---|---|---|\n");
    }
        printf("===================================================\n");
}

/**
 * Function name : set_starting_point()
 * Date Created  : 10 October 2018
 * Usage         : set_starting_point (int , int ,char* ,ship* );
 * Definition    : Deploy the starting point of ship and display the grid
 * Pre-condition : SHIP are defined as constant macros
 * Post-condition: SET the particular position of array to SHIP
 * Parameter     : x set by user  , y set by user , array in pointer, ship struct in pointer
 * Return        : return 0 (TRUE) only to check_starting_point();
 */
int set_starting_point (int x, int y,char *array,ship *ships){
    //set the particular position of the array to SHIP
    array[x * COLS + y] = SHIP;
    //Display the grid
    print_grid(array);

    return 0;
}

/**
 * Function name : check_starting_point()
 * Date Created  : 10 October 2018
 * Usage         : check_starting_point(int , int ,char*);
 * Definition    : CHECK the position defined by player is not occupied by other ship
 * Pre-condition : WATER are defined as constant macros
 * Post-condition: void
 * Parameter     : x set by user  , y set by user , array in pointer
 * Return        : return 0 (TRUE) or 1 (FALSE) only to userinput() function
 */
int check_starting_point(int x, int y,char *array){

    if(array[x * COLS + y] == WATER)
        //if the position of the array is equal to WATER
        set_starting_point(x, y, array,ships1);
    else
        //return 1 to the user input
        return 1;

    return 0;
}

/**
 * Function name : checkDirection ()
 * Date Created  : 10 October 2018
 * Usage         : checkDirection (int , int , char*, int* ,int*, ship*);
 * Definition    : CHECK the direction defined by player is not occupied by other ship
 * Pre-condition : SHIP & WATER & ship_Size & ROWS &COLS are defined as constant macros
 * Post-condition: SET the struct ship and Deploy the ship base on orientation
 * Parameter     : x and y is initialpoint set by user, array pointer, type of ship, direction,struct ship pointer
 * Return        : return 0 (TRUE) or 1 (FALSE) only to askDirection() function
 */
int checkDirection (int x, int y, char *array, int*shipType ,int *direction, ship *ships){
    //initialize
    int x_backup = x, y_backup = y;
    int shipSize = 0;
    //define the size of ship
    //and minus 1 for the origin
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

    //calculate the end point of the array
    int pos = x * ROWS + y;
    int endPoint = (x * ROWS + y) + shipSize;
    //calculate the diffrence of available space and the size of ship
    int diff = endPoint - pos + 1;
    //printf("pos = %i endPoint = %i\n",pos,endPoint);
    //printf("Diffr = %i\n",diff);

    //direction is North
    if(*direction == N) {
        //check no overflow by using remainder
        int col = (x * ROWS + y)%10;
        //check available space is smaller than ship size
        for(int i = 0; i < shipSize; i ++){
            x--;
            //overflow ! return 1 to previous function
            if(col != (x * ROWS + y)%10){
                //printf("Invalid");
                return 1;
            }
        }
        // the difference of available space is smaller than the size of ship
        // testing purpose
            if(shipSize < diff  && diff >= 0){
                    //printf("Valid\n");
                }

            else{
                    //printf("Invalid Diffr = %i\n",diff);
                    return 1;
                }
    }

    //reset value x and y
    x = x_backup; y = y_backup;
    //a boolean expression
    // TRUE (0), FALSE (1)
    int valid = 0;

    //direction North
    if(*direction == N){
        //return 1 when the next space to deploy the ships is not water
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

        //available space and deploy the ship
        //store the coordinate (position) to the struct ship array
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

    //direction South
    else if (*direction == S){
        //initialize....
        valid = 0;
        //check the availble space is not water and return 1
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
        //available space exsist deploy the ships
        if (valid == 0){
            //reset value of x and y
            x = x_backup; y = y_backup;
            for (int i = 0; i < shipSize; i++){
                        x++;
                        //plot the ship
                        array [ x * ROWS + y ] = SHIP;
                        //store in to stuct ship position array
                        ships->position[i+1].x = x;
                        ships->position[i+1].y = y;
                    }
        }
        else {
            return 1;
        }
    }

    //direction WEST
    else if(*direction == W) {
        valid = 0;
        //check no overflow by calculating the y value
        int col = (x * ROWS + y)/10;
        for (int j = 0; j < shipSize; j++){
            y--;
            if((col - (x * ROWS + y)/10 )!= 0){
                return 1;
            }
        }
        //reset value of y
        y = y_backup;
        //check flowing spcae is not water then return 1
        for (int i = 0; i < shipSize; i++) {
            y--;
            if(col == (x * ROWS + y)/10) {
                if(array[ x * ROWS + y] != WATER) {
                    valid = 1;
                    return 1;
                }
            }
            else{
                return 1;
            }
        }
        //availble space deploy the ship
        if(valid == 0){
            //reset value of x and value of y
            x = x_backup; y = y_backup;
            for(int i  = 0; i < shipSize; i++) {
                y--;
                array [ x * ROWS + y ] = SHIP;
                //store in to stuct ship position array
                ships->position[i+1].x = x;
                ships->position[i+1].y = y;
            }
        }else{
            return 1;
        }
    }
    else if(*direction == E) {
        valid = 0;
        //check no overflow by calculating the y value
        int col = (x * ROWS + y)/10;
        for (int j = 0; j < shipSize; j++){
            y++;
            if((col - (x * ROWS + y)/10 )!= 0){
                return 1;
            }
        }
        //reset value of y
        y = y_backup;
        for (int i = 0; i < shipSize; i++) {
            y++;
            if(col == (x * ROWS + y)/10) {
                if(array[ x * ROWS + y] != WATER) {
                    valid = 1;
                    return 1;
                }
            }
            else{
                return 1;
            }
        }
        //availble space deploy the ship
        if(valid == 0){
            //reset value of x and value of y
            x = x_backup; y = y_backup;
            for(int i  = 0; i < shipSize; i++) {
                y++;
                array [ x * ROWS + y ] = SHIP;
                //store in to stuct ship position array
                ships->position[i+1].x = x;
                ships->position[i+1].y = y;
            }
        }else{
            return 1;
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
        //run if not (0 - 9) and if (A - Z)
    }while((start_x < 0 || start_x > 9) || (start_y < 0 || start_y > 9 ));

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

    // set the array and struct of ship base on number of player
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

     system("cls");
     printf("                 Player %i BOARD\n",*player);
     printf("===================================================\n");
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
            userinput(player,&carrier,array,&ships[*turn]);// 1 carrier
            break;
        case 1 ... 2:
            userinput(player,&battleship,array,&ships[*turn]);// 2 battleship
            break;
        case 3 ... 6:
            userinput(player,&cruiser,array,&ships[*turn]);// 3 cuirser
            break;
        case 7 ... 10:
            userinput(player,&submarine,array,&ships[*turn]);// 4submarie
            break;
        case 11 ... 15:
            userinput(player,&destroyer,array,&ships[*turn]);// 5 destoryer
            break;
        default:
            printf("Invalid setShip\n");
            setShip(player,turn);
    }
    return 0;
}
