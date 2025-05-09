#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "SpaceX.h"

int main() {
    Game_settings game_state = {
            .pesent_diffficulty = Easy,.score=0,.fuel =100,.life = 3
    };
    Spaceship spaceship  ;
    intotext();
    leaderboard();
    print_difficulty_menu(&game_state);//calling print function
    char choice= getch();//getting the character stored under the choice
    switch (choice) { //choosing between choices
        case '1'://if one inputted
            Difficulty(
                    &game_state,Easy,&spaceship);//switch difficulty level to easy
            break;//Break after choosing
        case '2'://if two inputted
            Difficulty(&game_state,Medium,&spaceship);//switch difficulty level to medium
            break;//Break after choosing
        case '3'://if three inputted
            Difficulty(&game_state,Hard,&spaceship);//switch difficulty level to hard
            break;//Break after choosing
        default:
            printf("Invalid choice,Setting difficulty to medium\n");//if an invalid number is chosen switch to medium
            Difficulty(&game_state,Medium,&spaceship);//
            break;
    }
    printf("Difficulty level:\n");//Display difficulty level
    switch (choice) {//swich between each choice easy,medium,hard
        case '1'://if 1 entered
            printf("Easy\n");//print easy
            break;//break
        case '2'://if 2 entered
            printf("Medium\n");//print medium
            break;//break
        case '3'://if 3 entered
            printf("Hard\n");//print hard
            break;//break
        default://default incases of wrong input switch to medium
            printf("Medium \n");//print medium
            break;//break
    }
    printf("Max Garbage:%d\n",game_state.max_garbage);//for each difficulty print the aount of garbage
    printf("Game time:%d\n",game_state.game_time);//game time
    printf("Fuel reduction per movement :%d\n",game_state.fuel_reduction_per_movement);//and reduction per movement
    time_t time_start = time(NULL);
    // Garbage: A struct type previously defined to represent a piece of garbage, containing fields  x, y, and letters.
    //garbages: This is the name of the array declared.
    // [max_garbage]: This creates an array of Garbage structs with max_garbage number of elements .
    Garbage garbages[game_state.max_garbage];//Initialising array garbage with max (5) Garbage struct
    //Asteroid: A struct  defined earlier that holds details about an asteroid x, y, asterisk, and direction.
    //asteroid: The name of the array being created.
    //[max_asteroid]: The size of the array , set depending on the chosen difficulty .
    Asteroid asteroid[game_state.max_asteroid];//Initialising array asteroid with max (3) asteroid struct
    //Spaceship: This is a struct type you defined it contains x,y ,caret;
    //spaceship: This is the variable name it represents one spaceship on your grid.
    //Initialising array asteroid with 1 Spaceship struct
    srand(time(NULL)); // To change garbage placement and asteroid placement in the grid each time it is run

//it is the address of because  functions are written to accept a pointer to the entire struct, not just a single field.
    Grid(&game_state);//calling function Grid with input grid
    placeGarbage(&game_state, garbages);//Calling function place Garbage with input grid and garbage array 5
    placeAsteroid(&game_state, asteroid);//Calling function place Asteroid with input grid and asteroid array 3
    placeSpaceship(&game_state, &spaceship);//Calling function place Asteroid with input grid and spaceship
    printGrid(&game_state);//calling the function to print the grid
    Timer(&game_state);
    game_over(&game_state);


    for (;;) {


        int time_used = time(NULL) - time_start;//Getting the time used while playing
        game_state.time_left = game_state.game_time - time_used;//Getting the time left
        if (game_state.time_left <= 0) {//if the time is less than o
            printf("Time up,Game over!");//Tell the user
            exit(0);//then leave the game
        }
        if (kbhit()) {//if any key pressed
            char ch = getch();//initialising stored  in getch() to ch

            if (ch == 'W' || ch == 'A' || ch == 'S' || ch == 'D'|| ch=='w'|| ch == 'a' || ch == 's' || ch == 'd') {
                for (int i = 0; i < game_state.max_asteroid; i++) {
                    moveAsteroid(&game_state, &asteroid[i]);//moving the spaceship on key pressed
                }
                moveSpaceship(&game_state, &spaceship, ch);//moving the spaceship on key pressed
                collision(&game_state,&spaceship,asteroid);
                printGrid(&game_state);//update the grid after spaceship has moved
            }


        }
    }




    return 0;

}