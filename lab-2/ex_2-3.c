#include <stdio.h>
#include <stdlib.h>
struct item{//создаётся структура, где будут сохранены данные о предмете
    char name[1000];
    double vol; 
};
int cmprsn(const void* a,const void* b){//процедура сравнения
    double pr_a, pr_b;
    pr_a = ((struct item*)a)->vol;
    pr_b = ((struct item*)b)->vol;
    if(pr_a==pr_b){
        return 0;
    }else if(pr_a>pr_b){
        return -1;
    }else{
        return 1;
    }
}
int main(int args, char * fname[]){
    FILE * IM,*OM;//создание двух файлов, один для считывания информации, второй для записи
    IM = fopen(fname[1],"r");
    OM = fopen(fname[2],"w");
    char ch;
    if(IM==NULL){
        printf("File not found\n");
        return 0;
    }
    int q=0;
    while(ch!=EOF){
        ch=fgetc(IM);
        if(ch=='\n'){//подсчёт количества товаров
            q++;
        }
    }
    struct item objs[q];//создаётся массив структур(предметов)
    fseek(IM,0,SEEK_SET);
    int coun=0;
    while(fscanf(IM,"%1000s %lf",objs[coun].name,&objs[coun].vol)==2 && coun<q){
        coun++;
    }
    fclose(IM);
    if(coun>0){//далее происходит сортировк предметов и запись данных о них в файл
        qsort(objs,coun,sizeof(struct item),cmprsn);
        if(OM==NULL){
            printf("ERROR(FILE NOT FOUND)");
            return 0;
        }
        for(int k=0;k<coun;k++){
            fprintf(OM,"%s %.1f\n",objs[k].name,objs[k].vol);
        }
        fclose(OM);
        printf("SUCCESS\n");
    }else{
        printf("ERROR(NON-READABLE STRUCTURES)");
    }
    return 0;
}
