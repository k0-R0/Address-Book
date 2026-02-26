#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveContactsToFile(AddressBook *addressBook) {
    FILE *contactsFile = fopen("contacts.txt", "w+");
    if (!contactsFile) {
        fprintf(stderr, "File not found\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(contactsFile, "%s,%s,%s\n", addressBook->contacts[i].name,
                addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(contactsFile);
    exit(0);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *contactsFile = fopen("contacts.txt", "r");
    if (!contactsFile) {
        fprintf(stderr, "File not found\n");
        return;
    }

    char lineBuffer[120];

    while (fscanf(contactsFile, "%[^\n]", lineBuffer) > 0) {

        char *name = strtok(lineBuffer, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (!name || !phone || !email) {
            printf("File not formatted correctly\n");
            continue; // skip malformed lines
        }

        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);

        addressBook->contactCount++;
        fgetc(contactsFile);
    }

    fclose(contactsFile);
}
