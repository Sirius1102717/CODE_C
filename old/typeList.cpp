// C program for generic linked list
#include <stdio.h>
#include <stdlib.h>

/* A linked list node */
typedef struct Node {
    // Any data type can be stored in this node
    void *data;

    struct Node *next;
}NODE;

/* Function to add a node at the beginning of Linked List.
This function expects a pointer to the data to be added
and size of the data type */
void push(NODE **head, void *newData, size_t dataSize) {
    // Allocate memory for node
    NODE *newNode = (NODE *)malloc(sizeof(NODE));

    newNode->data = malloc(dataSize);
    newNode->next = (*head);

    // Copy contents of newData to newly allocated memory.
    // Assumption: char takes 1 byte.
    int i;
    for (i = 0; i < dataSize; i++)
        *(char *)(newNode->data + i) = *(char *)(newData + i);

    // Change head pointer as new node is added at the beginning
    (*head) = newNode;
}

/* Function to print nodes in a given linked list. fpitr is used
to access the function to be used for printing current node data.
Note that different data types need different specifier in printf() */
void printList(NODE *node, void (*fptr)(void *)) {
    while (node != NULL) {
        (*fptr)(node->data);
        node = node->next;
    }
}

// Function to print an integer
void printInt(void *n) { printf(" %d", *(int *)n); }

// Function to print a float
void printFloat(void *f) { printf(" %f", *(float *)f); }

/* Driver program to test above function */
int main() {
    NODE *start = NULL;

    // Create and print an int linked list
    unsigned int_size = sizeof(int);
    int arr[] = {10, 20, 30, 40, 50}, i;
    for (i = 4; i >= 0; i--)
        push(&start, &arr[i], int_size);
    printf("Created integer linked list is \n");
    printList(start, printInt);

    // Create and print a float linked list
    unsigned float_size = sizeof(float);
    start = NULL;
    float arr2[] = {10.1, 20.2, 30.3, 40.4, 50.5};
    for (i = 4; i >= 0; i--)
        push(&start, &arr2[i], float_size);
    printf("\n\nCreated float linked list is \n");
    printList(start, printFloat);

    return 0;
}