#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "postfix.h"


int main(void){
    char infix[100] = "(6+2)*5-8/4";
    char postfix[100] = {0};

    printf("\n\nInfix: \n");
    for(int i = 0; infix[i] != '\0'; i++){
        printf("%c", infix[i]);
    }
    convertToPostfix(infix, postfix);

    printf("\n\nPostFix: \n");
    for(int i = 0; postfix[i] != '\0'; i++){
        printf("%c", postfix[i]);
    }
    printf("\n\n");

    printf("Result: %d\n", evaluatePostfixExpression(postfix));
    return 0;
    return 1;
}
