#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "SFML/Graphics.hpp"

class Graphic
{
public:
    void create_Window(sf::Window &window, int size_x, int size_y, std::string title);
    void load_And_Set_Texture(sf::Sprite &sprite, sf::Texture &texture, std::string path);
    void clear_Render(sf::RenderWindow &window, sf::Color color);
    void draw_Render(sf::RenderWindow &window, sf::Sprite &sprite, int texture_x, int texture_y, int width, int height, int pos_x, int pos_y);
    void display_Render(sf::RenderWindow &window);
};
#endif // GRAPHIC_H
