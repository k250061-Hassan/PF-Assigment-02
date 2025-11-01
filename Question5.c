#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void encodeMessage(char message[]){

        int reverse[MAX_LEN];
        int s = strlen(message);
        int temp;

    temp = message[1];
    message[1] = message[4];
    message[4] = temp;        

    printf("---In letters---: \n");
    for(int i=s-1, j=0; i>=0; i--, j++){
        reverse[j] = message[i];
        printf("%c", reverse[j]);
    }
    printf("\n---Binary Code---\n");
    for(int i=0; i<s; i++){
        for(int j=7; j>=0; j--){
            printf("%d", (reverse[i] >> j) & 1);
        }
    }
    
}

    void decodeMessage(char message[]){
        int reverse[MAX_LEN];
        int s = strlen(message);
        int temp;

            temp = message[1];
            message[1] = message[4];
            message[4] = temp;        
            
    printf("---In letters---: \n");
    for(int i=s-1, j=0; i>=0; i--, j++){
        reverse[j] = message[i];
        printf("%c", reverse[j]);
    }
}

void showMenu(void) {
    printf("\n============================================\n");
      printf("     TCS Message Encoding/Decoding Utility  \n");
      printf("============================================\n");
    printf("1. Encode Message\n");
    printf("2. Decode Message\n");
    printf("3. EXIT\n");
    printf("--------------------------------------------\n");
}

int main(){

    int choice;
    char message[MAX_LEN];

    do{
        showMenu();

        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1){
            printf("\nInvalid Input. Please enter a number\n");
            while(getchar() != '\n');
            continue;
        } while(getchar() != '\n');

        switch(choice){

            case 1: 
            printf("Enter message to Encode: ");
            scanf(" %[^\n]", message);
            while(getchar() != '\n');
            encodeMessage(message);
            break;

            case 2:
            printf("Enter message to Decode: ");
            scanf(" %[^\n]", message);
            while(getchar() != '\n');
            decodeMessage(message);

            case 3:
            printf("Exiting the System. Goodbye!");break;

            default: printf("Invalid option. Please enter between 1-3.");break;
  
        }

    }while(choice != 3);

    return 0;
}