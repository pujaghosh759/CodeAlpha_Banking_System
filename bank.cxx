#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

// Add new account
void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "ab");

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);

    printf("Enter Name: ");
    scanf("%s", acc.name);

    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

// Deposit money
void deposit() {
    struct Account acc;
    int accNum;
    float amount;
    int found = 0;

    FILE *fp = fopen("bank.dat", "rb+");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNum) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);

            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("\nAmount Deposited Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nAccount Not Found!\n");

    fclose(fp);
}

// Withdraw money
void withdraw() {
    struct Account acc;
    int accNum;
    float amount;
    int found = 0;

    FILE *fp = fopen("bank.dat", "rb+");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNum) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (acc.balance >= amount) {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("\nWithdrawal Successful!\n");
            } else {
                printf("\nInsufficient Balance!\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nAccount Not Found!\n");

    fclose(fp);
}

// Balance enquiry
void checkBalance() {
    struct Account acc;
    int accNum;
    int found = 0;

    FILE *fp = fopen("bank.dat", "rb");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNum) {
            printf("\nAccount Number: %d", acc.accNo);
            printf("\nName: %s", acc.name);
            printf("\nCurrent Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nAccount Not Found!\n");

    fclose(fp);
}

// Main Menu
int main() {
    int choice;

    while (1) {
        printf("\n\n===== BANKING SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: exit(0);
            default: printf("\nInvalid Choice! Try Again.\n");
        }
    }

    return 0;
}