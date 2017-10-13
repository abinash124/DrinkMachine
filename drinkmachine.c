//
//  drinkmachine.c
//  Homework-3
//
//  Created by Abinash Bhattarai on 10/7/17.
//  Copyright © 2017 Abinash Bhattarai. All rights reserved.
//

#include "drinkmachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//To use strlen function
const int INVALID_INDEX=-1;
const char * INPUT_FILE_NAME = "drink_machine.txt";
const int STRING_BUFFER_SIZE=128;


DrinkMachine* create ()
{
    FILE *inFile;
    DrinkMachine *drinkmachines_ss=calloc(1, sizeof(DrinkMachine));//Creates a new DrinkMachine pointer specifying how much size it would need to store all the documents in struct
    int num;
    inFile = fopen(INPUT_FILE_NAME, "r");
    if(inFile==NULL)//Checking if the file opens correctly or not
    {
        puts("Error opening file");
        free(drinkmachines_ss);//We need to free drinkmachines_ss if file does not open correctly because we had allocated specific memory for drinkmachine. If we do not do this stp there might be memory leak.
        return NULL;
    }
    
    
        drinkmachines_ss->items=calloc(drinkmachines_ss->numOfDS, sizeof(DrinkItem));//Since drinkmachine items is also pointer,we need to designate the specific size for the items too
    
        drinkmachines_ss->curr=INVALID_INDEX;//Currently we haven't read anything from the file so this index points to invalid index
        fscanf(inFile,"%d", &num);//Reads the first line of the items to see how many items are there on drinkmachine
        drinkmachines_ss->numOfDS=num;//Stores the number of items in numOfDs
        char tempBuff[STRING_BUFFER_SIZE];//Creating a temporary buffer of size 128 before we allocate any specific memory for name. Cause We don't really know how much space is it gonna take at the beginning. This could also be done the other way by just allocating more than enough memory for the name but that takes extra space than required which cannot be the efficient way
        int length;//To figure out the length of the name that we read from the file

        
        for(int i=0;i<num;i++)//Read everything from the file and store in items array of our drinkmachine structure
        {
            drinkmachines_ss->items[i].id=i+1;
            
            drinkmachines_ss->items[i].id=i+1;
            fscanf(inFile,"%s", tempBuff);
            length=(int)strlen(tempBuff);//For some reason Xcode didn't allow me to use length as int so I had to explicitly typecast to int.
            drinkmachines_ss->items[i].name=malloc(length+1);
            memcpy(drinkmachines_ss->items[i].name, tempBuff, length+1);
            /*
             Might need to debug here
             */
            fscanf(inFile,"%lf", &drinkmachines_ss->items[i].price);
            fscanf(inFile,"%d", &drinkmachines_ss->items[i].noOfdrinks);
            drinkmachines_ss->items[i].drink_purchased=0;
            
            
            
        }
        fclose(inFile);//Certainly we do need to close our file after we open it
        return drinkmachines_ss;
}


void destroy(DrinkMachine* drinkmachines)//This functions frees up everything after
{
    for(int i=0;i<=drinkmachines->numOfDS;i++)
    {
        drinkmachines->items[i].name=NULL;
        drinkmachines->items[i].price=0;
        drinkmachines->items[i].id=0;
        drinkmachines->items[i].noOfdrinks=0;
        drinkmachines->items[i].drink_purchased=0;
        
    }
    free(drinkmachines);
}


DrinkItem* firstDrink( DrinkMachine* drinkmachines)//It returns the address of the firstDrink if there is any
{
    if(drinkmachines->items==NULL)//If there is nothing in the items then it will set the curr position to 0.
    {
        drinkmachines->curr=INVALID_INDEX;
    }
    drinkmachines->curr=0;//If it founds out there is something in the items, then it sets the current position of drinmachines to 0.
    return &drinkmachines->items[0];
    
    
    
}

DrinkItem* nextDrink( DrinkMachine* drinkmachines)
{
    if(drinkmachines->curr==INVALID_INDEX)//If there was no firstdrink(i.e curr position is INVALID_INDEX) found then it can't proceed to the next drink. In that case we return null to say the drinkItems is emppty
    {
        return NULL;
    }
    else 
    {
        drinkmachines->curr+=1; //Else we increment the current position by 1 to set into index of nextDrink item in the array
        if (drinkmachines->curr<drinkmachines->numOfDS) // If after incrementing, theres still some drinkItems left then we return the address of the current drinkItems
        {
            return &drinkmachines->items[drinkmachines->curr];
        }
        //If not we just have figured that's the end of the array so our job is done. Yay. So we set the current position back to Invalid index and return null to tell the program that no further nextDrink check is required.
        drinkmachines->curr=INVALID_INDEX;
        return NULL;
    }
   
}

int items(DrinkMachine* drinkmachines)//It just basically returns the num of drinkItems in drinkmachines.
{
    return (drinkmachines->numOfDS);
    
}


bool available(DrinkMachine* drinkmachines,int drinkId){
    if (drinkmachines->items[drinkId].noOfdrinks>=1)//It checks if the specific drinkItem is avaliable or not. We could have sold each of the items and it might have been empty. In that case we just say we are out of the items by returning false.
        return true;
    else
        return false;
}


double cost(DrinkMachine* drinkmachines,int drinkId)//It returns the cost of drinkItems.
{

    if(drinkId>drinkmachines->numOfDS || drinkId<0)
        return -1.0;
    return drinkmachines->items[drinkId].price;
    
}


Purchase purchase(DrinkMachine* drinkmachines,int drinkId , double cashPaid,double* change)
{
    if(drinkId>drinkmachines->numOfDS || drinkId<0)//If the id user has given is not valid then we should return invalid.
        return INVALID;
    else if (!available(drinkmachines,drinkId))//If we don't have we don't sell it.
        return NOT_AVAILABLE;
    else if(cashPaid< cost(drinkmachines, drinkId))//If user doesn't have sufficient balance there's no bargaining in the drinkmachine. We can't just sell it
        return INSUFFICIENT_FUNDS;
    else//If everything is alright we sell it, and have one less drinkItems and we sold one more drinkItems. That's why we do the following thing
    {
        drinkmachines->items[drinkId].noOfdrinks-=1;
        drinkmachines->items[drinkId].drink_purchased+=1;
        *change=cashPaid-drinkmachines->items[drinkId].price;
        return PURCHASED;//And obviously if PURCHASED we have to return PURCHASED
    }
    
    
}
void dumpDrinkMachine(DrinkMachine* drinkmachines)//This displays everything including the number of drinkItems that we sold
{
    putchar('\n');
    printf("%-8s%-21s%-7s%-8s%-6s\n", "ID", "NAME", "Price", "Quanity","SOLD");//Those random symbols at the beginning are to align spacing for the Display so the user can see the clear display in the screen
    for (int j=0;j<drinkmachines->numOfDS;j++)//Loop till the end to display everything
        
    {
        printf("%-8d%-21s%-.2lf%7i%6d\n", drinkmachines->items[j].id,drinkmachines->items[j].name,drinkmachines->items[j].price,drinkmachines->items[j].noOfdrinks,drinkmachines->items[j].drink_purchased);
    }
}
    
    void dumpDrinkMachine2(DrinkMachine* drinkmachines)//This does the same thing as the prior function except it does not display the number of sold items. Its version 2.0 of dumpDrinkMACHINE.
    {
        putchar('\n');
        printf("%-8s%-21s%-7s%-8s\n", "ID", "NAME", "Price", "Quanity");
        for (int j=0;j<drinkmachines->numOfDS;j++)
            
        {
            printf("%-8d%-21s%-.2lf%7i\n", drinkmachines->items[j].id,drinkmachines->items[j].name,drinkmachines->items[j].price,drinkmachines->items[j].noOfdrinks);
        }
    }


