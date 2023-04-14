#ifndef OPERATOR_H
#define OPERATOR_H

#include "token.h"

class Operator: public Token{
public:
    Operator(const string& op, TOKEN_TYPES type = TOKEN_TYPES::OPERATOR);
    void Print(ostream& outs) const override;


    int getPrecedent() const;
    bool getLeft() const;
    int getParameter() const;

    friend bool operator >(const Operator& lhs, const Operator& rhs);
    friend bool operator ==(const Operator& lhs, const Operator& rhs);

    double compute(double lhs, double rhs);



private:
    string _operator;
    int _precedent;
    bool _left;
    int _parameter;
};

#endif //OPERATOR_H