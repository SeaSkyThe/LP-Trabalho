#include <stdio.h>
#include <stdlib.h>
#include "Simpletron.h"


int main(void){


    //Criando e inicializando a memória
    int memory[100];
    clear_memory(memory);

     //Acumulador(registrador) que irá guardar os resultados de operações quando necessário
    int acc = 0;

    //Instruções sendo carregadas na memória
    memory[0] = 1029; //Entrar 1 no inicio, para auxiliar na contagem
    memory[1] = 1030; //Entrar 7, que é o MAX de numeros a serem lidos
    memory[2] = 2030; //Armazena MAX no Accumlator
    memory[3] = 2131; //Armazena MAX na pos 31
    memory[4] = 1032; //Entrar um numero para fazer a media
    memory[5] = 2030; //Passa o conteudo de 30 (que é a nossa variavel q esta decrementando), pro acc
    memory[6] = 3129; //Subtrai 1, do acc(decrementa variavel de contagem)
    memory[7] = 2130; //Devolve para a posicao 30, apos decrementar 1;

    memory[8] = 2032; //Armazena o numero da pos 32 no acc
    memory[9] = 1033; //Entra outro numero
    memory[10] = 3033; //Somar esse outro numero com o numero no acc
    memory[11] = 2132; //Passa o numero do acc para a pos 32 de memoria
    memory[12] = 2030; //Passa o conteudo de 30 (que é a nossa variavel q esta decrementando), pro acc
    memory[13] = 3129; //Subtrai 1, do acc(decrementa variavel de contagem)
    memory[14] = 2130; //Devolve para a posicao 20, apos decrementar 1;
    memory[15] = 4217; //Se acc for 0 vai fazer a media e finalizar o programa;
    memory[16] = 4008; //Volta pro loop

    memory[17] = 2032; //Carrega a soma q esta na pos 32 para o acc
    memory[18] = 3231; //Divide a soma que esta em acc, pelo MAX, que esta em 31
    memory[19] = 2132; //armazena o resultado da divisao na pos 32
    memory[20] = 1132; //printa o conteudo da pos 32 no terminal
    memory[21] = 4300; //fim

    int operation, operand;
    int program_counter = 0;
    int instructionRegister = 0;
    while(1){
        verify_and_execute_operation(&operation, &operand, memory, &acc, &program_counter, &instructionRegister);
        program_counter++;
    }

    return 0;
}
