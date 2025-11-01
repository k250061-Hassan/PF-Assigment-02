#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 100       // Maximum number of books the system can handle
#define MAX_TITLE_LEN 50    // Maximum length for a book title
#define LOW_STOCK_THRESHOLD 5 // Books below this quantity are considered low stock

int findBookIndex(const int isbns[], int bookCount, int targetIsbn);
void addNewBook(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int *bookCount);
void processSale(int isbns[], int quantities[], int bookCount);
void generateLowStockReport(const int isbns[], const char titles[][MAX_TITLE_LEN], const float prices[], const int quantities[], int bookCount);

int main() {
    int isbns[MAX_BOOKS] = {0};
    char titles[MAX_BOOKS][MAX_TITLE_LEN] = {{0}};
    float prices[MAX_BOOKS] = {0.0f};
    int quantities[MAX_BOOKS] = {0};

    int bookCount = 0;
    int choice;

    do {
        printf("\n--- Liberty Books Inventory System ---\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addNewBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, quantities, bookCount);
                break;
            case 3:
                generateLowStockReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Thank you for using the Liberty Books Inventory System. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please choose a number between 1 and 4.\n");
                break;
        }

    } while (choice != 4);

    return 0;
}


// Helper function to find the index of a book by ISBN.

int findBookIndex(const int isbns[], int bookCount, int targetIsbn) {
    for (int i = 0; i < bookCount; i++) {
        if (isbns[i] == targetIsbn) {
            return i;
        }
    }
    return -1;
}


// Adds a new book's details into the parallel arrays.
 
void addNewBook(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int *bookCount) {
    if (*bookCount >= MAX_BOOKS) {
        printf("Error: Inventory is full. Cannot add more than %d books.\n", MAX_BOOKS);
        return;
    }

    int isbn;
    char title[MAX_TITLE_LEN];
    float price;
    int quantity;
    int index = *bookCount;

    printf("\n--- Add New Book ---\n");
    printf("Enter ISBN (e.g., 1234): ");
    if (scanf("%d", &isbn) != 1) {
        printf("Error: Invalid ISBN input.\n");
        while (getchar() != '\n');
        return;
    }

    if (findBookIndex(isbns, *bookCount, isbn) != -1) {
        printf("Error: Book with ISBN %d already exists. Operation cancelled.\n", isbn);
        return;
    }

    // Get Title (Need to clear buffer after previous scanf)
    printf("Enter Title (max %d chars): ", MAX_TITLE_LEN - 1);
    while (getchar() != '\n'); // Clear the newline from the buffer
    if (fgets(title, MAX_TITLE_LEN, stdin) == NULL) {
        printf("Error reading title.\n");
        return;
    }
    // Remove trailing newline character
    title[strcspn(title, "\n")] = 0; 
    
    // Get Price
    printf("Enter Price: $");
    if (scanf("%f", &price) != 1 || price < 0) {
        printf("Error: Invalid price input.\n");
        while (getchar() != '\n');
        return;
    }
    
    // Get Initial Quantity
    printf("Enter Initial Quantity: ");
    if (scanf("%d", &quantity) != 1 || quantity < 0) {
        printf("Error: Invalid quantity input.\n");
        while (getchar() != '\n');
        return;
    }

    // Store data in parallel arrays
    isbns[index] = isbn;
    strcpy(titles[index], title);
    prices[index] = price;
    quantities[index] = quantity;

    // Increment the book count (modifying the main variable via the pointer)
    (*bookCount)++;

    printf("\nSuccess! Book added: \"%s\" (ISBN: %d). Current total books: %d\n", title, isbn, *bookCount);
}

 // Processes a sale, finding the book by ISBN and updating its quantity.

void processSale(int isbns[], int quantities[], int bookCount) {
    printf("\n--- Process a Sale ---\n");
    int isbn;
    int saleQuantity;

    printf("Enter ISBN of the book sold: ");
    if (scanf("%d", &isbn) != 1) {
        printf("Error: Invalid ISBN input.\n");
        while (getchar() != '\n');
        return;
    }

    int index = findBookIndex(isbns, bookCount, isbn);

    if (index == -1) {
        printf("Error: Book with ISBN %d not found in inventory.\n", isbn);
        return;
    }

    printf("Enter number of copies sold: ");
    if (scanf("%d", &saleQuantity) != 1 || saleQuantity <= 0) {
        printf("Error: Invalid sale quantity.\n");
        while (getchar() != '\n');
        return;
    }

    // Handle out-of-stock errors
    if (quantities[index] < saleQuantity) {
        printf("Sale Failed: Out-of-stock error!\n");
        printf("Only %d copies of book ISBN %d are available.\n", quantities[index], isbn);
    } else {
        quantities[index] -= saleQuantity;
        printf("\nSale Successful!\n");
        printf("ISBN: %d | Copies Sold: %d | New Stock: %d\n", isbn, saleQuantity, quantities[index]);
    }
}


 // Displays the details of all books where the quantity is below the low-stock threshold.
 
void generateLowStockReport(const int isbns[], const char titles[][MAX_TITLE_LEN], const float prices[], const int quantities[], int bookCount) {
    printf("\n--- Low-Stock Report (Quantity < %d) ---\n", LOW_STOCK_THRESHOLD);
    int lowStockFound = 0;

    if (bookCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        if (quantities[i] < LOW_STOCK_THRESHOLD) {
            lowStockFound = 1;
            printf("ISBN: %d | Title: %s | Price: $%.2f | Stock: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
        }
    }

    if (!lowStockFound) {
        printf("Great news! All books are currently above the low-stock threshold.\n");
    }
}