// Include all the required files
#include<iostream>
#include<stack>
#include<string>

// Define the namespace for standard library
using namespace std;

// Check weather the given character is an opening bracket or not
// Return true if it is an opening bracket else return false.
static int IsOpeningBracket(char openbracket) {
    return (openbracket == '(' || openbracket == '{' || openbracket == '[');
}

// Check weather the given character is a closing bracket or not
// Return true if it is an closing bracket else return false.
static int IsClosingBracket(char closedbracket) {
    return (closedbracket == ')' || closedbracket == '}' || closedbracket == ']');
}

// Check weather the given character is a number or not
// Return true if it is a number else return false.
static int IsNumber(char num) {
    // Subtract the ascii value of 0 to get the real value of the 
    // numbers
    return ((int)num - '0' >= 0 && (int)num - '0' <= 9);
}

// Check weather the character is Operator or not.
// Return true if it is an operator else return false.
static int IsOperator(char op) {
    // All the supported operators
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

// Give the precedence value of the character or operator
// Return the provided precedence value.
static int PrecedenceValue(char a) {
    // Since the operators are less so I implemented the if-else
    // loop. However if you want to make the precedence table of all
    // operators then make a hashtable for it.
    // Map the operator to a value in that hashtable. 
    if (a == '^') {
        return 3;
    }
    else if (a == '*' || a == '/') {
        return 2;
    }
    else if (a == '+' || a == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

// Operator Precedence Check
// If precedence of first operator is greater than other then return true 
// else return false.
static int CheckPrecedence(char first_op, char second_op) {
    // Check the precedence value of first operator and second operator
    // If the precedence value of first operator is greater then
    // return true else return false.
    return (PrecedenceValue(first_op) > PrecedenceValue(second_op));
}
