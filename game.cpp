#include "game.h"
Game::Game()
{
    core.init();
}
void Game::loop()
{
    while (core.app.isOpen())
    {
        core.get_Mouse_Position();
        handle_Events();
        update();
        render();
    }
}
void Game::render()
{
    graphic.clear_Render(core.app, Color::Black);
    graphic.draw_Render(core.app, core.background, 0, 0, 1900, 900, 0, 0);

    for (int i = 1; i <= core.diff_size_x; i++)
        for (int j = 1; j <= core.diff_size_y; j++)
        {
            int texture_x = core.show_Grid[i][j] * core.diff_pixel;
            int texture_y = 0;
            int position_x = core.diff_pos_x + i * core.diff_pixel;
            int position_y = core.diff_pos_y + j * core.diff_pixel;
            graphic.draw_Render(core.app, core.asset, texture_x, texture_y, core.diff_pixel, core.diff_pixel, position_x, position_y);
        }
    graphic.draw_Render(core.app, core.playing_win_lose, 0, 0, 340, 225, 1555, 200);
    if (core.check_If_Winning())
    {
        graphic.draw_Render(core.app, core.playing_win_lose, 0, 225, 340, 225, 1555, 200);
    }
    else if (core.check_If_Losing())
    {
        graphic.draw_Render(core.app, core.playing_win_lose, 0, 450, 340, 225, 1555, 200);
    }

    graphic.draw_Render(core.app, core.restart_back, 0, 0, 310, 129 / 2, 1570, 600);

    graphic.draw_Render(core.app, core.restart_back, 0, 129 / 2, 310, 129 / 2, 1570, 470);

    graphic.display_Render(core.app);
}
void Game::update()
{
    if (which_Update == 1) // restart game
    {
        core.create_Grid();
        which_Update = 0;
    }
    else if (which_Update == 2) // back to menu
    {
        core.choose_Difficulty();
        core.create_Grid();
        which_Update = 0;
    }
    else if (which_Update == 3) // click on blank element
    {
        core.show_Grid[core.x][core.y] = core.base_Grid[core.x][core.y];
        if (core.show_Grid[core.x][core.y] == 0)
            core.tracker(core.x, core.y);
        which_Update = 0;
    }
    else if (which_Update == 4) // set flag
    {
        if (core.show_Grid[core.x][core.y] == 11)
            core.show_Grid[core.x][core.y] = 10;
        else if (core.show_Grid[core.x][core.y] == 10)
            core.show_Grid[core.x][core.y] = 11;
        which_Update = 0;
    }
    for (int i = 1; i <= core.diff_size_x; i++)
        for (int j = 1; j <= core.diff_size_y; j++)
        {
            if (core.show_Grid[core.x][core.y] == 9)
                core.show_Grid[i][j] = core.base_Grid[i][j];
        }
}
void Game::handle_Events()
{
    Event e;
    while (core.app.pollEvent(e))
    {
        if (e.type == Event::Closed)
            core.app.close();
        if (e.type == Event::MouseButtonPressed)
            if (e.mouseButton.button == Mouse::Left)
            {
                if (core.pos.x > 1570 && core.pos.x < 1570 + 310 && core.pos.y > 470 && core.pos.y < 470 + 129 / 2)
                {
                    which_Update = 1;
                }
                else if (core.pos.x > 1570 && core.pos.x < 1570 + 310 && core.pos.y > 600 && core.pos.y < 600 + 129 / 2)
                {
                    which_Update = 2;
                }
                else if (core.pos.x > (core.diff_pixel + core.diff_pos_x) &&
                         core.pos.x < (core.diff_pixel * (core.diff_size_x + 1) + core.diff_pos_x) &&
                         core.pos.y > (core.diff_pixel + core.diff_pos_y) &&
                         core.pos.y < (core.diff_pixel * (core.diff_size_y + 1) + core.diff_pos_y))
                {
                    if (core.show_Grid[core.x][core.y] == 10)
                    {
                        which_Update = 3;
                    }
                }
            }
            else if (e.mouseButton.button == Mouse::Right)
            {
                if (core.pos.x > (core.diff_pixel + core.diff_pos_x) &&
                    core.pos.x < (core.diff_pixel * (core.diff_size_x + 1) + core.diff_pos_x) &&
                    core.pos.y > (core.diff_pixel + core.diff_pos_y) &&
                    core.pos.y < (core.diff_pixel * (core.diff_size_y + 1) + core.diff_pos_y))
                {
                    which_Update = 4;
                }
            }
    }
}