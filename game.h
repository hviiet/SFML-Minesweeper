#ifndef GAME_H // minesweeper
#define GAME_H // minesweeper

#include "SFML/Graphics.hpp"
#include <time.h>
#include <math.h>
#include <iostream>

using namespace std;
using namespace sf;

class Game
{
public:          // initial function and main loop
    Game();      // generate
    void loop(); // main loop of the game

private:                       // function
    void render();             // render playing field
    void update();             // update
    void handle_Events();      // handle mouse clicking event
    void get_Mouse_Position(); // to get mouse position

private:                           // support function
    void load_Assets();            // load the needed image
    void choose_Difficulty();      // choose easy-medium-hard difficulty
    void set_Difficulty(int diff); // set the difficulty
    void create_Grid();            // create the grid with the difficulty
    void check(int x, int y);      // used for tracker()
    void tracker(int x, int y);    // to track all the number when click a blank square
    void reset_Grid();             // reset the saving and showing grid
    bool check_If_Winning();       // check if player is winning or not
    bool check_If_Losing();        // check if player is losing or not

private: // window
    RenderWindow app;

private: // asset
    Texture t1, t2, t3, t4, t5, t6, t7;
    Sprite background, asset, button, difficulty_button, select_button, winning, losing;
    const int Window_Size_X = 1900;
    const int Window_Size_Y = 900;

private: // mouse position
    Vector2i pos;
    int x, y;

private: // saving and showing array
    int base_Grid[33][19];
    int show_Grid[33][19];

private: // difficulty adjust
    int diff_size_x;
    int diff_size_y;
    int diff_mines;
    int diff_pixel;
    int diff_pos_x;
    int diff_pos_y;
    int remeaning;
};

#endif // GAME_H
