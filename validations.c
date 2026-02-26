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

int validatePartialPhone(const char *phone) {
    // only numerics for searches , helps with early exit
    int len = strlen(phone);
    for (int i = 0; i < len; i++)
        if (!isdigit(phone[i]))
            return 0;
    return 1;
}

int validateEmail(const char *email) {
    int len = strlen(email);
    if (len < 5)
        return 0; // a@b.c minimum
    // store the index of @ and .
    char index[2] = {-1, -1};
    //@ , . shouldn't be the last
    if (email[len - 1] == '.' || email[len - 1] == '@')
        return 0;
    //@ , . shouldn't be the first
    if (email[0] == '@' || email[0] == '.')
        return 0;
    // only 1 @ should be present
    int atCount = 0;
    for (int i = 0; i < len; i++) {
        if (email[i] == ' ')
            return 0;
        if (email[i] == '@') {
            atCount++;
            index[0] = i;
        } else if (email[i] == '.') {
            if (i > 0 && email[i - 1] == '.') // no consecutive dots
                return 0;
            index[1] = i;
        }
    }
    // if @ count not 1 (0 or 2+) or if @ , . weren't found
    if (atCount != 1 || index[0] == -1 || index[1] == -1)
        return 0;
    // characters between @ and . should be present and can't be non alphanum
    if (index[1] - index[0] <= 1)
        return 0;
    for (int i = index[0] + 1; i < len; i++) {
        if (!(isalnum(email[i]) || email[i] == '.' || email[i] == '-'))
            return 0;
    }
    return 1;
}
