#ifndef RENDER_TABLE_H
#define RENDER_TABLE_H
typedef struct Contact Contact;
typedef struct AddressBook AddressBook;

void printCellEdge(void);
void printTableEdge(void);
void printTableHeaders(void);
void printMessage(const char *str);
void displayContact(int index, const Contact *contact);

#endif // !RENDER_TABLE_H
