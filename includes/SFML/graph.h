#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "graph_constants.h"
#include "../queue/MyQueue.h"

using namespace std;

class Graph
{
public:
    Graph();
    //Draws graph objects on the window reference.
    void Draw(sf::RenderWindow& window);
    //Draws the expression and determines color based on the int colorIndex 
    void drawPoints(Queue<sf::Vector2f> points, int colorIndex);
    //Removes all the functions off the screen.
    void clear();

    //Adjusts the low, high, increment, and scaling of the points.
    //Also calculates the domain and range.
    void setScale(int scale);

    //Accessors.
    float getScaler() const{ return scaler; }
    string getDomainRange()const{ return domainRange; }
    //Public variables because their purpose is to be changed outside the class.
    int scaleLevel;
    int functCount;

private:
    sf::RectangleShape xAxis;
    sf::RectangleShape yAxis;
    

    sf::VertexArray expression1;
    sf::VertexArray expression2;
    sf::VertexArray expression3;
    sf::VertexArray expression4;



    float scaler;
    sf::Text domain;
    string domainRange;
};

#endif // SYSTEM_H