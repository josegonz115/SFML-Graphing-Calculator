#ifndef FUNCTION_H
#define FUNCTION_H

#include "token.h"
#include <cmath>


class Function: public Token{
public:
    Function(const string& value, TOKEN_TYPES type = TOKEN_TYPES::FUNCTION);
    int getPrecedent() const;
    int getParameter() const;
    string getValue() const;
    double computeFunction();
    double computeFunction(double operand);
    double computeFunction(double operand1, double operand2);

    void Print(ostream& outs) const override;

private:
    string _value;
    int _precedent;
    int _parameter;
};

#endif //FUNCTION_H
