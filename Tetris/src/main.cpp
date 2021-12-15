#include <iostream>
#include <fstream>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "TetrisBlock.h"
#include "GameManager.h"

int main()
{
    int numOfHorizontalBlock = 20;
    int numOfVerticalBlock = 35;

    nsTetris::GameManager gm(numOfHorizontalBlock, numOfVerticalBlock, "Tetris");
    gm.startGame();

    return 0;
}