# Address Book CLI in C

A simple terminal address book built in C that lets you add, search, edit, delete,
and save contacts.

## Features
- Create new contact
- Search by name/phone/email
- Edit or delete contacts
- Save and load from disk

## Installation

Requires GCC/Clang.

```bash
cmake -S . -B build
cmake --build build
```


Alternatively if you're not using cmake
```bash
gcc main.c contact.c file.c renderTable.c sortEngine.c validations.c -o addressbook
```

## Run

Run the program by executing the binary. in case you've got the zip file. just run 
```bash
./build/addressbook
```

## Project Structure

```bash
Addressbook
├── contact.c
├── contact.h
├── contacts.txt
├── file.c
├── file.h
├── main.c
├── renderTable.c
├── renderTable.h
├── sortEngine.c
├── sortEngine.h
├── validations.c
└── validations.h
```

## File Responsibilities

### 1. main.c
   - Entry point of the program.
   - Handles the menu system and connects all modules together.

### 2. contact.c / contact.h
   - Defines the Contact structure and core contact-related CRUD operations.

### 3. file.c / file.h
   - Handles reading from and writing to contacts.csv

### 4. contacts.csv
   - Stores contact data persistently.


### 5. renderTable.c / renderTable.h
   - Formats and prints contacts in a clean table layout in the terminal.

### 6. sortEngine.c / sortEngine.h
   - Implements sorting logic for contacts (e.g., by name or phone).

### 7. validations.c
   - Contains input validation logic for:
   -  Email format
   -  Phone numbers
