#include "contact.h"
#include <stdio.h>
#include <string.h>

// print the lower edge of a table/cell, hardcoded values
// in the loop as the table will always render with
// all values
void printEdge(char ch) {
    int arr[4] = {5, 20, 15, 30};
    printf("+");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < arr[i] + 2; j++)
            printf("%c", ch);
        printf("+");
    }
    printf("\n");
}

void printCellEdge() { printEdge('-'); }

void printTableEdge() { printEdge('='); }

// print table headers before printing the details
void printTableHeaders() {
    printTableEdge();
    printf("| %-5s | %-20s | %-15s | %-30s |\n", "No.", "Name", "Phone",
           "Email");
    printCellEdge();
}

// print a single contact info
void displayContact(int index, const Contact *contact) {
    printf("| %-5d | %-20s | %-15s | %-30s |\n", index, contact->name,
           contact->phone, contact->email);
}

// print message edges the top / bottom
void printMessageEdge(int msgLength) {
    printf("+");
    for (int i = 1; i < msgLength - 1; i++)
        printf("=");
    printf("+\n");
}

// for any message to be printed print top & bottom edges
// and then print the content in between
// top and bottom are adjusted based on msg length
void printMessage(const char *str) {
    int msgLength = strlen(str);
    msgLength += 10;
    printMessageEdge(msgLength);
    // || + 3 spaces take up 5 characters on each side
    // that's why edges need to be for 10 + msg length
    printf("||   %s   ||\n", str);
    printMessageEdge(msgLength);
}
