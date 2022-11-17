#ifndef GAME_H // minesweeper
#define GAME_H // minesweeper

#include "SFML/Graphics.hpp"
#include "core.h"
#include "graphic.h"
#include <iostream>

using namespace std;
using namespace sf;

class Game
{
public:          // initial function and main loop
    Game();      // initial function
    void loop(); // main loop of the game

private:                  // function
    void render();        // render playing field
    void update();        // update
    void handle_Events(); // handle mouse clicking event

private:
    int which_Update = 0;
    Core core;
    Graphic graphic;
};

#endif // GAME_H
