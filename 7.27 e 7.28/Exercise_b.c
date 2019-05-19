#include <stdio.h>
#include <stdlib.h>
#include "7_27.h"


int main(void){


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

    memory[16] = 4300;

    int operation, operand;
    int program_counter = 0;
    while(1){
        verify_and_execute_operation(&operation, &operand, memory, &acc, &program_counter);
        program_counter++;
    }

    return 0;
}
