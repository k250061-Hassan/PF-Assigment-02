#include <stdio.h>
#define MAX_SIZE 5

int g_stack[MAX_SIZE]; 
int g_top = -1; // 'top' index: -1 indicates an empty stack

void push(int element);
void pop(void);
void peek(void);
void display(void);
void showMenu(void);

int main() {
    int choice;
    int element;

    do {
        showMenu();
        
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            choice = 0;
            continue;
        
        }while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter element to PUSH: ");
                if (scanf("%d", &element) == 1) {
                    while (getchar() != '\n');
                    push(element);
                } else {
                    printf("Invalid element input.\n");
                    while (getchar() != '\n');
                }
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                printf("\nExiting the Stack Program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option. Please choose a number between 1 and 5.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

void showMenu(void) {
    printf("\n============================================\n");
    printf("         STACK OPERATIONS (Max Size: %d)\n", MAX_SIZE);
    printf("============================================\n");
    printf("1. PUSH (Insert Element)\n");
    printf("2. POP (Remove Top Element)\n");
    printf("3. PEEK (Display Top Element)\n");
    printf("4. DISPLAY (Show All Elements)\n");
    printf("5. EXIT\n");
    printf("Current TOP index: %d\n", g_top);
    printf("--------------------------------------------\n");
}

void push(int element) {
    // Check for Stack Overflow
    if (g_top >= MAX_SIZE - 1) {
        printf("\n--- ERROR: STACK OVERFLOW! Cannot push element %d. ---\n", element);
        return;
    }

    g_top++;
    g_stack[g_top] = element;
    
    printf("\nSuccessfully PUSHED %d. New TOP is at index %d.\n", element, g_top);
}

void pop(void) {
    if (g_top == -1) {
        printf("\n--- ERROR: STACK UNDERFLOW! Cannot pop from an empty stack. ---\n");
        return;
    }
   
    int popped_element = g_stack[g_top];
    g_top--;
    
    printf("\nSuccessfully POPPED element %d. New TOP is at index %d.\n", popped_element, g_top);
}

void peek(void) {
    if (g_top == -1) {
        printf("\n--- ERROR: Stack is Empty. Cannot PEEK. ---\n");
        return;
    }
    
    printf("\nPEEK: The top element is %d (at index %d).\n", g_stack[g_top], g_top);
}

void display(void) {

    if (g_top == -1) {
        printf("\n--- DISPLAY: The stack is currently empty. ---\n");
        return;
    }

    printf("\n--- Current Stack Elements (TOP to BOTTOM) ---\n");
    printf("%3s %10s", "INDEX", "ELEMENT\n");
    for (int i = g_top; i >= 0; i--) {
        printf("[%d] \t %d", i, g_stack[i]);
        if (i == g_top) {
            printf(" <-- TOP\n");
        } else {
            printf("\n");
        }
    }
    printf("--------------------------------------------\n");
}