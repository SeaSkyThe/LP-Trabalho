#include <stdio.h>
#include <stdlib.h>
#include "7_27.h"

int main(void){

    //Criando e inicializando a memória
    int memory[100];
    clear_memory(memory);
    int acc = 0; //Acumulador(registrador) que irá guardar os resultados de operações quando necessário


    // EXERCICIO a)

    //Operações a serem feitas
    memory[0] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria
    memory[1] = 2023; //Carrega da posição de memoria 23' e joga no acumulador

    memory[2] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memory[3] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memory[4] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memory[5] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memory[6] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memory[7] = 3023;  //Soma o numero da posição de memória 23' com o do Acumulador

    memory[8] = 1023;  //Le entrada no terminal e coloca na posição 23 da memória(sobreescreve)
    memory[9] = 3023;  //Soma o numero da posição de memória 23' com o do Acumulador

    memory[10] = 1023;  //Le entrada no terminal e coloca na posição 23 da memória(sobreescreve)
    memory[11] = 3023;  //Soma o numero da posição de memória 23' com o do Acumulador

    memory[12] = 1023;  //Le entrada no terminal e coloca na posição 23 da memória(sobreescreve)
    memory[13] = 3023;  //Soma o numero da posição de memória 23' com o do Acumulador

    memory[14] = 1023;  //Le entrada no terminal e coloca na posição 23 da memória(sobreescreve)
    memory[15] = 3023;  //Soma o numero da posição de memória 23' com o do Acumulador

    memory[16] = 1023;  //Le entrada no terminal e coloca na posição 23 da memória(sobreescreve)
    memory[17] = 3023;  //Soma o numero da posição de memória 23' com o do Acumulador

    memory[18] = 1023;  //Le entrada no terminal e coloca na posição 23 da memória(sobreescreve)
    memory[19] = 3023;  //Soma o numero da posição de memória '23' com o do Acumulador

    memory[20] = 2123; //Armazena valor contido no acc em uma posição de memória
    memory[21] = 1123; //Printa no terminal o valor contido na posição de memória 23

    memory[22] = 4300; //Fim do programa

    int operation;  //Variavel que guarda a operação a ser feita
    int operand;  //Variavel que guarda o operando (posição de memória) da operação

    int program_counter = 0;
    while(1){
        verify_and_execute_operation_just_positive(&operation, &operand, memory, &acc, &program_counter);  //Passando endereço de memória e acc, ja que precisam ser modificados na função
        program_counter++;
    }

    return 0;
}
