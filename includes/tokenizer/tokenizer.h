#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../token/variable.h"
#include <string>
#include <cctype>

//using namespace std;

class Tokenizer{
public:
    //Constructors
    //Preprocessing: a string expression of a line
    //Postprocessing: initialize expression
    Tokenizer(string expression);

    //Mutators
    

    //Accessors
    //Preprocessing: _exp has a number expression
    Queue<Token*> getTokens();

    Queue<Token*> getTokens(string newExp);
    bool hasError() const{return error;}
private: 
    string _exp;
    Queue<Token*> _infix;
    bool error;

    //Reads the line that was passed
    void split();
    
};



#endif //TOKENIZER_H