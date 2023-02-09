/*
 * Name: Nathan Goller-Deitsch
 * Date Submitted: 1/30/2023
 * Lab Section: 001
 * Assignment Name: Lab 2
 */

#include <string>
#include <stack>
#include <stdbool.h>
#include <iostream>

using namespace std;

// Checks if an infix string has valid parentheses (each left is followed by a right)
// Returns true if valid or false otherwise.
bool validParens(string infix[], int length)
{
    // Keep track of the nesting level. If it ever drops below 0, the parens are illegal.
    // It should also be 0 at the end of the evaluation.

    int level = 0;

    for (int i = 0; i < length; i++)
    {
        // When we enter a paren, the nesting level increases.
        if (infix[i] == "(")
        {
            level++;
        }

        // When we exit a paren, the nesting level decreases.
        if (infix[i] == ")")
        {
            level--;
        }

        // If the nesting level is ever below 0, the string is illegal.
        if(level < 0){
            return false;
        }
    }
    
    // If the nesting level is not 0 at the end, the parens are illegal, 
    return (level == 0);
}

// Returns an int representing the precedence level of an element, where higher is greater precedence
int getPrecedenceLevel(string element)
{
    if (element == "*" || element == "/" || element == "%")
    {
        return 2;
    }
    else if (element == "+" || element == "-")
    {
        return 1;
    }
    else
    {  
        // Unknown chars have the lowest precedence (this is only implemented to avoid warnings)
        return -1;
    }
}
// Converts an infix arithmetic expression into postfix
// The function takes 3 parameters
// First parameter: array of strings for infix expression
//     each string is either an integer number or operator symbol
// Second parameter: number of strings in infix expression
// Third parameter: array of strings for postfix expression
//     generated by function, same format as first parameter
//     assumes that postfix is at least the size of postfix
// Return value: int, number of strings in postfix expression
//     Returns 0 if an error is encountered when converting expression
//     An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
// Operator symbols:
//  ( : left parenthesis, all operations between this and ")" take place first
//  ) : right parenthesis, all op.s back to previous "(" take place first
//  * : multiplication, higher precedence - takes place before "+" and "-"
//  / : division, higher precedence - takes place before "+" and "-"
//  % : remainder, higher precedence - takes place before "+" and "-"
//  + : addition, lower precedence - takes place after "*" , "/" , "%"
//  - : subtraction, lower precedence - takes place after "*" , "/" , "%"
// The function is not specified to work with any other operator symbols
// Any string in infix may be assumed to be an integer operand if none
//  of the above symbols
int infixToPostfix(string infix[], int length, string postfix[])
{  
    // If the parens are invalid, the function should return 0.
    if (!validParens(infix, length))
    {
        return 0;
    }

    stack<string> operatorStack;
    int postfixSize = 0;

    for (int i = 0; i < length; i++)
    {

        // If the character is (, add it to the operator stack
        if (infix[i] == "(")
        {
            operatorStack.push("(");
        }

        // If the character is ), pop all operators until we reach the matching left paren
        else if (infix[i] == ")")
        {

            // pop out all operators until we reach left paren
            while (operatorStack.top() != "(")
            {
                postfix[postfixSize] = operatorStack.top();
                operatorStack.pop();
                postfixSize++;
            }

            // remove left paren
            operatorStack.pop();
        }

        // If the character is an operator, pop all operators with greater or equal precedence, then add it to the stack
        else if (infix[i] == "*" || infix[i] == "/" || infix[i] == "%" || infix[i] == "+" || infix[i] == "-")
        {
            // If there are elements on the stack with greater or equal precedence, pop them out first

            while ((!operatorStack.empty() && (getPrecedenceLevel(infix[i]) <= getPrecedenceLevel(operatorStack.top()))))
            {
                postfix[postfixSize] = operatorStack.top();
                operatorStack.pop();
                postfixSize++;
            }

            operatorStack.push(infix[i]);
        }
        else
        // Otherwise, add to the postfix expression
        {
            postfix[postfixSize] = infix[i];
            postfixSize++;
        }
    }


    // Pop all remaining operators from the stack
    while (!operatorStack.empty())
    {
        postfix[postfixSize] = operatorStack.top();
        operatorStack.pop();
        postfixSize++;
    }

    return postfixSize;
}

// Main function to test infixToPostfix()
// Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//             to 2 3 4 * + 5 6 - 7 + 8 * +
/* int main()
{
string infixExp[] = {"2", "+", "3", "*", "4", "+", "(",
                         "5", "-", "6", "+", "7", ")", "*",
                         "8"};
    string postfixExp[15];
    int postfixLength;

    cout << "Infix expression: ";
    for (int i = 0; i < 15; i++)
    {
        cout << infixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: 15" << endl
         << endl;

    postfixLength = infixToPostfix(infixExp, 15, postfixExp);

    cout << "Postfix expression: ";
    for (int i = 0; i < postfixLength; i++)
    {
        cout << postfixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: " << postfixLength << endl;

    return 0;
} */
