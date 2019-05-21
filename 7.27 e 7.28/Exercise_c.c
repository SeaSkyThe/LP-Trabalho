#include <stdio.h>
#include <stdlib.h>
#include "base.h"


int main(void){
    //Criando e inicializando a memória
    int memory[100];
    clear_memory(memory);

     //Acumulador(registrador) que irá guardar os resultados de operações quando necessário
    int acc = 0;


    memory[0] = 1025;  //Le quantos numeros serao lidos

    memory[1] = 1020;  //Le um numero e guarda em 10(A)
    memory[2] = 2020;  //Armazena o numero(A) no ACC
    memory[3] = 2130;  //Coloca A na posicao 30, por ser o maior

    memory[4] = 1021; //Le um numero e guarda em 21(B)
    memory[5] = 3121; //Subtrai o que acabou de ser lido(B), pelo que esta no ACC(e na pos 30), que é o maior
    memory[6] = 4110;  //Se o resultado for negativo, quer dizer que o numero(B) em 11 é maior, entao pula para instrucao 10


    memory[7] = 2020;  //Armazena A no ACC
    memory[8] = 2130;  //Pega A do ACC e coloca na pos 30(MAIOR)
    memory[9] = 4004;  //Volta para a pos de memoria 4, para pedir outro numero para comparar

    memory[10] = 2021; //Armazena B no ACC
    memory[11] = 2130; //Pega B do ACC e coloca na pos 30(POS ONDE O MAIOR FICA ARMAZENADO)
    memory[12] = 4004; //Volta para a pos de memoria 4, para pedir outro numero para comparar

    memory[15] = 4300;

    int operation, operand;
    int program_counter = 0;
    while(1){
        verify_and_execute_operation(&operation, &operand, memory, &acc, &program_counter);
        program_counter++;
    }

    return 0;
}
