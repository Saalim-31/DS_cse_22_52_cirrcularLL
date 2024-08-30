#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;

void create() {
    int n;
    printf("Enter the number of elements you want to insert: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of elements should be positive.\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        Node* temp = (Node*)malloc(sizeof(Node));  // Use malloc for dynamic memory allocation
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        
        printf("Enter the element: ");
        scanf("%d", &(temp->data));
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
            tail = temp;
            tail->next = head;  // Circular link
        } else {
            tail->next = temp;
            tail = temp;
            tail->next = head;  // Circular link
        }
    }
}

void view() {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* trav = head;
    do {
        printf("%d\n", trav->data);
        trav = trav->next;
    } while (trav != head);
}

void insert() {
    int value, newData;
    printf("Enter the value after which you want to insert: ");
    scanf("%d", &value);
    printf("Enter the new element to insert: ");
    scanf("%d", &newData);

    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    temp->data = newData;

    if (head == NULL) {
        printf("The list is empty. Use create() to add elements first.\n");
        free(temp);
        return;
    }

    Node* trav = head;
    do {
        if (trav->data == value) {
            temp->next = trav->next;
            trav->next = temp;
            if (trav == tail) {
                tail = temp;  // Update tail if inserted after the tail
            }
            return;
        }
        trav = trav->next;
    } while (trav != head);

    printf("Value not found in the list.\n");
    free(temp);
}

void deleteNode() {
    int item;
    printf("Enter the node you want to delete: ");
    scanf("%d", &item);

    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node *temp, *prev;
    if (head->data == item) {
        temp = head;
        if (head == tail) {
            head = tail = NULL;
        } else {
            head = head->next;
            tail->next = head;  // Update tail's next
        }
        free(temp);
    } else {
        prev = head;
        temp = head->next;

        while (temp != head && temp->data != item) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == head) {
            printf("Item not found.\n");
            return;
        }

        if (temp == tail) {
            tail = prev;  // Update tail if deleting the tail
        }

        prev->next = temp->next;
        free(temp);
    }
}

int main() {
    int choice;
    while (1) {
        printf("1 for Create\n2 for View\n3 for Insert\n4 for Delete\n5 for Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                view();
                break;
            case 3:
                insert();
                break;
            case 4:
                deleteNode();
                break;
            case 5:
                // Free remaining nodes
                while (head != NULL) {
                    deleteNode();
                }
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

