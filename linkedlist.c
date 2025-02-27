#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


typedef struct LinkedList {
    Node* head;
    Node* tail;
} LinkedList;

LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

    if (list == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    return list;
}

Node* createNode(int d) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = d;
    newNode->next = NULL;
    return newNode;
}

void append(LinkedList* list, int d) {
    Node* newNode = createNode(d);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }
}

void delete(LinkedList* list) {
    Node* current = list->head;

    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }

    while(current != NULL) {
        Node* deleteNode = current;
        current = current->next;
        free(deleteNode);
    }

    free(list);
    printf("List deleted.\n");
}

void print(LinkedList* list) {
    if (list->head ==  NULL) {
        printf("List is empty.\n");
    } else {
        Node* current = list->head;
        while (current != NULL) {
            printf("%d\n",current->data);
            current = current->next;
        }
    }
}


int main() {

    LinkedList* myList = createList();

    append(myList, 10);
    append(myList, 20);

    print(myList);

    delete(myList);

    return 0;

}