#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define FILE_NOT_FOUND -111

typedef struct st{//объявляется тип Структура, содержащая указатель на следующий элемент(Узел стека)
    double data;
    struct st *prev;
}elem;

void push(elem **top, double dta, int size, int max_size){//Добавить элемент
    elem * adr = malloc(sizeof(elem));//Выделить память и вернуть адрес элемента 
    if(adr==NULL||size>max_size){
        printf("STACK IS OVERFLOW");
        exit(STACK_OVERFLOW);//проверка на переполненность
    }
    adr->prev = *top;//обратиться по адресу элемента и в поле указателя на пред. элемент указать адрес вершины
    adr->data = dta;//обратиться по адресу элемента и в поле данных указать данные
    *top = adr;//в адрес вершины записать адрес узла

    size++;
}

double pop2(elem **top, int size){//Удалить элемент и вернуть данные 
    elem * out;//создать указатель на элемент
    double dta;
    if(*top==NULL){
        printf("STACK IS EMPTY\n");
        exit(STACK_UNDERFLOW);
    }
    out = *top;//присвоить указателю адрес вершины стека
    *top = (*top)->prev;//указателю на вершину присвоить адрес предыдущего элемента
    dta = out->data;
    free(out);//освободить память
    size--;
    return dta;//вернуть данные из элемента
}

double peek(elem *top){
    if(top==NULL){
        printf("STACK IS EMPTY\n");
        exit(STACK_UNDERFLOW);
    }
    return top->data;
}

int getSize(const elem *top){//Узнать размер стека
    int size = 0;//создать переменную, фиксирующую размер
    while(top){//добавлять число, равное размеру узла и переходить к следующему элементу
        size++;
        top = top->prev;
    }
    return size;
}

void main(int cnames, char *fnames[])
{
    elem *top = NULL;
    int stack_size = 1447;
    int size = 0;
    FILE *ff = fopen(fnames[1], "r");
    if (ff == NULL)
    {
        printf("FilE NOT FOUND");
        exit(FILE_NOT_FOUND);
    }
    char ch;
    double a, b;
    while ((ch = fgetc(ff)) != EOF){
        if (isdigit(ch))
        {
            push(&top, ch - '0',size, stack_size);
            printf("%lf\n",peek(top));
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            a = pop2(&top,size);
            b = pop2(&top,size);
            switch (ch)
            {
            case '+':
                push(&top, a + b,size,stack_size);
                break;
            case '-':
                push(&top, a - b,size,stack_size);
                break;
            case '*':
                push(&top, a * b,size,stack_size);
                break;
            case '/':
                push(&top, a / b,size,stack_size);
                break;
            default:
                break;
            }
        }
    }
    fclose(ff);
    if(top!=NULL){
        printf("результат равен %lf\n", pop2(&top,size));
    }else{
        printf("стек пуст\n");
    }
}
