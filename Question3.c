#include <stdio.h>
#include <string.h>

#define GRID_ROWS 3
#define GRID_COLS 3
#define POWER_STATUS_BIT 0x01 // Binary 001
#define OVERLOAD_WARNING_BIT 0x02 // Binary 010
#define MAINTENANCE_REQUIRED_BIT 0x04 // Binary 100

int g_grid_status[GRID_ROWS][GRID_COLS] = {0};
void displayMenu(void);
void updateSectorStatus(int grid[GRID_ROWS][GRID_COLS]);
void querySectorStatus(const int grid[GRID_ROWS][GRID_COLS]);
void runSystemDiagnostic(const int grid[GRID_ROWS][GRID_COLS]);
void printStatusReport(int status, int row, int col);

int main() {
    int choice;
    
    do {
        displayMenu();
        
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                updateSectorStatus(g_grid_status);
                break;
            case 2:
                querySectorStatus(g_grid_status);
                break;
            case 3:
                runSystemDiagnostic(g_grid_status);
                break;
            case 4:
                printf("\nExiting IESCO Grid Monitoring System. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option. Please choose a number between 1 and 4.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}


void displayMenu(void) {
    printf("\n======================================================\n");
    printf("         IESCO Power Grid Monitoring System\n");
    printf("======================================================\n");
    printf("1. Update Sector Status (Set or Clear a Flag)\n");
    printf("2. Query Sector Status (Print Detailed Report)\n");
    printf("3. Run System Diagnostic (Find Overloads/Maintenance)\n");
    printf("4. Exit System\n");
    printf("------------------------------------------------------\n");
}

void printStatusReport(int status, int row, int col) {
    printf("\n--- Sector Status Report [%d, %d] ---\n", row, col);
    
    if (status & POWER_STATUS_BIT) {
        printf("  Power Status: ON (Bit 0 is 1)\n");
    } else {
        printf("  Power Status: OFF (Bit 0 is 0)\n");
    }

    if (status & OVERLOAD_WARNING_BIT) {
        printf("  Overload Warning: OVERLOADED (Bit 1 is 1)\n");
    } else {
        printf("  Overload Warning: Normal (Bit 1 is 0)\n");
    }
    
    if (status & MAINTENANCE_REQUIRED_BIT) {
        printf("  Maintenance Required: REQUIRED (Bit 2 is 1)\n");
    } else {
        printf("  Maintenance Required: No (Bit 2 is 0)\n");
    }
    
    printf("  Raw Status Value: %d\n", status);
}

void updateSectorStatus(int grid[GRID_ROWS][GRID_COLS]) {
    int row, col, flag_choice, action_choice;
    int bit_mask = 0;

    printf("\n--- Update Sector Status ---\n");

    // 1. Get Coordinates
    printf("Enter Row (0 to %d): ", GRID_ROWS - 1);
    scanf("%d", &row);
    printf("Enter Column (0 to %d): ", GRID_COLS - 1);
    scanf("%d", &col);
    while (getchar() != '\n'); // Clear buffer

    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) {
        printf("Error: Invalid coordinates.\n");
        return;
    }

    // 2. Choose Flag
    printf("\nSelect Status Flag to change:\n");
    printf("  1. Power Status (Bit 0)\n");
    printf("  2. Overload Warning (Bit 1)\n");
    printf("  3. Maintenance Required (Bit 2)\n");
    printf("Enter flag number: ");
    scanf("%d", &flag_choice);
    while (getchar() != '\n'); 

    switch (flag_choice) {
        case 1: bit_mask = POWER_STATUS_BIT; break;
        case 2: bit_mask = OVERLOAD_WARNING_BIT; break;
        case 3: bit_mask = MAINTENANCE_REQUIRED_BIT; break;
        default: printf("Error: Invalid flag choice.\n"); return;
    }

    // 3. Choose Action (Set or Clear)
    printf("\nSelect Action:\n");
    printf("  1. SET Flag (set bit to 1)\n");
    printf("  2. CLEAR Flag (set bit to 0)\n");
    printf("Enter action number: ");
    scanf("%d", &action_choice);
    while (getchar() != '\n');

    // 4. Perform Bitwise Manipulation
    if (action_choice == 1) {
        grid[row][col] |= bit_mask;
        printf("\nSuccess: Flag SET for Sector [%d, %d].\n", row, col);
    } else if (action_choice == 2) {
        grid[row][col] &= ~bit_mask;
        printf("\nSuccess: Flag CLEARED for Sector [%d, %d].\n", row, col);
    } else {
        printf("Error: Invalid action choice.\n");
    }
}

void querySectorStatus(const int grid[GRID_ROWS][GRID_COLS]) {
    int row, col;

    printf("\n--- Query Sector Status ---\n");
    printf("Enter Row (0 to %d): ", GRID_ROWS - 1);
    scanf("%d", &row);
    printf("Enter Column (0 to %d): ", GRID_COLS - 1);
    scanf("%d", &col);
    while (getchar() != '\n');

    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) {
        printf("Error: Invalid coordinates.\n");
        return;
    }

    printStatusReport(grid[row][col], row, col);
}

void runSystemDiagnostic(const int grid[GRID_ROWS][GRID_COLS]) {
    int overloaded_count = 0;
    int maintenance_count = 0;
    
    printf("\n--- System Diagnostic Report ---\n");
    
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            int status = grid[i][j];

            if (status & OVERLOAD_WARNING_BIT) {
                overloaded_count++;
                printf("! Overloaded: Sector [%d, %d] (Status: %d)\n", i, j, status);
            }

            if (status & MAINTENANCE_REQUIRED_BIT) {
                maintenance_count++;
                printf("! Maintenance: Sector [%d, %d] (Status: %d)\n", i, j, status);
            }
        }
    }
    
    printf("\n======================================================\n");
    printf("DIAGNOSTIC SUMMARY:\n");
    printf("Total sectors in grid: %d\n", GRID_ROWS * GRID_COLS);
    printf("Sectors with Overload Warning: %d\n", overloaded_count);
    printf("Sectors requiring Maintenance: %d\n", maintenance_count);
    printf("======================================================\n");
}