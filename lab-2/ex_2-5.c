#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define FILE_NOT_FOUND -111

typedef struct st
{
    int data;
    struct st *prev;
} elem;

void push(elem **top, int dta)
{   
    elem *adr = malloc(sizeof(elem)); 
    if(adr==NULL){
        exit(STACK_OVERFLOW); 
    }
    adr->prev = *top; 
    adr->data = dta;  
    *top = adr;      
}

int pop2(elem **top)
{ 
    elem *out;
    int dta;
    if (*top == NULL)
    {
        printf("STACK IS EMPTY-1\n");
        exit(STACK_UNDERFLOW);
    }
    out = *top;
    *top = (*top)->prev;
    dta = out->data;
    free(out);
    return dta;
}

int peek(elem *top)
{
    if (top == NULL)
    {
        printf("STACK IS EMPTY-2\n");
        exit(STACK_UNDERFLOW);
    }
    return top->data;
}

size_t getSize(const elem *top)
{
    size_t size = 0;
    while (top)
    {
        size += sizeof(elem);
        top = top->prev;
    }
    return size;
}

void main(int cnames, char *fnames[])
{
    elem *top = NULL;//создать указатель на вершину, т.е. объявить создание стека
    size_t stcksize = 14470;//объявить размер стека
    FILE *ff = fopen(fnames[1], "r");//открыть файл, где содержится выражение в постфиксной записи
    if (ff == NULL)//проверка файла на наличие
    {
        printf("FilE NOT FOUND");
        exit(FILE_NOT_FOUND);
    }
    char ch;
    int a, b, result;//объявление переменных, с которыми будет происходить работа
    while ((ch = fgetc(ff)) != EOF){
        if (isdigit(ch))
        {//если символ - цифра, занести его в стек
            push(&top, ch - '0');
        }//если символ - действие, то действия будут иные
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {//достать числа из стека
            a = pop2(&top);//записать их в переменные и выполнить действия
            b = pop2(&top);//занести в стек результат
            if (ch == '+')
            {
                push(&top, b + a);
            }
            else if (ch == '-')
            {
                push(&top, b - a);
            }
            else if (ch == '*')
            {
                push(&top, b * a);
            }
            else if (ch == '/')
            {
                push(&top, b / a);
            }
        }
    }
    fclose(ff);//закрыть файл
    if(top!=NULL){//вывести результат консоль
        printf("результат равен %d\n", pop2(&top));
    }else{
        printf("стек пуст\n");
    }
}
