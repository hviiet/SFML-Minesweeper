#include "graphic.h"
void Graphic::create_Window(sf::Window &window, int size_x, int size_y, std::string title)
{
    window.create(sf::VideoMode(size_x, size_y), title);
}
void Graphic::load_And_Set_Texture(sf::Sprite &sprite, sf::Texture &texture, std::string path)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
}
void Graphic::clear_Render(sf::RenderWindow &window, sf::Color color)
{
    window.clear(color);
}
void Graphic::draw_Render(sf::RenderWindow &window, sf::Sprite &sprite, int texture_x, int texture_y, int width, int height, int pos_x, int pos_y)
{
    sprite.setTextureRect(sf::IntRect(texture_x, texture_y, width, height));
    sprite.setPosition(pos_x, pos_y);
    window.draw(sprite);
}
void Graphic::display_Render(sf::RenderWindow &window)
{
    window.display();
}