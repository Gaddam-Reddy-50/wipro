#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node* prev;
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->prev = NULL;
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

// Function to add a new node at the beginning of the doubly linked list
struct Node* addToBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);

    if (head == NULL) {
        return newNode;
    }

    newNode->next = head;
    head->prev = newNode;

    return newNode;
}
struct Node* addToEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);

    if (head == NULL) {
        return newNode;
    }

    struct Node* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;

    return head;
}
struct Node* addBeforeNode(struct Node* head, int target, int data) {
    struct Node* newNode = createNode(data);

    if (head == NULL) {
        return newNode;
    }

    struct Node* current = head;

    while (current != NULL) {
        if (current->data == target) {
            newNode->prev = current->prev;
            newNode->next = current;

            if (current->prev != NULL) {
                current->prev->next = newNode;
            }

            current->prev = newNode;

            if (current == head) {
                return newNode;
            }

            return head;
        }

        current = current->next;
    }

    printf("%d not found in the list. Insertion not possible.\n", target);
    return head;
}
struct Node* addAfterNode(struct Node* head, int target, int data) {
    struct Node* newNode = createNode(data);

    if (head == NULL) {
        return newNode;
    }

    struct Node* current = head;

    while (current != NULL) {
        if (current->data == target) {
            newNode->prev = current;
            newNode->next = current->next;

            if (current->next != NULL) {
                current->next->prev = newNode;
            }

            current->next = newNode;

            return head;
        }

        current = current->next;
    }

    printf("%d not found in the list. Insertion not possible.\n", target);
    return head;
}
struct Node* deleteFirst(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Deletion not possible.\n");
        return NULL;
    }

    struct Node* newHead = head->next;

    if (newHead != NULL) {
        newHead->prev = NULL;
    }

    free(head);

    return newHead;
}
struct Node* deleteLast(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Deletion not possible.\n");
        return NULL;
    }

    struct Node* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    if (current->prev != NULL) {
        current->prev->next = NULL;
    } else {
        head = NULL;
    }

    free(current);

    return head;
}
struct Node* deleteByValue(struct Node* head, int target) {
    if (head == NULL) {
        printf("List is empty. Deletion not possible.\n");
        return NULL;
    }

    struct Node* current = head;

    while (current != NULL) {
        if (current->data == target) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current);

            return head;
        }

        current = current->next;
    }

    printf("%d not found in the list. Deletion not possible.\n", target);
    return head;
}
int search(struct Node* head, int target) {
    struct Node* current = head;

    while (current != NULL) {
        if (current->data == target) {
            return 1; // Found
        }

        current = current->next;
    }

    return 0; // Not found
}
void traverse(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Doubly Linked List: ");

    struct Node* current = head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, target;

    while (1) {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert before a value\n");
        printf("4. Insert after a value\n");
        printf("5. Delete from the beginning\n");
        printf("6. Delete from the end\n");
        printf("7. Delete by value\n");
        printf("8. Search for a value\n");
        printf("9. Traverse the list\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

       switch (choice) {

    case 1:
        printf("Enter the value to insert at the beginning: ");
        scanf("%d", &data);

        head = addToBeginning(head, data);
        break;

    case 2:
        printf("Enter the value to insert at the end: ");
        scanf("%d", &data);

        head = addToEnd(head, data);
        break;

    case 3:
        printf("Enter the target value before which to insert: ");
        scanf("%d", &target);

        printf("Enter the value to insert: ");
        scanf("%d", &data);

        head = addBeforeNode(head, target, data);
        break;

    case 4:
        printf("Enter the target value after which to insert: ");
        scanf("%d", &target);

        printf("Enter the value to insert: ");
        scanf("%d", &data);

        head = addAfterNode(head, target, data);
        break;

    case 5:
        head = deleteFirst(head);
        break;

    case 6:
        head = deleteLast(head);
        break;

    case 7:
        printf("Enter the value to delete: ");
        scanf("%d", &target);

        head = deleteByValue(head, target);
        break;

    case 8:
        printf("Enter the value to search: ");
        scanf("%d", &target);

        if (search(head, target)) {
            printf("%d found in the list.\n", target);
        } else {
            printf("%d not found in the list.\n", target);
        }
        break;

    case 9:
        traverse(head);
        break;

    case 10:
        exit(0);

    default:
        printf("Invalid choice. Please enter a valid option.\n");
}
    }
    return 0;
}
