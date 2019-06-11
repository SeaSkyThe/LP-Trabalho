#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SimpleCompiler.h"

#define SIZE 100

int main(void){


    struct tableEntry* symbolTable[SIZE];
    for(int i = 0; i < SIZE; i++){
        symbolTable[i] = (struct tableEntry*)malloc(sizeof(struct tableEntry));
    }
    int SML[1000];
    //READING STRUCTURE
    FILE *file;
    char line[1000];
    char *local = "/Users/seaskythe/Documents/LP-Trabalho/12.26 e 12.27/programs.txt";

    if ((file = fopen(local, "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }
    else{
        //Getting each sentence and put into "line" variable
        char *token = (char *) malloc(100);
        char *lineNumber;



        int symbolTableCount = 0;           //o resto é colocado normalmente
        int symbolTableCountVariables = 99; //Variaveis sao colocadas de tras pra frente na tabela de simbolos
        int location = 0; // Contador de instruções

        while (fgets(line, sizeof(line), file) != NULL){
            //separating into tokens

            struct tableEntry* lineEntry ;
            struct tableEntry* Entry;

            lineNumber = strtok(line, " ");
            lineEntry -> symbol = atoi(lineNumber);//Convertendo string para int
            lineEntry -> type = 'L';
            lineEntry -> location = location;
            do{
                printf("Entrada: %d\n", symbolTableCount);
                /* Nas próximas chamadas, deve-se passar um ponteiro “nulo”.
                Isto “indica” para a função que a pesquisa deve continuar
                no ponteiro anterior. */


                token = strtok(NULL, " "); //Demais pesquisas por , (vírgula) ou espaço em branco.


                //NECESSARIO VER SE TOKEN É IGUAL A 'rem' mas nao sei fazer isso
                symbolTable[symbolTableCount] = lineEntry;
                printf("\nType:%c", (symbolTable[symbolTableCount] -> type));
                printf("\nLine:%d\n", (symbolTable[symbolTableCount] -> symbol));



                /* Um valor nulo (NULL) é considerado sempre falso em comparações
                booleanas (verdadeiro ou falso). */
                if(token){
                    printf("Retorno = %s\n", token);
                }
           }while(token != NULL);
           symbolTableCount++;
           symbolTableCountVariables++;
        }
    }
    fclose(file);
    return 0;
}
