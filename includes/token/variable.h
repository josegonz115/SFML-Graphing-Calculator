#ifndef VARIABLE_H
#define VARIABLE_H

#include "token.h"


class Variable: public Token{
public:
    Variable(const string& value, TOKEN_TYPES type = TOKEN_TYPES::VARIABLE);
    void Print(ostream& outs) const override;

private:
    string _value;
};

#endif //VARIABLE_H