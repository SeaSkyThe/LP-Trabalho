#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Simpletron.h"


int main(int argc, char *argv[]){

    //Inicializando memoria
    int memory[100] = {0};

    //Loading program
    char filename[] = "programs.sml";
    if (argc > 1)
      strcpy(filename, argv[1]);
    FILE* file = fopen(filename, "r");
    int instruction, i;
    while (!feof(file)) {
      if (feof(file)) break;
      fscanf(file, "%d", &instruction);
      memory[i++] = instruction;
      // printf("+%d\n", instruction);
    }

    FILE* f = fopen("execution_output.txt", "w");

    printf("\n*** Program loading completed for %s ***\n", filename);
    fprintf(f, "*** Program loading completed for %s ***\n", filename);
    printf("*** Program execution begins  ***\n");
    fprintf(f, "*** Program execution begins  ***\n");

    //Execution starts
    int acc_register = 0;       //Acumulador --- Nao tem oq explicar
    int instructionCounter = 0; //Guarda o local onde está o programa
    int instructionRegister = 0;
    int operationCode = 0;     //Codigo da operação a ser realizada
    int operand = 0;           //Local da memória sob a qual a operação vai ser realizada

    while(1){
        verify_and_execute_operation(&operationCode, &operand, memory, &acc_register, &instructionCounter, &instructionRegister, f);
        instructionCounter++;
    }

    fclose(f);
    return 0;
}
