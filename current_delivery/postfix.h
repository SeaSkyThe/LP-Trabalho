#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "stack.h"

//Functions user to convert INFIX to POSTFIX 12.12
int isOperator(char c){
    if(c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '%'){
        return 1;
    }
    else{
        return 0;
    }
}

int precedence(char operator1, char operator2){
    if(operator1 == '^'){
        if(operator2 == '^'){
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(operator1 == '*' || operator1 == '/'){
        if(operator2 == '^'){
            return -1;
        }
        else if(operator2 == '*' || operator2 == '/'){
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(operator1 == '+' || operator1 == '-'){
        if(operator2 == '^' || operator2 == '*' || operator2 == '/'){
            return -1;
        }
        else if(operator2 == '+' || operator2 == '-'){
            return 0;
        }
    }
}

void convertToPostfix(char infix[], char postfix[]){
    struct stack *op_parenthesis = (struct stack*)malloc(sizeof(struct stack));  //Operations and parenthesis
    start_stack(op_parenthesis);
    push(op_parenthesis, '(');
    strcat(infix,")");
    int count_postfix = 0;
    int i;

    while(!isEmpty(op_parenthesis)){
        for(i = 0; *(infix + i) != '\0'; i++){
            if(!isOperator(*(infix + i)) && *(infix + i) != '(' && *(infix + i) != ')'){
                *(postfix + count_postfix) = *(infix + i);
                count_postfix++;
            }
            else if(*(infix + i) == '('){
                push(op_parenthesis, '(');
            }
            else if(isOperator(*(infix + i))){
                while(isOperator(op_parenthesis -> top -> data) && (precedence(op_parenthesis -> top -> data, *(infix + i))) != -1){
                    *(postfix + count_postfix) = pop(op_parenthesis);
                    count_postfix++;
                }
                push(op_parenthesis, *(infix + i));
            }
            else if(*(infix + i) == ')'){
                while(op_parenthesis -> top -> data != '('){
                    *(postfix + count_postfix) = pop(op_parenthesis);
                    count_postfix++;
                }
                pop(op_parenthesis);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------//
//FUNCTIONS USED TO EVALUATE POSTFIX EXPRESSIONS 12.13


int calculate(int op1, int op2, char operador){
    if(operador == '+'){
        return (op1 + op2);
    }
    else if(operador == '-'){
        return (op1 - op2);
    }
    else if(operador == '*'){
        return (op1 * op2);
    }
    else if(operador == '/'){
        return (op1 / op2);
    }
    else if(operador == '^'){
        return (pow(op1,op2));
    }
    else{
        return 0;
    }
}
