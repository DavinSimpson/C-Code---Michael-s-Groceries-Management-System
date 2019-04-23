#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "storerecords.h"
#include <windows.h>
#include <time.h>
#include <ctype.h>

#define KINGSTONSTOCK "KingstonStock.st"
#define CLARENDONSTOCK "ClarendonStock.st"
#define KINGSTONTRANSACTION "KingstonTransactions.st"
#define CLARENDONTRANSACTION "ClarendonTransactions.st"
#define KINGSTONMEMBERS "KingstonMembers.st"
#define CLARENDONMEMBERS "ClarendonMembers.st"

#define KINGSTONTRANSTRACK "KingstonTransTrack.txt"
#define CLARENDONTRANSTRACK "ClarendonTransTrack.txt"
#define KINGSTONSTOCKTRACK "KingstonStockTrack.txt"
#define CLARENDONSTOCKTRACK "ClarendonStockTrack.txt"
#define KINGSTONMEMBTRACK "KingstonMembTrack.txt"
#define CLARENDONMEMBTRACK "ClarendonMembTrack.txt"

Transaction transactions[50];
Item stock[100];
Member members[50];
int fileChoice;


void transTrackInitial()
{
    FILE *fp;

    if ((fp = fopen(KINGSTONTRANSTRACK, "w")) == NULL)
    {
        fprintf(stderr, "\n\nFile could not open");
    }
    else
    {
        fprintf(fp, "%i", 0);
        fclose(fp);
    }

    if ((fp = fopen(CLARENDONTRANSTRACK, "w")) == NULL)
    {
        fprintf(stderr, "\n\nFile could not open.");
    }
    else
    {
        fprintf(fp, "%i", 0);
        fclose(fp);
    }
}

void stockTrackInitial()
{
    FILE *fp;

    if ((fp = fopen(KINGSTONSTOCKTRACK, "w")) == NULL)
    {
        fprintf(stderr, "\n\nFile could not open");
    }
    else
    {
        fprintf(fp, "%i", 0);
        fclose(fp);
    }

    if ((fp = fopen(CLARENDONSTOCKTRACK, "w")) == NULL)
    {
        fprintf(stderr, "\n\nFile could not open");
    }
    else
    {
        fprintf(fp, "%i", 0);
        fclose(fp);
    }
}

void membTrackInitial()
{
    FILE *fp;

    if ((fp = fopen(KINGSTONMEMBTRACK, "w")) == NULL)
    {
        fprintf(stderr, "\n\nFile could not open.");
    }
    else
    {
        fprintf(fp, "%d", 0);
        fclose(fp);
    }

    if ((fp = fopen(CLARENDONMEMBTRACK, "w")) == NULL)
    {
        fprintf(stderr, "\n\nFile could not open.");
    }
    else
    {
        fprintf(fp, "%d", 0);
        fclose(fp);
    }
}
///timeDelay
void timeDelay()
{
    Sleep(2000);
}

void genString(char *s, int len)
{
    int i;
    const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    srand(time(0));
    for (i = 0; i < len; i++)
    {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void assignDate(Date *dt)
{
  SYSTEMTIME t;

  GetLocalTime(&t);

  dt->day = t.wDay;
  dt->month = t.wMonth;
  dt->year = t.wYear;
}

void errorMessage()
{
    printf("Incorrect Option Entered. Press any key to try again.");
    getch();
    system("cls");
}

void passwordEnter(char *password)
{
    int index = 0;
    char c;

    printf("\nPassword\n");
   /* 13 is ASCII value of Enter key */
   while((c = getch()) != 13)
    {
       if(index < 0)
           index = 0;
       /* 8 is ASCII value of BACKSPACE character */
       if(c == 8){
           putch('\b');
           putch('\0');
           putch('\b');
           index--;
           continue;
       }

       if ((c == 'M') || (c == 'P') || (c == 'H') || (c == 'K'))
       {
           continue;
       }


       if ((isalpha(c) > 0) || (isdigit(c) > 0))
       {
            password[index++] = c;
            putch('.');
       }
   }
   password[index] = '\0';

}

///login
void login()
{
	char setuser[10] = "14321", setpass[20] = "michaelgrocer", username[10], password[20];
	int match1, match2, passLength;

    do
    {
        printf("                LOGIN               \n\n");
        printf("Username\n");
        scanf("%s", username);

        match1 = strcmp(setuser, username);

        passwordEnter(password);

        passLength = strlen(setpass);
        match2 = strncmp(setpass, password, passLength);

        if ((match1 == 0) && (match2 == 0))
        {
            printf("\n\nAccess Granted.\n");
            printf("Press any key to proceed.");
            getch();
            system("cls");
            branchSelect(&fileChoice);
        }

        else
        {
            printf("\nInvalid Username or Password.\n");
            printf("Press a key to try again\n\n");
            getch();
            system("cls");
        }
    }
    while ((match1 != 0) || (match2 != 0));
}

///branchSelect
void branchSelect(int *choiceFile)
{
    int branch;

    do
    {
        fflush(stdin);
        printf("                SELECT A BRANCH               \n\n");
        printf("1. Kingston\n");
        printf("2. Clarendon\n\n");
        printf("\nOption: ");
        scanf("%i", &branch);



        switch (branch)
        {
            case 1:
                system("cls");
                *choiceFile = 1;
                //printf("%i\n\n", *choiceFile);
                mainMenu();
                break;
            case 2:
                system("cls");
                *choiceFile = 2;
                //printf("%i\n\n", *choiceFile);
                mainMenu();
                break;
            default:
                fflush(stdin);
                if (isdigit(branch))
                {
                    printf("\nEnter a valid number option. Press any key to try again.");
                    getch();
                    system("cls");
                }
                else
                {
                    printf("\nNot a number option. Press any key to try again.");
                    getch();
                    system("cls");
                }
                //errorMessage();
        }


    } while((branch < 1) || (branch > 2));
}

///mainMenu
void mainMenu()
{
    int choice;

    do
    {
        printf("              MAIN MENU\n\n");
        printf("---TRANSACTIONS--\n");
        printf("1. New Transaction\n");
        printf("2. Transaction History\n");
        printf("3. Transaction Search\n");
        printf("4. Clear Transactions\n");
        printf("-------STOCK------\n");
        printf("5. Add Item to Stock\n");
        printf("6. Update Item Stock\n");
        printf("7. Stock View\n");
        printf("8. Item Search\n");
        printf("9. Clear Stock\n");
        printf("-------MEMBERS----\n");
        printf("10. Add New Member\n");
        printf("11. View Members\n");
        printf("12. Members Search\n");
        printf("13. Clear Members\n");
        printf("-------------------\n");
        printf("14. Exit Program\n\n");
        printf("Option: ");
        scanf("%i", &choice);

        switch (choice)
        {
            case 1:
                system("cls");
                newTransaction(transactions);
                //printf("New Transaction");
                break;
            case 2:
                system("cls");
                //printf("Trans History");
                viewTransactions();
                break;
            case 3:
                system("cls");
                transSearch();
                //printf("Trans Search");
                break;
            case 4:
                system("cls");
                //printf("Clear Transactions");
                clearTransChoice();
                break;
            case 5:
                system("cls");
                addItem(stock);
                //printf("Add Item");
                break;
            case 6:
                system("cls");
                //printf("Update Stock");
                updateStock();
                break;
            case 7:
                system("cls");
                //printf("Stock View");
                viewStock();
                break;
            case 8:
                system("cls");
                //printf("Item Search");
                itemSearch();
                break;
            case 9:
                system("cls");
                //printf("Clear Stock");
                clearItemChoice();
                break;
            case 10:
                system("cls");
                addMember(members);
                //printf("Add Member.");
                break;
            case 11:
                system("cls");
                //printf("View Members");
                membView();
                break;
            case 12:
                system("cls");
                //printf("Members Search");
                memberSearch();
                break;
            case 13:
                system("cls");
                //printf("Clear Members");
                clearMembersChoice();
                break;
            case 14:
                system("cls");
                printf("Exit Program");
                exit(0);
                break;
            default:
                fflush(stdin);
                if (isdigit(choice))
                {
                    printf("\nEnter a valid number option. Press any key to try again.");
                    getch();
                    system("cls");
                }
                else
                {
                    printf("\nNot a number option. Press any key to try again.");
                    getch();
                    system("cls");
                }

                //errorMessage();
                //printf("Error");
        }
    } while ((choice < 1) || (choice > 14));


}

void newTransaction(Transaction *trans)
{
    FILE *fp;
    int itemTrack = 0, transTrack, match1, match2, match3;
    char membChoice, transChoice;
    char memberId[5];
    float gctPrice;

    emptStockCheck();
    transLimitTest();

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONTRANSTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &transTrack);
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONTRANSTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &transTrack);
                fclose(fp);
            }
            break;
        }
    }

    totCostSet(trans);

    do
    {
        //check if stock is empty

        //prompt for and read item code
        fflush(stdin);
        printf("Item Code ('NULL' ends transaction enter): ");
        scanf("%s", trans->tranItem[itemTrack].itCode);
        //test code entered
        fflush(stdin);

        match1 = strcmp(trans->tranItem[itemTrack].itCode, "NULL");
        match2 = strcmp(trans->tranItem[itemTrack].itCode, "Null");
        match3 = strcmp(trans->tranItem[itemTrack].itCode, "null");

        ///while loop
        //do loop while code is not equal to NULL
        while ((match1 != 0) && ((match2 != 0)) && ((match3 != 0)))
        {
            //scan through stock
            assignItem(&trans->tranItem[itemTrack]);
            //display name and price
            //prompt for quantity (if found)
            printf("Quantity: ");
            scanf("%d", &trans->quantity[itemTrack]);
            gctPrice = (trans->tranItem[itemTrack].unitCost) + ((trans->tranItem[itemTrack].unitCost) * 0.165);
            //calculate total cost
            calcTotCost(gctPrice, trans->quantity[itemTrack], &trans->totCost);
            printf("\nCurrent Total: %.2f\n", trans->totCost);
            //reprompt and read item code
            trans->numItems++;
            itemTrack++;
            fflush(stdin);
            printf("Item Code ('NULL' ends transaction enter): ");
            scanf("%s", trans->tranItem[itemTrack].itCode);
            fflush(stdin);
            //test code entered
            match1 = strcmp(trans->tranItem[itemTrack].itCode, "NULL");
            match2 = strcmp(trans->tranItem[itemTrack].itCode, "Null");
            match3 = strcmp(trans->tranItem[itemTrack].itCode, "null");
        }

        printf("\nFinal Total: %.2f\n", trans->totCost);
        assignDate(&trans->tranDate);
        genString(trans->tranId, 6);
        trans->tranId[sizeof(trans->tranId) - 1] = '\0';
        printf("Transaction ID: %s\n", trans->tranId);

        ///while ends here
        //prompt if customer is member
        fflush(stdin);
        printf("\nIs Customer a Member? \nY - Yes \nAny other key - No \nOption: ");
        scanf("%c", &membChoice);
        fflush(stdin);

        if ((membChoice == 'Y') || (membChoice == 'y'))
        {
            //if yes, check if list empty
            printf("Enter Member ID: ");
            scanf("%s", memberId);
            //include validation
            memCheck(memberId);
            trans->totCost = discountMember(trans->totCost);
        }

        //if no, proceed
        //determine customer's change
        dispTotal(trans->totCost);
        //option to accept another transaction
        //write transaction to file

        switch (fileChoice)
        {
            case 1:
            {
                if ((fp = fopen(KINGSTONTRANSACTION, "ab")) == NULL)
                {
                    fprintf(stderr, "\nFile could not open.\n");
                }
                else
                {
                    fwrite(trans, sizeof(Transaction), 1, fp);
                    fclose(fp);
                }
                break;
            }
            case 2:
            {
                if ((fp = fopen(CLARENDONTRANSACTION, "ab")) == NULL)
                {
                    fprintf(stderr, "\nFile could not open.\n");
                }
                else
                {
                    fwrite(trans, sizeof(Transaction), 1, fp);
                    fclose(fp);
                }
                break;
            }
        }

        fflush(stdin);
        printf("Enter Another Transaction? \nY - Yes \n Any other key - N \nOption: ");
        scanf("%c", &transChoice);

        if ((transChoice == 'Y') || (transChoice == 'y'))
        {
            //accept another transaction
            trans++;
            transTrack++;

        }

        else
        {
            transTrack++;

            switch (fileChoice)
            {
                case 1:
                {
                    if ((fp = fopen(KINGSTONTRANSTRACK, "w")) == NULL)
                    {
                        fprintf(stderr, "\n\nFile could not open.\n");
                    }
                    else
                    {
                        fprintf(fp, "%i", transTrack);
                        fclose(fp);
                    }
                    break;
                }
                case 2:
                {
                    if ((fp = fopen(KINGSTONTRANSTRACK, "w")) == NULL)
                    {
                        fprintf(stderr, "\n\nFile could not open.\n");
                    }
                    else
                    {
                        fprintf(fp, "%i", transTrack);
                        fclose(fp);
                    }
                    break;
                }
            }

            system("cls");
            mainMenu();
        }

    } while ((transChoice == 'y') || (transChoice == 'Y'));

}

void totCostSet(Transaction *trans)
{
    FILE *fp;
    int transTrack, i;

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONTRANSTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &transTrack);
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONTRANSTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &transTrack);
                fclose(fp);
            }
            break;
        }
    }

    for (i = transTrack; i < 50; i++)
    {
        trans->totCost = 0;
        trans->numItems = 0;
        trans++;
    }
    //read trans track from file
    //from it till limit, set tot cost to zero

}

void transLimitTest()
{
    FILE *fp;
    int transTrack, choice;

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONTRANSTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &transTrack);
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONTRANSTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &transTrack);
                fclose(fp);
            }
            break;
        }
    }
    if (transTrack >= 50)
    {
        printf("Transaction File is Full. Will You Clear the file?\n1. Yes\n2. No.");
        scanf("%i", &choice);

        switch (choice)
        {
            case 1:
            {
                clearTransAll();
                break;
            }
            case 2:
            {
                printf("Returning to Main Menu...");
                timeDelay();
                system("cls");
                mainMenu();
                break;
            }
        }

    }
}

void emptStockCheck()
{
    FILE *fp;
    long size;

    switch (fileChoice)
    {
        case 1:
        {
            //open stock file
            if ((fp = fopen(KINGSTONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                //scan through
                //if empty, give prompt "cant add transaction", return to main menu
                fseek(fp, 0, SEEK_END);
                size = ftell(fp);

                if (size == 0)
                {
                    printf("Stock is Empty. Cannot add transaction.\n");
                    printf("Returning to Main Menu...\n");
                    //delay
                    timeDelay();
                    system("cls");
                    mainMenu();
                }
                //if not empty, proceed with transaction
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            //open stock file
            if ((fp = fopen(CLARENDONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                //scan through
                //if empty, give prompt "cant add transaction", return to main menu
                fseek(fp, 0, SEEK_END);
                size = ftell(fp);

                if (size == 0)
                {
                    printf("Stock is Empty. Cannot add transaction.\n");
                    printf("Returning to Main Menu...\n");
                    //delay
                    timeDelay();
                    system("cls");
                    mainMenu();
                }
                //if not empty, proceed with transaction
                fclose(fp);
            }
            break;
        }
    }
}

void assignItem(Item *it)
{
    FILE *fp;
    int match = -1;
    Item tmp;

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not be found.\n");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (match != 0)
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, it->itCode);
                }
                if (match == 0)
                {
                    *it = tmp;
                    dispNamePrice(*it);
                }
                if (match != 0)
                {
                    printf("\nMatch not found.\n");
                    break;
                }

                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not be found.\n");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (match != 0)
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, it->itCode);
                }

                if (match == 0)
                {
                    *it = tmp;
                    dispNamePrice(*it);
                }
                if (match != 0)
                {
                    printf("\nMatch not found.\n");
                    break;
                }
                fclose(fp);
            }
            break;
        }
    }
}

void dispNamePrice(Item it)
{
    printf("NAME     |     PRICE\n");
    printf("--------------------\n");
    printf("%s\t|     %.2f\n\n", it.itName, it.unitCost);


    //printf("Name: %s\n", it.itName);
    //printf("Unit Price: %.2f\n\n", it.unitCost);
}

void calcTotCost(float uniCost, int quantity, float *totCostAccept)
{
    float itemCost;

    itemCost = uniCost * quantity;
    *totCostAccept = itemCost + *totCostAccept;
}


///edit
void memCheck(char memberId[])
{
    FILE *fp;
    Member tmp;
    int match = -1;


    //open members file
    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONMEMBERS, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (match != 0)
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Member), 1, fp);
                    match = strcmp(tmp.memId, memberId);
                }

                if (match == 0)
                {
                    dispMember(tmp);
                }

                if (match != 0)
                {
                    printf("\nMember could not be found.\n");//probably do a loop that does until valid item code etc etc
                }
                //search file for matching member id
                //if found, assign member information
                //display member information
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONMEMBERS, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (match != 0)
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Member), 1, fp);
                    match = strcmp(tmp.memId, memberId);
                }

                if (match == 0)
                {
                    dispMember(tmp);
                }

                if (match != 0)
                {
                    printf("\nMember could not be found.\n");//probably do a loop that does until valid item code etc etc
                }
                //search file for matching member id
                //if found, assign member information
                //display member information
                fclose(fp);
            }
            break;
        }

    }

}

float discountMember(float totCost)
{
    float discount, discCost;
    //apply 20% discount to price
    discount = (20 / 100) * totCost;
    discCost = totCost - discount;
    //return value
    return discCost;
}

void dispMember(Member memb)
{
    printf("Name: %s %s\n", memb.fName, memb.lName);
    printf("ID: %s\n\n", memb.memId);
}

void dispTotal(float totPrice)
{
    float amtGiven, change;

    //display total price
    printf("\nFinal Price: %.2f\n", totPrice);
    printf("Amount of Money Given: ");
    //accept amount of money received
    scanf("%f", &amtGiven);
    //calculate change to received
    change = amtGiven - totPrice;
    printf("Change: %.2f\n\n", change);
}

void viewTransactions()
{
    FILE *fp;
    Transaction tmp;
    int i;
    float totCost;

    //read transaction from file
    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONTRANSACTION, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                printf("TRANSACTION DATE\tID\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                rewind(fp);
                while (!feof(fp))
                {
                    fread(&tmp, sizeof(Transaction), 1, fp);
                    if (!feof(fp))
                    {
                        printf("%d/%d/%d\t%s\n", tmp.tranDate.day, tmp.tranDate.month, tmp.tranDate.year, tmp.tranId);
                        for (i = 0; i < (tmp.numItems); i++)
                        {
                            totCost = (tmp.quantity[i]) * (tmp.tranItem[i].unitCost);
                            printf("%s\t%s\n%i\t%.2f\t%.2f\n", tmp.tranItem[i].itCode, tmp.tranItem[i].itName, tmp.quantity[i], tmp.tranItem[i].unitCost, totCost);
                            printf("\t\t ---- \t\t\n");
                        }
                        printf("\nFINAL COST: %.2f\n", tmp.totCost);
                    printf("------------------------------------------------------------------------------\n");
                    }
                }
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONTRANSACTION, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                printf("TRANSACTION DATE\tID\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                rewind(fp);
                while (!feof(fp))
                {
                    fread(&tmp, sizeof(Transaction), 1, fp);
                    if (!feof(fp))
                    {
                        printf("%d/%d/%d\t%s\n", tmp.tranDate.day, tmp.tranDate.month, tmp.tranDate.year, tmp.tranId);
                        for (i = 0; i < (tmp.numItems); i++)
                        {
                            totCost = (tmp.quantity[i]) * (tmp.tranItem[i].unitCost);
                            printf("%s\t%s\n%i\t%.2f\t%.2f\n", tmp.tranItem[i].itCode, tmp.tranItem[i].itName, tmp.quantity[i], tmp.tranItem[i].unitCost, totCost);
                            printf("\t\t ---- \t\t\n");
                        }
                        printf("\nFINAL COST: %.2f\n", tmp.totCost);
                    printf("------------------------------------------------------------------------------\n");
                    }
                }
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void transSearch()
{
    FILE *fp;
    int found, match = -1, i;
    float totCost;
    char search[6];
    Transaction tmp, foundTrans;

    printf("ID of Transaction: ");
    scanf("%s", search);
    search[sizeof(search) - 1] = '\0';

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONTRANSACTION, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (!feof(fp))
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Transaction), 1, fp);
                    match = strcmp(tmp.tranId, search);
                    //printf("\n match: %i\n", match);
                    if (match == 0)
                    {
                        found = 1;
                        foundTrans = tmp;
                    }
                }
                if (found == 1)
                {
                    printf("Match Found.\n\n");
                    printf("RESULT\n\n");
                    printf("TRANSACTION DATE\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                    printf("%d/%d/%d\n", foundTrans.tranDate.day, foundTrans.tranDate.month, foundTrans.tranDate.year);
                        for (i = 0; i < (foundTrans.numItems); i++)
                        {
                            totCost = (foundTrans.quantity[i]) * (foundTrans.tranItem[i].unitCost);
                            printf("%s\t%s\n%i\t%.2f\t%.2f\n", foundTrans.tranItem[i].itCode, foundTrans.tranItem[i].itName, foundTrans.quantity[i], foundTrans.tranItem[i].unitCost, totCost);
                            printf("\t\t ---- \t\t\n");
                        }
                        printf("\nFINAL COST: %.2f\n", foundTrans.totCost);
                    printf("------------------------------------------------------------------------------\n");
                }
                else
                {
                    printf("Match Not Found\n\n");
                }
            fclose(fp);
            }
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONTRANSACTION, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (!feof(fp))
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Transaction), 1, fp);
                    match = strcmp(tmp.tranId, search);
                    printf("\n match: %i\n", match);
                    if (match == 0)
                    {
                        found = 1;
                        foundTrans = tmp;
                    }
                }
                if (found == 1)
                {
                    printf("Match Found.\n\n");
                    printf("RESULT\n\n");
                    printf("TRANSACTION DATE\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                    printf("%d/%d/%d\n", foundTrans.tranDate.day, foundTrans.tranDate.month, foundTrans.tranDate.year);
                        for (i = 0; i < (foundTrans.numItems); i++)
                        {
                            totCost = (foundTrans.quantity[i]) * (foundTrans.tranItem[i].unitCost);
                            printf("%s\t%s\n%i\t%.2f\t%.2f\n", foundTrans.tranItem[i].itCode, foundTrans.tranItem[i].itName, foundTrans.quantity[i], foundTrans.tranItem[i].unitCost, totCost);
                            printf("\t\t ---- \t\t\n");
                        }
                        printf("\nFINAL COST: %.2f\n", foundTrans.totCost);
                    printf("------------------------------------------------------------------------------\n");
                }
                else
                {
                    printf("Match Not Found\n\n");
                }
            fclose(fp);
            }
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void clearTransChoice()
{
   int choice;

    printf("Removal Method\n1. Single Transaction\n2. All Transactions\nOption: ");
    scanf("%i", &choice);

    switch (choice)
    {
        case 1:
            system("cls");
            clearTransSingle();
            break;
        case 2:
            system("cls");
            //clearItemAll();
            break;
    }
}

void clearTransSingle()
{
    FILE *fp;
    Transaction tmp;
    char id[6];
    int transTrack = 0, match, i, numItems;
    float totCost;

    //read item id
    printf("Code of Transaction to Clear: ");
    scanf("%s", id);
    id[sizeof(id) - 1] = '\0';

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONTRANSACTION, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    transTrack++;
                    fread(&tmp, sizeof(Transaction), 1, fp);
                    match = strcmp(tmp.tranId, id);

                }while(match != 0);

                printf("TRANSACTION DATE\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                printf("%d/%d/%d\n", tmp.tranDate.day, tmp.tranDate.month, tmp.tranDate.year);
                for (i = 0; i < (tmp.numItems); i++)
                {
                    totCost = (tmp.quantity[i]) * (tmp.tranItem[i].unitCost);
                    printf("%s\t%s\n%i\t%.2f\t%.2f\n", tmp.tranItem[i].itCode, tmp.tranItem[i].itName, tmp.quantity[i], tmp.tranItem[i].unitCost, totCost);
                    printf("\t\t ---- \t\t\n");
                }
                printf("----------------------------------------\n");
                numItems = tmp.numItems;
                blankTrans(&tmp);
                fseek(fp, (transTrack - 1) * sizeof(Transaction), SEEK_SET);
                fwrite(&tmp, sizeof(Transaction), 1, fp);
                printf("\nUPDATED TRANSACTION\n");
                printf("TRANSACTION DATE\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                printf("%d/%d/%d\n", tmp.tranDate.day, tmp.tranDate.month, tmp.tranDate.year);
                for (i = 0; i < numItems; i++)
                {
                    totCost = (tmp.quantity[i]) * (tmp.tranItem[i].unitCost);
                    printf("%s\t%s\n%i\t%.2f\t%.2f\n", tmp.tranItem[i].itCode, tmp.tranItem[i].itName, tmp.quantity[i], tmp.tranItem[i].unitCost, totCost);
                    printf("\t\t ---- \t\t\n");
                }
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;

        }
        case 2:
        {
            if ((fp = fopen(CLARENDONTRANSACTION, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    transTrack++;
                    fread(&tmp, sizeof(Transaction), 1, fp);
                    match = strcmp(tmp.tranId, id);

                }while(match != 0);

                printf("TRANSACTION DATE\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                printf("%d/%d/%d\n", tmp.tranDate.day, tmp.tranDate.month, tmp.tranDate.year);
                for (i = 0; i < (tmp.numItems); i++)
                {
                    totCost = (tmp.quantity[i]) * (tmp.tranItem[i].unitCost);
                    printf("%s\t%s\n%i\t%.2f\t%.2f\n", tmp.tranItem[i].itCode, tmp.tranItem[i].itName, tmp.quantity[i], tmp.tranItem[i].unitCost, totCost);
                    printf("\t\t ---- \t\t\n");
                }
                printf("----------------------------------------\n");
                numItems = tmp.numItems;
                blankTrans(&tmp);
                fseek(fp, (transTrack - 1) * sizeof(Transaction), SEEK_SET);
                fwrite(&tmp, sizeof(Transaction), 1, fp);
                printf("\nUPDATED TRANSACTION\n");
                printf("TRANSACTION DATE\nITEM CODE\tITEM NAME\nQUANTITY    UNIT COST    TOTAL COST\n\n");
                printf("%d/%d/%d\n", tmp.tranDate.day, tmp.tranDate.month, tmp.tranDate.year);
                for (i = 0; i < numItems; i++)
                {
                    totCost = (tmp.quantity[i]) * (tmp.tranItem[i].unitCost);
                    printf("%s\t%s\n%i\t%.2f\t%.2f\n", tmp.tranItem[i].itCode, tmp.tranItem[i].itName, tmp.quantity[i], tmp.tranItem[i].unitCost, totCost);
                    printf("\t\t ---- \t\t\n");
                }
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void clearTransAll()
{
    FILE *fp;

    printf("Working...");

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONTRANSACTION, "wb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fclose(fp);
            }
            timeDelay();
            printf("Transactions Cleared.\n");
            printf("Press any key to continue.\n");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONTRANSACTION, "wb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fclose(fp);
            }
            timeDelay();
            printf("Transactions Cleared.\n");
            printf("Press any key to continue.\n");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }

}

void blankTrans(Transaction *trans)
{
    int i;

    trans->tranDate.day = 0;
    trans->tranDate.month = 0;
    trans->tranDate.year = 0;
    strcpy(trans->tranId, "--");
    trans->totCost = 0;

    for (i = 0; i < trans->numItems; i++)
    {
        strcpy(trans->tranItem[i].itCode, "--");
        strcpy(trans->tranItem[i].itName, "--");
        trans->tranItem[i].stockAmt = 0;
        trans->tranItem[i].unitCost = 0;
        trans->quantity[i] = 0;
    }
    trans->numItems = 0;
}

void addItem(Item *it)
{
    FILE *fp;
    int stockTrack;
    char stockChoice;
    Item stock;

    itemLimitTest();


    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCKTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &stockTrack);
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCKTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &stockTrack);
                fclose(fp);
            }
            break;
        }
    }



    do
    {

        //generate item id
        genString(stock.itCode, 6);

        stock.itCode[sizeof(stock.itCode) - 1] = '\0';

        //prompt for item name
        fflush(stdin);
        printf("Item Name: ");
        fgets(stock.itName, sizeof(stock.itName), stdin);

        //copy name to stockItem
        strcpy(it->itName, stock.itName);


        //copy id to stockItem
        strcpy(it->itCode, stock.itCode);

        //prompt for item stock quantity
        printf("Item Stock Amount: ");
        scanf("%d", &stock.stockAmt);


        //prompt item unit cost
        printf("Item Unit Cost: ");
        scanf("%f", &stock.unitCost);

        it->stockAmt = stock.stockAmt;
        it->unitCost = stock.unitCost;


        //display data entered to user
        printf("\nDATA ENTERED\n");
        printf("Item Name: %s", it->itName);
        printf("Item Stock Amount: %d\n", it->stockAmt);
        printf("Item Unit Cost: %.2f\n", it->unitCost);

        //print all data entered.
        printf("Item Code is %s\n", it->itCode);

        //
        printf("Press any key to proceed.\n");
        getch();



        switch (fileChoice)
        {
            case 1:
            {
                if ((fp = fopen(KINGSTONSTOCK, "ab")) == NULL)
                {
                    fprintf(stderr, "File could not open.");
                }
                else
                {
                    fwrite(it, sizeof(Item), 1, fp);
                    fclose(fp);
                }
                break;
            }
            case 2:
            {
                if ((fp = fopen(CLARENDONSTOCK, "ab")) == NULL)
                {
                    fprintf(stderr, "File could not open.");
                }
                else
                {
                    fwrite(it, sizeof(Item), 1, fp);
                    fclose(fp);
                }
                break;
            }
        }

        //option to add another item
        fflush(stdin);
        printf("\nEnter Another Item? \nY - Yes \nAny other key - No\n Option: ");
        scanf("%c", &stockChoice);
        fflush(stdin);

        if ((stockChoice == 'y') || (stockChoice == 'Y'))
        {
            it++;
            stockTrack++;
            system("cls");
        }

        else
        {
            stockTrack++;

            switch (fileChoice)
            {
                case 1:
                {
                    if ((fp = fopen(KINGSTONSTOCKTRACK, "w")) == NULL)
                    {
                        fprintf(stderr, "\n\nFile could not open.");
                    }
                    else
                    {
                        fprintf(fp, "%i", stockTrack);
                        fclose(fp);
                    }
                    break;
                }
                case 2:
                {
                    if ((fp = fopen(CLARENDONSTOCKTRACK, "w")) == NULL)
                    {
                        fprintf(stderr, "\n\nFile could not open.");
                    }
                    else
                    {
                        fprintf(fp, "%i", stockTrack);
                        fclose(fp);
                    }
                    break;
                }
            }


            system("cls");
            mainMenu();
        }

    } while((stockChoice == 'Y') || (stockChoice == 'y'));
}

void itemLimitTest()
{
    FILE *fp;
    int stockTrack, choice;

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCKTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &stockTrack);
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCKTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                fscanf(fp, "%i", &stockTrack);
                fclose(fp);
            }
            break;
        }
    }

    if (stockTrack >= 100)
    {
        printf("Stock File is Full. Will You Clear the file?\n1. Yes\n2. No.");
        scanf("%i", &choice);

        switch (choice)
        {
            case 1:
            {
                clearItemAll();
                break;
            }
            case 2:
            {
                printf("Returning to Main Menu...");
                timeDelay();
                system("cls");
                mainMenu();
                break;
            }
        }

    }
}

void updateStock()
{
    FILE *fp;
    Item tmp;
    char id[6];
    int stockTrack = 0, match, choice, addAmt, reduceAmt;

    //read item id
    printf("Code of Item to Update: ");
    scanf("%s", id);
    id[sizeof(id) - 1] = '\0';

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCK, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    stockTrack++;
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, id);

                }while(match != 0);

                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                printf("----------------------------------------\n");
                printf("How to Update Stock?\n1. Add To\n2. Reduce\nOption: ");
                scanf("%i", &choice);
                switch (choice)
                {
                    case 1:
                    {
                        printf("Amount to Add: ");
                        scanf("%i", &addAmt);
                        tmp.stockAmt = tmp.stockAmt + addAmt;
                        break;
                    }
                    case 2:
                    {
                        printf("Amount to Remove: ");
                        scanf("%i", &reduceAmt);
                        tmp.stockAmt = tmp.stockAmt - reduceAmt;
                        break;
                    }
                }
                fseek(fp, (stockTrack - 1) * sizeof(Item), SEEK_SET);
                fwrite(&tmp, sizeof(Item), 1, fp);
                printf("\nUPDATED ITEM\n");
                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCK, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    stockTrack++;
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, id);

                }while(match != 0);

                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                printf("----------------------------------------\n");
                printf("How to Update Stock?\n1. Add To\n2. Reduce\nOption: ");
                scanf("%i", &choice);
                switch (choice)
                {
                    case 1:
                    {
                        printf("Amount to Add: ");
                        scanf("%i", &addAmt);
                        tmp.stockAmt = tmp.stockAmt + addAmt;
                        break;
                    }
                    case 2:
                    {
                        printf("Amount to Remove: ");
                        scanf("%i", &reduceAmt);
                        tmp.stockAmt = tmp.stockAmt - reduceAmt;
                        break;
                    }
                }
                fseek(fp, (stockTrack - 1) * sizeof(Item), SEEK_SET);
                fwrite(&tmp, sizeof(Item), 1, fp);
                printf("\nUPDATED ITEM\n");
                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }

}

void viewStock()
{
    FILE *fp;
    Item tmp;
    //read stock file
    //display stock, while not at the end of file
    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open");
            }
            else
            {
                printf("ITEM CODE\tITEM NAME\nSTOCK AMOUNT\tPRICE\n\n");
                rewind(fp);
                while (!feof(fp))
                {
                    fread(&tmp, sizeof(Item), 1, fp);
                    if (!feof(fp))
                    {
                        displayStock(tmp);
                        printf("------------------------------------------------------------------------------\n");
                    }
                }
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open");
            }
            else
            {
                printf("ITEM CODE\tITEM NAME\nSTOCK AMOUNT\tPRICE\n\n");
                rewind(fp);
                while (!feof(fp))
                {
                    fread(&tmp, sizeof(Item), 1, fp);
                    if (!feof(fp))
                    {
                        displayStock(tmp);
                        printf("------------------------------------------------------------------------------\n");
                    }
                }
                fclose(fp);
            }
            break;
        }
    }

    printf("Press any key to continue.\n");
    getch();
    system("cls");
    mainMenu();
}

void displayStock(Item it)
{
    printf("%s\t", it.itCode);
    puts(it.itName);
    printf("%i\t%.2f\n", it.stockAmt, it.unitCost);
}

void itemSearch()
{
    FILE *fp;
    int found, match = -1;
    char search[6];
    Item tmp, foundItem;

    printf("ID of Item: ");
    scanf("%s", search);
    search[sizeof(search) - 1] = '\0';

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (!feof(fp))
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, search);
                    //printf("\n match: %i\n", match);
                    if (match == 0)
                    {
                        found = 1;
                        foundItem = tmp;
                    }
                }
                if (found == 1)
                {
                    printf("Match Found.\n\n");
                    printf("RESULT\n\n");
                    printf("ITEM CODE\tITEM NAME\nSTOCK AMOUNT\tPRICE\n\n");
                    printf("%s\t%s\t%i\t%.2f\n", foundItem.itCode, foundItem.itName, foundItem.stockAmt, foundItem.unitCost);
                }
                else
                {
                    printf("Match Not Found\n\n");
                }
            }
            fclose(fp);
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCK, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (!feof(fp))
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, search);
                    printf("\n match: %i\n", match);
                    if (match == 0)
                    {
                        found = 1;
                        foundItem = tmp;
                    }
                }
                if (found == 1)
                {
                    printf("Match Found.\n\n");
                    printf("RESULT\n\n");
                    printf("ITEM CODE\tITEM NAME\nSTOCK AMOUNT\tPRICE\n\n");
                    printf("%s\t%s\t%i\t%.2f\n", foundItem.itCode, foundItem.itName, foundItem.stockAmt, foundItem.unitCost);
                }
                else
                {
                    printf("Match Not Found\n\n");
                }
            }
            fclose(fp);
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }

    }

}

void clearItemChoice()
{
    int choice;

    printf("Removal Method\n1. Single Items\n2. All Items\nOption: ");
    scanf("%i", &choice);

    switch (choice)
    {
        case 1:
            system("cls");
            clearItemSingle();
            break;
        case 2:
            system("cls");
            clearItemAll();
            break;
    }
}

void clearItemSingle()
{
    FILE *fp;
    Item tmp;
    char id[6];
    int stockTrack = 0, match;

    //read item id
    printf("Code of Item to Clear: ");
    scanf("%s", id);
    id[sizeof(id) - 1] = '\0';

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCK, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    stockTrack++;
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, id);

                } while(match != 0);

                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                printf("----------------------------------------\n");
                blankItem(&tmp);
                fseek(fp, (stockTrack - 1) * sizeof(Item), SEEK_SET);
                fwrite(&tmp, sizeof(Item), 1, fp);
                printf("\nUPDATED ITEM\n");
                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;

        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCK, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    stockTrack++;
                    fread(&tmp, sizeof(Item), 1, fp);
                    match = strcmp(tmp.itCode, id);

                }while(match != 0);

                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                printf("----------------------------------------\n");
                blankItem(&tmp);
                fseek(fp, (stockTrack - 1) * sizeof(Item), SEEK_SET);
                fwrite(&tmp, sizeof(Item), 1, fp);
                printf("\nUPDATED ITEM\n");
                printf("ITEM CODE\tITEM NAME\tSTOCK AMOUNT\tPRICE\n\n");
                printf("%s\t%s\t%i\t%.2f\n", tmp.itCode, tmp.itName, tmp.stockAmt, tmp.unitCost);
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void clearItemAll()
{
    FILE *fp;

    printf("Working.....\n");

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONSTOCK, "wb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open,\n");
            }
            else
            {
                fclose(fp);
            }
            timeDelay();
            printf("Clear Complete.\n");
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONSTOCK, "wb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open,\n");
            }
            else
            {
                fclose(fp);
            }

            timeDelay();
            printf("Clear Complete.\n");
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void blankItem(Item *it)
{
    strcpy(it->itCode, "--");
    strcpy(it->itName, "--");
    it->stockAmt = 0;
    it->unitCost = 0;
}

void addMember(Member *memb)
{
    FILE *fp;
    int membTrack;
    char id[6], membChoice;


    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONMEMBTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                fscanf(fp, "%d", &membTrack);
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONMEMBTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                fscanf(fp, "%d", &membTrack);
                fclose(fp);
            }
            break;
        }
    }

    //read Member Track from file


    memberLimitTest();

    do
    {
        //generate member id
        genString(id, 6);

        id[sizeof(id) - 1] = '\0';

        strcpy(memb->memId, id);

        //prompt user for first name
        fflush(stdin);
        printf("First Name: ");
        scanf("%s", memb->fName);
        //prompt user for last name
        printf("Last Name: ");
        scanf("%s", memb->lName);
        //display info to user
        assignDate(&memb->dateJoin);
        printf("DATE REGISTERED: %d/%d/%d\n", memb->dateJoin.day, memb->dateJoin.month, memb->dateJoin.year);
        printf("Member ID: %s\n\n", memb->memId);

        //write member to file
        switch (fileChoice)
        {
            case 1:
            {
                if ((fp = fopen(KINGSTONMEMBERS, "ab")) == NULL)
                {
                    fprintf(stderr, "\n\nFile could not open.\n");
                }
                else
                {
                    fwrite(memb, sizeof(Member), 1, fp);
                    fclose(fp);
                }
            }
            case 2:
            {
                if ((fp = fopen(CLARENDONMEMBERS, "ab")) == NULL)
                {
                    fprintf(stderr, "\n\nFile could not open.\n");
                }
                else
                {
                    fwrite(memb, sizeof(Member), 1, fp);
                    fclose(fp);
                }
            }
        }
        fflush(stdin);
        printf("Enter Another Member?\nY - Yes\nAny Other Key - No\nOption: ");
        scanf("%c", &membChoice);
        printf("\n");

        if ((membChoice == 'Y') || (membChoice == 'y'))
        {
            memb++;
            membTrack++;
            system("cls");
        }
        else
        {
            membTrack++;

            switch (fileChoice)
            {
                case 1:
                {
                    if ((fp = fopen(KINGSTONMEMBTRACK, "w")) == NULL)
                    {
                        fprintf(stderr, "\n\nFile could not open.");
                    }
                    else
                    {
                        fprintf(fp, "%i", membTrack);
                        fclose(fp);
                    }
                    break;
                }
                case 2:
                {
                    if ((fp = fopen(CLARENDONMEMBTRACK, "w")) == NULL)
                    {
                        fprintf(stderr, "\n\nFile could not open.");
                    }
                    else
                    {
                        fprintf(fp, "%i", membTrack);
                        fclose(fp);
                    }
                    break;
                }
            }


            system("cls");
            mainMenu();
        }

    } while((membChoice == 'Y') || (membChoice == 'y'));

}

void memberLimitTest()
{
    FILE *fp;
    int membTrack, choice;

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONMEMBTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                fscanf(fp, "%d", &membTrack);
                fclose(fp);
            }
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONMEMBTRACK, "r")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                fscanf(fp, "%d", &membTrack);
                fclose(fp);
            }
            break;
        }
    }

    if (membTrack >= 50)
    {
        printf("Member File is Full. Will You Clear the file?\n1. Yes\n2. No.");
        scanf("%i", &choice);

        switch (choice)
        {
            case 1:
            {
                clearMembersAll();
                break;
            }
            case 2:
            {
                printf("Returning to Main Menu...");
                timeDelay();
                system("cls");
                mainMenu();
                break;
            }
        }

    }
}

void membView()
{
    FILE *fp;
    Member tmp;

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONMEMBERS, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                printf("MEMBER ID\tMEMBER NAME\tDATE REGISTERED\n");
                rewind(fp);
                while (!feof(fp))
                {
                    fread(&tmp, sizeof(Member), 1, fp);
                    if (!feof(fp))
                    {
                        printf("%s\t%s %s\t%d/%d/%d\n", tmp.memId, tmp.fName, tmp.lName, tmp.dateJoin.day, tmp.dateJoin.month, tmp.dateJoin.year);
                        printf("----------------------------------------------\n");
                    }
                }
                fclose(fp);
            }
            printf("\n\nPress any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONMEMBERS, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.\n");
            }
            else
            {
                printf("MEMBER ID\tMEMBER NAME\tDATE REGISTERED\n");
                rewind(fp);
                while (!feof(fp))
                {
                    fread(&tmp, sizeof(Member), 1, fp);
                    if (!feof(fp))
                    {
                        printf("%s\t%s %s\t%d/%d/%d\n", tmp.memId, tmp.fName, tmp.lName, tmp.dateJoin.day, tmp.dateJoin.month, tmp.dateJoin.year);
                        printf("----------------------------------------------\n");
                    }
                }
            fclose(fp);
            }
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void memberSearch()
{
    FILE *fp;
    int found, match = -1;
    char search[6];
    Member tmp, foundMember;

    printf("ID of Member: ");
    scanf("%s", search);
    search[sizeof(search) - 1] = '\0';

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONMEMBERS, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (!feof(fp))
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Member), 1, fp);
                    match = strcmp(tmp.memId, search);
                    //printf("\n match: %i\n", match);
                    if (match == 0)
                    {
                        found = 1;
                        foundMember = tmp;
                    }
                }
                if (found == 1)
                {
                    printf("Match Found.\n\n");
                    printf("RESULT\n\n");
                    printf("ID\tNAME\tREGISTER DATE\n");
                    printf("%s\t%s %s\t%i/%i/%i\n\n", foundMember.memId, foundMember.fName, foundMember.lName, foundMember.dateJoin.day, foundMember.dateJoin.month, foundMember.dateJoin.year);
                }
                else
                {
                    printf("Match Not Found\n\n");
                }
            }
            fclose(fp);
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONMEMBERS, "rb")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                //accept item code from transaction.
                //search stock for item code
                while (!feof(fp))
                {
                    //if match found, assign item name and price
                    fseek(fp, 0, SEEK_CUR);
                    fread(&tmp, sizeof(Member), 1, fp);
                    match = strcmp(tmp.memId, search);
                    printf("\n match: %i\n", match);
                    if (match == 0)
                    {
                        found = 1;
                        foundMember = tmp;
                    }
                }
                if (found == 1)
                {
                    printf("Match Found.\n\n");
                    printf("RESULT\n\n");
                    printf("ID\tNAME\tREGISTER DATE\n");
                    printf("%s\t%s %s\t%i/%i/%i\n\n", foundMember.memId, foundMember.fName, foundMember.lName, foundMember.dateJoin.day, foundMember.dateJoin.month, foundMember.dateJoin.year);
                }
                else
                {
                    printf("Match Not Found\n\n");
                }
            }
            fclose(fp);
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }

    }
}

void clearMembersChoice()
{
    int choice;

    printf("Removal Method\n1. Single Members\n2. All Members\nOption: ");
    scanf("%i", &choice);

    switch (choice)
    {
        case 1:
            system("cls");
            clearMembersSingle();
            break;
        case 2:
            system("cls");
            clearMembersAll();
            break;
    }
}

void clearMembersSingle()
{
    FILE *fp;
    Member tmp;
    char id[6];
    int memTrack = 0, match;

    //read item id
    printf("Code of Member to Clear: ");
    scanf("%s", id);
    id[sizeof(id) - 1] = '\0';

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONMEMBERS, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    memTrack++;
                    fread(&tmp, sizeof(Member), 1, fp);
                    match = strcmp(tmp.memId, id);

                }while(match != 0);

                printf("MEMBER ID\tNAME\tDATE JOINED\n\n");
                printf("%s\t%s %s\t%i/%i/%i\n\n", tmp.memId, tmp.fName, tmp.lName, tmp.dateJoin.day, tmp.dateJoin.month, tmp.dateJoin.year);
                printf("----------------------------------------\n");
                blankMember(&tmp);
                fseek(fp, (memTrack - 1) * sizeof(Member), SEEK_SET);
                fwrite(&tmp, sizeof(Item), 1, fp);
                printf("\nUPDATED MEMBER\n");
                printf("MEMBER ID\tNAME\tDATE JOINED\n\n");
                printf("%s\t%s %s\t%i/%i/%i\n\n", tmp.memId, tmp.fName, tmp.lName, tmp.dateJoin.day, tmp.dateJoin.month, tmp.dateJoin.year);
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;

        }
        case 2:
        {
            if ((fp = fopen(KINGSTONMEMBERS, "rb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open.");
            }
            else
            {
                rewind(fp);
                fseek(fp, 0, SEEK_SET);
                do
                {
                    fseek(fp, 0, SEEK_CUR);
                    memTrack++;
                    fread(&tmp, sizeof(Member), 1, fp);
                    match = strcmp(tmp.memId, id);

                }while(match != 0);

                printf("MEMBER ID\tNAME\tDATE JOINED\n\n");
                printf("%s\t%s %s\t%i/%i/%i\n\n", tmp.memId, tmp.fName, tmp.lName, tmp.dateJoin.day, tmp.dateJoin.month, tmp.dateJoin.year);
                printf("----------------------------------------\n");
                blankMember(&tmp);
                fseek(fp, (memTrack - 1) * sizeof(Member), SEEK_SET);
                fwrite(&tmp, sizeof(Item), 1, fp);
                printf("\nUPDATED MEMBER\n");
                printf("MEMBER ID\tNAME\tDATE JOINED\n\n");
                printf("%s\t%s %s\t%i/%i/%i\n\n", tmp.memId, tmp.fName, tmp.lName, tmp.dateJoin.day, tmp.dateJoin.month, tmp.dateJoin.year);
                fclose(fp);
            }

            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void clearMembersAll()
{
    FILE *fp;

    printf("Working.....\n");

    switch (fileChoice)
    {
        case 1:
        {
            if ((fp = fopen(KINGSTONMEMBERS, "wb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open,\n");
            }
            else
            {
                fclose(fp);
            }
            timeDelay();
            printf("Clear Complete.\n");
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
        case 2:
        {
            if ((fp = fopen(CLARENDONMEMBERS, "wb+")) == NULL)
            {
                fprintf(stderr, "\n\nFile could not open,\n");
            }
            else
            {
                fclose(fp);
            }
            timeDelay();
            printf("Clear Complete.\n");
            printf("Press any key to continue.");
            getch();
            system("cls");
            mainMenu();
            break;
        }
    }
}

void blankMember(Member *memb)
{
    strcpy(memb->memId, "--");
    strcpy(memb->fName, "--");
    strcpy(memb->lName, "--");
    memb->dateJoin.day = 0;
    memb->dateJoin.month = 0;
    memb->dateJoin.year = 0;
}
