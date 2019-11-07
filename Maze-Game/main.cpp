#include <iostream>
#include <string>

#include "game-defs.h"
#include "game-map-utils.h"
#include "random-utils.h"

bool keyCheck = false;

// Checks if user want so play
// Return true if user wants to play; false otherwise
bool doesUserWantsToPlay()
{
    bool rResult = false;
    std::cout << "Maze Game" << std::endl;

    while (true)
    {
        std::cout << "Do you want to play? (1 - yes, 0 - no):";

        std::string answer;
        std::cin >> answer;

        if ((answer == "1") || (answer == "0"))
        {
            rResult = (answer == "1");
            break;
        }

        std::cout << "Sorry, I did not understand." << std::endl;
    }

    return rResult;
}


// Generates maze
// Parameters:
//       maze - reference to maze field that will be modified
//              (walls added, added character and exit)
void generateMaze(std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    for (int row = 0; row < mazeRows; row++)
    {
        for (int column = 0; column < mazeColumns; column++)
        {
            if ((row%2 == 0) || (column%2 == 0))
            {
                prMaze[row][column] = wallSymbol;
            }
            else 
            {
                prMaze[row][column] = emptySymbol;
				
            }
        }
    }

	for (int row = 1; row < mazeRows; row+=2)
	{
		for (int column = 1; column < mazeColumns; column+=2)
		{
			int rand = generateRandomNumber(0, 2);
				if (rand == 1) {
					if(column + 1 != mazeColumns - 1)
					prMaze[row][column + 1] = emptySymbol;
				else if (row + 1 != mazeRows - 1 && column + 1 == mazeColumns - 1)
					prMaze[row + 1][column] = emptySymbol;
				}
				
				if (rand == 0)
				{
					if(row + 1 != mazeRows - 1)
						prMaze[row + 1][column] = emptySymbol;
					else if (row + 1 == mazeRows - 1 && column + 1 != mazeColumns -1)
						prMaze[row][column + 1] = emptySymbol;
				}

				if (rand == 2 && row + 1 != mazeRows - 1 && column + 1 != mazeColumns - 1)
				{	
					prMaze[row + 1][column] = emptySymbol;
					prMaze[row][column + 1] = emptySymbol;
				}
				else if (row + 1 == mazeRows - 1 && column + 1 != mazeColumns - 1)
					prMaze[row][column + 1] = emptySymbol;
				else if (row + 1 != mazeRows - 1 && column + 1 == mazeColumns - 1)
					prMaze[row + 1][column] = emptySymbol;
				
		}
	}



    // Place character
        do{
          int col=generateRandomNumber(1, mazeColumns-2);
          int rows=generateRandomNumber(1, mazeRows-2);
          if((col%2==1) && (rows%2==1)){
              if(prMaze[rows + 1][col] == wallSymbol && prMaze[rows - 1][col]== wallSymbol && prMaze[rows][col+1]== wallSymbol){
                prMaze[rows][col] = exitSymbol;
            break;
          }
          else if(prMaze[rows + 1][col] == wallSymbol && prMaze[rows - 1][col]== wallSymbol && prMaze[rows][col-1]== wallSymbol){
              prMaze[rows][col] = exitSymbol;
            break;
        }
        else if(prMaze[rows + 1][col] == wallSymbol && prMaze[col + 1][col]== wallSymbol && prMaze[rows][col-1]== wallSymbol){
            prMaze[rows][col] = exitSymbol;
            break;
      }
        else if(prMaze[rows - 1][col] == wallSymbol && prMaze[col + 1][col]== wallSymbol && prMaze[rows][col-1]== wallSymbol){
             prMaze[rows][col] = exitSymbol;
             break;
          }
             else{
                continue;
             }
        }

     }
        while (true);
    placeCharRandomly(prMaze, characterSymbol, 1);
    placeCharRandomly(prMaze, keySymbol, 1);
}

// Moves character according to given command and retuns eaten symbol (if any)
// Parameters:
//      row - character row position
//      column - character column position
//      command - test string with given command ("l" - left, "r" - right, "u" - up, "d" - down)
//      prMaze - reference to maze field; will be modified as a result of command execution
char moveAndGather(int row,
                   int column,
                   char command,
                   std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    char rCharMovedOnto = emptySymbol;

    // Take character out from map
    prMaze[row][column] = emptySymbol;

    if (command == 'l')
    {
        rCharMovedOnto = prMaze[row][column - 1];
        if (rCharMovedOnto != wallSymbol && rCharMovedOnto != exitSymbol)
        {
            column--;
        }
    }

    if (command == 'r')
    {
        rCharMovedOnto = prMaze[row][column + 1];

        if (rCharMovedOnto != wallSymbol && rCharMovedOnto != exitSymbol)
        {
            column++;
        }
    }

    if (command == 'u')
    {
        rCharMovedOnto = prMaze[row - 1][column];

        if (rCharMovedOnto != wallSymbol && rCharMovedOnto != exitSymbol)
        {
            row--;
        }
    }

    if (command == 'd')
    {
        rCharMovedOnto = prMaze[row + 1][column];

        if (rCharMovedOnto != wallSymbol && rCharMovedOnto != exitSymbol)
        {
            row++;
        }
    }

    // Place character back with new position
    prMaze[row][column] = characterSymbol;

    return rCharMovedOnto;
}

// Prints message to player.
// Parameters:
//      message - text message to player
void gameMessage(const std::string& message)
{
    std::cout << std::endl << message << std::endl << std::endl;
}

// Moves character and check if exit was found as a result of that move.
// Parameters:
//      prMaze - reference to maze field; will be modified while player moves.
bool moveCharacterAndCheckIfExitFound(std::array<std::array<char, mazeColumns>, mazeRows> &prMaze)
{
    bool rExitFound = false;

    int charRow = 1;
    int charColumn = 1;
    if (scanForChar(prMaze, characterSymbol, charRow, charColumn))
    {
        std::cout << "Command (l - left, r - right, u - up, d- down):";
        char command;
        std::cin >> command;

        const char charMovedOnto = moveAndGather(charRow, charColumn, command, prMaze);

        if (charMovedOnto == wallSymbol)
        {
            gameMessage("Cannot move here!");
        }

		if (charMovedOnto == keySymbol)
		{
			gameMessage("You found a key!");
			keyCheck = true;
		}
		if (charMovedOnto == exitSymbol && keyCheck == false)
		{
			gameMessage("You need a key!");
		}

        if (charMovedOnto == exitSymbol && keyCheck == true)
        {
            gameMessage("Exit found!");
            rExitFound = true;
        }
    }
    else
    {
        gameMessage("Error: cannot find char!");
    }

    return rExitFound;
}

// Executes one round of the game
void playMazeGame()
{
    std::cout << "LETS START!" << std::endl;

    std::array<std::array<char, mazeColumns>, mazeRows> maze;
    generateMaze(maze);

    do
    {
        drawMaze(maze);
    }
    while (!moveCharacterAndCheckIfExitFound(maze));
}

int main()
{
    while (doesUserWantsToPlay())
    {
        playMazeGame();
    }
}
