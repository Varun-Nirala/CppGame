#include <iostream>
#include <fstream>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "BattleShip.h"
#include "GameManager.h"

int main()
{
    AsteroidNS::GameManager gm;
    gm.startGame();

    return 0;
}