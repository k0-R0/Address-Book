#include "contact.h"
#include "file.h"
#include "populate.h"
#include "renderTable.h"
#include "sortEngine.h"
#include "validations.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function to validate proper integers are being given when asked for options
int readInt(int *value) {
    // create a string buffer and store to it first
    char buffer[20];
    scanf("%s", buffer);
    // ensure that the string only has numbers
    for (int i = 0; buffer[i]; i++) {
        if (!isdigit(buffer[i])) {
            // clear the buffer if alphabets or symbols are present so
            // that the next input from user is read
            while (getchar() != '\n')
                ;
            return 0;
        }
    }
    // convert the string to int if there were only numerics and return 1
    *value = atoi(buffer);
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
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook) {
    /* Define the logic to create a Contacts */
    char name[50];
    char phone[20];
    char email[50];
    printf("Enter name of contact : \n");
    scanf(" %49[^\n]", name);

    // keep asking for input till a valid number is entered
    do {
        printf("Enter phone of contact : \n");
        scanf("%s", phone);
        if (!validatePhone(addressBook, phone))
            printf("Invalid or duplicate phone number. Try again.\n");
    } while (!validatePhone(addressBook, phone));

    // keep asking for input till a valid email is entered
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
    // keep asking for user input to filter on till valid filter is given
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
    // if searching by phone verify only numerics are there in the
    // search text otherwise we can exit early
    if (searchFilter == PHONE) {
        do {
            scanf("%s", searchText);
            if (!validatePartialPhone(searchText)) {
                printf("please enter only numbers for searching through phone "
                       "numbers\n");
                while (getchar() != '\n')
                    ;
            }
        } while (!validatePartialPhone(searchText));
    } else {
        scanf("%s", searchText);
    }
    char *contactInfo;
    // based on the filter provided look for the string in a different field
    // using enums to represent the different options
    // reference can be found in sortEngine
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
        // doing a case insensitive search as user can
        // enter lower case letters for search
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
    // use this arr array to keep track of search results
    // arr will have contact index set to 1 if contact is present during search
    int arr[100] = {0};
    int contactPresent = searchContact(addressBook, arr);
    if (!contactPresent)
        return;
    printf("Enter the contact to edit\n");

    int index;
    do {
        // check if user entered a proper number
        if (!readInt(&index)) {
            printf("Please enter a number.\n");
            continue;
        }
        // check if index is out of range or if it is not returned from the
        // search
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
    // enums for different contact info , refer sortEngine.c
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
    // use this arr array to keep track of search results
    // arr will have contact index set to 1 if contact is present during search
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
        // check if index is out of range or if it is not returned from the
        // search
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
