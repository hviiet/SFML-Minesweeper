#include "gamea.h"
GameA::GameA()
{
    core.init();
}
void GameA::loop()
{
    while (core.app.isOpen())
    {
        core.get_Mouse_Position();
        handle_Events();
        update();
        render();
    }
}
void GameA::render()
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
    if (core.check_If_Winning())
    {
        graphic.draw_Render(core.app, core.winning, 0, 0, 300, 33, 1600, 200);
    }
    else if (core.check_If_Losing())
    {
        graphic.draw_Render(core.app, core.losing, 0, 0, 300, 163, 1600, 200);
    }

    graphic.draw_Render(core.app, core.button, 0, 0, 200, 77, 1600, 470);

    graphic.draw_Render(core.app, core.select_button, 0, 0, 200, 79, 1600, 600);

    graphic.display_Render(core.app);
}
void GameA::update()
{
    for (int i = 1; i <= core.diff_size_x; i++)
        for (int j = 1; j <= core.diff_size_y; j++)
        {
            if (core.show_Grid[core.x][core.y] == 9)
                core.show_Grid[i][j] = core.base_Grid[i][j];
        }
}
void GameA::handle_Events()
{
    Event e;
    while (core.app.pollEvent(e))
    {
        if (e.type == Event::Closed)
            core.app.close();

        if (e.type == Event::MouseButtonPressed)
            if (e.mouseButton.button == Mouse::Left)
            {
                if (core.pos.x > 1600 && core.pos.x < 1600 + 220 && core.pos.y > 470 && core.pos.y < 470 + 77)
                {
                    core.create_Grid();
                }
                else if (core.pos.x > 1600 && core.pos.x < 1600 + 220 && core.pos.y > 600 && core.pos.y < 600 + 79)
                {
                    core.choose_Difficulty();
                    core.create_Grid();
                }
                else if (core.pos.x > (core.diff_pixel + core.diff_pos_x) &&
                         core.pos.x < (core.diff_pixel * (core.diff_size_x + 1) + core.diff_pos_x) &&
                         core.pos.y > (core.diff_pixel + core.diff_pos_y) &&
                         core.pos.y < (core.diff_pixel * (core.diff_size_y + 1) + core.diff_pos_y))
                {
                    if (core.show_Grid[core.x][core.y] == 10)
                    {
                        core.show_Grid[core.x][core.y] = core.base_Grid[core.x][core.y];
                        if (core.show_Grid[core.x][core.y] == 0)
                            core.tracker(core.x, core.y);
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
                    {
                        if (core.show_Grid[core.x][core.y] == 11)
                            core.show_Grid[core.x][core.y] = 10;
                        else if (core.show_Grid[core.x][core.y] == 10)
                            core.show_Grid[core.x][core.y] = 11;
                    }
                }
            }
    }
}