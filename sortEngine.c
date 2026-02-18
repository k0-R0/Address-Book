#include "contact.h"
#include <string.h>

typedef enum { NAME = 1, PHONE, EMAIL } ContactInfo;

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

void sortContacts(AddressBook *addressBook, ContactInfo sc) {
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
