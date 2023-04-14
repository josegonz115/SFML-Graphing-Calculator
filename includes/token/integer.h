#ifndef INTEGER_H
#define INTEGER_H

#include "token.h"


class Integer: public Token{
public:
    Integer(double number,TOKEN_TYPES type = INTEGER);
    void Print(ostream& outs) const override;

    double check() const;
private:
    double _number;
};

#endif //INTEGER_H