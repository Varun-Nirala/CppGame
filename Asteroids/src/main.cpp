#include <iostream>
#include <fstream>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "BattleShip.h"
#include "GameManager.h"

int main()
{
    AsteroidNS::GameManager gm(600, 800);
    gm.startGame();

    return 0;
}