#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix.h"

#define TABLE_SIZE 100

struct tableEntry {
  int symbol;
  char type;     // C, L, ou V
  int location;  // 00 a 99
};
//  Tabela de simbolos
struct tableEntry symbolTable[TABLE_SIZE];
//  Memoria SML
int SMLMemory[1000];
int flag[1000];
//  Controla as instrucoes da memoria do SML
int instructions_counter = 0;
//  Printa detalhes
int debug = 0;

char is_token_word(char *word) {
  // checa se e uma variavel
  if (strlen(word) == 1 && *word >= 'a' && *word <= 'z') {
    if (debug) printf("Found some \"%s\" and it is V.\n", word);
    return 'V';
  }

  // checa se e uma constante
  char seeker = *word;
  int i = 0;

  if (isdigit(*word)) {
    if (debug) printf("Found some \"%c\" and it is C.\n", word);
    return 'C';
  }
  return '0';
}

//   remove o line break que surge por causa do fgets
void purgeLineBreak(char *string) {
  if (string == NULL) return;
  char *pos;
  if ((pos=strchr(string, '\n')) != NULL)
    *pos = '\0';
}

short has_an_entry(char* token) {
  int i = 0;
  for (i = 0; i < TABLE_SIZE; i++) {
    if (symbolTable[i].type == 'V') {
      if (*token == symbolTable[i].symbol) return 1;
    } else if (symbolTable[i].type == 'C' || symbolTable[i].type == 'L') {
      if (atoi(token) == symbolTable[i].symbol) return 1;
    }
  }
  return 0;
}

int  get_location_from_table(char* token) {
  int i = 0;
  for (i = 0; i < TABLE_SIZE; i++) {
    if (symbolTable[i].type == 'V') {
      if (*token == symbolTable[i].symbol) return symbolTable[i].location;
    } else if (symbolTable[i].type == 'C' || symbolTable[i].type == 'L') {
      if (atoi(token) == symbolTable[i].symbol) return symbolTable[i].location;
    }
  }
  return 0;
}

void add_to_table(char* token, char type, int step, int* location, int* table_entry) {
  //  O parametro step existe para controlar quando o ponteiro de location vai
  //  andar ou nao
  if (type == 'V')
    //  Pega apenas o primeiro char de token
    symbolTable[*table_entry].symbol = *token;
  else
    symbolTable[*table_entry].symbol = atoi(token);
  symbolTable[*table_entry].type = type;
  symbolTable[*table_entry].location = *location;
  if (type == 'V' || type == 'C')
    *location -= step;
  else
    *location += step;
  *table_entry += 1;
}

void add_compiled_command(int command) {
  SMLMemory[instructions_counter] = command;
  instructions_counter += 1;
}

void flag_token(char *token, int location_in_memory) {
  flag[location_in_memory] = atoi(token);
}

int evaluatePostfixExpression(char *expr, int* current_variable_entry, int* current_table_entry){
  int i, x, y;
  struct stack *stack = (struct stack*)malloc(sizeof(struct stack));
  start_stack(stack);
  for(i= 0; *(expr + i) != '\0'; i++){
    if (*(expr + i) == ' ') continue;
    char current_char = *(expr + i);
    if (debug) printf("\nCURRENT_CHAR \"%c\"\n", current_char);
    if(isOperator(current_char)){
      x = pop(stack);
      y = pop(stack);
      if (debug) printf("\nWARD \"%d\", \"%d\" (%d) \n", x, y, *current_variable_entry);
      //  LOAD y
      add_compiled_command((20 * 100) + y);
      //  OPERATE on x
      switch (current_char) {
        case '+':
          add_compiled_command((30 * 100) + x);
          break;
        case '-':
          add_compiled_command((31 * 100) + x);
          break;
        case '/':
          add_compiled_command((32 * 100) + x);
          break;
        case '*':
          add_compiled_command((33 * 100) + x);
          break;
        case '%':
          add_compiled_command((34 * 100) + x);
          break;
      }
      add_compiled_command((21 * 100) + *current_variable_entry);
      if (debug) printf("%d", (21 * 100) + *current_variable_entry);
      push(stack, *current_variable_entry);
      //  Salta o espaco de memoria temporario
      *current_variable_entry -= 1;
    } else {
      if (!has_an_entry(&current_char))
        //  Adiciona na tabela de simbolos
        add_to_table(&current_char, is_token_word(&current_char), 1, current_variable_entry, current_table_entry);
      if (is_token_word(&current_char) == 'C') {
        add_compiled_command((22 * 100) + current_char - '0');
        add_compiled_command((21 * 100) + get_location_from_table(&current_char));
      }
      int value = get_location_from_table(&current_char);
      if (debug) printf("\nAI MDS: %d for %c\n", value, current_char);
      push(stack , value);

    }
  }
  return pop(stack);
}

void main (int argc, char *argv[]) {
  //  nome do programa a ser buscado.
  char filename[] = "programs.txt";
  if (argc > 1)
    strcpy(filename, argv[1]);
  //  ponteiro para o arquivo com o programa
  FILE *file = NULL;
  //  variavel que lera cada linha do programa
  char line_text[200];
  //  variavel que guardara cada token de uma linha de codigo
  char *tokens_in_the_line;
  //  Conta quantos itens da tabela de simbolos foram usados
  int current_table_entry = 0;
  //  Conta quantas variaveis e constantes existem (de baixo pra cima da tabela)
  int current_variable_entry = 99;
  //  Comando de 4 digitos do tipo SML
  int SMLCommand = 0;
  //  backup da linha completa para comandos let
  char full_line_backup[200];
  //  Zera o vetor de flags e memoria
  int i;
  for (i = 0; i < 1000; i++) {
    flag[i] = -1;
    SMLMemory[i] = 0;
  }
  file = fopen(filename, "r");
  while (!feof(file)) {
    //  Recupera uma linha completa do arquivo + \n
    fgets(line_text, sizeof(line_text), file);
    if (feof(file)) break;
    if (debug) printf("%s\n", line_text);
    strcpy(full_line_backup, line_text);
    //  Busca a primeira token da linha (numero da linha)
    tokens_in_the_line = strtok(line_text, " ");
    //  Adiciona o numero da linha na tabela de simbolos
    add_to_table(tokens_in_the_line, 'L', 0, &instructions_counter, &current_table_entry);

    while (tokens_in_the_line != NULL) {
      //  Pega a proxima token
      tokens_in_the_line = strtok(NULL, " ");

      if (tokens_in_the_line == NULL) break;
      //  remove quebra de linhas da string se tiver (as ultimas tokens da linha tem)
      purgeLineBreak(tokens_in_the_line);
      //  Passa para a proxima linha depois do comando rem
      if (strcmp(tokens_in_the_line, "rem") == 0) break;
      //  Processa o comando INPUT
      if (strcmp(tokens_in_the_line, "input") == 0) {
        //  Codigo do comando input
        SMLCommand = 10 * 100;
        //  Pega a proxima token que deve ser uma variavel
        tokens_in_the_line = strtok(NULL, " ");
        purgeLineBreak(tokens_in_the_line);
        //  Verifica se a variavel ja esta na tabela de simbolos
        if (!has_an_entry(tokens_in_the_line))
          //  Adiciona variavel na tabela de simbolos
          add_to_table(tokens_in_the_line, 'V', 1, &current_variable_entry, &current_table_entry);
        //  Adiciona o comando completo a memoria
        SMLCommand += get_location_from_table(tokens_in_the_line);
        add_compiled_command(SMLCommand);
        break;
      } else if (strcmp(tokens_in_the_line, "if") == 0) {
        //  Pega a proxima token
        tokens_in_the_line = strtok(NULL, " ");
        purgeLineBreak(tokens_in_the_line);
        //  Verifica se a variavel ja esta na tabela de simbolos
        if (!has_an_entry(tokens_in_the_line))
          //  Adiciona variavel na tabela de simbolos
          add_to_table(tokens_in_the_line, is_token_word(tokens_in_the_line), 1, &current_variable_entry, &current_table_entry);
        char* token_to_load = tokens_in_the_line;
        //  Pega a proxima token (operador logico)
        tokens_in_the_line = strtok(NULL, " ");
        purgeLineBreak(tokens_in_the_line);
        //  Caso o operador logico seja ==
        if (strcmp(tokens_in_the_line, "==") == 0) {
          //  LOAD token to ACC
          SMLCommand = (20 * 100) + get_location_from_table(token_to_load);
          add_compiled_command(SMLCommand);
          //  Pega a proxima token (operando)
          tokens_in_the_line = strtok(NULL, " ");
          purgeLineBreak(tokens_in_the_line);
          //  Verifica se o operando esta na tabela de simbolos
          if (!has_an_entry(tokens_in_the_line))
            //  Adiciona variavel na tabela de simbolos
            add_to_table(tokens_in_the_line, is_token_word(tokens_in_the_line), 1, &current_variable_entry, &current_table_entry);
          //  SUB token from ACC
          SMLCommand = (31 * 100) + get_location_from_table(tokens_in_the_line);
          add_compiled_command(SMLCommand);
          //  Vai para a proxima token para encontrar o goto e depois a linha-alvo
          strtok(NULL, " "); tokens_in_the_line = strtok(NULL, " ");
          //  Verifica se a linha esta na tabela de simbolos
          if (!has_an_entry(tokens_in_the_line)) {
            //  Se nao estiver, precisa receber uma FLAG
            flag_token(tokens_in_the_line, instructions_counter);
          }
          //  BRANCH ZERO
          SMLCommand = (42 * 100) + get_location_from_table(tokens_in_the_line);
          add_compiled_command(SMLCommand);
        } else if (strcmp(tokens_in_the_line, "<") == 0 || strcmp(tokens_in_the_line, "<=") == 0) {
          //  LOAD token to ACC
          SMLCommand = (20 * 100) + get_location_from_table(token_to_load);
          add_compiled_command(SMLCommand);
          //  Pega a proxima token (operando)
          tokens_in_the_line = strtok(NULL, " ");
          purgeLineBreak(tokens_in_the_line);
          //  Verifica se o operando esta na tabela de simbolos
          if (!has_an_entry(tokens_in_the_line))
            //  Adiciona variavel na tabela de simbolos
            add_to_table(tokens_in_the_line, is_token_word(tokens_in_the_line), 1, &current_variable_entry, &current_table_entry);
          //  SUB token from ACC
          SMLCommand = (31 * 100) + get_location_from_table(tokens_in_the_line);
          add_compiled_command(SMLCommand);
          //  Vai para a proxima token para encontrar o goto e depois a linha-alvo
          strtok(NULL, " "); tokens_in_the_line = strtok(NULL, " ");
          //  Verifica se a linha esta na tabela de simbolos
          if (!has_an_entry(tokens_in_the_line)) {
            //  Se nao estiver, precisa receber uma FLAG
            flag_token(tokens_in_the_line, instructions_counter);
          }
          //  BRANCHNEG
          SMLCommand = (41 * 100) + get_location_from_table(tokens_in_the_line);
          add_compiled_command(SMLCommand);
        } else if (strcmp(tokens_in_the_line, ">") == 0 || strcmp(tokens_in_the_line, ">=") == 0) {
          //  Pega a proxima token (operando)
          tokens_in_the_line = strtok(NULL, " ");
          purgeLineBreak(tokens_in_the_line);
          //  Verifica se o operando esta na tabela de simbolos
          if (!has_an_entry(tokens_in_the_line))
            //  Adiciona variavel na tabela de simbolos
            add_to_table(tokens_in_the_line, is_token_word(tokens_in_the_line), 1, &current_variable_entry, &current_table_entry);
          //  LOAD token to ACC
          SMLCommand = (20 * 100) + get_location_from_table(tokens_in_the_line);
          add_compiled_command(SMLCommand);
          //  SUB token from ACC
          SMLCommand = (31 * 100) + get_location_from_table(token_to_load);
          add_compiled_command(SMLCommand);
          //  Vai para a proxima token para encontrar o goto e depois a linha-alvo
          strtok(NULL, " "); tokens_in_the_line = strtok(NULL, " ");
          //  Verifica se a linha esta na tabela de simbolos
          if (!has_an_entry(tokens_in_the_line)) {
            //  Se nao estiver, precisa receber uma FLAG
            flag_token(tokens_in_the_line, instructions_counter);
          }
          //  BRANCHNEG
          SMLCommand = (41 * 100) + get_location_from_table(tokens_in_the_line);
          add_compiled_command(SMLCommand);
        }
        break;
      } else if (strcmp(tokens_in_the_line, "let") == 0) {
        //  Pega a proxima token (recebedor)
        tokens_in_the_line = strtok(NULL, " ");
        char* receiver = tokens_in_the_line;
        char statement[200];
        purgeLineBreak(full_line_backup);
        //  Pega tudo depois do =
        strcpy(statement, full_line_backup + 11);
        char postfix[200];
        convertToPostfix(statement, postfix);
        int result = evaluatePostfixExpression(postfix, &current_variable_entry, &current_table_entry);
        add_compiled_command((20 * 100) + result);
        if (!has_an_entry(receiver))
          //  Adiciona variavel na tabela de simbolos
          add_to_table(receiver, is_token_word(receiver), 1, &current_variable_entry, &current_table_entry);
        add_compiled_command((21 * 100) + get_location_from_table(receiver));
      } else if (strcmp(tokens_in_the_line, "goto") == 0) {
        //  Pega a proxima token (linha)
        tokens_in_the_line = strtok(NULL, " ");
        purgeLineBreak(full_line_backup);
        if (!has_an_entry(tokens_in_the_line)) {
          //  Adiciona variavel na tabela de simbolos
          flag_token(tokens_in_the_line, instructions_counter);
        }
        //  BRANCH to linha
        SMLCommand = (40 * 100) + get_location_from_table(tokens_in_the_line);
        add_compiled_command(SMLCommand);
      } else if (strcmp(tokens_in_the_line, "print") == 0) {
        //  Pega a proxima token (variavel)
        tokens_in_the_line = strtok(NULL, " ");
        purgeLineBreak(full_line_backup);
        if (!has_an_entry(tokens_in_the_line))
          //  Adiciona variavel na tabela de simbolos
          add_to_table(tokens_in_the_line, is_token_word(tokens_in_the_line), 1, &current_variable_entry, &current_table_entry);
        //  WRITE var
        SMLCommand = (11 * 100) + get_location_from_table(tokens_in_the_line);
        add_compiled_command(SMLCommand);
      } else if (strcmp(tokens_in_the_line, "end") == 0) {
        SMLCommand = (43 * 100);
        add_compiled_command(SMLCommand);
      }
    }
  }
  //  Segunda passada
  for (i = 0; i < 1000; i++) {
    if (flag[i] == -1) continue;
    char str[200];
    if (debug) sprintf(str, "%d", flag[i]);
    SMLMemory[i] = SMLMemory[i] + get_location_from_table(str);
  }
  if (debug) {
    printf("\n==========================================================\n");
    printf("====================SYMBOL TABLE==========================\n");
    printf("==========================================================\n");
    for (i = 0; i < current_table_entry; i++) {
      if (symbolTable[i].type == 'L' || symbolTable[i].type == 'C')
        printf("\n| %3d | %3d  | %c  | %2d  |", i, symbolTable[i].symbol, symbolTable[i].type, symbolTable[i].location);
      else
        printf("\n| %3d | %3c  | %c  | %2d  |", i, symbolTable[i].symbol, symbolTable[i].type, symbolTable[i].location);
    }
    printf("\n\n==========================================================\n");
    printf("=====================SML MEMORY===========================\n");
    printf("==========================================================\n");
    for (i = 0; i < instructions_counter; i++) {
      printf("\n| %3d | +%4d  |", i, SMLMemory[i]);
    }
  }
  //  Grava o programa compilado num arquivo de saida

  //  Monta o nome do novo arquivo
  char compiled_filename[100];
  //  Se o usuario passar o nome de saida pelo terminal
  if (argc > 2)
    strcpy(compiled_filename, argv[2]);
  else {
    //  Se o usuario nao passou um nome de saida, calcular via filename
    int k;
    for (k = 0; *(filename + k) != '\0' && *(filename + k) != '.'; k++) compiled_filename[k] = *(filename + k);
    compiled_filename[k] = '\0';
    //  Adiciona a extensao
    strcat(compiled_filename, ".sml");
  }
  FILE* compiled = fopen(compiled_filename, "w+");
  if (compiled == NULL) {
    printf("Sem permissao para gravar arquivo!\n");
    exit(0);
  }
  for (i = 0; i < instructions_counter; i++) {
    fprintf(compiled, "%d\n", SMLMemory[i]);
  }
  fclose(compiled);
}
