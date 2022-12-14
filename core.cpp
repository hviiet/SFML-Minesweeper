#include "core.h"
void Core::init()
{
    graphic.create_Window(app, Window_Size_X, Window_Size_Y, "Minesweeper");
    load_Assets();
    choose_Difficulty();
    create_Grid();
}
void Core::create_Random_Mines()
{
    srand(time(0));
    for (int i = 1; i <= diff_mines; i++)
    {
        int mines, temp_x, temp_y;
        do
        {
            mines = rand() % (diff_size_x * diff_size_y) + 1;
            temp_x = (mines - 1) / diff_size_y + 1;
            if (mines % diff_size_y == 0)
                temp_y = diff_size_y;
            else
                temp_y = mines % diff_size_y;
        } while (base_Grid[temp_x][temp_y] == 9);
        base_Grid[temp_x][temp_y] = 9;
    }
}
void Core::create_Grid()
{
    reset_Grid();
    create_Random_Mines();
    for (int i = 1; i <= diff_size_x; i++)
        for (int j = 1; j <= diff_size_y; j++)
        {
            show_Grid[i][j] = 10;
            int n = 0;
            if (base_Grid[i][j] == 9)
                continue;
            if (base_Grid[i + 1][j] == 9)
                n++;
            if (base_Grid[i][j + 1] == 9)
                n++;
            if (base_Grid[i - 1][j] == 9)
                n++;
            if (base_Grid[i][j - 1] == 9)
                n++;
            if (base_Grid[i + 1][j + 1] == 9)
                n++;
            if (base_Grid[i - 1][j - 1] == 9)
                n++;
            if (base_Grid[i - 1][j + 1] == 9)
                n++;
            if (base_Grid[i + 1][j - 1] == 9)
                n++;
            base_Grid[i][j] = n;
        }
}
void Core::check(int x, int y)
{
    if (base_Grid[x - 1][y - 1] > 0 && base_Grid[x - 1][y - 1] < 9)
        show_Grid[x - 1][y - 1] = base_Grid[x - 1][y - 1];
    if (base_Grid[x - 1][y] > 0 && base_Grid[x - 1][y] < 9)
        show_Grid[x - 1][y] = base_Grid[x - 1][y];
    if (base_Grid[x - 1][y + 1] > 0 && base_Grid[x - 1][y + 1] < 9)
        show_Grid[x - 1][y + 1] = base_Grid[x - 1][y + 1];
    if (base_Grid[x][y - 1] > 0 && base_Grid[x][y - 1] < 9)
        show_Grid[x][y - 1] = base_Grid[x][y - 1];
    if (base_Grid[x][y + 1] > 0 && base_Grid[x][y + 1] < 9)
        show_Grid[x][y + 1] = base_Grid[x][y + 1];
    if (base_Grid[x + 1][y - 1] > 0 && base_Grid[x + 1][y - 1] < 9)
        show_Grid[x + 1][y - 1] = base_Grid[x + 1][y - 1];
    if (base_Grid[x + 1][y] > 0 && base_Grid[x + 1][y] < 9)
        show_Grid[x + 1][y] = base_Grid[x + 1][y];
    if (base_Grid[x + 1][y + 1] > 0 && base_Grid[x + 1][y + 1] < 9)
        show_Grid[x + 1][y + 1] = base_Grid[x + 1][y + 1];
}
void Core::tracker(int x, int y)
{
    check(x, y);
    if (base_Grid[x][y + 1] == 0 && show_Grid[x][y + 1] == 10)
    {
        check(x, y + 1);
        show_Grid[x][y + 1] = base_Grid[x][y + 1];
        tracker(x, y + 1);
    }
    if (base_Grid[x][y - 1] == 0 && show_Grid[x][y - 1] == 10 && y - 1 > 0)
    {
        check(x, y - 1);
        show_Grid[x][y - 1] = base_Grid[x][y - 1];
        tracker(x, y - 1);
    }
    if (base_Grid[x + 1][y] == 0 && show_Grid[x + 1][y] == 10)
    {
        check(x + 1, y);
        show_Grid[x + 1][y] = base_Grid[x + 1][y];
        tracker(x + 1, y);
    }
    if (base_Grid[x - 1][y] == 0 && show_Grid[x - 1][y] == 10 && x - 1 > 0)
    {
        check(x - 1, y);
        show_Grid[x - 1][y] = base_Grid[x - 1][y];
        tracker(x - 1, y);
    }
}
void Core::set_Difficulty(int diff)
{
    if (diff == 1)
    {
        diff_size_x = 8;
        diff_size_y = 8;
        diff_mines = 10;
        diff_pixel = 100;
        diff_pos_x = 300;
        diff_pos_y = -50;
    }
    else if (diff == 2)
    {
        diff_size_x = 16;
        diff_size_y = 16;
        diff_mines = 40;
        diff_pixel = 50;
        diff_pos_x = 350;
        diff_pos_y = 0;
    }
    else if (diff == 3)
    {
        diff_size_x = 30;
        diff_size_y = 16;
        diff_mines = 99;
        diff_pixel = 50;
        diff_pos_x = 0;
        diff_pos_y = 0;
    }
}
void Core::load_Assets()
{
    graphic.load_And_Set_Texture(background, t_background, "src/images/background.png");
    graphic.load_And_Set_Texture(play_exit, t_play_exit, "src/images/play_exit.png");
    graphic.load_And_Set_Texture(difficulty, t_difficulty, "src/images/difficulty.png");
    graphic.load_And_Set_Texture(restart_back, t_restart_back, "src/images/restart_back.png");
    graphic.load_And_Set_Texture(playing_win_lose, t_playing_win_lose, "src/images/playing_win_lose.png");
    graphic.load_And_Set_Texture(title, t_title, "src/images/title.png");
}
void Core::choose_Difficulty()
{
    int which_case = 0;
    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
            if (e.type == Event::MouseButtonPressed)
                if (e.mouseButton.button == Mouse::Left)
                {
                    if (which_case == 0)
                    {
                        if (pos.x > 700 && pos.x < 700 + 500 && pos.y > 450 && pos.y < 450 + 209 / 2)
                        {
                            which_case = 1;
                        }
                        else if (pos.x > 700 && pos.x < 700 + 500 && pos.y > 650 && pos.y < 650 + 209 / 2)
                        {
                            app.close();
                        }
                    }
                    if (which_case == 1)
                    {
                        if (pos.x > 700 && pos.x < 700 + 500 && pos.y > 350 && pos.y < 350 + 310 / 3)
                        {
                            set_Difficulty(1);
                            graphic.load_And_Set_Texture(asset, t_asset, "src/images/diff-easy4.png");
                            return;
                        }
                        else if (pos.x > 700 && pos.x < 700 + 500 && pos.y > 550 && pos.y < 550 + 310 / 3)
                        {
                            set_Difficulty(2);
                            graphic.load_And_Set_Texture(asset, t_asset, "src/images/diff-medium-hard4.png");
                            return;
                        }
                        else if (pos.x > 700 && pos.x < 700 + 500 && pos.y > 750 && pos.y < 750 + 310 / 3)
                        {
                            set_Difficulty(3);
                            graphic.load_And_Set_Texture(asset, t_asset, "src/images/diff-medium-hard4.png");
                            return;
                        }
                    }
                }
        }
        graphic.clear_Render(app, Color::Black);
        graphic.draw_Render(app, background, 0, 0, 1900, 900, 0, 0);
        graphic.draw_Render(app, title, 0, 0, 1100, 246, 400, 60);
        if (which_case == 0)
        {
            graphic.draw_Render(app, play_exit, 0, 0, 500, 209 / 2, 700, 450);
            graphic.draw_Render(app, play_exit, 0, 209 / 2, 500, 209 / 2, 700, 650);
        }
        if (which_case == 1)
        {
            graphic.draw_Render(app, difficulty, 0, 0, 500, 310 / 3, 700, 350);
            graphic.draw_Render(app, difficulty, 0, 207, 500, 310 / 3, 700, 550);
            graphic.draw_Render(app, difficulty, 0, 310 / 3, 500, 310 / 3, 700, 750);
        }
        graphic.display_Render(app);
    }
}
void Core::reset_Grid()
{
    for (int i = 1; i <= 31; i++)
        for (int j = 1; j <= 17; j++)
        {
            base_Grid[i][j] = 0;
            show_Grid[i][j] = 0;
        }
}
bool Core::check_If_Winning()
{
    int count = 0;
    for (int i = 1; i <= diff_size_x; i++)
        for (int j = 1; j <= diff_size_y; j++)
        {
            if (show_Grid[i][j] >= 0 && show_Grid[i][j] <= 8)
                count++;
            else if (show_Grid[i][j] == 9)
                return false;
        }
    if (count == (diff_size_x * diff_size_y - diff_mines))
        return true;
    else
        return false;
}
bool Core::check_If_Losing()
{
    for (int i = 1; i <= diff_size_x; i++)
        for (int j = 1; j <= diff_size_y; j++)
        {
            if (show_Grid[i][j] == 9)
                return true;
        }
    return false;
}
void Core::get_Mouse_Position()
{
    pos = Mouse::getPosition(app);
    x = (pos.x - diff_pos_x) / diff_pixel;
    y = (pos.y - diff_pos_y) / diff_pixel;
}