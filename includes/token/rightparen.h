#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include "token.h"

class RightParen: public Token{
public:
    RightParen(TOKEN_TYPES type = TOKEN_TYPES::RPAREN);
    void Print(ostream& outs) const override;
private:
    string _value;
};

#endif //RIGHTPAREN_H