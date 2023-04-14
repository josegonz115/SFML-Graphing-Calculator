#ifndef ANIMATE_H
#define ANIMATE_H

#include <iostream>
#include <functional>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "graph_constants.h"
#include "graph.h"
#include "sidebar.h"

using namespace std;

// set up the range and scale of the graph
const float xMin = -10.0f;
const float xMax = 10.0f;
const float xScale = GRAPH_PANEL / (xMax - xMin);
const float yMin = -10.0f;
const float yMax = 10.0f;
const float yScale = SCREEN_HEIGHT / (yMax - yMin);

class Animate
{
public:
    Animate();
    void run();
    void processEvents();
    void render();
    void Draw();

    //Added function to replot points when rescaling the graph.
    void replot();
    

private:
    sf::RenderWindow window;            //Main display window
    Graph graph;                        //container for all the animated objects
    Sidebar sidebar;                    //rectangular message sidebar
   
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen



};

#endif // ANIMATE_H