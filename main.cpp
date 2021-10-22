#include <SDL.h>
#include<iostream>
#include "GameEngine.h"
#include "SpaceShooterGame.h"

int main(int argc, char** args)
{
    GameEngine* gameEngine = new GameEngine(new SpaceShooterGame());

    gameEngine->Initialize();

    gameEngine->GameLoop();

    delete gameEngine;

    return 0;
}