#include "sidebar.h"

Sidebar::Sidebar() {}

Sidebar::Sidebar(float left, float width):_left(left), _width(width)
{
    cout<<"Sidebar CTOR: TOP"<<endl;
    

    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));//SCREEN_HEIGHT UNDEFINED?

    //Set up the type box rectangle:
    typeBox.setFillColor(sf::Color(192,192,192));//silver ?
    typeBox.setPosition(sf::Vector2f(left + 10, 100)); 
    typeBox.setSize(sf::Vector2f(rect.getLocalBounds().width - 20, 50));

    //Setup where the typer object goes.
    TextBox texter(35, sf::Color::White, true);
    textBox = texter;
    textBox.getTextbox().setFont(font);
    //textBox.setFont(font);
    textBox.setPosition(sf::Vector2f(left + 10, 100)); //(sf::Vector2f(left + 10, 100)
    textBox.setLimit(true, 25); //Text limit: 25

    // Setup the function boxes.
    Button temp4("", {width - 15, 75}, 25, sf::Color::Green, sf::Color::Black);
    function1 = temp4;
    function1.setPosition(sf::Vector2f(left + 10, 200));
    function1.getSFText().setFont(font);
    Button temp5("", {width - 15, 75}, 25, sf::Color::Blue, sf::Color::Black);
    function2 = temp5;
    function2.setPosition(sf::Vector2f(left + 10, 300));
    function2.getSFText().setFont(font);
    Button temp6("", {width - 15, 75}, 25, sf::Color::Red, sf::Color::Black);
    function3 = temp6;
    function3.setPosition(sf::Vector2f(left + 10, 400));
    function3.getSFText().setFont(font);
    Button temp7("", {width - 15, 75}, 25, sf::Color::Yellow, sf::Color::Black);
    function4 = temp7;
    function4.setPosition(sf::Vector2f(left + 10, 500));
    function4.getSFText().setFont(font);


    //Setup the decrease scale button. 
    Button temp("Decrease Scale", {width / 2 - 10, 75}, 15, sf::Color::White, sf::Color::Black);
    decScaleBtn = temp;
    decScaleBtn.setPosition(sf::Vector2f(left + 10, 700));
    decScaleBtn.getSFText().setFont(font);

    //Setup the increase scale button
    Button temp2("Increase Scale", {width / 2 - 15, 75}, 15, sf::Color::White, sf::Color::Black);
    incScaleBtn = temp2;
    incScaleBtn.setPosition(sf::Vector2f(left + 5 +  width / 2, 700));
    incScaleBtn.getSFText().setFont(font);

    //Setup the reset all functions button
    Button temp3("Reset Functions", {width - 15, 75}, 25, sf::Color::White, sf::Color::Black);
    resetBtn = temp3;
    resetBtn.setPosition(sf::Vector2f(left + 10, 800));
    resetBtn.getSFText().setFont(font);
    
    //Create history underneath.

    cout<<"Sidebar CTOR: about to load font."<<endl;
    //--- FONT ----------
    if(!font.loadFromFile("includes/SFML/arial.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    cout<<"Sidebar CTOR: loaded font."<<endl;







    cout<<"Sidebar: CTOR: Exit."<<endl;
}

void Sidebar::draw(sf::RenderWindow& window)
{
    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;


    //Window was passed by reference.
    window.draw(rect);
    window.draw(typeBox);

    function1.drawTo(window);
    function2.drawTo(window);
    function3.drawTo(window);
    function4.drawTo(window);

    textBox.drawTo(window);
    decScaleBtn.drawTo(window);
    incScaleBtn.drawTo(window);
    resetBtn.drawTo(window);

}

void Sidebar::changeString(string newExpression, int functIndex){
    if(functIndex == 0){
        function1.getSFText().setString(newExpression);
    }
    else if(functIndex == 1){
        function2.getSFText().setString(newExpression);
    }
    else if(functIndex == 2){
        function3.getSFText().setString(newExpression);
    }
    else if(functIndex == 3){
        function4.getSFText().setString(newExpression);
    }
}

void Sidebar::clear(){
    function1.getSFText().setString("");
    function2.getSFText().setString("");
    function3.getSFText().setString("");
    function4.getSFText().setString("");
    while(!history.empty()){
        history.pop();
    }
}

bool Sidebar::checkExpression(string expression){
    //Error handling,
    Tokenizer tokenizer(expression);
    Queue<Token*> tokens = tokenizer.getTokens();
    if(tokenizer.hasError()){
        return false;
    }
    ShuntingYard sy(tokens);
    Queue<Token*> postfix = sy.postfix();
    if(sy.hasError()){
        return false;
    }
    RPN rpn(postfix);
    double check = rpn();
    if(rpn.hasError()){
        return false;
    }
    return  true;
}

Queue<sf::Vector2f> Sidebar::PlotExpression(string expression, float low, float high, float increments, float scaler = 1){
    //Scale parameters.
    low = low / scaler;
    high = high / scaler;
    increments = (high - low) / GRAPH_PANEL;
    
    //Create a an rpn object with its variable.
    Tokenizer tokenizer(expression);
    Queue<Token*> infix = tokenizer.getTokens();
    ShuntingYard sy(infix);
    Queue<Token*> postfix = sy.postfix();
    RPN rpn(postfix);


    Queue<sf::Vector2f> allPoints;
    for(float i = low; i <= high; i += increments){
        float y = rpn(i) * scaler;
        //Scaler is used to make sure y is graphed correctly.
        allPoints.push(sf::Vector2f(i*scaler + X_ORIGIN, Y_ORIGIN - y)); 
    }
    //Make sure to add the text to the history
    return allPoints;
}


void Sidebar::addExpression(string expression){
    history.push(expression);
}

