//
//  drinkmachine.h
//  Homework-3
//
//  Created by Abinash Bhattarai on 10/7/17.
//  Copyright © 2017 Abinash Bhattarai. All rights reserved.
//
#include <stdbool.h>
#ifndef drinkmachine_h
#define drinkmachine_h
typedef struct _DrinkItem{ //Struct Drink Item
    int id;
    char* name;
    double price;
    int noOfdrinks;
    int drink_purchased;
    
    
}DrinkItem;

typedef struct _DrinkMachine { //Struct Drink Machine which contains an array of drink items
    int versionNo;
    int numOfDS;
    DrinkItem* items;
    int curr;
    
    
}DrinkMachine;


DrinkMachine* create (void); //Creates DrinkMachine
void destroy(DrinkMachine*); //Destroys DrinkMachine after all transaction has been done and user selects to end the program
DrinkItem* firstDrink( DrinkMachine*);// Returns pointer of firstDrinkitem in the array
DrinkItem* nextDrink( DrinkMachine*);//Returns pointer of nextDrinkItem in the array
int items(DrinkMachine*);// Return number of items in DrinkMachine
bool available(DrinkMachine*,int);//Checks if the items is available or not
double cost(DrinkMachine*,int);// Returns cost of drinkitem
typedef enum Purchase { PURCHASED, INVALID,NOT_AVAILABLE, INSUFFICIENT_FUNDS } Purchase;//Makes the transaction
Purchase purchase(DrinkMachine*,int ,double,double*);
void dumpDrinkMachine(DrinkMachine*);// Displays all the items of the files including items sold
void dumpDrinkMachine2(DrinkMachine*);//Displays all the items of the files excluding items sold

#endif /* drinkmachine_h */

