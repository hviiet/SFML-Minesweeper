#include "game.h"
Game::Game()
{
    app.create(VideoMode(Window_Size_X, Window_Size_Y), "Minesweeper");
    load_Assets();
    choose_Difficulty();
    create_Grid();
}
void Game::loop()
{
    while (app.isOpen())
    {
        get_Mouse_Position();
        handle_Events();
        update();
        render();
    }
}
void Game::render()
{
    app.clear(Color::Black);
    background.setTextureRect(IntRect(0, 0, 1900, 900));
    background.setPosition(0, 0);
    app.draw(background);

    for (int i = 1; i <= diff_size_x; i++)
        for (int j = 1; j <= diff_size_y; j++)
        {
            asset.setTextureRect(IntRect(show_Grid[i][j] * diff_pixel, 0, diff_pixel, diff_pixel));
            asset.setPosition(diff_pos_x + i * diff_pixel, diff_pos_y + j * diff_pixel);
            app.draw(asset);
        }
    if (check_If_Winning())
    {
        winning.setTextureRect(IntRect(0, 0, 300, 33));
        winning.setPosition(1600, 200);
        app.draw(winning);
    }
    else if (check_If_Losing())
    {
        losing.setTextureRect(IntRect(0, 0, 300, 163));
        losing.setPosition(1600, 200);
        app.draw(losing);
    }

    button.setTextureRect(IntRect(0, 0, 200, 77));
    button.setPosition(1600, 470);
    app.draw(button);

    select_button.setTextureRect(IntRect(0, 0, 200, 79));
    select_button.setPosition(1600, 600);
    app.draw(select_button);

    app.display();
}
void Game::update()
{
    for (int i = 1; i <= diff_size_x; i++)
        for (int j = 1; j <= diff_size_y; j++)
        {
            if (show_Grid[x][y] == 9)
                show_Grid[i][j] = base_Grid[i][j];
        }
}
void Game::handle_Events()
{
    Event e;
    while (app.pollEvent(e))
    {
        if (e.type == Event::Closed)
            app.close();

        if (e.type == Event::MouseButtonPressed)
            if (e.mouseButton.button == Mouse::Left)
            {
                if (pos.x > 1600 && pos.x < 1600 + 220 && pos.y > 470 && pos.y < 470 + 77)
                {
                    create_Grid();
                }
                else if (pos.x > 1600 && pos.x < 1600 + 220 && pos.y > 600 && pos.y < 600 + 79)
                {
                    choose_Difficulty();
                    create_Grid();
                }
                else if (pos.x > (diff_pixel + diff_pos_x) &&
                         pos.x < (diff_pixel * (diff_size_x + 1) + diff_pos_x) &&
                         pos.y > (diff_pixel + diff_pos_y) &&
                         pos.y < (diff_pixel * (diff_size_y + 1) + diff_pos_y))
                {
                    if (show_Grid[x][y] == 10)
                    {
                        show_Grid[x][y] = base_Grid[x][y];
                        if (show_Grid[x][y] == 0)
                            tracker(x, y);
                    }
                }
            }
            else if (e.mouseButton.button == Mouse::Right)
            {
                if (pos.x > (diff_pixel + diff_pos_x) &&
                    pos.x < (diff_pixel * (diff_size_x + 1) + diff_pos_x) &&
                    pos.y > (diff_pixel + diff_pos_y) &&
                    pos.y < (diff_pixel * (diff_size_y + 1) + diff_pos_y))
                {
                    {
                        if (show_Grid[x][y] == 11)
                            show_Grid[x][y] = 10;
                        else if (show_Grid[x][y] == 10)
                            show_Grid[x][y] = 11;
                    }
                }
            }
    }
}
void Game::get_Mouse_Position()
{
    pos = Mouse::getPosition(app);
    x = (pos.x - diff_pos_x) / diff_pixel;
    y = (pos.y - diff_pos_y) / diff_pixel;
}
void Game::create_Grid()
{
    srand(time(0));
    reset_Grid();
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
void Game::check(int x, int y)
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
    return;
}
void Game::tracker(int x, int y)
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
void Game::set_Difficulty(int diff)
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
void Game::load_Assets()
{
    t1.loadFromFile("src/images/background.png");
    background.setTexture(t1);

    t3.loadFromFile("src/images/restart.png");
    button.setTexture(t3);

    t4.loadFromFile("src/images/diff-button.png");
    difficulty_button.setTexture(t4);

    t5.loadFromFile("src/images/select-button.png");
    select_button.setTexture(t5);

    t6.loadFromFile("src/images/winning.png");
    winning.setTexture(t6);

    t7.loadFromFile("src/images/losing.png");
    losing.setTexture(t7);
}
void Game::choose_Difficulty()
{
    while (app.isOpen())
    {
        t1.loadFromFile("src/images/background.png");
        Vector2i pos = Mouse::getPosition(app);
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.mouseButton.button == Mouse::Left)
                {
                    if (pos.x > 500 && pos.x < 500 + 290 && pos.y > 200 && pos.y < 200 + 100)
                    {
                        set_Difficulty(1);
                        t1.loadFromFile("src/images/background-easy.png");
                        t2.loadFromFile("src/images/diff-easy.png");
                        asset.setTexture(t2);
                        return;
                    }
                    else if (pos.x > 500 && pos.x < 500 + 290 && pos.y > 400 && pos.y < 400 + 100)
                    {
                        set_Difficulty(2);
                        t1.loadFromFile("src/images/background-easy.png");
                        t2.loadFromFile("src/images/diff-medium-hard.png");
                        asset.setTexture(t2);
                        return;
                    }
                    else if (pos.x > 500 && pos.x < 500 + 290 && pos.y > 600 && pos.y < 600 + 100)
                    {
                        set_Difficulty(3);
                        t1.loadFromFile("src/images/background-hard.png");
                        t2.loadFromFile("src/images/diff-medium-hard.png");
                        asset.setTexture(t2);
                        return;
                    }
                }
        }
        app.clear(Color::Black);
        background.setTextureRect(IntRect(0, 0, 1900, 900));
        background.setPosition(0, 0);
        app.draw(background);

        difficulty_button.setTextureRect(IntRect(0, 0, 290, 100));
        difficulty_button.setPosition(500, 200);
        app.draw(difficulty_button);

        difficulty_button.setTextureRect(IntRect(0, 100, 290, 100));
        difficulty_button.setPosition(500, 400);
        app.draw(difficulty_button);

        difficulty_button.setTextureRect(IntRect(0, 200, 290, 100));
        difficulty_button.setPosition(500, 600);
        app.draw(difficulty_button);
        app.display();
    }
}
void Game::reset_Grid()
{
    for (int i = 1; i <= 31; i++)
        for (int j = 1; j <= 17; j++)
        {
            base_Grid[i][j] = 0;
            show_Grid[i][j] = 0;
        }
}
bool Game::check_If_Winning()
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
bool Game::check_If_Losing()
{
    for (int i = 1; i <= diff_size_x; i++)
        for (int j = 1; j <= diff_size_y; j++)
        {
            if (show_Grid[i][j] == 9)
                return true;
        }
    return false;
}