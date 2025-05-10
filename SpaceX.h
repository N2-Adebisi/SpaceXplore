
#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// Grid constants
#define Row 18
#define Column 18

// Difficulty Levels
#define Easy 1
#define Medium 2
#define Hard 3

// Difficulty Settings
#define Easy_max_Garbage 5
#define Medium_max_Garbage 8
#define Hard_max_Garbage 10

#define Easy_max_asteroid 3
#define Medium_max_asteroid 4
#define Hard_max_asteroid 5

#define Easy_fuel_reduction 2
#define Medium_fuel_reduction 4
#define Hard_fuel_reduction 6

#define Hard_life 1




// Structs
typedef struct {
    int pesent_diffficulty;
    int max_garbage;
    int max_asteroid;
    int fuel_reduction_per_movement;
    int game_time;
    int score;
    int fuel;
    int time_left;
    int life;
    char grid[19][19];
}Game_settings;
typedef struct {//type def in C to create aliases for structure types
    // and define shorter, more descriptive names for the structures
    int x;
    int y;
    char letters;
} Garbage;

typedef struct {
    int x;
    int y;
    char asterisk;
    int direction;
} Asteroid;

typedef struct {
    int x;
    int y;
    char caret;
} Spaceship;

// Function declarations
void intotext();
void leaderboard();
void Difficulty(Game_settings *game_state,int difficulty,Spaceship *spaceship);
void print_difficulty_menu(Game_settings *game_state);
void Grid(Game_settings *game_state);
void moveSpaceship(Game_settings *game_state, Spaceship *spaceship,int arrow_key);
void moveAsteroid(Game_settings *game_state, Asteroid asteroid[],Spaceship *spaceship);
int possitionOccupied(Game_settings *game_state, int x, int y);
void placeGarbage(Game_settings *game_state, Garbage *garbages);
void placeAsteroid(Game_settings *game_state, Asteroid *asteroid);
void placeSpaceship(Game_settings *game_state, Spaceship *spaceship);
void printGrid(Game_settings *game_state);
void Spaceship_fuel(Game_settings *game_state);
void collision(Game_settings *game_state, Spaceship *spaceship,Asteroid asteroid[]);
void Timer(Game_settings *game_state);
void game_over(Game_settings *game_state);


#endif
