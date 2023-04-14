#include "integer.h"

Integer::Integer(double number, TOKEN_TYPES type):Token(type), _number(number){}

void Integer::Print(ostream &outs) const{
    outs << _number;
}

double Integer::check() const{
    return _number;
}
