//My custom linked list data structure
//Singly linked list containing strings.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    char* data;
    struct Node* next;
}Node;

//Initializes a linked list and adds the given string to the first node created. 
//Returns the head node pointer
Node* init(char* string) {
    Node* head = malloc(sizeof(Node));
    Node* node = malloc(sizeof(Node));
    if(head == NULL || node == NULL) {
        return NULL;
    }

    head->data = "HEAD NODE";
    head->next = node;

    node->data = malloc(strlen(string) + 1);
    if(node->data == NULL) {
        printf("Error: Failure to allocate memory for node.data\n");
        free(head);
        free(node);
        return NULL;
    }

    strcpy(node->data, string);
    node->next = NULL;
    return head;
}

//Attempts to create a new node at the end of the list provided and add the string as data 
//to the node
void addElem(Node* head, char* string) {
    Node* node = head;
    while(node->next != NULL) {
        node = node->next;
    }
    Node* newNode = malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Error: Failure to allocate memory for newNode\n");
        return;
    }

    newNode->data = malloc(strlen(string) + 1);
    if(newNode->data == NULL) {
        printf("Error: Failure to allocate memory for newnode.data\n");
        free(newNode);
        return;
    }

    strcpy(newNode->data, string);

    newNode->next = NULL;
    node->next = newNode;
    return;
}

//Attempts to find the given string in the linked list. Returns the index of the 
//element if found, otherwise returns -1.
int findElem(Node* head, char* string) {
    int index = -1;
    Node* traversalNode = head;
    while(traversalNode != NULL) {
        //If match found
        if(strcmp(traversalNode->data, string) == 0) {
            return index;
        }
        traversalNode = traversalNode->next;
        index++;
    }
    return -1;

}

//Returns the size of the linkedList NOT including the head
int size(Node* linkedList) {
    Node* node = linkedList;
    int index = -1;
    while(node != NULL) {
        node = node->next;
        index++;
    }

    return index;
}

//Returns the data from the linkedList at the index provided
char* getElem(Node* linkedList, int index) {
    //Returns error if invalid index 
    if(index < 0 || index >= size(linkedList)) {
        printf("Error: Invalid index provided\n");
        return "NULL";
    }
    
    Node* node = linkedList;

    int i = -1;
    while(node != NULL) {
        if(i != index) {
            node = node->next;
            i++;
            continue;
        }
        else {
            return node->data;
        }
    }

    return "NULL";

    
}

//Pretty prints the contents of the linked list
void printList(Node* linkedList) {
    Node* node = linkedList;
    for(int i = -1; node != NULL; i++) {
        printf("%d %s\n", i, node->data);
        node = node->next;
    }

}

//Removes an element at the given index
void removeElem(Node* linkedList, int index) {
    if(index < 0 || index >= size(linkedList)) {
        printf("Error: Invalid index provided\n");
        return;
    }

    Node* node = linkedList;
    Node* temp;
    //Traverse through the list until the index is found.
    for(int i = -1; i < index; i++) {
        node = node->next;
    }
    //we are at the node RIGHT BEFORE the index to be removed.

    temp = node;
    node = node->next;
    temp->next = temp->next->next;
    free(node);

    return;
}

int main(int argc, char const *argv[]) {
    Node* linkedList = init("Kevin Pluas"); //Should be index of 0 
    addElem(linkedList, "Valerie Ramirez");
    addElem(linkedList, "David Ramirez");
    addElem(linkedList, "Celia Ramirez");
    addElem(linkedList, "Teresa Pluas");

    printList(linkedList);

    removeElem(linkedList, 2);

    printf("This is the list after the deletion of index 2 which was David\n");
    printList(linkedList);

    return 0;
}
