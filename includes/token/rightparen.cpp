#include "rightparen.h"

RightParen::RightParen(TOKEN_TYPES type):Token(type), _value(")"){}

void RightParen::Print(ostream& outs) const{
    outs << _value;
}