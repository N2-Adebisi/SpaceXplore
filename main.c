#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


#define Row 18
#define Column 18
//#define Easy 1
#define Medium 2
#define Hard 3
#define Easy_max_Garbage 5
#define Medium_max_Garbage 8
#define Hard_max_Garbage 10
#define Easy_max_asteroid 3
#define Medium_max_asteroid 4
#define Hard_max_asteroid 5

//int pesent_diffficulty = Easy;
int max_garbage;
int max_asteroid;
int fuel_reduction_per_movement;
int game_time;

/*void intotext(){//Function to read the file in
    FILE *readfile ;
    readfile = fopen("Introduction.txt","r");//open the introduction file in read mode
    if (readfile ==NULL){//if not file seen
        printf("Failed to load introduction text\n");//Tell the user
        return ;
    }
    char line[1000];//store the content of the file
    while(fgets(line, 1000,readfile)){//Read the content
        printf("%s",line);//and print it
    }
    fclose(readfile);//Close file
}
void leaderboard(){
    FILE *writefile;
    writefile = fopen("Leaderboard.txt","w");
    fprintf(writefile,"Naveedah");
    fclose(writefile);

}*/


/*void Difficulty(int difficulty){
    switch(difficulty){ //swich through all difficulty setting
        case Easy://if easy
            max_garbage=Easy_max_Garbage;//max garbage= 5
            max_asteroid=Easy_max_asteroid;
            game_time=180;//game time = 180
            fuel_reduction_per_movement=2 ;//fuel reduction per movement = 2

            break;//break
        case Medium://if Medium
            max_garbage= Medium_max_Garbage;//max garbage= 8
            max_asteroid=Medium_max_asteroid;
            game_time=120 ;//game time = 120
            fuel_reduction_per_movement= 4;//fuel reduction per movement = 4
            break;//break
        case Hard://if hard
            max_garbage=Hard_max_Garbage;//max garbage= 10
            max_asteroid=Hard_max_asteroid;
            game_time= 60;//game time = 60
            fuel_reduction_per_movement=6;//fuel reduction per movement = 6
            break;
        default:
            Difficulty(Medium);
            break;
    }
}
void print_difficulty_menu(){//Function for Difficulty menu
    printf("Select difficulty level\n");//Display difficult level user can choose from
    printf("1.Easy\n");
    printf("2.Medium\n");
    printf("3.Hard\n");

}
*/


// Structure for garbage piece
typedef struct {
    int x;//Declaring the row position x
    int y;//Declaring the colon position y
    char letters;//declaring random letters for the garbage
} Garbage;

// Structure for asteroid piece
/*typedef struct {
    int x;//Declaring the row position x
    int y;//Declaring the colon position y
    char asterisk;//declaring random letters for the garbage
    int direction;
} Asteroid;

// Structure for asteroid piece
typedef struct {
    int x;//Declaring the row position x
    int y;//Declaring the colon position y
    char caret;//declaring random letters for the garbage
} Spaceship;
*/
char grid[19][19];
int score = 0;
int fuel =100;
int time_left;
int life = 3;




void Grid(char grid[19][19]) {// Function to create the grid}
    printf("Player: ^\t|\trandom letters: garbage\t|\tAsteroid: *\n");
    for (int i = 0; i <= Row; i++) { //Lopping through the row for the grid
        for (int j = 0; j <= Column; j++) { //Lopping through the colon for the grid
            if (i == 0 || i == Row|| j == 0 || j == Column) {//if i is 0 or i is equal to amount of row(18)or j is 0 or j is equal to amount of colon(18)
                grid[i][j] = 'x';//initialise grid array [i][j] to x
            } else {//if not
                grid[i][j] = ' ';//initialising grid array [i][j] to space
            }
        }
    }
}
int possitionOccupied(char grid[19][19],int x,int y){//Function to check that no garbages are placed in rhe same position
    if(grid[x][y]!=' '&& grid[x][y]!=x){//check if theres a garbage there
        return 1;//if yes return 1
    }
    return 0;//if no return 0
}
// Function to place garbages in the grid using structure
void placeGarbage(char grid[19][19], Garbage *garbages) {

    for (int i = 0; i < max_garbage; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r=rand() % (Row-1)+1; //Getting random position on the row in the grid
            c=rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(grid,r,c)); //
        garbages[i].x = r;//initialising the random row position to the x position of the garbage
        garbages[i].y = c;//initialising the random column position to the x position of the garbage
        garbages[i].letters = 'A' + (rand() % 26);//initialising the getting random letters to the letters in the garbage struct
        grid[r][c] = garbages[i].letters;//initialising grid array position [r][c] to the random letters

    }
}
// Function to place asteroid in the grid using structure
/*void placeAsteroid(char grid[19][19],  Asteroid *asteroid) {
    for (int i = 0; i < max_asteroid; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r= rand() % (Row-1)+1; //Getting random position on the row in the grid
            c= rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(grid,r,c));
        asteroid[i].x = r;//initialising the random row position to the x position of the asteroid
        asteroid[i].y = c;//initialising the random column position to the x position of the asteroid
        asteroid[i].asterisk = '*';//initialising * to the asteroid
        grid[r][c] = asteroid[i].asterisk;//initialising grid array position [r][c] to the asterisk
    }
}
// Function to place spaceship in the grid using structure
void placeSpaceship(char grid[19][19], Spaceship *spaceship) {
    for (int i = 0; i < 1; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r=rand() % (Row-1)+1; //Getting random position on the row in the grid
            c=rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(grid,r,c));
        spaceship[i].x = r;//initialising the random row position to the x position of the spaceship
        spaceship[i].y = c;//initialising the random column position to the x position of the spaceship
        spaceship[i].caret = '^';//initialising ^ to the spaceship
        grid[r][c] = spaceship[i].caret;//initialising grid array position [r][c] to the spaceship
    }
}*/
// Function to print the grid
void printGrid(char grid[19][19]) {
    for (int i = 0; i <= Row; i++) {//looping through the row
        for (int j = 0; j <= Column; j++) {//looping through the colon
            printf(" %c ", grid[i][j]);//Printing the grid with the garbage included
        }
        printf("\n"); //Printing the space
    }
  /*  printf("Score:%d\n",score);//Show thr score the spaceship has attained after getting a garbage
    printf("Fuel:%d\n",fuel);//Show fuel of the spaceship at it is played
    printf("Time left:%d\n",time_left);//Show the time left as it is played
    printf("Lives: %d\n", life);//Show the life of the spaceship as it is played
    if(score>=max_garbage){//if the score is greater than the maximum garbage
        printf("You cleaned the space,you win!\n");//Tell the user they have cleaned the space and have won
        exit(0);//Then leave the game
    }*/
}
int main() {
   /* intotext();
    leaderboard();
    print_difficulty_menu();//calling print function
    char choice = getch();//getting the character stored under the choice
    switch (choice) { //choosing between choices
        case '1'://if one inputted
            Difficulty(Easy);//switch difficulty level to easy
            break;//Break after choosing
        case '2'://if two inputted
            Difficulty(Medium);//switch difficulty level to medium
            break;//Break after choosing
        case '3'://if three inputted
            Difficulty(Hard);//switch difficulty level to hard
            break;//Break after choosing
        default:
            printf("Invalid choice,Setting difficulty to medium\n");//if an invalid number is chosen switch to medium
            Difficulty(Medium);//
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
    printf("Max Garbage:%d\n", max_garbage);//for each difficulty print the aount of garbage
    printf("Game time:%d\n", game_time);//game time
    printf("Fuel reduction per movement :%d\n", fuel_reduction_per_movement);//and reduction per movement
    time_t time_start = time(NULL);*/
    Garbage garbages[max_garbage];//Initialising array garbage with max (5) garbage struct
   // Asteroid asteroid[max_asteroid];//Initialising array asteroid with max (3) asteroid struct
    //Spaceship spaceship;//Initialising array asteroid with 1 Spaceship struct

    srand(time(NULL)); // To change garbage placement and asteroid placement in the grid each time it is run

    Grid(grid);//calling function Grid with input grid
    placeGarbage(grid, garbages);//Calling function place Garbage with input grid and garbage array 5
  //  placeAsteroid(grid, asteroid);//Calling function place Asteroid with input grid and asteroid array 3
    //placeSpaceship(grid, &spaceship);//Calling function place Asteroid with input grid and spaceship
    printGrid(grid);//calling the function to print the grid
    //paceship_fuel();



    /* ##for (;;) {

         int time_used = time(NULL) - time_start;//Getting the time used while playing
         time_left = game_time - time_used;//Getting the time left
         if (time_left <= 0) {//if the time is less than o
             printf("Time up,Game over!");//Tell the user
             exit(0);//then leave the game
         }
         if (kbhit()) {//if any key pressed
             char ch = getch();//initialising stored  in getch() to ch

             if (ch == 'W' || ch == 'A' || ch == 'S' || ch == 'D') {
                 moveAsteroid(grid, asteroid, &spaceship);//moving the spaceship on key pressed
                 moveSpaceship(grid, &spaceship, ch);//moving the spaceship on key pressed
                 Spaceship_fuel();
                 printGrid(grid);//update the grid after spaceship has moved
                 printf("knfnkmo");
             }


         }
     }*/




    return 0;
}