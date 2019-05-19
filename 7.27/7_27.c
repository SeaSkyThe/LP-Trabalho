#include <stdio.h>
#include <stdlib.h>
#include "7_27.h"

int main(void){


    //Criando e inicializando a memória
    int memoria[100];
    reiniciar_memoria(memoria);
    int acc = 0; //Acumulador(registrador) que irá guardar os resultados de operações quando necessário




    // EXERCICIO a)

    //Operações a serem feitas
    memoria[0] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria
    memoria[1] = 2023; //Carrega da posição de memoria 23' e joga no acumulador

    memoria[2] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[3] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[4] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[5] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[6] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[7] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[8] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[9] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[10] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[11] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[12] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[13] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[14] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[15] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[16] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[17] = 3023;  //Soma o numero da posição de memoria 23' com o do Acumulador

    memoria[18] = 1023;  //Le entrada no terminal e coloca na posição 23 da memoria(sobreescreve)
    memoria[19] = 3023;  //Soma o numero da posição de memoria '23' com o do Acumulador

    memoria[20] = 2123; //Armazena valor contido no acc em uma posição de memoria
    memoria[21] = 1123; //Printa no terminal o valor contido na posição de memória 23

    memoria[22] = 4300; //Fim do programa

    int operacao;  //Variavel que guarda a operação a ser feita
    int operando;  //Variavel que guarda o operando(posição de memoria) da operação

    int aux = 0;
    while(1){
        operacao = memoria[aux]/100; //Extrai a operação a ser feita
        operando = memoria[aux]%100; //Extrai o operando (posicao de memoria)

        verifica_operacao(operacao, operando, &memoria, &acc);  //Passando endereço de memoria e acc, ja que precisam ser modificados na função
        aux++;
    }





    // EXERCICIO b)

    return 0;
}
