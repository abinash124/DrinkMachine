//
//
//  main.c
//  Homework-3
//
//  Created by Abinash Bhattarai on 10/7/17.
//  Copyright © 2017 Abinash Bhattarai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "drinkmachine.h"

int main(void)
{

    DrinkItem *pDrink; //Creates a new drinkItem structure
    DrinkMachine *drinkmachines_s;// Creates new drinkmachine structure


    //Create a new drinkmachine structure and fill it with the contents in file
    int userId=8;//Just to initialize userId other than 0 so we could use (whie(userId!=0)
    double cashPaid = 0.0;
    double change;
    drinkmachines_s=create();//It calls create function to create the drinkmachine structure



    printf("%-8s%-21s%-7s%-8s%-6s\n", "ID", "NAME", "Price", "Quanity","SOLD");//With the specified spacing ID NAME PRICE and everything is displayed
    
    for (pDrink=firstDrink(drinkmachines_s);pDrink!=NULL;pDrink=nextDrink(drinkmachines_s))//Displaying every drinkmachine

    {
        printf("%-8d%-21s%-.2lf%7i%6d\n", pDrink->id,pDrink->name,pDrink->price,pDrink->noOfdrinks,pDrink->drink_purchased);
    }
    
    while(userId!=0)//Ask user to select drinkid as long as the user press 0. When user press 0 display the items sold from drinkmachine and exit the program
    {
        printf("\n");
        printf("Enter the drink id you wish to purchase or press 0 to quit.");
        scanf("%d",&userId);
        if(userId==0)
        {
           
            dumpDrinkMachine(drinkmachines_s);//To display drinkmachine after selling everything
            printf("Thank you for using our drinkmachine");
            destroy(drinkmachines_s);
            return 0;
        }
        if (available(drinkmachines_s,userId-1)==true)//The array index starts with 1 less than the user gives the input
        {
            printf("Enter the amount of cash that you are paying(upto $2.00)");
            scanf("%lf",&cashPaid);
        }
        if (cashPaid>2)//The maximum amount that user could enter is 2
        {
            printf("The amount that you have given is not valid");
        }
        else
            
        {
            switch(purchase(drinkmachines_s, userId-1, cashPaid, &change))//If cash is valid check if it sufficient enough or not and if the item is available or not.
            {
                case PURCHASED: {
                    printf("Successfully purchased the items that you were looking for");
                    printf("Your change is $");
                    printf("%0.2lf",change);
                    dumpDrinkMachine2(drinkmachines_s);
                
                    break;
                }
                case INVALID:
                {
                    printf("The drink ID that you gave is not valid");
                    dumpDrinkMachine2(drinkmachines_s);
                    break;
                }
                case NOT_AVAILABLE:
                {
                    printf("The item that you are trying to buys in not available");
                    dumpDrinkMachine2(drinkmachines_s);
                    break;
                }
                case INSUFFICIENT_FUNDS:
                {
                    printf("You don't have really sufficient fund to buy this. The price is $");
                    double costP=cost(drinkmachines_s, userId-1);
                    printf("%.2lf",costP);
                    dumpDrinkMachine2(drinkmachines_s);
                    
                 break;
                default:
                    {
                        printf("Oops something wrong went up...Fixing it");
                        break;
                    }
                }//End of switch case

            }// End of else
        }//End of loop
    }//End of main
   

    

}
