#include "operator.h"
#include <cmath>

Operator::Operator(const string& op, TOKEN_TYPES type):Token(type){
    _operator = op;
    char charOp = _operator[0];
    switch(charOp){
        case '+':
        case '-':
            _precedent = 1;
            _left = true;
            _parameter = 2;
            break;
        case '*':
        case '/':
            _precedent = 2;
            _left = true;
            _parameter = 2;
            break;
        case '^':
            _precedent = 3;
            _left = false;
            _parameter = 2;
            break;
        default:
            _precedent = -1;
            _left = false;
            _parameter = -1;
    }
}

void Operator::Print(ostream& outs) const{
    outs << _operator;
}

int Operator::getPrecedent() const{
    return _precedent;
}

bool Operator::getLeft() const{
    return _left;
}

int Operator::getParameter() const{
    return _parameter;
}

bool operator >(const Operator& lhs, const Operator& rhs){
    return lhs._precedent > rhs._precedent;
}

bool operator ==(const Operator& lhs, const Operator& rhs){
    return lhs._precedent == rhs._precedent;
}

double Operator::compute(double lhs, double rhs){
    const char ADD = '+';
    const char SUBTRACT = '-';
    const char MULTIPLY = '*';
    const char DIVIDE = '/';
    const char POWER_OF = '^';
    const double ROUND = 1E-9;

    double result;
    char op = _operator[0];
    switch(op){
        case ADD:
            result = lhs + rhs;
            break;
        case SUBTRACT:
            result = lhs - rhs; 
            break;
        case MULTIPLY:
            result = lhs * rhs;
            break;
        case POWER_OF:
            result = pow(lhs, rhs);
            break;
        default: //case DIVIDE
            result = lhs / rhs;
    }
    return result + ROUND;
}