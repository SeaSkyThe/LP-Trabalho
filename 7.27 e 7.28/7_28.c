#include <stdio.h>
#include <stdlib.h>
#include "Simpletron.h"


int main(void){

    printf("\n\n*** Welcome to Simpletron! ***\n");
    printf("*** Please enter your program one instruction ***\n");
    printf("*** (or data word) at a time. I will type the ***\n");
    printf("*** location number and a question mark (?).  ***\n");
    printf("*** You then type the word for that location. ***\n");
    printf("*** Type the sentinel -99999 to stop entering ***\n");
    printf("*** your program. ***\n\n");

    //Inicializando memoria
    int memory[100] = {0};

    //Loading program
    int instruction;
        for(int i = 0; instruction != -99999; i++){
            instruction = 10000;
            while((instruction < -9999 || instruction > 9999) && instruction != -99999){
                printf("%3d (?): ", i);
                scanf("%d", &instruction);
                memory[i] = instruction;
            }
        }

    printf("\n*** Program loading completed ***\n");
    printf("*** Program execution begins  ***\n");

    //Execution starts
    int acc_register = 0;       //Acumulador --- Nao tem oq explicar
    int instructionCounter = 0; //Guarda o local onde está o programa
    int instructionRegister = 0;
    int operationCode = 0;     //Codigo da operação a ser realizada
    int operand = 0;           //Local da memória sob a qual a operação vai ser realizada

    while(1){
        verify_and_execute_operation(&operationCode, &operand, memory, &acc_register, &instructionCounter, &instructionRegister);
        instructionCounter++;
    }

    return 0;
}
