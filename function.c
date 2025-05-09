
#include "Header.h"


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
            game_state->max_asteroid=Easy_max_asteroid;
            game_state->game_time=180;//game time = 180
            game_state->fuel_reduction_per_movement=Easy_fuel_reduction ;//fuel reduction per movement = 2

            break;//break
        case Medium://if Medium
            game_state->max_garbage= Medium_max_Garbage;//max garbage= 8
            game_state->max_asteroid=Medium_max_asteroid;
            game_state->game_time=120 ;//game time = 120
            game_state->fuel_reduction_per_movement=Medium_fuel_reduction;//fuel reduction per movement = 4
            break;//break
        case Hard://if hard
            game_state->max_garbage=Hard_max_Garbage;//max garbage= 10
            game_state->max_asteroid=Hard_max_asteroid;
            game_state->game_time= 60;//game time = 60
            game_state->fuel_reduction_per_movement=Hard_fuel_reduction;//fuel reduction per movement
            int X = (*spaceship).x;
            int Y= spaceship->y;
            if (game_state->grid[X][Y] == '*') { //If an asteroid is hit
                game_state->life = Hard_life;
                game_state->life = game_state->life - 1;//Reduce life by 1 - 1 total for hard**********

                if(game_state->life<=0){
                    printf("You hit an asteroid and ran out of life!\n");//Display "You hit an asteroid and ran out of life!"
                    exit(0);//Exit the game
                }
            }

            break;
        default:
            Difficulty(game_state,Medium,spaceship);
            break;
    }

    game_state->time_left = game_state->game_time;
}
void print_difficulty_menu(Game_settings *game_state){//Function for Difficulty menu
    printf("Select difficulty level\n");//Display difficult level user can choose from
    printf("1.Easy\n");
    printf("2.Medium\n");
    printf("3.Hard\n");

}

void Grid(Game_settings *game_state) {// Function to create the grid}
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
//Return type function while void is a non-return type function
int possitionOccupied(Game_settings *game_state,int x,int y){//Function to check that no garbages are placed in the same position
    if(game_state->grid[x][y]!=' ' && game_state->grid[x][y]!='x'){//check if theres a garbage there
        return 1;//if yes return 1
    }
    return 0;//if no return 0
}
// Function to place garbages in the grid using structure
void placeGarbage(Game_settings *game_state, Garbage *garbages) {

    for (int i = 0; i < game_state->max_garbage; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r=rand() % (Row-1)+1; //Getting random position on the row in the grid
            c=rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(game_state,r,c)); //
        garbages[i].x = r;//initialising the random row position to the x position of the garbage
        garbages[i].y = c;//initialising the random column position to the x position of the garbage
        garbages[i].letters = 'A' + (rand() % 26);//initialising the getting random letters to the letters in the garbage struct
        game_state->grid[r][c] = garbages[i].letters;//initialising grid array position [r][c] to the random letters

    }
}

// Function to place asteroid in the grid using structure
//char grid[19][19]: a 2D array representing the game grid. Each cell can hold a character representing empty space, walls ('x'), garbage, spaceship ('^'), or asteroid ('*').
//Asteroid *asteroid: a pointer to an array of Asteroid structures where each asteroid’s position (x, y) and symbol (*) are stored.
void placeAsteroid(Game_settings *game_state,  Asteroid *asteroid) {
    for (int i = 0; i < game_state->max_asteroid; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r= rand() % (Row-1)+1; //Getting random position on the row in the grid
            c= rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(game_state,r,c));
        asteroid[i].x = r;//initialising the random row position to the x position of the asteroid
        asteroid[i].y = c;//initialising the random column position to the x position of the asteroid
        asteroid[i].asterisk = '*';//initialising * to the asteroid
        game_state->grid[r][c] = asteroid[i].asterisk;//initialising grid array position [r][c] to the asterisk
    }
}
// Function to place spaceship in the grid using structure
void placeSpaceship(Game_settings *game_state, Spaceship *spaceship) {
    for (int i = 0; i < 1; i++) { //looping through to place the garbages with a max value of 5
        int r ,c;
        do{
            r=rand() % (Row-1)+1; //Getting random position on the row in the grid
            c=rand() % (Column-1)+1; //Getting random position on the column in the grid

        } while (possitionOccupied(game_state,r,c));
        spaceship[i].x = r;//initialising the random row position to the x position of the spaceship
        spaceship[i].y = c;//initialising the random column position to the x position of the spaceship
        spaceship[i].caret = '^';//initialising ^ to the spaceship
        game_state->grid[r][c] = spaceship[i].caret;//initialising grid array position [r][c] to the spaceship
    }
}
// Function to print the grid
void printGrid(Game_settings *game_state) {
    for (int i = 0; i <= Row; i++) {//looping through the row
        for (int j = 0; j <= Column; j++) {//looping through the colon
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

void Spaceship_fuel(Game_settings *game_state){//Function to control the amount of fuel the pace ship uses at every movement
    game_state->fuel -= game_state->fuel_reduction_per_movement;//Fuel uses by 2 at each motion
    if(game_state->fuel<=0){//if the fuel is less or equal to 0
        printf("Out of fuel!,Game over \n");//Tell the user there out of fuel and the game is over
        exit(0);// Then exit the code
    }
}

// Move spaceship
//char grid[19][19]: a 2D array representing the game grid. Each cell can hold a character representing empty space, walls ('x'), garbage, spaceship ('^'), or asteroid ('*').
//Spaceship *spaceship: a pointer to a Spaceship structures where each spaceship’s position (x, y) and symbol (^) are stored.
void moveSpaceship(Game_settings *game_state, Spaceship *spaceship, int arrow_key) {
    Spaceship_fuel(game_state);
    int X = spaceship->x; //initialising new x to the old spaceship x coordinate
    int Y = spaceship->y;//initialising new y to the old spaceship y coordinate
    printf("4\n");
    if (arrow_key == 'W' && spaceship->x > 1) { // using W character to
        X--;//Move up
    } else if (arrow_key == 'A' && spaceship->y > 1) { // using S character to
        Y--;//Move left
    } else if (arrow_key == 'S' && spaceship->x < Row - 1) { // using A character to
        X++;//Move down
    } else if (arrow_key == 'D' && spaceship->y < Column - 1) { // using D character to
        Y++;
    }

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
                } else if (recycle == 'F') {
                    if (game_state->fuel < 100) {
                        game_state->fuel = game_state->fuel + 10;
                        printf(" Fuel topped up ,current fuel is %d \n:", game_state->fuel);
                        one_option = 1;
                    }
                }
            }

            else {
                printf("Invalid recycle option\n");}
        }

    }
    else{//if not
        printf("No garbage collected\n");//Display No garbage collected
    }

    game_state->grid[spaceship->x][spaceship->y] = ' '; // Clearing the spaceship old position so it csn move to the new position after being moved
    spaceship->x = X;//updating the spaceship position on x-axis to X after being moved
    spaceship->y = Y;//updating the position to y after being moved

    game_state->grid[spaceship->x][spaceship->y] = spaceship->caret;// Placing spaceship at new position

}

void moveAsteroid(Game_settings *game_state, Asteroid *asteroid) {//remove spaceship
    int direction = rand ()% 4;
    int X = asteroid->x; //initialising new x to the old ASTEROID!!!!!!!!!! coordinate
    int Y = asteroid->y;//initialising new x to the old spaceship coordinate

    if(direction==0 && asteroid->x>1 ){
        X--;
    }
    else if(direction==1 && asteroid->x<Row-1 ){
        X++;
    }
    else if(direction==2 && asteroid->y > 1 ){
        Y--;
    }
    else if(direction==3 && X< Column-1 ){
        Y++;
    }
    if (game_state->grid[X][Y]=='x'){
        X = asteroid->x;
        Y= asteroid->y;
    }
    game_state->grid[asteroid->x][asteroid->y] = ' '; // Clearing the spaceship old position so it csn move to the new position after being moved
    asteroid->x=X;
    asteroid->y=Y;
    game_state->grid[X][Y] = '*';// Placing spaceship at new position
}

void collision(Game_settings *game_state, Spaceship *spaceship, Asteroid asteroid[]) {
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
}
void Timer(Game_settings *game_state) {
    time_t time_start = time(NULL);
    game_state->time_left = time(NULL) - time_start;
    if (game_state->time_left >= game_state->game_time) {
        printf("Game over! Time's up!\n");
        exit(0);
    }
}
void game_over(Game_settings *game_state) {
    if (game_state->fuel <= 0 || game_state->life <= 0) {
        printf("Game Over: You ran out of fuel!\n");
    } else if (game_state->score >= game_state->max_garbage) {
        printf("You win!,you got all the garbage!\n");
        exit(0);
    }
}
