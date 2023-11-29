#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
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

void main(){

    int maxsize=55;
    struct Stack * stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top=NULL;
    stack->size=0;
    printf("Введите 3 для прекращения работы, 2 для просмотра вершины стека, 1 для добавления элемента в стек и 0 для удаления\n");
    int choice;
    while(choice!=3){
        scanf("%d",&choice);
        switch(choice){
            case 0:
                printf("Удален %lf\n",pop(stack));
                break;
            case 1:
                printf("Введите число для добавления в стек\n");
                double num;
                scanf("%lf\n",&num);
                push(stack,num,maxsize);
                break;
            case 2:
                printf("Вершина равна %lf\n",peek(stack));
                break;
            default:
                printf("Работа прекращена\n");
                break;
        }
    }
    printf("Спасибо за работу\n");
}