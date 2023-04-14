#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include "token.h"

class LeftParen: public Token{
public:
    LeftParen(TOKEN_TYPES type = TOKEN_TYPES::LPAREN);
    void Print(ostream& outs) const override;
private:
    string _value;
};

#endif //LEFTPAREN_H