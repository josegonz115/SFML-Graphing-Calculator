#include "rpn.h"

//Constructors
RPN::RPN():error(false){ queue; }

RPN::RPN(const Queue<Token*>& input_q):queue(input_q),error(false){}

// save input_q to member variable queue
void RPN::set_input(const Queue<Token*> &input_q){
    queue = input_q;
}

// return result from member variable queue
double RPN::RPN::operator()(double value){ return rpn(value); }

//called by operator ()
double RPN::rpn(double value){                           
    typename Queue<Token*>::Iterator token = queue.begin();
    Stack<Token*> output;
    while(token){ 
        Token* token1 = *token;
        TOKEN_TYPES tokenType = token1->getType(); 
        if(tokenType == INTEGER){
            output.push(token1);
        }
        else if(tokenType == VARIABLE){
            output.push(new Integer(value));
        }
        else if(tokenType == OPERATOR){
            int operandsNeeded = 2;
            int operands = output.size();
            //if operands are not enough assert
            //assert(operands >= operandsNeeded);
            if(operands < operandsNeeded){
                error = true;
                return -1;
            }
            //else below
            double operand2 = dynamic_cast<Integer*>(output.pop())->check();
            double operand1 = dynamic_cast<Integer*>(output.pop())->check();
            double numResult = dynamic_cast<Operator*>(token1)->compute(operand1, operand2);
            output.push(new Integer(numResult));
        }
        else if(tokenType == FUNCTION){
            //calculate function on operand and put the result into the output stack
            Function* funct = dynamic_cast<Function*>(token1);
            string functName = funct->getValue();
            int operandsNeeded = funct->getParameter();
            int operands = output.size();
            //assert(operands >= operandsNeeded);
            if(operands < operandsNeeded){
                error = true;
                return -1;
            }
            double operand2;
            if(operandsNeeded > 0){
                operand2 = dynamic_cast<Integer*>(output.pop())->check();
            }
            double result;
            if(operandsNeeded == 2){
                double operand = dynamic_cast<Integer*>(output.pop())->check();
                result = funct->computeFunction(operand, operand2);
            }
            else if(operandsNeeded == 1){
                result = funct->computeFunction(operand2);
            }
            else if(operandsNeeded == 0){
                result = funct->computeFunction();
            }
            output.push(new Integer(result));
        }
        ++token;
    }
    //Should only be one operand in output stack
    //assert(output.size() == 1);
    if(output.size() != 1){
        error = true;
        return -1;
    }
    return dynamic_cast<Integer*>(output.pop())->check();
}