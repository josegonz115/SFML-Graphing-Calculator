#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
    Button() {}

    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor){
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);
    }

    Button& operator =(const Button& rhs){
        if(&rhs == this){
            return *this;
        }
        text.setString(rhs.text.getString());
        text.setFillColor(rhs.text.getFillColor());
        text.setCharacterSize(rhs.text.getCharacterSize());

        button.setSize(rhs.button.getSize());
        button.setFillColor(rhs.button.getFillColor());
        return *this;
    }

    void setPosition(sf::Vector2f pos){
        button.setPosition(pos);
        float xPos = (pos.x + button.getLocalBounds().width / 5) - (text.getLocalBounds().width / 2);
        float yPos = (pos.y + button.getLocalBounds().height / 5) - (text.getLocalBounds().height / 2);
        //text.setPosition({xPos, yPos});
        text.setPosition(sf::Vector2f(xPos, yPos));
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window){
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;

        float buttonPosX = button.getPosition().x;
        float buttonPosY = button.getPosition().y;
        float buttonXPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float buttonYPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < buttonXPosWidth && mouseX > buttonPosX && mouseY < buttonYPosHeight && mouseY > buttonPosY){
            return true;
        }
        return false;
    }

    std::string getText(){
        return text.getString();
    }

    sf::RectangleShape& getButton(){ return button; }
    sf::Text& getSFText(){ return text; }
private:
    sf::RectangleShape button;
    sf::Text text;

};

#endif //BUTTON_H