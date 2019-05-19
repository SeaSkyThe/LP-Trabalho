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
    memory[0] = 1020;  //Le entrada no terminal e coloca na posição 20 da memoria
    memory[1] = 2020; //Carrega da posição de memoria 20 e joga no acumulador
    memory[2] = 4110;    //Se o acumulador tiver num negativo, finaliza o programa

    memory[3] = 1021;  //Le entrada no terminal e coloca na posição 21 da memoria(sobreescreve)
    memory[4] = 2021;  //Carrega o numero da posição de memoria 21 no Acumulador
    memory[5] = 4109;  //Se o segundo numero lido for negativo, pular para posicao 9

    //Soma a posicao 20 no acumulador
    memory[6] = 3020;
    //Pega do acumulador e joga na posicao 20 da memoria
    memory[7] = 2120;

    memory[8] = 4003; //Volta para a memoria 03 (esse é o nosso loop)
    memory[9] = 1120; //Printa no terminal o conteudo da posicao de memoria 20

    memory[10] = 4300; //Fim do programa

    int operation;  //Variavel que guarda a operação a ser feita
    int operand;  //Variavel que guarda o operando (posição de memória) da operação

    int program_counter = 0;
    while(1){
        verify_and_execute_operation(&operation, &operand, memory, &acc, &program_counter);  //Passando endereço de memória e acc, ja que precisam ser modificados na função
        program_counter++;
    }

    return 0;
}
