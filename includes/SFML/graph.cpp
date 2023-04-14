#include "graph.h"

Graph::Graph()
{
    cout << "Creating the graph axis points.\n";
    //Setup default scaling 10x10
    scaleLevel = 0;
    functCount = 0;
    setScale(scaleLevel);

    //sf::RectangleShape xAxis;
    xAxis.setSize(sf::Vector2f(GRAPH_PANEL, AXIS_SIZE));
    xAxis.setPosition(sf::Vector2f(0, Y_ORIGIN));
    xAxis.setFillColor(sf::Color::White);

    //sf::RectangleShape yAxis;
    yAxis.setSize(sf::Vector2f(AXIS_SIZE, SCREEN_HEIGHT));
    yAxis.setPosition(sf::Vector2f(X_ORIGIN, 0));
    yAxis.setFillColor(sf::Color::White);

}


void Graph::Draw(sf::RenderWindow& window)
{
  
    window.draw(xAxis);
    window.draw(yAxis);
    
    //Draw every single graph in expressions
    window.draw(expression1);
    window.draw(expression2);
    window.draw(expression3);
    window.draw(expression4);
  
}

void Graph::drawPoints(Queue<sf::Vector2f> points, int colorIndex)
{
    sf::Color color;
    if(colorIndex == 0){
        color = sf::Color::Green;
    }
    else if(colorIndex == 1){
        color = sf::Color::Blue;
    }
    else if(colorIndex == 2){
        color = sf::Color::Red;
    }
    else if(colorIndex == 3){
        color = sf::Color::Yellow;
    }
    sf::VertexArray line(sf::Points);
    int i = 0;
    while(!points.empty()){
        line.append(points.pop());
        line[i].color = color;
        i++;
    }
    if(colorIndex == 0){
        expression1 = line;
    }
    else if(colorIndex == 1){
        expression2 = line;
    }
    else if(colorIndex == 2){
        expression3 = line;
    }
    else if(colorIndex == 3){
        expression4 = line;
    }
}

void Graph::clear(){
    
    expression1.clear();
    expression2.clear();
    expression3.clear();
    expression4.clear();
    functCount = 0;
}

void Graph::setScale(int scale){
    //set scaling
    if(scale == 0){
        scaler = 100;//50 before
    }
    else if(scale == 1){
        scaler = 50;//10 before
    }
    else if(scale == 2){
        scaler = 10; //5 before
    }
    else if(scale = 3){
        scaler = 10; //1 before
    }
    int low = round(LOW/scaler);
    int high = round(HIGH/scaler);
    domainRange = "D&R: [" + to_string(low) + ", " + to_string(high) + "]\n";
 
}
