#include <stdio.h>
#include <stdlib.h>
#include "postfix.h"


int main(void){
    char infix[100] = "6+2*5-8/4";
    char postfix[100] = {0};

    printf("\n\nInfix: \n");
    int i;
    for(i = 0; infix[i] != '\0'; i++){
        printf("%c", infix[i]);
    }


    convertToPostfix(infix, postfix);

    printf("\n\nPostFix: \n");
    for(i = 0; postfix[i] != '\0'; i++){
        printf("%c", postfix[i]);
    }
    printf("\n\n");
    return 0;
}
