#ifndef CORE_H
#define CORE_H

#include "SFML/Graphics.hpp"
#include "graphic.h"
#include <time.h>
#include <math.h>
#include <iostream>

using namespace std;
using namespace sf;

class Core
{
    friend class Game;

private:
    void init();
    void get_Mouse_Position();
    void load_Assets();            // load the needed image
    void choose_Difficulty();      // choose easy-medium-hard difficulty
    void set_Difficulty(int diff); // set the difficulty
    void create_Random_Mines();    // create random mines
    void create_Grid();            // create the grid with the difficulty
    void check(int x, int y);      // used for tracker()
    void tracker(int x, int y);    // to track all the number when click a blank square
    void reset_Grid();             // reset the saving and showing grid
    bool check_If_Winning();       // check if player is winning or not
    bool check_If_Losing();        // check if player is losing or not

private:
    Graphic graphic;

private: // window
    RenderWindow app;
    const int Window_Size_X = 1900;
    const int Window_Size_Y = 900;

private: // mouse position
    Vector2i pos;
    int x, y;

private: // asset
    Texture t_background, t_play_exit, t_difficulty, t_restart_back, t_asset, t_playing_win_lose, t_title;
    Sprite background, play_exit, difficulty, restart_back, asset, playing_win_lose, title;

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
};
#endif // CORE_H