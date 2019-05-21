#include <stdio.h>
#include <stdlib.h>
#include "Simpletron.h"


int main(void){
    //Criando e inicializando a memória
    int memory[100];
    clear_memory(memory);

     //Acumulador(registrador) que irá guardar os resultados de operações quando necessário
    int acc = 0;


    memory[0] = 1035; //Pede o numero '1' para auxiliar na contagem
    memory[1] = 1036; //Pede uma entrada, quantidade de numeros a serem lidos(contador)

    memory[2] = 1030; //Pede o numero A
    //Decrementando
    memory[3] = 2036; //Contador é enviado para o acc
    memory[4] = 3135; //Acc é subtraido em 1
    memory[5] = 2136; //Contador é devolvido para a pos 36

    memory[6] = 2030; //Carrega o numero A no acc
    memory[7] = 2140; //Carrega o numero A que esta no acc, na posicao do MAIOR (40 na memoria)

    memory[8] = 1031; //Pede o numero B
    //Decrementando
    memory[9] = 2036; //Carrega contador no acc
    memory[10] = 3135; //Subtrai 1 do acc
    memory[11] = 2136; //Devolve o contador atualizado para a pos 36

    memory[12] = 2040; //Armazena o maior numero no ACC

    memory[13] = 3131;  //Subtrai o que acabou de ser lido(B), pelo que esta no ACC, que é o maior
    memory[14] = 4118;  //Se o resultado for negativo, quer dizer que o numero(B) é maior, entao pula para instrucao 19

    memory[15] = 2036; //Carrega contador no acc
    memory[16] = 4223; //se acc for 0, acabou
    memory[17] = 4008; //Volta para a pos de memoria 8, para pedir outro numero para comparar

    //Atualizando maior, caso seja o B
    memory[18] = 2031; //Armazena B no ACC
    memory[19] = 2140; //Pega B do ACC e coloca na pos 40(POS ONDE O MAIOR FICA ARMAZENADO)
    memory[20] = 2036; //Carrega contador no acc
    memory[21] = 4223; //se acc for 0, acabou
    memory[22] = 4008; //Volta para a pos de memoria 8, para pedir outro numero para comparar


    memory[23] = 1140; //Exibe na tela o maior
    memory[24] = 4300;

    int operation, operand;
    int program_counter = 0;
    int instructionRegister = 0;
    while(1){
        verify_and_execute_operation(&operation, &operand, memory, &acc, &program_counter, &instructionRegister);
        program_counter++;
    }

    return 0;
}
