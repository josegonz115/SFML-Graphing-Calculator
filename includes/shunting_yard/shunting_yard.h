#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include <cassert>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

using namespace std;

class ShuntingYard
{
public:
    // CTOR
    ShuntingYard();
    ShuntingYard(const Queue<Token*>& input_q);

    // save input_q to member variable queue
    void infix(const Queue<Token*>& input_q);

    // generate postfix queue from infix queue
    Queue<Token*> postfix();
    Queue<Token*> postfix(const Queue<Token*>& input_q);
    // called by postfix()
    Queue<Token*> shunting_yard();

    bool hasError() const{ return error; }
private:
    Queue<Token*> queue;
    bool error;
};

#endif //SHUNTING_YARD_H