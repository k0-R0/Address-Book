typedef struct Contact Contact;
typedef struct AddressBook AddressBook;

typedef enum { NAME = 1, PHONE, EMAIL } ContactInfo;

int compareByName(const Contact *a, const Contact *b);

int compareByPhone(const Contact *a, const Contact *b);

int compareByEmail(const Contact *a, const Contact *b);

void sortBook(AddressBook *addressBook,
              int (*compare)(const Contact *a, const Contact *b));

void sortContacts(AddressBook *addressBook, ContactInfo sc);
