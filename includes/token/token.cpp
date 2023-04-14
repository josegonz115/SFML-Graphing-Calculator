#include "token.h"

Token::Token(TOKEN_TYPES type):_type(type){}

void Token::Print(ostream &outs) const
{
    outs << "TOKEN Print: DON't ^%#$# call me again!" << endl;
}

ostream& operator <<(ostream& outs, const Token* token)
{
    token->Print(outs);
    return outs;
}

ostream &operator<<(ostream &outs, const Token &token)
{
    token.Print(outs);
    return outs;
}

TOKEN_TYPES Token::getType() const{
    return _type;
}