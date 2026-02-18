#include "contact.h"
#include "file.h"
#include "populate.h"
#include "renderTable.h"
#include "sortEngine.h"
#include "validations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listContacts(AddressBook *addressBook) {
    // Sort contacts based on the chosen criteria
    SortCriteria sc;
    do {
        printf("Sort Menu : \n");
        printf("1. Sort by Name (Ascending)\n");
        printf("2. Sort by Phone (Ascending)\n");
        printf("3. Sort by Email (Ascending)\n");
        int choice;
        int result = scanf("%d", &choice);
        sc = (SortCriteria)choice;
        if (result != 1) {
            printf("Invalid input, please enter a number");
            while (getchar() != '\n')
                ;
            continue;
        }
        if (sc > 3 || sc < 1)
            printf("Enter a valid criteria\n");
    } while (sc > 3 || sc < 1);
    sortContacts(addressBook, sc);
    printTableHeaders();
    for (int i = 0; i < addressBook->contactCount; i++) {
        displayContact(i + 1, &addressBook->contacts[i]);
        if (i != addressBook->contactCount - 1)
            printCellEdge();
        else
            printTableEdge();
    }
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

    do {
        printf("Enter phone of contact : \n");
        scanf("%s", phone);
        if (!validatePhone(addressBook, phone))
            printf("Invalid or duplicate phone number. Try again.\n");
    } while (!validatePhone(addressBook, phone));

    do {
        printf("Enter email of contact : \n");
        scanf("%s", email);
        if (!validateEmail(email))
            printf("Invalid email. Please try again.\n");
    } while (!validateEmail(email));

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount++].email, email);
    printf("\nContact Added - \n");
    printTableHeaders();
    displayContact(addressBook->contactCount,
                   &addressBook->contacts[addressBook->contactCount - 1]);
    printTableEdge();
}

int searchContact(AddressBook *addressBook) {
    /* Define the logic for search */
    printf("Enter search text...\n");
    char searchText[50];
    char contactPresent = 0;
    scanf("%s", searchText);
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strstr(addressBook->contacts[i].name, searchText) ||
            strstr(addressBook->contacts[i].phone, searchText) ||
            strstr(addressBook->contacts[i].email, searchText)) {
            if (!contactPresent) {
                printTableHeaders();
            }
            displayContact(i + 1, &addressBook->contacts[i]);
            printCellEdge();
            contactPresent = 1;
        }
    }
    if (!contactPresent)
        printMessage("Contact not found.");
    return contactPresent;
}
void editContactName(AddressBook *addressBook, int index) {
    char name[50];
    printf("Enter name of contact : \n");
    scanf(" %49[^\n]", name);
    strcpy(addressBook->contacts[index].name, name);
}

void editContactPhone(AddressBook *addressBook, int index) {
    char phone[20];
    do {
        printf("Enter phone of contact : \n");
        scanf("%s", phone);
        if (!validatePhone(addressBook, phone))
            printf("Invalid or duplicate phone number. Try again.\n");
    } while (!validatePhone(addressBook, phone));
    strcpy(addressBook->contacts[index].phone, phone);
}

void editContactEmail(AddressBook *addressBook, int index) {
    char email[50];
    do {
        printf("Enter email of contact : \n");
        scanf("%s", email);
        if (!validateEmail(email))
            printf("Invalid email. Please try again.\n");
    } while (!validateEmail(email));
    strcpy(addressBook->contacts[index].email, email);
}

void editContact(AddressBook *addressBook) {
    /* Define the logic for Editcontact */
    int contactPresent = searchContact(addressBook);
    if (!contactPresent)
        return;
    printf("Enter which contact to edit\n");
    int index;
    scanf("%d", &index);

    printf("1. Edit name\n");
    printf("2. Edit phone\n");
    printf("3. Edit email\n");
    int choice;
    scanf("%d", &choice);
    SortCriteria sc = (SortCriteria)choice;
    switch (sc) {
    case NAME:
        editContactName(addressBook, index - 1);
        break;
    case PHONE:
        editContactPhone(addressBook, index - 1);
        break;
    case EMAIL:
        editContactEmail(addressBook, index - 1);
        break;
    default:
        printf("Enter a valid field to edit\n");
    }
    printMessage("Contact Updated Successfully");
    printTableHeaders();
    displayContact(index, &addressBook->contacts[index - 1]);
    printTableEdge();
}

void deleteContact(AddressBook *addressBook) {
    /* Define the logic for deletecontact */
    int contactPresent = searchContact(addressBook);
    if (!contactPresent)
        return;
    printf("Enter which contact to delete\n");
    int index;
    scanf("%d", &index);
    for (int i = index - 1; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printMessage("Contact Deleted.");
}
