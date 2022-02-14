#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
///whether the input is a number or a symbol
typedef union {
    float fData;
    char cData;
} Item;

///stack definition
typedef struct Stack{
    int top;
    Item stack[MAX];
} Stack;

Stack* initialize();
int isEmpty(Stack* s);
Item top(Stack* s);
Item pop(Stack* s);
void push(Stack* s, Item val);
char precedence (char symbol);
unsigned char isLower(char symbol1,char symbol2);
unsigned char is_operator(char symbol);
void infixToPostfix(char* infix, char* postfix);
float Evaluate(float operand1, float operand2, char operator);
float evaluatePostfix(char* postfix);
void replaceNewLineBySpace(char *s);



