#include "contact.h"
#include <stdio.h>
#include <string.h>

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

void printTableHeaders() {
    printTableEdge();
    printf("| %-5s | %-20s | %-15s | %-30s |\n", "No.", "Name", "Phone",
           "Email");
    printCellEdge();
}

void displayContact(int index, const Contact *contact) {
    printf("| %-5d | %-20s | %-15s | %-30s |\n", index, contact->name,
           contact->phone, contact->email);
}

void printMessageEdge(int msgLength) {
    printf("+");
    for (int i = 1; i < msgLength - 1; i++)
        printf("=");
    printf("+\n");
}

void printMessage(const char *str) {
    int msgLength = strlen(str);
    msgLength += 10;
    printMessageEdge(msgLength);
    printf("||   %s   ||\n", str);
    printMessageEdge(msgLength);
}
