//
// Created by sonata on 2/28/21.
//

#include "pharmacy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// запись структуры в файл
int save(char * filename, struct Person *p)
{
    FILE * fp;
    char *c;
    int size = sizeof(struct Person); // количество записываемых байтов

    if ((fp = fopen(filename, "wb")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    // устанавливаем указатель на начало структуры
    c = (char *)p;
    // посимвольно записываем в файл структуру
    for (int i = 0; i < size; i++)
    {
        putc(*c++, fp);
    }
    fclose(fp);
    return 0;
}

// загрузка из файла структуры
struct Person* load(char * filename)
{
    FILE * fp;
    char *c;
    int i; // для считывания одного символа
    // количество считываемых байтов
    int size = sizeof(struct Person);
    // выделяем память для считываемой структуры
    struct Person * ptr = (struct Person *) malloc(size);

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }

    // устанавливаем указатель на начало блока выделенной памяти
    c = (char *)ptr;
    // считываем посимвольно из файла
    while ((i = getc(fp))!=EOF)
    {
        *c = i;
        c++;
    }

    fclose(fp);
    // вывод на консоль загруженной структуры
    return ptr;
}


void setData(struct Person* person)
{
    (*person).pharmacy = (struct Pharmacy*)malloc(sizeof(struct Pharmacy));
    for(int i=0; i<7; i++)
    {
        (*person).pharmacy->antibioticPrice[i] = rand()%75+5;
        (*person).pharmacy->receiptNeeded[i] = rand()%2;
    }
    (*person).currentCoins = 100;

    strcpy((*person).pharmacy->antibiotics[0], "aspirin");
    strcpy((*person).pharmacy->antibiotics[1], "peracetamol");
    strcpy((*person).pharmacy->antibiotics[2], "drotaverin");
    strcpy((*person).pharmacy->antibiotics[3], "ambroxol");
    strcpy((*person).pharmacy->antibiotics[4], "ketorol");
    strcpy((*person).pharmacy->antibiotics[5], "pirocetam");
    strcpy((*person).pharmacy->antibiotics[6], "gromicin");

    save("info", person);

}

void addSomeCoins(struct Person* person, double coins)
{
    (*person).currentCoins += coins;
}

int buyAntibiotics(struct Person* person)
{
    int decision;
    int c;
    do {
        showInfo(person);
        do {
            printf("Write a number of antibiotic, what you want to buy: ");
            scanf("%i", &decision);
            while(getchar()!='\n');

            if(decision>7 || decision<0)
                printf("incorrect input, please, try again\n");
            else break;
        }while(1);

        if(person->currentCoins>(*person).pharmacy->antibioticPrice[decision-1])
        {
            person->currentCoins-=(*person).pharmacy->antibioticPrice[decision-1];
            printf("success\n");
        }
        else
        {
            printf("You haven't enough money.\n");
        }
        printf("Something else?(1 - yes, 0 - no): ");
        do
        {
            scanf("%i", &c);
            while ((getchar()) != '\n');
            printf("\n");
            if(c == 1 || c == 0)
                break;
        }while(1);
    }while(c!=0);
}

void showInfo(struct Person* person)
{
    printf("\nYour balance: %lf\n", (*person).currentCoins);
    puts("\nAvailable antibiotics:");
    for(int i = 0; i < 7; i++){
        printf("%d. %s. cost: %d", i+1, (*person).pharmacy->antibiotics[i], (*person).pharmacy->antibioticPrice[i]);
        if((*person).pharmacy->receiptNeeded[i] == 1)
            printf(", receipt neededn\n");
        else printf(", receipt not needed\n");
    }
}


void menu()
{
    struct Person* person;
    person = load("info");
    int coins;
    int choiceInMenu = 1;
    do {
        puts("1. Buy antibiotics");
        puts("2. Add some coins");
        puts("3. Exit");
        while (!scanf("%i", &choiceInMenu) || (choiceInMenu < 1 || choiceInMenu > 3))
        {
            while(getchar()!='\n');
        }
        switch (choiceInMenu) {
            case 1:
                buyAntibiotics(person);
                break;
            case 2:
                printf("input number of coins you want to add: ");
                while (!scanf("%d", &coins))
                {
                    printf("\n you must input a number.\n");
                    rewind(stdin);
                }
                addSomeCoins(person, coins);
                break;

        }
    } while(choiceInMenu != 3);
    exit(1);
}