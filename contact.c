#include "contact.h"
#include "file.h"
#include "populate.h"
#include "renderTable.h"
#include "sortEngine.h"
#include "validations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int readInt(int *value) {
    int result = scanf("%d", value);
    if (result != 1) {
        while (getchar() != '\n')
            ;
        return 0;
    }
    return 1;
}

void listContacts(AddressBook *addressBook) {
    // Sort contacts based on the chosen criteria
    ContactInfo sc;
    do {
        printf("Sort Menu : \n");
        printf("1. Sort by Name (Ascending)\n");
        printf("2. Sort by Phone (Ascending)\n");
        printf("3. Sort by Email (Ascending)\n");
        int choice;
        if (!readInt(&choice)) {
            printf("Invalid input, please enter a number\n");
            continue;
        }
        sc = (ContactInfo)choice;
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

int searchContact(AddressBook *addressBook, int *arr) {
    /* Define the logic for search */
    printf("Search by one of the following fields:\n1. Name\n2. "
           "Phone\n3. Email\n");
    int searchFilter;
    do {
        if (!readInt(&searchFilter)) {
            printf("Please enter a number.\n");
            continue;
        }
        if (searchFilter > 3 || searchFilter < 1) {
            printf("please enter a valid choice.\n");
            continue;
        }
        break;
    } while (1);

    printf("Enter search text...\n");
    char searchText[50];
    char contactPresent = 0;
    scanf("%s", searchText);
    char *contactInfo;
    for (int i = 0; i < addressBook->contactCount; i++) {
        const char *field;
        switch (searchFilter) {
        case NAME:
            field = addressBook->contacts[i].name;
            break;
        case PHONE:
            field = addressBook->contacts[i].phone;
            break;
        case EMAIL:
            field = addressBook->contacts[i].email;
            break;
        }
        if (strcasestr(field, searchText)) {
            if (!contactPresent) {
                printTableHeaders();
            }
            displayContact(i + 1, &addressBook->contacts[i]);
            printCellEdge();
            arr[i] = 1;
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
    int arr[100] = {0};
    int contactPresent = searchContact(addressBook, arr);
    if (!contactPresent)
        return;
    printf("Enter the contact to edit\n");

    int index;
    do {
        if (!readInt(&index)) {
            printf("Please enter a number.\n");
            continue;
        }
        if (index < 1 || index > addressBook->contactCount || !arr[index - 1]) {
            printf("Please select one of the contacts listed above\n");
            continue;
        }
        break;
    } while (1);

    int choice;
    do {
        printf("1. Edit name\n");
        printf("2. Edit phone\n");
        printf("3. Edit email\n");
        printf("4. Return to main menu\n");
        if (!readInt(&choice)) {
            printf("Please enter a number.\n");
            continue;
        }
        if (choice < 1 || choice > 4)
            printf("Enter a valid field to edit\n");
    } while (choice < 1 || choice > 4);

    ContactInfo sc = (ContactInfo)choice;
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
        return;
    }

    printMessage("Contact Updated Successfully");
    printTableHeaders();
    displayContact(index, &addressBook->contacts[index - 1]);
    printTableEdge();
}

void deleteContact(AddressBook *addressBook) {
    /* Define the logic for deletecontact */
    int arr[100] = {0};
    int contactPresent = searchContact(addressBook, arr);
    if (!contactPresent)
        return;
    printf("Enter which contact to delete\n");

    int index;
    do {
        if (!readInt(&index)) {
            printf("Please enter a number.\n");
            continue;
        }
        if (index < 1 || index > addressBook->contactCount || !arr[index - 1]) {
            printf("Please select one of the contacts listed above\n");
            continue;
        }
        break;
    } while (1);

    for (int i = index - 1; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printMessage("Contact Deleted.");
}
