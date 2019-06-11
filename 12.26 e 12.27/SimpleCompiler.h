#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct tableEntry{
    int symbol; //integer that represents ascii representation of a variable,  a line number or constant
    char type; /* 'C', 'L' or 'V*/  // Constant, Line number, Variable
    int location;  /* 00 to 99 for now*/ // Simpletron memory location to which symbol refers
};


int verifyCommand(char *token){
    int operand;
    switch(*token){
        case 'rem':
            return 0;
        case 'input':
            operand = 10;
            break;
        case 'print':
            operand = 11;
            break;
        case 'goto':
            operand = 40;
            break;
        case 'end':
            operand = 43;
            break;

        return operand;

    }
}
