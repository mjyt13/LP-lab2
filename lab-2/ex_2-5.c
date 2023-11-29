#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define FILE_NOT_FOUND -120

struct st{//объявляется тип Структура, содержащая указатель на следующий элемент(Узел стека)
    double data;
    struct st *prev;
};

struct Stack{
    double size;
    struct st * top;
};

void push(struct Stack * stack, double data, int maxsize){//Добавить элемент
    if(stack->size>=maxsize){
        printf("STACK IS OVERFLOW\n");
        exit(STACK_OVERFLOW);
    }
    struct st * adr = malloc(sizeof(struct st));
    adr->data=data;
    adr->prev=stack->top;
    stack->top=adr;
    stack->size++;
}

double pop(struct Stack * stack){
    if(stack->top==NULL){
        printf("STACK IS UNDERFLOW\n");
        exit(STACK_UNDERFLOW);
    }
    struct st * out = stack->top;
    stack->top = stack->top->prev;
    double data = out->data;
    free(out);
    stack->size--;
    return data;
}

double peek(struct Stack * stack){
    if(stack->top==NULL){
        printf("STACK IS UNDERFLOW\n");
        exit(STACK_UNDERFLOW);
    }
    struct st * out = stack->top;
    double data = out->data;
    return data;
}

void main(int cnames, char * fnames[]){

    int maxsize=55;
    struct Stack * stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top=NULL;
    stack->size=0;
    
    FILE *ff = fopen(fnames[1], "r");

    if (ff == NULL){
        printf("FilE NOT FOUND");
        exit(FILE_NOT_FOUND);
    }

    char ch;
    double a, b;

    while ((ch = fgetc(ff)) != EOF){
        if (isdigit(ch))
        {
            push(stack, ch - '0',maxsize);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            b = pop(stack);
            a = pop(stack);
            switch (ch)
            {
            case '+':
                push(stack, a + b,maxsize);
                printf("inter %lf\n",peek(stack));
                break;
            case '-':
                push(stack, a - b,maxsize);
                printf("inter %lf\n",peek(stack));
                break;
            case '*':
                push(stack, a * b,maxsize);
                printf("inter %lf\n",peek(stack));
                break;
            case '/':
                push(stack, a / b,maxsize);
                printf("inter %lf\n",peek(stack));
                break;
            default:
                break;
            }
        }
    }
    fclose(ff);
    if(stack!=NULL){
        printf("результат равен %lf\n", pop(stack));
    }else{
        printf("стек пуст\n");
    }
}
