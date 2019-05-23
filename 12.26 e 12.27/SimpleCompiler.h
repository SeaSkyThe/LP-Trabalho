#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct tableEntry{
    int symbol; //integer that represents ascii representation of a variable,  a line number or constant
    char type; /* 'C', 'L' or 'V*/  // Constant, Line number, Variable
    int location;  /* 00 to 99 for now*/ // Simpletron memory location to which symbol refers
};
