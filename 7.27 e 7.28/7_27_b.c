#include <stdio.h>
#include <stdlib.h>
#include "7_27.h"


void main(){


    //Criando e inicializando a memória
    int memory[100];
    clear_memory(memory);

     //Acumulador(registrador) que irá guardar os resultados de operações quando necessário
    int acc = 0;

    //Instruções sendo carregadas na memória
    memory[0] = 1017;
    memory[1] = 3017;

    memory[2] = 1017;
    memory[3] = 3017;

    memory[4] = 1017;
    memory[5] = 3017;

    memory[6] = 1017;
    memory[7] = 3017;

    memory[8] = 1017;
    memory[9] = 3017;

    memory[10] = 1017;
    memory[11] = 3017;

    memory[12] = 1017;
    memory[13] = 3017;

    memory[14] = 2117;
    memory[15] = 1117;

    memory[16] = 4300;

    int operation, operand;
    int number_counter = 0;
    while(number_counter < 7*2 + 2 + 1){
        verify_and_execute_operation(&operation, &operand, memory, &acc, &number_counter);
        number_counter++;
    }
}
