#include "animate.h"



Animate::Animate():sidebar(GRAPH_PANEL, SIDE_BAR)
{
    cout<<"Animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Jose's Graphing Calculator", sf::Style::Close); //sf::Style::Close used to restrict resizing.
    window.setFramerateLimit(FRAME_RATE); //Don't call vsync if framrateLimit is used.
    
    //Trying to help out graphics with anti-aliasing.
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    cout<<"Animate CTOR: preparing to load the font."<<endl;

    //--- FONT ----------
    if (!font.loadFromFile("includes/SFML/arial.ttf")){
        cout<<"Animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    //Create starting text label which will show the domain and range.
    myTextLabel = sf::Text("Domain/Range", font);//"Initital String for myTextLabel"
    myTextLabel.setCharacterSize(50);  
    myTextLabel.setFillColor(sf::Color::Red);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-100));

    cout<<"Animate instantiated successfully."<<endl;
}

void Animate::run()
{
    //Run the program as long as the window is open
    while (window.isOpen())
    {
        //Check all the window's events that were triggered since the last iteration of the loop.
        processEvents();
        render(); //clear/draw/display
    }
    cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}


void Animate::processEvents()
{
    sf::Event event;
    string expression = "";
    Queue<sf::Vector2f> points;

    while (window.pollEvent(event))//or waitEvent
    {
    // check the type of the event...
        switch (event.type)
        {
            //  "close requested" event: we close the window
            case sf::Event::Closed:
                window.close();
                cout << "Shutting down, thank you!\n";
                break;
            case sf::Event::TextEntered:
                //Accessed the textbox inside sidebar
                sidebar.getTextBox().typedOn(event); 
                break;
            case sf::Event::MouseMoved:
                break;
            //Watching for button pressing events. 
            case sf::Event::MouseButtonPressed:
                if(sidebar.getDecButton().isMouseOver(window) && graph.scaleLevel > 0){
                    std::cout << "You decreased the scale a level.\n";
                    graph.setScale(--graph.scaleLevel);
                    myTextLabel.setString(graph.getDomainRange());
                    replot();
                    
                }
                else if(sidebar.getIncButton().isMouseOver(window) && graph.scaleLevel < 3){
                    cout << "You increased the scale a level.\n";
                    graph.setScale(++graph.scaleLevel);
                    myTextLabel.setString(graph.getDomainRange());
                    replot();
                    
                }
                else if(sidebar.getResetButton().isMouseOver(window)){
                    cout << "You reset the graph on the calculator.\n";
                    graph.clear();
                    sidebar.clear();
                }
                break;
            // key pressed
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                    case sf::Keyboard::Enter:
                        if(graph.functCount < 4){ // and if expression is valid
                            //Clear string and points if previously used.
                            expression.clear();
                            myTextLabel.setString(graph.getDomainRange());
                            cout << "ENTER KEY PRESSED\n";
                            expression += sidebar.getTextBox().getText();
                            sidebar.getTextBox().clear();
                            //validate the expression
                            if(sidebar.checkExpression(expression)){
                                points = sidebar.PlotExpression(expression, LOW, HIGH, INCREMENT, graph.getScaler());
                                //add to history
                                sidebar.addExpression(expression);
                                sidebar.changeString(expression, graph.functCount);
                                graph.drawPoints(points, graph.functCount);
                                graph.functCount++;
                            }

                        }
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        cout << "Shutting down, thank you!\n";
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

//animation being done: cleared window , drawn shapes, and finally displayed
void Animate::render()
{
    window.clear();
    Draw();
    window.display();
}
void Animate::Draw()
{
    //draw the two main objects: graph and sidebar along with some text in the lower left corner.
    graph.Draw(window);
    sidebar.draw(window);
    window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}

void Animate::replot(){
        Queue<string> functions = sidebar.getHistory();
        int index = 0;
        for (Queue<string>::Iterator it = functions.begin(); it != functions.end(); ++it){
            Queue<sf::Vector2f> points = sidebar.PlotExpression(*it, LOW, HIGH, INCREMENT, graph.getScaler());
            graph.drawPoints(points, index);
            index++;
        }
        index = 0;
    }

