#include <stdio.h>
#include <ctype.h>
#define ITEMLIMIT 4

    void updateinventory(int productcode[],int quantity[],float price[],int *pCounter) {
        char choice;
        for(int i=*pCounter;i<ITEMLIMIT;i++) {
            (*pCounter)++;
            printf("Enter product code: ");
            scanf("%d",&productcode[i]);
            printf("Enter quantity: ");
            scanf("%d",&quantity[i]);
            printf("Enter price: ");
            scanf("%f",&price[i]);
            printf("Do you want to add more items: ");
            scanf(" %c",&choice); 
            choice=toupper(choice);           
        if(choice=='N')
            break;
        }
    }
    void displayinventory(int productcode[],int quantity[],float price[],int *pCounter) {
        printf("--------INVENTORY--------\n");
        printf("Product Code\tQuantity in stock\tPrice per Product\n");
        for(int i=0;i<*pCounter;i++) {
            printf("%d \t\t%d\t\t\tPKR%.2f\n",productcode[i],quantity[i],price[i]);
        }
    }
    void addtocart(int productcode[],int quantity[],int purchaseqty[],int *pCounter,float purchasepc[],float price[]) {
        char choice;
        int productchosen[ITEMLIMIT]={0};
        for(int i=0;i<*pCounter;i++) {
        printf("Enter the product code of the item you want to add to your cart: ");
        scanf("%d",&productchosen[i]);
        printf("How many items do you want to purchase: ");
        scanf("%d",&purchaseqty[i]);
        fflush(stdin);
        quantity[i]-=purchaseqty[i];
        purchasepc[i]+=purchaseqty[i]*price[i];
           printf("Do you want to add more items to the cart: ");
            scanf(" %c",&choice);
            choice=toupper(choice);            
        if(choice=='N')
            break;
        }

    }

    float discount(float total) {
        float discountedprice=0;
        discountedprice+=total*0.75;
        return discountedprice;
    }

    void printbill(float purchasepc[],char cnic[],char phone[],int productcode[],int purchaseqty[],float price[],int *pCounter) {
        float total=0,discountedpc=0;
        char choice;
        for(int i=0;i<*pCounter;i++) {
            total+=purchasepc[i];
        }
        printf("Do you have a discount voucher: ");
        scanf(" %c",&choice);
        if(choice=='Y')
        discountedpc=discount(total);
        printf("-------Bill------\n");
        printf("Costumer details\n");
        printf("CNIC:%s\nPhone number:%s\nTotal Price:PKR%.2f\n",cnic,phone,total);
        printf("-----------------\n");
        if(discountedpc>0) {
            printf("Discounted price:PKR%.2f",discountedpc);
        }

    }
    
    void mainmenu(char cnic[],char phone[],int cart[],int *pCounter,int productcode[],float price[],int quantity[],int purchaseqty[],float purchasepc[]) {
    int option;
    char choice;
    printf("-----Main Menu----\n");
    printf("Choose an option:\n1.Update Inventory\n2.Display Inventory\n3.Add to cart\n4.Print bill\n ");
    while(scanf("%d",&option)!=1 || option<1 || option>4) {
        printf("Invalid input.Please enter again: ");
        while(getchar()!='\n');
    }
    switch(option) {
        case 1:
        updateinventory(productcode,quantity,price,pCounter);
        break;
        case 2:
        displayinventory(productcode,quantity,price,pCounter);
        break;
        case 3:
        addtocart(productcode,quantity,purchaseqty,pCounter,purchasepc,price);
        printf("Do you want to purchase the items: ");
        scanf(" %c",&choice);
        break;
        case 4:
        printbill(purchasepc,cnic,phone,productcode,purchaseqty,price,pCounter);
    }
}

    int main() {
    char cnic[20],phone[12];
    int cart[ITEMLIMIT]={0},counter=0,productcode[ITEMLIMIT]={0},quantity[ITEMLIMIT]={0},purchaseqty[ITEMLIMIT]={0},flag=1;
    int *pCounter=&counter;
    float price[ITEMLIMIT]={0},purchasepc[ITEMLIMIT]={0};
    printf("Enter your CNIC: ");
    scanf("%s",cnic);
    printf("Enter phone number: ");
    scanf("%s",phone);
    do {
    mainmenu(cnic,phone,cart,pCounter,productcode,price,quantity,purchaseqty,purchasepc);
    printf("1.Return to main menu\n2.Exit\n");
    scanf("%d",&flag);
    }while(flag==1);
    return 0;
}