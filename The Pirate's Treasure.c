#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// Chest structure
struct chest {
    int identifier;
    char message[200];
    struct chest* next;
};

// Function to check if the length of a message is prime
bool is_prime_length(char* message) {
    int len = strlen(message);
    if (len <= 1) return false;
    for (int i = 2; i <= sqrt(len); i++) {
        if (len % i == 0) return false;
    }
    return true;
}

// Extract first number from message
int FindNumber(char* message) {
    int num = 0, found = 0;
    for (int i = 0; message[i]; i++) {
        if (isdigit(message[i])) {
            num = num * 10 + (message[i] - '0');
            found = 1;
        } else if (found) break;
    }
    return found ? num : 0;
}

// Insert chest sorted by identifier
void insert(struct chest** head, int ide, char m[]) {
    struct chest* newchest = (struct chest*)malloc(sizeof(struct chest));
    newchest->identifier = ide;
    strcpy(newchest->message, m);
    newchest->next = NULL;

    if (*head == NULL || (*head)->identifier > ide) {
        newchest->next = *head;
        *head = newchest;
        return;
    }

    struct chest* p = *head;
    while (p->next && p->next->identifier < ide) {
        p = p->next;
    }
    newchest->next = p->next;
    p->next = newchest;
}

// Delete a chest by ID
void delet(int ide, struct chest** head) {
    struct chest *p = *head, *prev = NULL;

    while (p && p->identifier != ide) {
        prev = p;
        p = p->next;
    }

    if (p != NULL) {
        if (prev == NULL) *head = p->next;
        else prev->next = p->next;
        free(p);
        printf("Chest %d removed.\n", ide);
    } else {
        printf("Chest not found.\n");
    }
}

// Modify chest message by ID
void modify(int ide, struct chest** head, char newmsg[]) {
    struct chest* p = *head;
    while (p && p->identifier != ide) p = p->next;
    if (p) {
        strcpy(p->message, newmsg);
        printf("Chest %d updated.\n", ide);
    } else {
        printf("Chest not found.\n");
    }
}

// Display all chests
void display(struct chest* head) {
    int i = 1;
    while (head != NULL) {
        printf("Chest %d:\n", i++);
        printf("Identifier: %d\n", head->identifier);
        printf("Message: %s\n\n", head->message);
        head = head->next;
    }
}

// Calculate the final treasure combination
int getcombination(struct chest* head) {
    int sum = 0;
    while (head != NULL) {
        if (is_prime_length(head->message)) {
            int val = FindNumber(head->message);
            sum += val;
        }
        head = head->next;
    }
    return sum;
}
int main() {
    struct chest* head = NULL;
    int choice, id;
    char message[200];

    do {
        printf("\n--- Pirate's Treasure Menu ---\n");
        printf("1. Add a chest\n");
        printf("2. Remove a chest\n");
        printf("3. Modify a chest\n");
        printf("4. Display all chests\n");
        printf("5. Discover the treasure combination\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline

        switch (choice) {
            case 1:
                printf("Enter chest identifier: ");
                scanf("%d", &id);
                getchar();
                printf("Enter chest message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                insert(&head, id, message);
                break;

            case 2:
                printf("Enter chest identifier to delete: ");
                scanf("%d", &id);
                delet(id, &head);
                break;

            case 3:
                printf("Enter chest identifier to modify: ");
                scanf("%d", &id);
                getchar();
                printf("Enter new message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                modify(id, &head, message);
                break;

            case 4:
                display(head);
                break;

            case 5:
                printf("Final Treasure Combination: %d\n", getcombination(head));
                break;

            case 0:
                printf("Goodbye, pirate!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
