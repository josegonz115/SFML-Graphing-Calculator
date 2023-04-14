#include "variable.h"

Variable::Variable(const string& value, TOKEN_TYPES type):Token(type), _value(value){}

void Variable::Print(ostream& outs)const{
    outs << _value;
}
