#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef enum { CREATE = 1, SEARCH, UPDATE, DELETE, LIST, SAVE, EXIT } Action;

typedef struct Contact {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct AddressBook {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, int *arr);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int readInt(int *value);

#endif
