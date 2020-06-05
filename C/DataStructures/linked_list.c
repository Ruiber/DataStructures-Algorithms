#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *next;
}node;

node *search(int key, node *head){
    while(head != NULL && head->key != key)
        head = head->next;

    return head;
}

node *last(node *head){
    if(head == NULL) return head;
    while(head->next != NULL)
        head = head->next;
    
    return head;
}

int insertNode(int key, node **head){
    node *aux1 = search(key, *head);
    node *aux2 = last(*head);
    node *new;

    if(*head == NULL){
        *head = (node *)malloc(sizeof(node));
        (*head)->key = key;
        (*head)->next = NULL;
        return 1;
    }
    
    if(aux1 == NULL){
        new = (node *)malloc(sizeof(node));
        new->key = key;
        new->next = NULL;
        aux2->next = new;
        return 1;
    }

    return 0;
}

int removeNode(int key, node **head){
    node *aux1 = search(key, *head);
    node *aux2 = *head;
    
    if(aux1 == NULL){
        return 0;
    }

    if(aux1 == *head){
        *head = (*head)->next;
    }
    else{
        while(aux2->next->key != aux1->key){
            aux2 = aux2->next;
        }
        aux2->next = aux1->next;
    }
    free(aux1);

    return 1;
}

void printList(node *head){
    if(head == NULL)
        printf("The list is empty.\n");
    else{
        while(head != NULL){
            printf("%d ", head->key);
            head = head->next;
        }
        printf("\n");
    }
}

int main(){
    node *head = NULL;
        
    insertNode(10, &head);
    printList(head);
    insertNode(9, &head);
    printList(head);
    insertNode(8, &head);
    printList(head);
    insertNode(16, &head);
    printList(head);
    insertNode(20, &head);
    printList(head);
    insertNode(3, &head);
    printList(head);
    insertNode(14, &head);
    printList(head);
    insertNode(25, &head);
    printList(head);

    removeNode(16, &head);
    printList(head);
    removeNode(3, &head);
    printList(head);
    removeNode(10, &head);
    printList(head);
    removeNode(8, &head);
    printList(head);
    removeNode(9, &head);
    printList(head);
    removeNode(20, &head);
    printList(head);
    removeNode(25, &head);
    printList(head);
    removeNode(14, &head);
    printList(head);

    return 0;
}