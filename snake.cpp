/************************************************************************************************************

Snake Game in c++ - Version 1.0
Created by Mikołaj Kubat
Date: 17/11/2024

Description: This is a simple implementation of the classic Snake game in C++.
The game is played in a console window and the user can control the snake using the 'w',
'a', 's', 'd' keys.
The game ends when the snake collides with the wall or itself.


************************************************************************************************************/

/************************************************************************************************************
 * Library Include Files
************************************************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

/************************************************************************************************************
 * Featire Macro Definitions
************************************************************************************************************/
/* NONE */

/************************************************************************************************************
 * Feature Level Type Definitions
************************************************************************************************************/
/* NONE */

/************************************************************************************************************
 * Feature Level Variables
************************************************************************************************************/
const int width = 80;
const int height = 20;

int x, y; // variables to stare the coordinates in Y and X Axis
int fruitCordX, fruitCordY; // Cordinates of fruit == dot
int PlayerScore; // variable to store the score of the player

int SnakeTail_X[100], SnakeTail_Y[100]; //Arrays to store the coordinates of snakes tail

int SnakeTail_Len; // variable to store the length of snake tail

enum SnakesDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

SnakesDirection SnekDir;

bool IsGameOver;

/************************************************************************************************************
 * Task Local Function Prototypes
************************************************************************************************************/
void Game_Init();
void Game_Render(std::string Player_Name);
void Update_Game();
int Set_Difficulty();
void User_Input();


/************************************************************************************************************
 * 
 * Function Name - Main
 * Descroption - Main Function for program
 * Parameters - None
 * 
************************************************************************************************************/

int main() 
{
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator
    int dfc;
    std::string Player_Name;

    std::cout << "Enter your name: ";
    std::cin >> Player_Name;

    dfc = Set_Difficulty();
    Game_Init();

    while (!IsGameOver) {
        Game_Render(Player_Name);
        User_Input();
        Update_Game();
    }

    return 0;
}

/************************************************************************************************************
 * 
 * Function Name - Game_Init
 * Description - Function to initialize the Game.
 * Parameters - None
 * Return - None
 * 
************************************************************************************************************/

void Game_Init() 
{
    IsGameOver = false;
    SnekDir = STOP;

    x = width / 2;
    y = height / 2;

    fruitCordX = rand() % width;
    fruitCordY = rand() % height;

    PlayerScore = 0;
    SnakeTail_Len = 0; // Initialize the snake's tail length
}


/************************************************************************************************************
 * 
 * Function Name - Game_Render
 * Description - This function will create the game board and rendering
 * Parameters - string Player_Name
 * Return - None
 * 
************************************************************************************************************/

void Game_Render(std::string Player_Name) 
{
    system("cls");

    for (int i = 0; i < width; i++) {
        std::cout << "-";
    }
    std::cout << '\n';

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width) {
                std::cout << '|';
            } else if (j == x && i == y) {
                std::cout << "C"; // Snake head
            } else if (j == fruitCordX && i == fruitCordY) {
                std::cout << "*"; // Fruit
            } else {
                bool Tail = false;
                for (int k = 0; k < SnakeTail_Len; k++) {
                    if (SnakeTail_X[k] == j && SnakeTail_Y[k] == i) {
                        std::cout << "o"; // Snake tail
                        Tail = true;
                    }
                }
                if (!Tail) {
                    std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }

    for (int i = 0; i < width + 2; i++) {
        std::cout << "-";
    }
    std::cout << '\n';

    std::cout << Player_Name << " Score: " << PlayerScore << '\n';
}


/************************************************************************************************************
 * 
 * Function Name - Update_Game
 * Description - This function will update the game state
 * Parameters - None
 * Return - None
 * 
************************************************************************************************************/

void Update_Game() 
{
    int prev_X = SnakeTail_X[0];
    int prev_Y = SnakeTail_Y[0];
    int prev_2X, prev_2Y;

    SnakeTail_X[0] = x;
    SnakeTail_Y[0] = y;

    for (int i = 1; i < SnakeTail_Len; i++) {
        prev_2X = SnakeTail_X[i];
        prev_2Y = SnakeTail_Y[i];
        SnakeTail_X[i] = prev_X;
        SnakeTail_Y[i] = prev_Y;
        prev_X = prev_2X;
        prev_Y = prev_2Y;
    }

    switch (SnekDir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    if (x >= width || x < 0 || y >= height || y < 0) {
        IsGameOver = true;
    }

    for (int i = 0; i < SnakeTail_Len; i++) {
        if (SnakeTail_X[i] == x && SnakeTail_Y[i] == y) {
            IsGameOver = true;
        }
    }

    if (x == fruitCordX && y == fruitCordY) {
        PlayerScore += 1;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        SnakeTail_Len++;
    }
}



/************************************************************************************************************
 * 
 * Function Name - Set_Difficulty
 * Description - This function will set the game difficulty level
 * Parameters - None
 * Return - int difficulty
 * 
************************************************************************************************************/

int Set_Difficulty() 
{
    int dfc, choice;

    std::cout << "Select the difficulty level:" << '\n';
    std::cout << "1. Easy" << '\n';
    std::cout << "2. Medium" << '\n';
    std::cout << "3. Hard" << '\n';
    std::cin >> choice;

    switch (choice) {
        case 1:
            dfc = 50;
            std::cout << "You selected Easy difficulty." << '\n';
            break;
        case 2:
            dfc = 100;
            std::cout << "You selected Medium difficulty." << '\n';
            break;
        case 3:
            dfc = 150;
            std::cout << "You selected Hard difficulty." << '\n';
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Medium difficulty." << '\n';
            dfc = 100; // Default difficulty
            break;
    }

    return dfc;
}


/************************************************************************************************************
 * 
 * Function Name - User_Input
 * Description - This function will handle the user input with switch cases
 * Parameters - None
 * Return - None
 * 
************************************************************************************************************/

void User_Input() 
{
    if (std::cin.peek() != EOF) { // Check if there is input
        char input;
        std::cin >> input; // Read input
        switch (input) {
            case 'a':
                if (SnekDir != RIGHT) SnekDir = LEFT; // Prevent reversing
                break;
            case 'd':
                if (SnekDir != LEFT) SnekDir = RIGHT; // Prevent reversing
                break;
            case 'w':
                if (SnekDir != DOWN) SnekDir = UP; // Prevent reversing
                break;
            case 's':
                if (SnekDir != UP) SnekDir = DOWN; // Prevent reversing
                break;
            case 'p':
                IsGameOver = true;
                break;
        }
    }
}
