#include "function.h"

Function::Function(const string& value, TOKEN_TYPES type):Token(type), _value(value)
{
    if(_value == MAX || _value == MIN){
        _precedent = 4;
        _parameter = 2;
    }
    else if(_value == PI){
        _precedent = 4;
        _parameter = 0;
    }
    else{
        _precedent = 4;
        _parameter = 1;
    }
}

int Function::getPrecedent() const{
    return _precedent;
}


int Function::getParameter() const{
    return _parameter;
}

string Function::getValue() const{
    return _value;
}

double Function::computeFunction(double operand){
    double result;
    if(_value == SIN){
        result = sin(operand);
    }
    else if(_value == COS){
        result = cos(operand);
    }
    else if (_value == TAN){
        result = tan(operand); 
    }
    else if(_value == ABS){
        result = fabs(operand);
    }
    else if(_value == EX){
        result = exp(operand);
    }
    else if(_value == LOG){
        result = log(operand);
    }
    return result;
}

double Function::computeFunction(double operand1, double operand2){
    double result;
    if(_value == MIN){
        result = min(operand1, operand2);
    }
    else if(_value == MAX){
        result = max(operand1, operand2);
    }
    return result;
}
double Function::computeFunction(){
    double result;
    if(_value == PI){
        result = PI_VALUE;
    }
    return result;
}


void Function::Print(ostream& outs)const{
    outs << _value;
}
