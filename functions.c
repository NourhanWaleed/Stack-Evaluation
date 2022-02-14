#include "functions.h"
#define MAX 100
///stack initialization
Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = 0;
    return s;
}

///checks whether stack is empty or not
int isEmpty(Stack* s) {
    if (s->top == 0) return 1;
    return 0;
}

///returns top item
Item top(Stack* s) {
    return s->stack[s->top-1];
}

///pops top item from stack
Item pop(Stack* s) {
    if (s->top == 0){
        Item item;
        item.fData = 0;
        return item;
    }
    else
        return s->stack[--s->top];
}

///pushes item into stack
void push(Stack* s, Item val) {
    if (s->top == MAX - 1)
        printf("Stack overflow,can't push item\n");
    else
        s->stack[s->top++] = val;
}

///checks precedence
char precedence (char symbol)
{
    switch (symbol)
    {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        case '^':
            return 3;
    }
    return -1;
}

///returns which symbol has lower precedence
unsigned char isLower(char symbol1,char symbol2)
{
    return (precedence(symbol1)<precedence(symbol2))? 1 : 0;
}

///returns whether symbol is an operator or a bracket
unsigned char is_operator(char symbol)
{
    if(precedence(symbol)!= -1){ return 1;} else{ return 0;}
}

///converts expression from infix to postfix
void infixToPostfix(char* infix, char* postfix)
{
    strcpy(postfix,"");
    char num[7] = "";char  tempchar;
    Item temp;
    char ch = *infix;
    Stack *s = initialize();
    int length = strlen(infix);
    for (int i = 0; i < length; i++){
        if(*infix == NULL){
            break;}
        if (*infix == ' ')
        {
            infix++;
            continue;
        }
        ///for negative nums
        if (*infix == '-')
        {
            if (*infix == ch) ///if its the first character in the expression then its a negative num
            {
                strcat(postfix,"-");
                infix++;
                continue;
            }else if(isdigit(*(infix+1))){
                ///if its followed by a number directly w/o a space then its negative
                strcat(postfix,"-");
                infix++;
                continue;
            }
        }
        ///for numbers
        while (isdigit(*infix ) || (*infix   == '.'))
        {
            ch = *(infix++);
            strncat(num,&ch, sizeof(char));
        }
        if (strcmp(num,""))
        {
            strcat(postfix,num);
            strcat(postfix," ");
            strncpy(num,"",7* sizeof(char));
        }
            ///for brackets
        else if (*infix == '(')
        {
            temp.cData = *(infix++);
            push(s,temp);
        } else if (*(infix) == ')')
        {
            temp = pop(s);
            while(temp.cData != '(')
            {
                strncat(postfix,&(temp.cData), sizeof(char));
                strncat(postfix," ", sizeof(char));
                if (isEmpty(s)){ break;}
                else{temp = pop(s);}
            }
            infix++;
        }
            ///for operators
        else if (is_operator(*(infix)))
        {
            temp = top(s);
            if (isEmpty(s) || isLower(temp.cData,*infix) || (temp.cData == '('))
            {
                temp.cData = *infix;
                push(s,temp);
                infix++;
            } else
            {
                tempchar = (top(s).cData);
                while ((isLower(*infix,tempchar) || precedence(*infix) == precedence(tempchar)))
                {
                    tempchar = pop(s).cData;
                    if (tempchar == '('){ break;}
                    strncat(postfix,&tempchar, sizeof(char));
                    strncat(postfix," ", sizeof(char));
                    if(isEmpty(s)){
                        break;
                    }
                    tempchar = (top(s).cData);
                }

                temp.cData = *infix;
                push(s,temp);
                infix++;
            }
        }
    }
    while (!isEmpty(s))
    {
        tempchar = pop(s).cData;
        strncat(postfix,&tempchar, sizeof(char));
        strcat(postfix," ");
    }
}

float Evaluate(float operand1, float operand2, char operator) {
    switch (operator)
    {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        case '^':
            return pow(operand1, operand2);
        default:
            perror("invalid operator");
            break;
    }
    return 0;
}
float evaluatePostfix(char* postfix)
{
    char *expression = postfix;
    char* token = malloc(10*sizeof(char));
    unsigned char boolean;

    ///initializes the stack instance
    Stack* stack = initialize();
    Item item;
    token = strtok(expression, " ");
    while (token != NULL)
    {
        boolean = is_operator(*token);

        if (strlen(token) > 1)	///to make sure negative numbers are not evaluated as operators
        {
            boolean = 0;
        }

        if (boolean == 1)
        {
            item.fData = Evaluate(pop(stack).fData,
                                pop(stack).fData,
                                *token);

            push(stack, item);
        }
        else if (boolean == 0)
        {
            item.fData = atof(token);
            push(stack, item);
        }
        else {
            perror("Unknown token");
        }

        token = strtok(NULL, " ");
    }

    item = pop(stack);
    float result = item.fData;
    return result;
}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
