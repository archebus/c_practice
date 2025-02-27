#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

typedef struct Stack {
    struct Node* head;
} Stack;


typedef struct Node {
    void* data;
    struct Node* next;
} Node;


Node* createNode(void* d) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Node memory allocation failed.\n");
        return NULL;
    }

    newNode->data = d;
    newNode->next = NULL;

    return newNode;
}

Stack* createStack() {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));

    if (newStack == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newStack->head = NULL;

    return newStack;
}

void push(Stack* stack, void* d) {
    Node* newNode = createNode(d);
    
    if (stack->head == NULL) {
        stack->head = newNode;
        return;
    }

    newNode->next = stack->head;
    stack->head = newNode;

}

Node* pop(Stack* stack) {
    Node* popNode = stack->head;

    stack->head = stack->head->next;
    popNode->next = NULL;

    return popNode;
}

Node* peek(Stack* stack) {
    return stack->head;
}

bool isEmpty(Stack* stack) {
    if (stack->head == NULL) {
        return true;
    }
    return false;
}

void printInt(Stack* stack) {
    if (stack->head == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    
    printf("Stack contents: \n");
    Node* current = stack->head;
    while(current != NULL) {
        printf("%d\n", *(int*)current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Stack* myStack = createStack();
    
    for (int i=1; i<20; i++) {
        int* value = (int*)malloc(sizeof(int));
        *value = i;
        push(myStack, value);
    }

    printInt(myStack);

    pop(myStack);

    printInt(myStack);

    printf("Is the stack empty? %d",isEmpty(myStack));

    free(myStack);
    
    return 0;
}