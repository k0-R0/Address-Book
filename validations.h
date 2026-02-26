#ifndef VALIDATIONS_H
#define VALIDATIONS_H

typedef struct AddressBook AddressBook;

int validatePhone(AddressBook *addressBook, const char *phone);
int validateEmail(const char *email);
int validatePartialPhone(const char *phone);

#endif // !VALIDATIONS_H
