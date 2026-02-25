#ifndef FILE_H
#define FILE_H

typedef struct AddressBook AddressBook;
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
