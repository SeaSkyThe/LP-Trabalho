// 'word' é como se fosse uma palavra de memoria, um conteúdo, um número

// INPUT / OUTPUT
#define READ 10   //Le uma 'word' do terminal e coloca numa posição da memória   (1031 - Lê do terminal e coloca na posição 31 da memória)

#define WRITE 11 //Le uma 'word' de uma posição da memória e coloca no terminal

// CARREGAR / ARMAZENAR
#define LOAD 20  //Carrega uma 'word' de uma posição da memória e joga pro acumulador

#define STORE 21  //Armazena uma 'word' do acumulador em uma posição da memória

// OPERAÇÕES ARITIMÉTICAS
#define ADD 30      //Soma uma 'word' de uma posição da memória à 'word' no que está no acumulador (deixa o resultado no acumulador)

#define SUBTRACT 31 //Subtrai uma 'word' de uma posição da memória da 'word' no que está no acumulador (deixa o resultado no acumulador)

#define DIVIDE 32  //Divide uma 'word' de uma posição da memória pela 'word' no que está no acumulador (deixa o resultado no acumulador) - Duvidas

#define MULTIPLY 33 //Multiplica uma 'word' de uma posição da memória pela 'word' no que está no acumulador (deixa o resultado no acumulador)

// TRANSFERIR O CONTROLE DE OPERAÇÕES
#define BRANCH 40     // "BRANCH" para uma posição especifica da memória

#define BRANCHNEG 41  //faz o mesmo de cima, caso o valor do acumulador armazenado seja negativo

#define BRANCHZERO 42 //faz o mesmo de cima, caso o valor do acumulador armazenado seja zero

#define HALT 43   //PROGRAMA FINALIZOU SUAS TAREFAS

void reiniciar_memoria(int *memoria){
    for(int i = 0; i < 100; i++){
        memoria[i] = 0;
    }
}

int verifica_operacao(int operacao, int operando, int *memoria, int *acc){
    switch(operacao){
        int num;
        case READ:
            printf("Digite um numero para ser carregado na memoria: ");
            scanf("%d", &num);
            *(memoria + operando) = num;
            break;

        case WRITE:
            num = *(memoria + operando);
            printf("Numero da posicao de memoria %d: %d\n\n", operando, num);
            break;

        case LOAD:
            *acc = *(memoria + operando);
            break;

        case STORE:
            *(memoria + operando) = *acc;
            break;

        case ADD:
            *acc = *acc + (*(memoria + operando));
            break;

        case SUBTRACT:
            *acc = *acc - (*(memoria + operando));
            break;

        case DIVIDE:
            *acc = *acc/(*(memoria + operando));
            break;

        case MULTIPLY:
            *acc = *acc*(*(memoria + operando));
            break;

        case BRANCH:

            break;
        case BRANCHNEG:
            if(*acc < 0){

            }
            break;
        case BRANCHZERO:
            if(*acc == 0){

            }
        case HALT:
            exit(0);
            break;
    }
}
