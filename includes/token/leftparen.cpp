#include "leftparen.h"

LeftParen::LeftParen(TOKEN_TYPES type):Token(type), _value("(") {}

void LeftParen::Print(ostream& outs) const{
    outs << _value;
}