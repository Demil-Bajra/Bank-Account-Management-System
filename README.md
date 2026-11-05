# Bank Account Management System

A console-based bank account management system written in C. It lets you create and manage customer accounts, handle deposits and withdrawals, and keeps all data saved between runs using binary file storage.

I built this as my Grade 12 project to practice C fundamentals: structs, file handling, input validation, and modular function design.

## Features

- **Create Account** – register a new account with account number, name, address, phone number, and an initial deposit
- **Deposit** – add money to an existing account
- **Withdraw** – take money out, with an insufficient-balance check
- **Check Balance** – view account holder details and current balance
- **List All Accounts** – display every account in a formatted table
- **Update Account** – edit the name, address, and phone number of an account
- **Delete Account** – permanently remove an account
- **Persistent storage** – all records are saved to a file, so data survives after the program closes

## Concepts Practiced

- `struct` for modelling an account record
- Binary file I/O with `fopen`, `fread`, `fwrite`, `fseek`
- In-place record updates using `fseek` with `SEEK_CUR`
- Record deletion using a temporary file (`remove` + `rename`)
- Input validation (positive account numbers, positive amounts, duplicate account check)
- Menu-driven programs using `switch` inside a loop
- Safe string input with `fgets` and `strcspn`

## Account Structure

```c
typedef struct {
  int acc_no;
  char name[100];
  char address[100];
  char phone[20];
  float balance;
} Account;
```

## Getting Started

### Prerequisites

- A C compiler such as [GCC](https://gcc.gnu.org/) (MinGW on Windows)

### Compile

```bash
gcc bank.c -o bank
```

### Run

```bash
./bank       # Linux / macOS
bank.exe     # Windows
```

> **Note:** The program uses `system("cls")` to clear the screen, which works on **Windows**. On Linux or macOS, change `"cls"` to `"clear"` in the source code.

## Usage

When you run the program you will see this menu:

```
 BANK ACCOUNT MANAGEMENT SYSTEM
1. Create New Account
2. Deposit Amount
3. Withdraw Amount
4. Check Balance
5. List All Accounts
6. Update Account
7. Delete Account
0. Exit
Enter the choice:
```

Type the number of the option you want and follow the prompts.

## Data Storage

Accounts are stored in a file named `accounts.txt` in the same folder as the program. Despite the `.txt` extension, records are saved in **binary format**, so the file is not meant to be opened in a text editor. It is created automatically when you add your first account.

## Project Structure

```
.
├── bank.c       # Complete source code
└── README.md
```

## Possible Improvements

- Use `double` instead of `float` for more accurate money handling
- Add PIN/password authentication for accounts
- Add transaction history and fund transfers between accounts
- Make screen clearing work on all operating systems
- Add a proper database (e.g. SQLite) instead of a flat binary file

## Author

**Demil Bajracharya**
BCA Student, Trinity International College, Kathmandu, Nepal

## License

This project is open source and available for learning purposes. Feel free to use and modify it.
