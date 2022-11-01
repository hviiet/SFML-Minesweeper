#ifndef GAMEA_H // minesweeper
#define GAMEA_H // minesweeper

#include "SFML/Graphics.hpp"
#include "core.h"
#include "graphic.h"
#include <iostream>

using namespace std;
using namespace sf;

class GameA
{
public:          // initial function and main loop
    GameA();     // initial function
    void loop(); // main loop of the game

private:                  // function
    void render();        // render playing field
    void update();        // update
    void handle_Events(); // handle mouse clicking event

private:
    Core core;
    Graphic graphic;
};

#endif // GAMEA_H
