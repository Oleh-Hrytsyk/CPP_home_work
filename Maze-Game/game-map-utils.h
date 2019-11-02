#ifndef GAME_MAP_UTILS_H
#define GAME_MAP_UTILS_H

#include <array>
#include "game-defs.h"

void drawMaze(const std::array<std::array<char, mazeColumns>, mazeRows> &maze);
bool scanForChar(const std::array<std::array<char, mazeColumns>, mazeRows> &maze, const char charToFind,
                 int &prCharRow, int &prCharColumn);
void placeCharRandomly(std::array<std::array<char, mazeColumns>, mazeRows> &rMaze,
                       char charToPlace,int charCount);

#endif // GAME_MAP_UTILS_H