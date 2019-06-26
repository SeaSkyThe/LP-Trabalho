#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// INPUT / OUTPUT
#define READ 10   //Le uma 'word' do terminal e coloca numa posição da memória   (1031 - Lê do terminal e coloca na posição 31 da memória)

#define WRITE 11 //Le uma 'word' de uma posição da memória e coloca no terminal

// CARREGAR / ARMAZENAR
#define LOAD 20  //Carrega uma 'word' de uma posição da memória e joga pro acumulador

#define STORE 21  //Armazena uma 'word' do acumulador em uma posição da memória

// HOMEBREW
#define LOADINT 22  //Armazena um inteiro no acumulador

// OPERAÇÕES ARITIMÉTICAS
#define ADD 30      //Soma uma 'word' de uma posição da memória à 'word' no que está no acumulador (deixa o resultado no acumulador)

#define SUBTRACT 31 //Subtrai uma 'word' de uma posição da memória da 'word' no que está no acumulador (deixa o resultado no acumulador)

#define DIVIDE 32  //Divide uma 'word' da pos de memoria pela 'word' no acc(deixa o resultado no acumulador) - Duvidas

#define MULTIPLY 33 //Multiplica uma 'word' de uma posição da memória pela 'word' no que está no acumulador (deixa o resultado no acumulador)

#define MODULUS 34 //Faz a operação %, de uma 'word' numa posição de memoria pela que está no acumulador, e deixa o resultado no acumulador

#define POW 35 //Faz a operação de exponenciação de uma 'word' da pos memoria pela que está no acc (memoria ^ acc)

// TRANSFERIR O CONTROLE DE OPERAÇÕES
#define BRANCH 40     // "BRANCH" para uma posição especifica da memória

#define BRANCHNEG 41  //faz o mesmo de cima, caso o valor do acumulador armazenado seja negativo

#define BRANCHZERO 42 //faz o mesmo de cima, caso o valor do acumulador armazenado seja zero

#define HALT 43   //PROGRAMA FINALIZOU SUAS TAREFAS

void clear_memory(int *memory){
    int i;
    for(i = 0; i < 100; i++){
        memory[i] = 0;
    }
}

void verify_and_execute_operation(int *operationCode, int *operand, int *memory, int *acc, int *instruction_counter, int *instruction_register, FILE* f){
    *instruction_register = memory[*instruction_counter];
    *operationCode = *(memory + *instruction_counter)/100; //Extrai a operação a ser feita
    *operand = *(memory + *instruction_counter)%100; //Extrai o *operando (posicao de memorória)
    switch(*operationCode){
        int num = 0;
        case READ:
            printf("Por favor digite um numero para ser carregado na memoria: ");
            scanf("%d", &num);
            fprintf(f, "Por favor digite um numero para ser carregado na memoria: %d\n", num);
            *(memory + *operand) = num;
            break;

        case WRITE:
            num = *(memory + *operand);
            printf("\nNumero armazenado na posicao de memoria de armazenamento: %d\n\n", num);
            fprintf(f, "\nNumero armazenado na posicao de memoria de armazenamento: %d\n\n", num);
            break;

        case LOAD:
            *acc = *(memory + *operand);
            break;

        case STORE:
            *(memory + *operand) = *acc;
            break;

        case LOADINT:
            *acc = *operand;
            break;

        case ADD:
            *acc = *acc + (*(memory + *operand));
            break;

        case SUBTRACT:
            *acc = *acc - (*(memory + *operand));
            break;

        case DIVIDE:
            if(*(memory+*operand) != 0){
                *acc = (*(memory + *operand))/(*acc);
            }
            else{
                printf("\n*** Attempt to divide by zero ***\n");
                fprintf(f, "\n*** Attempt to divide by zero ***\n");
                printf("*** Simpletron execution abnormally terminated ***\n");
                fprintf(f, "*** Simpletron execution abnormally terminated ***\n");
                printf("REGISTERS:\n");
                fprintf(f, "REGISTERS:\n");
                printf("Accumlator: %d\n", *acc);
                fprintf(f, "Accumlator: %d\n", *acc);
                printf("instructionCounter: %d\n", *instruction_counter);
                fprintf(f, "instructionCounter: %d\n", *instruction_counter);
                printf("instructionRegister: %d\n", *instruction_register);
                fprintf(f, "instructionRegister: %d\n", *instruction_register);
                printf("operationCode: %d\n", *operationCode);
                fprintf(f, "operationCode: %d\n", *operationCode);
                printf("operand: %d\n", *operand);
                fprintf(f, "operand: %d\n", *operand);

                printf("\nMEMORY:\n");
                fprintf(f, "\nMEMORY:\n");
                int i;
                for(i = 0; i < 100; i = i + 10){
                    printf("\n");
                    int k = 0;
                    for(k = 0; k < 10; k++){
                        printf("%6d ", memory[i+k]);
                        fprintf(f, "%6d ", memory[i+k]);
                    }
                }
                printf("\n");
                fprintf(f, "\n");
                exit(0);
            }
            break;

        case MULTIPLY:
            *acc = *acc*(*(memory + *operand));
            break;

        case MODULUS:
            if(*(memory+*operand) != 0){
                *acc = (*acc)%(*(memory + *operand));
            }
            else{
                printf("\n*** Attempt to divide by zero ***\n");
                printf("*** Simpletron execution abnormally terminated ***\n");
                printf("REGISTERS:\n");
                printf("Accumlator: %d\n", *acc);
                printf("instructionCounter: %d\n", *instruction_counter);
                printf("instructionRegister: %d\n", *instruction_register);
                printf("operationCode: %d\n", *operationCode);
                printf("operand: %d\n", *operand);

                printf("\nMEMORY:\n");
                int i;
                for(i = 0; i < 100; i = i + 10){
                    printf("\n");
                    int k = 0;
                    for(k = 0; k < 10; k++){
                        printf("%6d ", memory[i+k]);
                    }
                }
                printf("\n");
                exit(0);
            }
        break;

        case POW:
            *acc = pow(*(memory + *operand),(*acc));
            break;

        case BRANCH:
            *instruction_counter = *operand - 1;  //-1 porque no fim do loop ele é incrementado em 1
            break;
        case BRANCHNEG:
            if(*acc < 0){
                *instruction_counter = *operand - 1;
            }
            break;
        case BRANCHZERO:
            if(*acc == 0){
                *instruction_counter = *operand - 1;
            }
            break;

        case HALT:
            printf("*** Simpletron execution terminated ***\n");
            fprintf(f, "*** Simpletron execution terminated ***\n");
            printf("REGISTERS:\n");
            fprintf(f, "REGISTERS:\n");
            printf("Accumlator: %d\n", *acc);
            fprintf(f, "Accumlator: %d\n", *acc);
            printf("instructionCounter: %d\n", *instruction_counter);
            fprintf(f, "instructionCounter: %d\n", *instruction_counter);
            printf("instructionRegister: %d\n", *instruction_register);
            fprintf(f, "instructionRegister: %d\n", *instruction_register);
            printf("operationCode: %d\n", *operationCode);
            fprintf(f, "operationCode: %d\n", *operationCode);
            printf("operand: %d\n", *operand);
            fprintf(f, "operand: %d\n", *operand);

            printf("\nMEMORY:\n");
            fprintf(f, "\nMEMORY:\n");
            int i;
            for(i = 0; i < 100; i = i + 10){
                printf("\n");
                fprintf(f, "\n");
                int k = 0;
                for(k = 0; k < 10; k++){
                    printf("%6d ", memory[i+k]);
                    fprintf(f, "%6d ", memory[i+k]);
                }
            }
            printf("\n\n\n");
            fprintf(f, "\n\n\n");
            exit(0);
            break;
        break;
    }
}
