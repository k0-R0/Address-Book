#include "contact.h"
#include <ctype.h>
#include <string.h>

int validatePhone(AddressBook *addressBook, const char *phone) {
    // 10 digits
    if (strlen(phone) != 10)
        return 0;
    // numerics
    for (int i = 0; i < 10; i++)
        if (!isdigit(phone[i]))
            return 0;
    // unique
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            return 0;
    }
    return 1;
}

int validateEmail(const char *email) {
    //@ , . should be present
    int len = strlen(email);
    char index[2] = {-1, -1};
    //. shouldn't be the last
    if (email[len - 1] == '.')
        return 0;
    //@ shouldn't be the first
    if (email[0] == '@' || email[0] == '.')
        return 0;
    for (int i = 0; i < len; i++) {
        if (email[i] == ' ')
            return 0;
        if (index[0] != -1 && index[1] != -1)
            break;
        if (email[i] == '@') {
            index[0] = i;
        } else if (email[i] == '.')
            index[1] = i;
    }
    if ((index[0] == -1 || index[1] == -1))
        return 0;
    // characters between @ and . should be present and can't be non alphanum
    // except -
    if (index[1] - index[0] <= 1)
        return 0;
    return 1;
}
