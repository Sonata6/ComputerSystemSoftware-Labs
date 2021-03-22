//
// Created by sonata on 2/28/21.
//

#ifndef LABA1_PHARMACY_H
#define LABA1_PHARMACY_H


struct Pharmacy{
    char antibiotics[7][15];
    int receiptNeeded[7];
    int antibioticPrice[7];
};


struct Person{
    double currentCoins;
    struct Pharmacy* pharmacy;
};

void setData(struct Person* person);
void addSomeCoins(struct Person* person, double coins);
int buyAntibiotics(struct Person* person);

void menu();

void showInfo(struct Person* person);

#endif //LABA1_PHARMACY_H
