  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void encodeMessage(char message[])
{
    // string reversal
    int len = strlen(message);
    char reversedMessage[len + 1];


    for (int i = 0; i < len; i++)
    {
        reversedMessage[i] = message[len - 1 - i];
    }
    reversedMessage[len] = '\0';

    // toggling the 2nd & 5th bit of the reversedMessage
    // toggling the 2nd and 5th bits means: XOR 18 (16 + 2)
    char encodedMessage[len + 1];
    for (int i = 0; i < len; i++)
    {
        encodedMessage[i] = (char) (reversedMessage[i] ^ 18);     // XOR 18
    }
    encodedMessage[len] = '\0';

    printf("  > Original: %s\n  > Reversed: %s\n  > Encoded: %s", message, reversedMessage, encodedMessage);
}
void decodeMessage(char message[])
{
    // untoggling the 2nd & 5th bit of the message
    int len = strlen(message);
    char decodedMessage[len + 1];
    for (int i = 0; i < len; i++)
    {
        decodedMessage[i] = (char) (message[i] ^ 18);
    }
    decodedMessage[len] = '\0';

    // string reversal of the decodedMessage
    char reversedMessage[len + 1];


    for (int i = 0; i < len; i++)
    {
        reversedMessage[i] = decodedMessage[len - 1 - i];
    }
    reversedMessage[len] = '\0';  

    printf("  > Original: %s\n  > Decoded: %s\n  > Reversed: %s", message, decodedMessage, reversedMessage);
}




int main()
{
    while (true)
    {
        system("cls");      // clearing the terminal screen
        printf("===========================\n| Message Encoder/Decoder |\n===========================\n\n\n[Main Menu]\n  [1] Encode Message\n  [2] Decode Message\n  [3] Exit");
       
        char userInput[63];       
        while (true)
        {
            printf("\nEnter an option [1-3]: ");
            fgets(userInput, sizeof(userInput), stdin);
            if   ((strlen(userInput) == 2) && (userInput[0] == '1' || userInput[0] == '2' || userInput[0] == '3')){ break; }
            else                                                                                                  { printf("> [!] Please enter 1,2, or 3"); }
        }


        if (userInput[0] == '3'){ return 0; }         
        else                                          
        {
            printf("\n\n\n[%s Message]\nEnter the message to %s: ",
                    (userInput[0] == '1')? "Encode" : "Decode", (userInput[0] == '1')? "encode" : "decode");
            char userMessage[63];
            fgets(userMessage, sizeof(userMessage), stdin);
            userMessage[strlen(userMessage) - 1] = '\0';      

            if   (userInput[0] == '1'){ encodeMessage(userMessage); }
            else                      { decodeMessage(userMessage); }

            printf("\n\n\n\n\nPress enter to continue: ");
            fgets(userInput, sizeof(userInput), stdin);    
        
        }
    }
}