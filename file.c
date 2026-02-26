#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveContactsToFile(AddressBook *addressBook) {
    // open file
    FILE *contactsFile = fopen("contacts.csv", "w+");
    if (!contactsFile) {
        fprintf(stderr, "File not found\n");
        return;
    }
    // print all contacts in a formatted manner
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(contactsFile, "%s,%s,%s\n", addressBook->contacts[i].name,
                addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(contactsFile);
    // early exit once user saves
    exit(0);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *contactsFile = fopen("contacts.csv", "r");
    if (!contactsFile) {
        fprintf(stderr, "File not found\n");
        return;
    }

    // lineBuffer to read each line from the file
    char lineBuffer[120];

    while (fscanf(contactsFile, "%[^\n]", lineBuffer) > 0) {

        // strtok to get each string before the delimiter ','
        char *name = strtok(lineBuffer, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        // check for corrupted file inform the user and continue reading rest of
        // the data
        if (!name || !phone || !email) {
            printf("File not formatted correctly\n");
            continue; // skip malformed lines
        }

        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);

        addressBook->contactCount++;
        // because we're using scanf to read each line '\n' is left in stdin
        // buffer clear it before reading next line
        fgetc(contactsFile);
    }

    fclose(contactsFile);
}
