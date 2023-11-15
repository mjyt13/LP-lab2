#include <stdio.h>
#include <stdlib.h>
int quantity(int num){
    int x = num;
    int k = 0;
    while(x>0){
        x=x/10;
        k++;
    }
    return k;
}

void main(int args, char* fname[]){
    FILE * InvNums=fopen(fname[1],"w");
    printf("Введите размер массива чисел c плавающей точкой\n");
    int r;
    double fl;
    scanf("%d",&r);//вводится размер двух массивов, один содержит целые числа, другой - с плавающей точкой
    int intmass[r];
    double floatmass[r];//создаётся массив для чисел с плавающей точкой
    srand(time(NULL));
    for(int i=0;i<r;i++){
        intmass[i]=rand();
        floatmass[i]=intmass[i];
        for(int j=0;j<quantity(intmass[i]);j++){//происходит создание числа с плавающей точкой за счёт деления целого числа на количество его цифр
            floatmass[i]=floatmass[i]/10;
        }
        printf("%d - %f\n",intmass[i],floatmass[i]);
    }
    for(int i=0;i<r;i++){//происходит сортировка массива в цикле
        int j=i;
        int k;
        fl=floatmass[i];
        while(j<r){
            if(fl>floatmass[j]){
                fl=floatmass[j];
                k=j;
            }
            j++;
        }
        floatmass[k]=floatmass[i];
        floatmass[i]=fl;
    }
    for(int i=0;i<r;i++){
        printf("%f\n",floatmass[i]);//выводится в консоль массив отсортированных чисел
    }
    
    for(int i=1;i<r;i++){
        char charmass[quantity(intmass[i])+2];//создаётся массив символов, где элементов на 2 больше,чем в целом числе(точка и ноль)
        sprintf(charmass,"%lf",floatmass[i]);
        fprintf(InvNums,"%s\n",charmass);
    }
    fclose(InvNums);
}