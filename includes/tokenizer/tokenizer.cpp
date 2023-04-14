#include "tokenizer.h"

Tokenizer::Tokenizer(string expression):_exp(expression), error(false){
    split();
}

Queue<Token*> Tokenizer::getTokens(){
    return _infix;
}

Queue<Token*> Tokenizer::getTokens(string nexExp){
    _exp = nexExp;
    split();
    return _infix;
}

void Tokenizer::split(){
    int lParenCount = 0;
    int rParenCount = 0;
    Queue<Token*> infix;
    for(int i = 0; i < _exp.length(); i++){
        string copy;
        if(_exp[i] >= '0' && _exp[i] <= '9'){
            copy.clear();
            while(i < _exp.length() && (_exp[i] == '.' ||  (_exp[i] >= '0' && _exp[i] <= '9'))){
                copy += _exp[i];
                i++;
            }
            i--;
            _infix.push(new Integer(stod(copy)));
        }
        else if(_exp[i] == ADD || _exp[i] == SUBTRACT || _exp[i] == MULTIPLY ||
         _exp[i] == DIVIDE || _exp[i] == POWER)
        {
            copy += _exp[i];
            _infix.push(new Operator(copy));
        }
        else if(_exp[i] == LEFT_PAREN){
            _infix.push(new LeftParen());
            lParenCount++;
        }
        else if(_exp[i] == RIGHT_PAREN){
            _infix.push(new RightParen());
            rParenCount++;
        }
        else if(_exp[i] == 'x' || _exp[i] == 'X' || _exp[i] == 'y' || _exp[i] == 'Y'){
            copy += _exp[i];
            _infix.push(new Variable(copy));
        }
        else if((_exp[i] >= 'a' && _exp[i] <= 'z') || (_exp[i] >= 'A' && _exp[i] <= 'Z'))
        {
            while((_exp[i] >= 'a' && _exp[i] <= 'z') || (_exp[i] >= 'A' && _exp[i] <= 'Z'))
            {
                copy += toupper(_exp[i]);
                i++;
            }
            i--;
            _infix.push(new Function(copy));
        }
        else if (_exp[i] == ' ' || _exp[i] == ','){
        }
        else{ 

        }
    }
    if(lParenCount != rParenCount){
        error = true;
    }
}