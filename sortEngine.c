#include "contact.h"
#include <strings.h>

// enum for easily readability of which contact info is being
// used for sorting / searching / editing / deleting
typedef enum { NAME = 1, PHONE, EMAIL } ContactInfo;

// comparator functions that return case insensitive comparison
// otherwise Alice would come before alice. personally lowercase
// coming up before upper case looks better
int compareByName(const Contact *a, const Contact *b) {
    return strcasecmp(a->name, b->name);
}

int compareByPhone(const Contact *a, const Contact *b) {
    return strcasecmp(a->phone, b->phone);
}

int compareByEmail(const Contact *a, const Contact *b) {
    return strcasecmp(a->email, b->email);
}

// this is the sort function instead of doing string comparison
// directly in the sort function and having 3 sorts
// using 3 comparators and 1 sort function that sorts differently
// based on comparator passed
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
    // pass the comparator function as well
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
