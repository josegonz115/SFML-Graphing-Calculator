#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>


enum TOKEN_TYPES
{
    FUNCTION,
    INTEGER,
    OPERATOR,
    LPAREN,
    RPAREN,
    TOKEN,
    VARIABLE
};

const char ADD = '+';
const char SUBTRACT = '-';
const char MULTIPLY = '*';
const char DIVIDE = '/';
const char POWER = '^';
const char LEFT_PAREN = '(';
const char RIGHT_PAREN = ')';

const std::string SIN = "SIN";
const std::string COS = "COS";
const std::string TAN = "TAN";
const std::string ABS = "ABS";
const std::string EX = "EX"; // calls exp()
const std::string PI = "PI";
const double PI_VALUE = 3.14159265358979323846;
const std::string MIN = "MIN";
const std::string MAX = "MAX";
const std::string LOG = "LOG";

#endif //CONSTANTS_H