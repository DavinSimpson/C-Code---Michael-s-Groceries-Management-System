#ifndef STORERECORDS_H_INCLUDED
#define STORERECORDS_H_INCLUDED


typedef struct
{
    int day;
    int month;
    int year;
} Date;


typedef struct
{
    char itCode[6];
    char itName[50];
    float unitCost;
    int stockAmt;
}Item;

typedef struct
{
    char tranId[6];
    Date tranDate;
    Item tranItem[100];
    int numItems;
    int quantity[100];
    float totCost;
}Transaction;

typedef struct
{
    char memId[6];
    char fName[20];
    char lName[30];
    Date dateJoin;
}Member;

void transTrackInitial();
void stockTrackInitial();
void membTrackInitial();
void timeDelay();
void genString(char *, int);
void assignDate(Date *);
void errorMessage();
void passwordEnter(char *);
void login();
void branchSelect(int *);
void mainMenu();
void newTransaction(Transaction *);
void totCostSet(Transaction *trans);
void transLimitTest();
void emptStockCheck();
void assignItem(Item *);
void dispNamePrice(Item);
void calcTotCost(float, int, float *);
void memCheck(char []);
void dispMember(Member);
float discountMember(float);
void dispTotal(float);
void viewTransactions();
void transSearch();
void clearTransChoice();
void clearTransSingle();
void clearTransAll();
void blankTrans(Transaction *);
void addItem(Item *);
void itemLimitTest();
void updateStock();
void viewStock();
void displayStock(Item);
void itemSearch();
void clearItemChoice();
void clearItemSingle();
void clearItemAll();
void blankItem(Item *);
void addMember(Member *);
void memberLimitTest();
void membView();
void memberSearch();
void clearMembersChoice();
void clearMembersSingle();
void clearMembersAll();
void blankMember(Member *);

#endif // STORERECORDS_H_INCLUDED
