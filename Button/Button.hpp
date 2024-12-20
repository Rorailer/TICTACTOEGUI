#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button {

    sf::RectangleShape buttonShape;
    sf::Text buttonText;

public:
    Button(const std::string& text, const sf::Font& font, int WIDTH,int HEIGHT, int colour[4]);

    void setPosition(float x, float y);
    bool isPressed(const sf::Vector2i& mousePos) const;
    void draw(sf::RenderWindow& window) const;

};
#endif