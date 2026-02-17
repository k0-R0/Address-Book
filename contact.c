#include "contact.h"
#include "file.h"
#include "populate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { NAME = 1, PHONE, EMAIL } SortCriteria;

void displayContact(Contact *contact) {
    printf("|%-20s |%-15s |%-30s |\n", contact->name, contact->phone,
           contact->email);
    printf("+---------------------+----------------+-------------------------"
           "------+\n");
}

int compareByName(const Contact *a, const Contact *b) {
    const char *aa = a->name;
    const char *bb = b->name;
    return strcasecmp(aa, bb);
}

int compareByPhone(const Contact *a, const Contact *b) {
    const char *aa = a->phone;
    const char *bb = b->phone;
    return strcasecmp(aa, bb);
}

int compareByEmail(const Contact *a, const Contact *b) {
    const char *aa = a->email;
    const char *bb = b->email;
    return strcasecmp(aa, bb);
}

void sortBook(AddressBook *addressBook,
              int (*compare)(const Contact *a, const Contact *b)) {
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        char swaps = 0;
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if (compare(&addressBook->contacts[j],
                        &addressBook->contacts[j + 1]) > 0) {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
                swaps = 1;
            }
        }
        if (!swaps)
            break;
    }
}

void sortContacts(AddressBook *addressBook, SortCriteria sc) {
    // sort the addressbook on name / email / phone
    switch (sc) {
    case NAME:
        sortBook(addressBook, compareByName);
        break;
    case PHONE:
        sortBook(addressBook, compareByPhone);
        break;
    case EMAIL:
        sortBook(addressBook, compareByEmail);
    }
}

void listContacts(AddressBook *addressBook) {
    // Sort contacts based on the chosen criteria
    SortCriteria sc;
    do {
        printf("Sort Menu : \n");
        printf("1. Sort by Name (Ascending)\n");
        printf("2. Sort by Phone (Ascending)\n");
        printf("3. Sort by Email (Ascending)\n");
        int result = scanf("%d", &sc);
        if (result != 1) {
            printf("Invalid input, please enter a number");
            while (getchar() != '\n')
                ;
            continue;
        }
        if (sc > 3 || sc < 1)
            printf("Enter a valid criteria\n");
    } while (sc > 3 || sc < 1);
    printf("+---------------------+----------------+-------------------------"
           "------+\n");
    printf("|%-20s |%-15s |%-30s |\n", "Name", "Phone", "Email");
    printf("+---------------------+----------------+-------------------------"
           "------+\n");
    sortContacts(addressBook, sc);
    for (int i = 0; i < addressBook->contactCount; i++)
        displayContact(&addressBook->contacts[i]);
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    // loadContactsFromFile(addressBook);
}

// void saveAndExit(AddressBook *addressBook) {
//     saveContactsToFile(addressBook); // Save contacts to file
//     exit(EXIT_SUCCESS); // Exit the program
// }

void createContact(AddressBook *addressBook) {
    /* Define the logic to create a Contacts */
    char name[50];
    char phone[20];
    char email[50];
    printf("Enter name of contact : \n");
    scanf(" %49[^\n]", name);
    // validate(NAME, name);
    printf("Enter phone of contact : \n");
    scanf("%s", phone);
    // validate(PHONE, phone);
    printf("Enter email of contact : \n");
    scanf("%s", email);
    // validate(EMAIL, email);
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount++].email, email);
    printf("\nContact Added - \n");
    printf("+---------------------+----------------+-------------------------"
           "------+\n");
    printf("|%-20s |%-15s |%-30s |\n", "Name", "Phone", "Email");
    printf("+---------------------+----------------+-------------------------"
           "------+\n");
    displayContact(&addressBook->contacts[addressBook->contactCount - 1]);
}

void searchContact(AddressBook *addressBook) {
    /* Define the logic for search */
    printf("Enter search text...\n");
    char searchText[50];
    scanf("%s", searchText);
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strstr(addressBook->contacts[i].name, searchText) ||
            strstr(addressBook->contacts[i].phone, searchText) ||
            strstr(addressBook->contacts[i].email, searchText)) {
            displayContact(&addressBook->contacts[i]);
            return;
        }
    }
    printf("\n --------------------\nContact not found\n-------------------\n");
}

void editContact(AddressBook *addressBook) {
    /* Define the logic for Editcontact */
}

void deleteContact(AddressBook *addressBook) {
    /* Define the logic for deletecontact */
}
