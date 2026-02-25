#include "contact.h"
#include <stdio.h>

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (!readInt(&choice)) {
            printf("Please enter a number.\n");
            continue;
        }
        Action ac = (Action)choice;
        switch (ac) {
        case CREATE:
            createContact(&addressBook);
            break;
        case SEARCH: {
            int arr[100] = {0};
            searchContact(&addressBook, arr);
            break;
        }
        case UPDATE:
            editContact(&addressBook);
            break;
        case DELETE:
            deleteContact(&addressBook);
            break;
        case LIST:
            listContacts(&addressBook);
            break;
        case SAVE:
            printf("Saving and Exiting...\n");
            // saveContactsToFile(&addressBook);
            break;
        case EXIT:
            printf("Exiting ... \n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
