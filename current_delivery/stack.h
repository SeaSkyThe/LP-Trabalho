#include <stdlib.h>
#include <stdio.h>

//LIFO

struct stack_node{
    char data;
    struct stack_node *next;
};

struct stack{
    struct stack_node *top;
};

void start_stack(struct stack *stack){
    stack -> top = NULL;
}

void push(struct stack *stack, char value){
    struct stack_node *new = (struct stack_node*)malloc(sizeof(struct stack_node));
    new -> data = value;
    new -> next = stack -> top;
    stack -> top = new;
}

char pop(struct stack *stack){
    struct stack_node *old = stack -> top;
    char popped_out = stack -> top -> data;
    stack -> top = stack -> top -> next;
    free(old);
    return popped_out;
}

int isEmpty(struct stack *stack){
    if(stack -> top == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void printStack(struct stack *stack){
    struct stack_node *go_through = stack -> top;
    while(go_through != NULL){
        printf("%c ", go_through -> data);
        go_through = go_through -> next;
    }
    return;
}
