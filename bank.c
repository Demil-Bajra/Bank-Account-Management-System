#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
  int acc_no;
  char name[100];
  char address[100];
  char phone[20];
  float balance;
} Account;

void create_account();
void deposit();
void withdraw();
void check_balance();
void list_accounts();
void update_account();
void delete_account();
int account_exists(int acc_no);

const char *FILENAME = "accounts.txt"; 

int main() {
  int choice;

  while (1) {

    printf("\n BANK ACCOUNT MANAGEMENT SYSTEM \n");
    printf("1. Create New Account\n");
    printf("2. Deposit Amount\n");
    printf("3. Withdraw Amount\n");
    printf("4. Check Balance\n");
    printf("5. List All Accounts\n");
    printf("6. Update Account\n");
    printf("7. Delete Account\n");
    printf("0. Exit\n");
    printf("Enter the choice: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input. Please enter a number.\n");
      while (getchar() != '\n'); 
      continue;
    }

    switch (choice) {
    case 1:
      create_account();
      break;
    case 2:
      deposit();
      break;
    case 3: 
      withdraw();
      break;
    case 4:
      check_balance();
      break;
    case 5:
      list_accounts();
      break;
    case 6:
      update_account();
      break;
    case 7:
      delete_account();
      break;
    case 0:
      printf("Thank you for using our system. Goodbye!\n");
      exit(0);
    default:
      printf("Invalid choice! Please try again.\n");
    }
  }
  return 0;
}

void create_account() {
  Account acc;
  system("cls");
  FILE *fp = fopen(FILENAME, "ab");

  if (fp == NULL) {
    printf("Error opening file!\n");
    return;
  }
 printf("Create Account\n");
  do {
    printf("\nEnter Account Number: ");
    scanf("%d", &acc.acc_no);
    if (acc.acc_no <= 0) {
      printf("Account number must be positive!\n");
    }
  } while (acc.acc_no <= 0);

  if (account_exists(acc.acc_no)) {
    printf("Account number already exists!\n");
    fclose(fp);
    return;
  }

  printf("Enter Account Holder Name: ");
  getchar();
  fgets(acc.name, sizeof(acc.name), stdin);
  acc.name[strcspn(acc.name, "\n")] = 0; 

  printf("Enter Address: ");
  fgets(acc.address, sizeof(acc.address), stdin);
  acc.address[strcspn(acc.address, "\n")] = 0; 

  printf("Enter Phone Number: ");
  fgets(acc.phone, sizeof(acc.phone), stdin);
  acc.phone[strcspn(acc.phone, "\n")] = 0; 

  do {
    printf("Enter Initial Deposit Amount: ");
    scanf("%f", &acc.balance);
    if (acc.balance <= 0) {
      printf("Initial deposit cannot be negative!\n");
    }
  } while (acc.balance <= 0);

  fwrite(&acc, sizeof(Account), 1, fp);
  fclose(fp);

  printf("\nAccount created successfully!\n");
  printf("\nPress Enter to continue...");
while(getchar() != '\n');  
getchar();  
}

void deposit() {
  int acc_no;
  float amount;
  Account acc;
  system("cls");
  int found = 0;
  FILE *fp = fopen(FILENAME, "rb+");

  if (fp == NULL) {
    printf("No accounts found!\n");
    return;
  }
  printf("Deposit Amount\n");

  do {
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    if (acc_no <= 0) {
      printf("Account number must be positive!\n");
    }
  } while (acc_no <= 0);

  while (fread(&acc, sizeof(Account), 1, fp)) {
    if (acc.acc_no == acc_no) {
      printf("Current Balance: %.2f\n", acc.balance);
      do {
        printf("Enter Amount to Deposit: ");
        scanf("%f", &amount);
        if (amount <= 0) {
          printf("Deposit amount cannot be negative!\n");
        }
      } while (amount <= 0);

      acc.balance += amount;
      fseek(fp, -sizeof(Account), SEEK_CUR);
      fwrite(&acc, sizeof(Account), 1, fp);

      printf("\nDeposit successful! New Balance: %.2f\n", acc.balance);
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Account not found!\n");
  }
  printf("\nPress Enter to continue...");
while(getchar() != '\n');  
getchar();  

  fclose(fp);
}

void withdraw() {
  int acc_no;
  float amount;
  Account acc;
  system("cls");
  int found = 0;
  FILE *fp = fopen(FILENAME, "rb+");

  if (fp == NULL) {
    printf("No accounts found!\n");
    return;
  }
  printf("Withdraw Amount\n");

  do {
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    if (acc_no <= 0) {
      printf("Account number must be positive!\n");
    }
  } while (acc_no <= 0);

  while (fread(&acc, sizeof(Account), 1, fp)) {
    if (acc.acc_no == acc_no) {
      printf("Current Balance: %.2f\n", acc.balance);
      do {
        printf("Enter Amount to Withdraw: ");
        scanf("%f", &amount);
        if (amount <= 0) {
          printf("Withdrawal amount cannot be negative!\n");
        }
      } while (amount <= 0);

      if (amount > acc.balance) {
        printf("Insufficient balance!\n");
      } else {
        acc.balance -= amount;
        fseek(fp, -sizeof(Account), SEEK_CUR);
        fwrite(&acc, sizeof(Account), 1, fp);
        printf("\nWithdrawal successful! New Balance: %.2f\n", acc.balance);
      }
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Account not found!\n");
  }
printf("\nPress Enter to continue...");
while(getchar() != '\n');  
getchar();  

  fclose(fp);
}

void check_balance() {
  int acc_no;
  Account acc;
  system("cls");
  int found = 0;
  FILE *fp = fopen(FILENAME, "rb");

  if (fp == NULL) {
    printf("No accounts found!\n");
    return;
  }
printf("Check Balance\n");
  do {
    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);
    if (acc_no <= 0) {
      printf("Account number must be positive!\n");
    }
  } while (acc_no <= 0);

  while (fread(&acc, sizeof(Account), 1, fp)) {
    if (acc.acc_no == acc_no) {
      printf("\nAccount Holder: %s\n", acc.name);
      printf("Address: %s\n", acc.address);
      printf("Phone Number: %s\n", acc.phone);
      printf("Current Balance: %.2f\n", acc.balance);
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Account not found!\n");
  }
printf("\nPress Enter to continue...");
while(getchar() != '\n');  
getchar(); 

  fclose(fp);
}

void list_accounts() {
  Account acc;
  system("cls");
  FILE *fp = fopen(FILENAME, "rb");

  if (fp == NULL) {
    printf("No accounts found!\n");
    return;
  }
  printf("List All Accounts\n");

  printf("\n%-10s %-20s %-20s %-15s %-10s\n", "Acc No", "Name", "Address",
         "Phone", "Balance");
  printf("---------------------------------------------------------------------"
         "---------------------\n");

  while (fread(&acc, sizeof(Account), 1, fp)) {
    printf("%-10d %-20s %-20s %-15s %.2f\n", acc.acc_no, acc.name, acc.address,
           acc.phone, acc.balance);
  }
printf("\nPress Enter to continue...");
while(getchar() != '\n');  
getchar();  

  fclose(fp);
}

void update_account() {
  int acc_no;
  Account acc;
  system("cls");
  int found = 0;
  FILE *fp = fopen(FILENAME, "rb+");

  if (fp == NULL) {
    printf("No accounts found!\n");
    return;
  }
  printf("Update Account\n");

  do {
    printf("\nEnter Account Number to Update: ");
    scanf("%d", &acc_no);
    if (acc_no <= 0) {
      printf("Account number must be positive!\n");
    }
  } while (acc_no <= 0);

  while (fread(&acc, sizeof(Account), 1, fp)) {
    if (acc.acc_no == acc_no) {
      printf("\nOld Details:\n");
      printf("Name: %s\n", acc.name);
      printf("Address: %s\n", acc.address);
      printf("Phone: %s\n", acc.phone);

      printf("\nEnter New Name: ");
      getchar();
      fgets(acc.name, sizeof(acc.name), stdin);
      acc.name[strcspn(acc.name, "\n")] = 0;

      printf("Enter New Address: ");
      fgets(acc.address, sizeof(acc.address), stdin);
      acc.address[strcspn(acc.address, "\n")] = 0;

      printf("Enter New Phone Number: ");
      fgets(acc.phone, sizeof(acc.phone), stdin);
      acc.phone[strcspn(acc.phone, "\n")] = 0;

      fseek(fp, -sizeof(Account), SEEK_CUR);
      fwrite(&acc, sizeof(Account), 1, fp);

      printf("\nAccount updated successfully!\n");
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("Account not found!\n");
  }
  printf("\nPress Enter to continue...");
while(getchar() != '\n');  
getchar();  

  fclose(fp);
}

void delete_account() {
  int acc_no;
  Account acc;
  system("cls");
  int found = 0;
  FILE *fp = fopen(FILENAME, "rb");
  FILE *ft = fopen("temp.txt", "wb");

  if (fp == NULL) {
    printf("No accounts found!\n");
    return;
  }
  printf("Delete Account\n");

  do {
    printf("\nEnter Account Number to Delete: ");
    scanf("%d", &acc_no);
    if (acc_no <= 0) {
      printf("Account number must be positive!\n");
    }
  } while (acc_no <= 0);

  while (fread(&acc, sizeof(Account), 1, fp)) {
    if (acc.acc_no == acc_no) {
      found = 1;
      printf("\nAccount with account no. %d deleted successfully.\n", acc_no);
    } else {
      fwrite(&acc, sizeof(Account), 1, ft);
    }
  }
printf("\nPress Enter to continue...");
while(getchar() != '\n');  
getchar();  

  fclose(fp);
  fclose(ft);
  remove(FILENAME);
  rename("temp.txt", FILENAME);

  if (!found) {
    printf("Account not found!\n");
  }
}

int account_exists(int acc_no) {
  Account acc;
  FILE *fp = fopen(FILENAME, "rb");
  if (fp == NULL)
    return 0;

  while (fread(&acc, sizeof(Account), 1, fp)) {
    if (acc.acc_no == acc_no) {
      fclose(fp);
      return 1;
    }
  }

  fclose(fp);
  return 0;
}
