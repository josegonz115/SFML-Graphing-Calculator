#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "constants.h"
using namespace std;

class Token{
public:
    Token(TOKEN_TYPES type = TOKEN);

    virtual void Print(ostream& outs) const;
    friend ostream& operator <<(ostream& outs, const Token* token);
    friend ostream& operator <<(ostream& outs, const Token &token);

    TOKEN_TYPES getType() const;

private:
    TOKEN_TYPES _type;
};

#endif //TOKEN_H