#include "shunting_yard.h"

// CTOR
ShuntingYard::ShuntingYard():error(false){ queue; }
ShuntingYard::ShuntingYard(const Queue<Token*>& input_q):queue(input_q), error(false){}

// save input_q to member variable queue
void ShuntingYard::infix(const Queue<Token*>& input_q){
    queue = input_q;
}

// generate postfix queue from infix queue
Queue<Token*> ShuntingYard::postfix(){
    return shunting_yard();
}

Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& input_q){
    queue = input_q;
    return shunting_yard();
}

// called by postfix()
Queue<Token*> ShuntingYard::shunting_yard(){
    Queue<Token*> empty;//used if error occurs
    typename Queue<Token*>::Iterator token = queue.begin();
    Queue<Token*> output;
    Stack<Token*> operators;
    while(token){
        Token* token1 = *token;
        TOKEN_TYPES tokenType = token1->getType();
        if(tokenType == INTEGER || tokenType == VARIABLE){
            output.push(token1);
        }
        else if (tokenType == TOKEN_TYPES::FUNCTION){
            //push it onto the operator stack if paramater > 0
            if(dynamic_cast<Function*>(token1)->getParameter() == 0){
                output.push(token1);
            }
            else{
                operators.push(token1);
            }
            
        }  
        // o1 operator
        else if(tokenType == OPERATOR){
            Operator* o1 = dynamic_cast<Operator*>(token1);
            bool nextStackIsOp = !operators.empty() && operators.top()->getType() != LPAREN;
            while(nextStackIsOp) {
                Operator *o2 = dynamic_cast<Operator*>(operators.top());
                if (o2->getPrecedent() > o1->getPrecedent() ||
                    (o2->getPrecedent() == o1->getPrecedent() && o1->getLeft())) {
                    output.push(operators.pop());
                    //get top value if not empty.
                    nextStackIsOp = !operators.empty() && operators.top()->getType() == OPERATOR;
                }
                else{
                    nextStackIsOp = false;
                }
            }
            operators.push(token1);
        }
        else if(tokenType == LPAREN){
            operators.push(token1);
        }
        else if(tokenType == RPAREN){
            bool nextStackIsNotLP = !operators.empty() && operators.top()->getType() != LPAREN;
            while(nextStackIsNotLP){
                //Assert that operator stack is not empty.
                //assert(!operators.empty()); //There are mismatched parenthesis.
                if(operators.empty()){
                    error = true;
                    return empty;
                }
                output.push(operators.pop());
                //get top value if not
                nextStackIsNotLP = !operators.empty() && operators.top()->getType() != LPAREN;
            }
            //Assert there is a left parenthesis at the top.
            //assert(!operators.empty() && operators.top()->getType() == LPAREN);
            if(operators.empty() || operators.top()->getType() != LPAREN){
                error = true;
                return empty;
            }
            operators.pop(); //Discard LPAREN
            //if(there is a function token on top of operator stack)
            bool nextStackIsFunct = !operators.empty() && operators.top()->getType() == FUNCTION;
            if(nextStackIsFunct){
                output.push(operators.pop());//pop function from operator stack and insert into output queue
            }
        }
        ++token;
    }
    //* After the while loop, pop the remaining items from the operator stack into the output queue. */
    while(!operators.empty()){
        /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
        //assert(operators.top()->getType() != LPAREN);
        if(operators.top()->getType() == LPAREN){
            error = true;
            return empty;
        }
        output.push(operators.pop());
    }
    return output;
}