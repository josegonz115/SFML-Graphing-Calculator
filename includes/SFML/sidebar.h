#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../tokenizer/tokenizer.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "graph_constants.h"
#include "text_box.h"
#include "button.h"


using namespace std;

class Sidebar
{
public:

    //Constructors.
    Sidebar();
    Sidebar(float left, float width);

    //Draw all Sidebar shapes to window.
    void draw(sf::RenderWindow& window);

    //Ading strings to the function buttons.
    void changeString(string newExpression, int functIndex);
    //Clears the string function buttons.
    void clear();

    //First check if expression is valid.
    //Returns true if expression is valid.
    bool checkExpression(string expression);
    //Plot vector2f points
    Queue<sf::Vector2f> PlotExpression(string expression, float low, float high, float increments, float scaler);
    //Add an expression to the expresssion history.
    void addExpression(string expression);
    

    //Accessor for the TextBox and Button references.
    TextBox& getTextBox(){ return textBox; }
    Button& getDecButton(){ return decScaleBtn; }
    Button& getIncButton(){ return incScaleBtn; }
    Button& getResetButton(){ return resetBtn; }
    //Accessor for all the expressions.
    Queue<string> getHistory(){ return history; }

private:
    
    Queue<string> history;              //holds the string history of expressions 
    sf::RectangleShape rect;            //sidebar rectangle
    sf::RectangleShape typeBox;         //Box to type equations in.
    sf::Font font;                      //used to draw text

    TextBox textBox;

    Button function1;
    Button function2;
    Button function3;
    Button function4;

    Button decScaleBtn;
    Button incScaleBtn;
    Button resetBtn;

    //_left is the starting point of the leftside of the sidebar
    //width is the width of sidebar
    float _left;
    float _width;
};

#endif // SIDEBAR_H