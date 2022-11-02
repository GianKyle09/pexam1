#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define MAXLENGTH 73
#define MAXORDER 100

typedef struct addons
{
    int addonID;
    char addonName[100];
    float addonPrice;
} addons;

typedef struct menu
{
    int itemID;
    char itemName[100];
    char addonCheck[2];
    float itemPrice;
    addons addon[3];
} menu;

typedef struct order
{
    int itemID;
    int addonCheck;
    int addonID;
    int itemQuantity;
    char itemName[100];
    char addonName[100];
    float itemPrice;
    float addonPrice;
} order;

menu menuItems[10] =
    {
        { 
            1,"Classic Chicken Sandwich","*",55.00,
            {
                {
                    01,"Cajun Fries",45.00
                },
                {
                    02,"Coke",30.00
                },
                {
                    03,"Spaghetti",59.00
                }
            }
        },
        {
            2,"Spicy Chicken Sandwich","*",145.00,
            {
                {
                    01,"Cajun Fries",45.00
                },
                {
                    02,"Coke",30.00
                },
                {
                    03,"Spaghetti",59.00
                }
            }
        },
        {
            3,"Chicken Tenders","*",68.00,
            {
                {
                    01,"Classic Biscuits",50.00
                },
                {
                    02,"Cajun Fries",45.00
                },
                {
                    03,"Rice",30.00
                }
            }
        },
        {
            4,"Signature Chicken","*",89.00,
            {
                {
                    01,"Rice",30.00
                },
                {
                    02,"Spaghetti",59.00
                },
                {
                    03,"Classic Biscuits",50.00
                }
            }
        },
        {
            5,"Fish Burger","*",129.00,
            {
                {
                    01,"Cajun Fries",45.00
                },
                {
                    02,"Classic Biscuit",50.00
                },
                {
                    03,"Coke",30.00
                }
            }
        },
        { 
            6,"Shrimp Burger","*",135.00,
            {
                {
                    01,"Cajun Fries",45.00
                },
                {
                    02,"Classic Biscuit",50.00
                },
                {
                    03,"Coke",30.00
                }
            }
        },
        {
            7,"Fluffy Pancake","*",89.00,
            {
                {
                    01,"Signature Chicken",89.00
                },
                {
                    02,"Choco Fudge",29.00
                },
                {
                    03,"Caramel Fudge",29.00
                }
            }
        },
        {
            8,"Honey Biscuit","",50.00
        },
        {
            9,"White Chocolate Biscuit","",61.00
        },
        {
            10,"Hazelnut Biscuit","",61.00
        }
    };

void menuList()
{
    printf("          Item No.         Name                        Price\n");
    for(int i = 0; i < 10; i++)
    {
        printf("\t  %02d\t\t   %-25s   %-10.2f%s \n", menuItems[i].itemID, menuItems[i].itemName, menuItems[i].itemPrice, menuItems[i].addonCheck);
    }
}
void addonList(int itemNumber)
{
    printf("          Addon No.        Name                        Price\n");
    for(int i = 0; i < 3; i++)
    {
        printf("\t  %02d\t\t   %-25s   %.2f \n", menuItems[itemNumber].addon[i].addonID, menuItems[itemNumber].addon[i].addonName, menuItems[itemNumber].addon[i].addonPrice);
    }
}
void logoDisplay()
{
    printf("'########:::'#######::'########::'########:'##:::'##:'########::'######::\n");
    printf(" ##.... ##:'##.... ##: ##.... ##: ##.....::. ##:'##:: ##.....::'##... ##:\n");
    printf(" ##:::: ##: ##:::: ##: ##:::: ##: ##::::::::. ####::: ##::::::: ##:::..::\n");
    printf(" ########:: ##:::: ##: ########:: ######:::::. ##:::: ######:::. ######::\n");
    printf(" ##.....::: ##:::: ##: ##.....::: ##...::::::: ##:::: ##...:::::..... ##:\n");
    printf(" ##:::::::: ##:::: ##: ##:::::::: ##:::::::::: ##:::: ##:::::::'##::: ##:\n");
    printf(" ##::::::::. #######:: ##:::::::: ########:::: ##:::: ########:. ######::\n");
    printf("..::::::::::.......:::..:::::::::........:::::..:::::........:::......:::\n");
}
void posDisplay(int menuType, int addonType)
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < MAXLENGTH; j++)
        {
            printf("=");
        }
        printf("\n");
        if(i == 0 && menuType == 0)
        {
            menuList();
        }
        else if(i == 0 && menuType == 1)
        {
            addonList(addonType);
        }
        else if(i == 1)
        {
            printf("\t\t\tItems with a * has add-ons\n");
        }
    }
}

bool orderInput(order *porder)
{
    int menuType = 0;
    int itemCount = 0;
    int itemNumber;
    int itemQuantity;
    int addonNumber;
    char orderPrompt[100];
    char addonPrompt[100];
    porder->addonCheck = 0;
            do
            {
                logoDisplay();
                posDisplay(menuType, itemNumber);
                printf("Enter Item Number:\n");
                scanf("%d", &itemNumber);
                if(itemNumber < 1 || itemNumber > 10)
                {
                    printf("Invalid Item Number! Please try again.\n");
                    fflush(stdin);
                    sleep(1);
                    printf("\033[2J");
                }
                porder->itemID = itemNumber;
                strcpy(porder->itemName, menuItems[itemNumber-1].itemName);
            }
            while(itemNumber < 1 || itemNumber > 10);

            printf("Enter Quantity of %s:\n", porder->itemName);
            scanf("%d", &itemQuantity);
            porder->itemQuantity = itemQuantity;
            
            if(itemNumber > 0 && itemNumber < 8)
                do
                {
                    printf("Do you want any add-ons? (Y/N)\n");
                    scanf("%s", addonPrompt);
                    if(strcmp(addonPrompt, "Y") == 0 || strcmp(addonPrompt, "y") == 0)
                    {
                        printf("\033[2J");
                        logoDisplay();
                        menuType = 1;
                        porder->addonCheck = 1;
                        posDisplay(menuType, itemNumber-1);
                        printf("Enter Add-on Number:\n");
                        scanf("%d", &addonNumber);
                        porder->addonID = addonNumber;
                        strcpy(porder->addonName, menuItems[itemNumber-1].addon[addonNumber-1].addonName);
                        porder->addonPrice = menuItems[itemNumber-1].addon[addonNumber-1].addonPrice;
                    }
                }
                while(strcmp(addonPrompt, "Y") == 0 || strcmp(addonPrompt, "Y") == 0);

            porder->itemPrice = menuItems[itemNumber-1].itemPrice;
            printf("Do you want to order more? (Y/N)\n");
            scanf("%s", orderPrompt);
            if(strcmp(orderPrompt, "N") == 0 || strcmp(orderPrompt, "n") == 0)
            {
                return false;
            }
            printf("\033[2J");
    return true;
}
void orderReceipt(order *porder, int itemCount)
{
    float total = 0;
    float cash;
    float change;

    printf("\033[2J");
    logoDisplay();
    for(int j = 0; j < 2; j++)
    {
        for(int k = 0; k < MAXLENGTH; k++)
        {
            printf("=");
        }
        printf("\n");
        if(j == 0)
        {
            printf("Name                                                Quantity    Price\n");
            for(int i = 0; i < itemCount; i++)
            {
                if(porder->addonCheck == 1)
                {
                    printf("%-40s\t\t%d\t%.2f\n", strcat(strcat(porder->itemName, " with "), porder->addonName), porder->itemQuantity, (porder->itemPrice+porder->addonPrice)*porder->itemQuantity);
                }
                else
                {
                    printf("%-40s\t\t%d\t%.2f\n", porder->itemName, porder->itemQuantity, porder->itemPrice*porder->itemQuantity);
                }
                
                total += (porder->itemPrice+porder->addonPrice)*porder->itemQuantity;
                porder++;
            }
        }
    }
    printf("Your total is %.2f\n", total);
    printf("Enter cash amount:\n");
    scanf("%f", &cash);
    change = cash-total;
    printf("Your change is: %.2f", change);
}

int main()
{
    order *orders;
    orders = (order *) malloc(MAXORDER * sizeof(order));
    bool orderLoop = false;
    int itemCount = 0;

    do
    {
        orderLoop = orderInput(orders+itemCount);
        itemCount++;
    } while (orderLoop);
    
    orderReceipt(orders, itemCount);
    return 0;
}