#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 10 //could be 10    or 13
#define ESCAPE_KEY 27

class TextBox{
public: 
    TextBox(){}
    TextBox(int size, sf::Color color, bool selected){
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected = selected;
        if(selected){
            textbox.setString("_");
        }
        else{
            textbox.setString("");
        }
        limit = 100;
        hasLimit = true;
    }

    TextBox& operator=(const TextBox& rhs){
        if(this == &rhs){
            return *this;
        }
        textbox.setCharacterSize(rhs.textbox.getCharacterSize());
        textbox.setFillColor(rhs.textbox.getFillColor());
        isSelected = rhs.isSelected;
        limit = rhs.limit;
        if(isSelected){
            textbox.setString("_");
        }
        else{
            textbox.setString("");
        }
        return *this;
    }

    void setPosition(sf::Vector2f pos){
        textbox.setPosition(pos);
    }

    void setLimit(bool status, int lim){
        hasLimit = status;
        limit = lim;
    }

    void setSelected(bool status){
        isSelected = status;
        if(!status){
            //std::string t = text.str();
            string t = text;
            std::string newT = "";
            for(int i = 0; i < t.length(); i++){
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    std::string getText(){
        return text;
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(textbox);
    }

    void typedOn(sf::Event input){
        if(isSelected){
            int charText = input.text.unicode;
            if(charText < 128){
                //Setup a limit to keep the textbox from reaching 25 chars
                if(hasLimit){
                    if(text.length() <= limit){
                        inputChar(charText);
                    }
                    //typing the delete key
                    else if(text.length() <= limit && charText != ESCAPE_KEY){
                        deleteLastChar();
                    }
                }
                else{
                    inputChar(charText);
                }
            }
        }
    }

    void addText(std::string in){
        if(in.length() + text.length() < limit){
            text += in;
        }
        textbox.setString(text + "_");
    }
    

    void clear(){
        text = "";
        textbox.setString(text + "_");
    }


    sf::Text& getTextbox() { return textbox; }


private:
    bool isSelected;
    sf::Text textbox;
    std::string text;
    bool hasLimit;
    int limit;

    void inputChar(int charKey){
        if(charKey != DELETE_KEY && charKey != ENTER_KEY && charKey != ESCAPE_KEY){
           // text << static_cast<char>(charKey);
           text.push_back(static_cast<char>(charKey));
        }
        else if(charKey == DELETE_KEY){
            if(text.length() > 0){
                deleteLastChar();
            }
        }
        textbox.setString(text + "_");
    }

    //Deletes the last character in text sstring
    void deleteLastChar(){
        std::string t = text;
        std::string newT = "";
        for(int i = 0; i < t.length() - 1; i++){
            newT += t[i];
        }
        text = "";
        text += newT;

        //Set the text in textbox to have new text with deleted tail.
        textbox.setString(text);
    }
};



#endif //TYPING_BOX_H