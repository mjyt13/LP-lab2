#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101

typedef struct st{//объявляется тип Структура, содержащая указатель на следующий элемент(Узел стека)
    int data;
    struct st *prev;
}elem;

void push(elem **top, int dta){//Добавить элемент
    elem * adr = malloc(sizeof(elem));//Выделить память и вернуть адрес элемента 
    if(adr==NULL){
        printf("STACK IS OVERFLOW");
        exit(STACK_OVERFLOW);//проверка на переполненность
    }
    adr->prev = *top;//обратиться по адресу элемента и в поле указателя на пред. элемент указать адрес вершины
    adr->data = dta;//обратиться по адресу элемента и в поле данных указать данные
    *top = adr;//в адрес вершины записать адрес узла
}

int pop2(elem **top){//Удалить элемент и вернуть данные 
    elem * out;//создать указатель на элемент
    int dta;
    if(*top==NULL){
        printf("STACK IS EMPTY\n");
        exit(STACK_UNDERFLOW);
    }
    out = *top;//присвоить указателю адрес вершины стека
    *top = (*top)->prev;//указателю на вершину присвоить адрес предыдущего элемента
    dta = out->data;
    free(out);//освободить память
    return dta;//вернуть данные из элемента
}

int peek(elem *top){
    if(top==NULL){
        printf("STACK IS EMPTY\n");
        exit(STACK_UNDERFLOW);
    }
    return top->data;
}

size_t getSize(const elem *top){//Узнать размер стека
    size_t size = 0;//создать переменную, фиксирующую размер
    while(top){//добавлять число, равное размеру узла и переходить к следующему элементу
        size+=sizeof(elem);
        top = top->prev;
    }
    return size;
}

void main(){
    elem * top = NULL;//создать указатель, значением которого является ничего, следоваательно, создать стек
    size_t stcksize = 44;//объявить размер, значение которого не должен превышать размер стека
    int choice = -1;
    printf("Введите 3 для прекращения работы, 2 для просмотра вершины стека, 1 для добавления элемента в стек и 0 для удаления\n");
    while(getSize(top)<stcksize && choice!=3){//Запуск работы со стеком
        scanf("%d",&choice);
        if(choice==1){
            printf("Введите число для добавления в стек\n");
            int num;
            scanf("%d\n",&num);
            push(&top,num);
        }
        if(choice==0){
            printf("Удален %d\n",peek(top));
            pop2(&top);
        }
        if(choice==2){
            printf("Вершина равна %d\n",peek(top));
        }
    }
    if(getSize(top)>=stcksize){
        printf("Стек переполнен, работа прекращена\n");
    }else{
        printf("Спасибо за работу\n");
    }
}