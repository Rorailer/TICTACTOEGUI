#include"Button.hpp"

Button::Button(const std::string& text, const sf::Font& font, int WIDTH=224, int HEIGHT=225, int colour[4] = nullptr ){
    
    buttonShape.setSize(sf::Vector2f(WIDTH,HEIGHT));
    buttonShape.setFillColor(sf::Color(colour[0],colour[1],colour[2],colour[3]));
    
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(70);
    buttonText.setFillColor(sf::Color(sf::Color::Blue));


    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(buttonShape.getSize().x / 2.0f, buttonShape.getSize().y / 2.0f);


}

void Button::setPosition(float x , float y){
    buttonShape.setPosition(x,y);
    buttonText.setPosition(x+buttonShape.getSize().x / 2.0f , y + buttonShape.getSize().y / 2.0f);
}

bool Button::isPressed(const sf::Vector2i& mousePos) const{
    return buttonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Button::draw(sf::RenderWindow& window) const{
    
    window.draw(buttonShape);
    window.draw(buttonText);
}