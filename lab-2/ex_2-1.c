#include <stdio.h>
#include <stdlib.h>
int quantity(int num){//Функция подсчёта количества цифр
    int x = num;
    int k = 0;
    while(x>0){
        x=x/10;
        k++;
    }
    return k;
}

int main(int args, char* fname[]){
    FILE * InvNums=fopen(fname[1],"w");//открыть файл, куда будут записываться числа
    printf("Введите размер массива целых чисел\n");//далее в 3 строках происходит создание размера массива
    int r;
    scanf("%d",&r);
    int intmass[r];//создаётся массив размера, заданного ранее
    srand(time(NULL));
    for(int i=0;i<r;i++){
        intmass[i]=rand();//происходит заполнение псевдослучайными числами
        printf("%d\n",intmass[i]);
    }
    for(int i=r-1;i>=0;i--){
        char charmass[quantity(intmass[i])];//создаётся массив символов, записывается число, и вносится в файл
        sprintf(charmass,"%i",intmass[i]);
        fprintf(InvNums,"%s\n",charmass);
    }
    fclose(InvNums);
}