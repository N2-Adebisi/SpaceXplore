
#include "SpaceX.h"


void intotext(){//Function to read the file in
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

}
//A function called Difficulty, which sets the game parameters based on the difficulty level the player selects.
//int difficulty is a number that represents the difficulty level chosen by the player.
void Difficulty(Game_settings *game_state,int difficulty,Spaceship *spaceship){
    switch(difficulty){ //swich through all difficulty setting
        case Easy://if easy
            game_state->max_garbage= Easy_max_Garbage;//max garbage= 5
            game_state->max_asteroid=Easy_max_asteroid;//max asteroid= 3
            game_state->game_time=180;//game time = 180
            game_state->fuel_reduction_per_movement=Easy_fuel_reduction ;//fuel reduction per movement = 2

            break;//break
        case Medium://if Medium
            game_state->max_garbage= Medium_max_Garbage;//max garbage= 8
            game_state->max_asteroid=Medium_max_asteroid;//max asteroid= 4
            game_state->game_time=120 ;//game time = 120
            game_state->fuel_reduction_per_movement=Medium_fuel_reduction;//fuel reduction per movement = 4
            break;//break
        case Hard://if hard
            game_state->max_garbage=Hard_max_Garbage;//max garbage= 10
            game_state->max_asteroid=Hard_max_asteroid;//max asteroid= 5
            game_state->game_time= 60;//game time = 60
            game_state->fuel_reduction_per_movement=Hard_fuel_reduction;//fuel reduction per movement
            int X = (*spaceship).x;//Derefrencing then using a dot operator to access the structure field of pointer spaceship or in use
            int Y= spaceship->y;//using arrow operator to access the structure field of pointer spaceship or in use
            if (game_state->grid[X][Y] == '*') { //If an asteroid is hit
                game_state->life = Hard_life;//initialising live to 1
                game_state->life = game_state->life - 1;//Reduce life by 1 - 1 total for hard
                if(game_state->life<=0){//if life =0
                    printf("You hit an asteroid and ran out of life!\n");//Display "You hit an asteroid and ran out of life!"
                    exit(0);//Exit the game
                }
            }

            break;
        default://in cases of wrong input
            Difficulty(game_state,Medium,spaceship);//set to medium difficulty
            break;
    }

    game_state->time_left = game_state->game_time;  //initialising time left to game time before count down to 0
}
void print_difficulty_menu(Game_settings *game_state){//Function for Difficulty menu
    printf("Select difficulty level\n");//Display difficult level user can choose from
    printf("1.Easy\n");//Easy
    printf("2.Medium\n");//Medium
    printf("3.Hard\n");//Hard

}
// Function to create the grid
//void - is a return type of a function
//Grid - Function name
//Game_settings *game_state - Formal argument
//Game setting -structure name ,gamestate - pointer
void Grid(Game_settings *game_state) {
    //int i = 0 — initializes the loop counter i to 0.
    //i <= Row — continues looping as long as i is less than or equal to Row (18).
    //i++ — increments i by 1 after each loop iteration.
    for (int i = 0; i <= Row; i++) { //Lopping through the row for the grid
        for (int j = 0; j <= Column; j++) { //Lopping through the colon for the grid
            if (i == 0 || i == Row|| j == 0 || j == Column) {//if i is 0 or i is equal to amount of row(18)or j is 0 or j is equal to amount of colon(18)
                game_state->grid[i][j] = 'x';//initialise grid array [i][j] to x
            } else {//if not
                game_state->grid[i][j] = ' ';//initialising grid array [i][j] to space
            }
        }
    }
}
// Function to create the grid
//void - is a return type of a function
//possitionOccupied- Function name
//Game_settings *game_state - Formal argument
//Game setting -structure name ,gamestate - pointer
//integer x,y
//An int function in C is a function that returns an integer
int possitionOccupied(Game_settings *game_state,int x,int y){//Function to check that no garbages are placed in the same position
    if(game_state->grid[x][y]!=' ' && game_state->grid[x][y]!='x'){//check if theres a garbage there
        return 1;//if yes return 1
    }
    return 0;//if no return 0
}
// Function to place garbages in the grid using structure
// Function to create the grid
//void - is a return type of a function
// placeGarbage- Function name
//Game_settings *game_state Garbage *garbages- Formal argument
//Game setting -structure name ,gamestate - pointer
//same for garbage garbages
void placeGarbage(Game_settings *game_state, Garbage *garbages) {
//-> is to get the structure field max garbage of pointer game_state
    for (int i = 0; i < game_state->max_garbage; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r=rand() % (Row-1)+1; //Getting random position on the row in the grid
            c=rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(game_state,r,c)); //
        //Dot operator is used to access the structure variable in the garbage array
        garbages[i].x = r;//initialising the random row position to the x position of the garbage
        garbages[i].y = c;//initialising the random column position to the x position of the garbage
        garbages[i].letters = 'A' + (rand() % 26);//initialising the getting random letters to the letters in the garbage struct
        game_state->grid[r][c] = garbages[i].letters;//initialising grid array position [r][c] to the random letters

    }
}

// Function to place asteroid in the grid using structure
// Function to create the grid
//void - is a return type of a function
// placeAsteroid- Function name
//Game_settings *game_state,e,  Asteroid *asteroid - Formal argument
//Game setting -structure name ,gamestate - pointer
//same for Asteroid asteroid
void placeAsteroid(Game_settings *game_state,  Asteroid *asteroid) {
    for (int i = 0; i < game_state->max_asteroid; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r= rand() % (Row-1)+1; //Getting random position on the row in the grid
            c= rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(game_state,r,c));
        //Dot operator is used to access the structure variable in the asteroid array
        asteroid[i].x = r;//initialising the random row position to the x position of the asteroid
        asteroid[i].y = c;//initialising the random column position to the x position of the asteroid
        asteroid[i].asterisk = '*';//initialising * to the asteroid
        //-> is to get the structure field grid of pointer game_state
        game_state->grid[r][c] = asteroid[i].asterisk;//initialising grid array position [r][c] to the asterisk
    }
}
// Function to place spaceship in the grid using structure
// Function to create the grid
//void - is a return type of a function
// placeSpaceship- Function name
//Game_settings *game_state, Spaceship *spaceship - Formal argument to access grid
//Game setting -structure name ,gamestate - pointer
//same for Spaceship spaceship
void placeSpaceship(Game_settings *game_state, Spaceship *spaceship) {
    for (int i = 0; i < 1; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r=rand() % (Row-1)+1; //Getting random position on the row in the grid
            c=rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(game_state,r,c));
        //Dot operator is used to access the structure variable in the spaceship array
        spaceship[i].x = r;//initialising the random row position to the x position of the spaceship
        spaceship[i].y = c;//initialising the random column position to the x position of the spaceship
        spaceship[i].caret = '^';//initialising ^ to the spaceship
        //-> is to get the structure field grid of pointer game_state
        game_state->grid[r][c] = spaceship[i].caret;//initialising grid array position [r][c] to the spaceship
    }
}
// Function to print the grid
// Function to  printGrid in the grid using structure
// Function to create the grid
//void - is a return type of a function
//  printGrid- Function name
//Game_settings *game_state - Formal argument to access grid
//Game setting -structure name ,gamestate - pointer

void printGrid(Game_settings *game_state) {
    for (int i = 0; i <= Row; i++) {//looping through the row
        for (int j = 0; j <= Column; j++) {//looping through the colon
            //-> is to get the structure field grid of pointer game_state
            printf(" %c ", game_state->grid[i][j]);//Printing the grid with the garbage included
        }
        printf("\n"); //Printing the space
    }
    printf("Score:%d\n",game_state->score);//Show thr score the spaceship has attained after getting a garbage
    printf("Fuel:%d\n",game_state->fuel);//Show fuel of the spaceship at it is played
    printf("Time left:%d\n",game_state->time_left);//Show the time left as it is played
    printf("Lives: %d\n", game_state->life);//Show the life of the spaceship as it is played
    if(game_state->score>=game_state->max_garbage){//if the score is greater than the maximum garbage
        printf("You cleaned the space,you win!\n");//Tell the user they have cleaned the space and have won
        exit(0);//Then leave the game
    }
}
// Function spaceship_fuel
//void - is a return type of a function
// Spaceship_fuel- Function name
//Game_settings *game_state - Formal argument to access grid
//Game setting -structure name ,gamestate - pointer
void Spaceship_fuel(Game_settings *game_state){//Function to control the amount of fuel the pace ship uses at every movement
    game_state->fuel -= game_state->fuel_reduction_per_movement;//Fuel uses by 2 at each motion
    //-> is to get the structure field fuel and fuel per movement of pointer game_state
    if(game_state->fuel<=0){//if the fuel is less or equal to 0
        printf("Out of fuel!,Game over \n");//Tell the user there out of fuel and the game is over
        exit(0);// Then exit the code
    }
}

// Function moveSpaceship
//void - is a return type of a function
// Spaceship_fuel- Function name
//Game_settings *game_state , Spaceship *spaceship, int arrow_key- Formal argument
//Game setting -structure name ,gamestate - pointer
//same as Spaceship spaceship
void moveSpaceship(Game_settings *game_state, Spaceship *spaceship, int arrow_key) {
    Spaceship_fuel(game_state);
    //-> is to get the  field x and y  of structure pointer spaceship
    int X = spaceship->x; //initialising new x to the old spaceship x coordinate
    int Y = spaceship->y;//initialising new y to the old spaceship y coordinate
    if (arrow_key == 'W' && spaceship->x > 1) { // using W character to
        X--;//Move up
    } else if (arrow_key == 'A' && spaceship->y > 1) { // using S character to
        Y--;//Move left
    } else if (arrow_key == 'S' && spaceship->x < Row - 1) { // using A character to
        X++;//Move down
    } else if (arrow_key == 'D' && spaceship->y < Column - 1) { // using D character to
        Y++;
    }
    //-> is to get the  field grid of  structure pointer spaceship
    if (game_state->grid[X][Y] >= 'A' && game_state->grid[X][Y] <= 'Z') {//if there's no empty space and no border is hit
        printf("You collected garbage: %c!\n",game_state->grid[X][Y]);//Tell the user the garbage that has been collected with in the space og the spaceship
        game_state->score++;//Add to score


        int one_option = 0;
        printf("\n Recycle option:\n");//Recycle options
        printf("Input T to top-up time (+10)\n");//if T is inputted by the user it means the user wants to top up on the time
        printf("Input L to top-up life(+1)\n");//if L is inputted by the user it means the user wants to top up on the life
        printf("Input F to top-up fuel(+10)\n");//if F is inputted by the user it means the user wants to top up on the fuel
        printf("Choose a recycling option:\n");//Tell the user tho choose an option
        while (one_option == 0) {//while one option is still 0 or is equal to zero
            char recycle = getch();//get the character inputted by the user for the recycling process
            //printf("\n %c",recycle);
            if (kbhit()) {//If any key Pressed on the keyboard
                if (recycle == 'T') {//if key pressed is T
                    game_state->time_left =game_state->time_left + 10;//increase the time left by 10
                    printf("Time increased,current time left %d \n:",
                           game_state->time_left);//Tell the user the new time after the increase
                    one_option = 1;//cut loop as one option is now one
                } else if (recycle == 'L') {//if key pressed is L
                    if (game_state->life < 3) {//and the Life is less than 3
                        game_state->life = game_state->life + 1;//increase the life by 1
                        printf("Life repaired,current life is %d \n:",game_state->life);//Tell the user the life has been increased
                        one_option = 1;//cut loop as one option is now one
                    } else {//if not
                        printf("Life is already full\n");//Tell the user the life is already full and has to choose another option
                    }
                } else if (recycle == 'F') {//if the key pressed is F
                    if (game_state->fuel < 100) { //check if fuel is less than 100
                        game_state->fuel = game_state->fuel + 10;//if yess add 10
                        printf(" Fuel topped up ,current fuel is %d \n:", game_state->fuel);//and tell the user the fuel
                        one_option = 1;//Cut the loop as one option = 1
                    }
                }
                break;
            }

            else {
                printf("Invalid recycle option\n");}//if its not L,T,F tell user
        }

    }
    else{//if not
        printf("No garbage collected\n");//Display No garbage collected
    }
    //-> is to get the  field grid of  structure pointer spaceship
    game_state->grid[spaceship->x][spaceship->y] = ' '; // Clearing the spaceship old position so it csn move to the new position after being moved
    spaceship->x = X;//updating the spaceship position on x-axis to X after being moved
    spaceship->y = Y;//updating the position to y after being moved

    game_state->grid[spaceship->x][spaceship->y] = spaceship->caret;// Placing spaceship at new position


}
// Function moveAsteroid
//void - is a return type of a function
// moveAsteroid- Function name
//Game_settings *game_state , Spaceship *spaceship, Asteroid *asteroid, int arrow_key- Formal argument
//Game setting -structure name ,gamestate - pointer
//same as Spaceship spaceship and Asteroid *asteroid
void moveAsteroid(Game_settings *game_state, Asteroid *asteroid,Spaceship *spaceship) {//remove spaceship
    int direction = rand ()% 4;//Declaring and Initialising rand to direction
    int X = asteroid->x; //initialising new x to the old ASTEROID x coordinate
    int Y = asteroid->y; //initialising new y to the old ASTEROID  y coordinate

    if(direction==0 && asteroid->x>1 ){//if the random position to go is up
        X--;//go up
    }
    else if(direction==2 && asteroid->y > 1 ){//if the random position to go is down
        Y--;//go down
    }
    else if(direction==1 && asteroid->x<Row-1 ){//if the random position to go is left
        X++;//go left
    }

    else if(direction==3 && X< Column-1 ){//if the random position to go is right
        Y++;//go right
    }
    //-> is to get the  field grid of  structure pointer spaceship
    if (game_state->grid[X][Y]=='x'){//if the spaces hits the border
        X = asteroid->x;//return to its old position
        Y= asteroid->y;//return to its old position
    }
    //-> is to get the  field grid of  structure pointer spaceship
    game_state->grid[asteroid->x][asteroid->y] = ' '; // Clearing the asteroid old position so it csn move to the new position after being moved
    asteroid->x=X;//initialising old asteroid position to new
    asteroid->y=Y;
    game_state->grid[X][Y] = '*';// Placing asteroid at new position
    //checking for collision
    for (int i = 0; i < game_state->max_asteroid; i++) {//each one of the asteroid
        if (spaceship->x == asteroid[i].x && spaceship->y == asteroid[i].y) {//if the spaceship and asteroid are at the same position
            game_state->life = game_state->life - 1;//life decreases by 1
            printf("You hit an asteroid! Lives left: %d\n", game_state->life);//Then display to the player
            if (game_state->life <= 0) {//if life is done
                printf("Game Over: You ran out of lives!\n");//tell the user the game is over as life is finished
                exit(0);//leave
            }
        }
    }
}

/*void collision(Game_settings *game_state, Spaceship *spaceship, Asteroid asteroid[]) {
    for (int i = 0; i < game_state->max_asteroid; i++) {
        //printf("Checking collision for asteroid %d", i+1);
        if (spaceship->x == asteroid[i].x && spaceship->y == asteroid[i].y) {
            game_state->life = game_state->life - 1;
            printf("You hit an asteroid! Lives left: %d\n", game_state->life);
            if (game_state->life <= 0) {
                printf("Game Over: You ran out of lives!\n");
                exit(0);
            }
        }
    }
}*/
// Function Timer
//void - is a return type of a function
// Timer- Function name
//Game_settings *game_state- Formal argument
//Game setting -structure name ,gamestate - pointer
void Timer(Game_settings *game_state) {
    time_t time_start = time(NULL);
    game_state->time_left = time(NULL) - time_start;
    if (game_state->time_left >= game_state->game_time) {
        printf("Game over! Time's up!\n");
        exit(0);
    }
}
// Function game over
//void - is a return type of a function
// game over- Function name
//Game_settings *game_state- Formal argument
//Game setting -structure name ,gamestate - pointer
void game_over(Game_settings *game_state) {
    if (game_state->fuel <= 0 || game_state->life <= 0) {//if the fuel or life is done
        printf("Game Over: You ran out of fuel or life!\n");//Tell the user the game over
    } else if (game_state->score >= game_state->max_garbage) {//if score is the same as max garbage
        printf("You win!,you got all the garbage!\n");//Tell the user they win and exit the game
        exit(0);
    }
}
