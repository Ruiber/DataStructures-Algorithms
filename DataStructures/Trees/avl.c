/*
The AVL tree is basicaly a binary search tree where given a node, the difference between the heights of it's
sub-trees is at most 1. This way we can garantee that the total height of the tree is proportional to log(n).
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key, balance;
    struct node *left, *right;
}node;

// Right rotation in order to rebalance a node with -2 balance
void right_rot(node **p){
    node *u = (*p)->left;
    node *v = u->right;
    // single rotation
    if(u->balance == -1){
        (*p)->left = u->right;
        u->right = *p;
        u->balance = 0;
        (*p)->balance = 0;
        *p = u;
    }
    // double rotation
    else{
        u->right = v->left;
        (*p)->left = v->right;
        v->left = u;
        v->right = *p;
        if(v->balance == 1){
            u->balance = -1;
            (*p)->balance = 0;
        }
        else if(v->balance == -1){
            u->balance = 0;
            (*p)->balance = 1;
        }
        else{
            u->balance = 0;
            (*p)->balance = 0;
        }
        v->balance = 0;
        *p = v;
    }
}

// Left rotation in order to rebalance a node with +2 balance
void left_rot(node **p){
    node *u = (*p)->right;
    node *v = u->left;
    // single rotation
    if(u->balance == 1){
        (*p)->right = u->left;
        u->left = *p;
        u->balance = 0;
        (*p)->balance = 0;
        *p = u;
    }
    // double rotation
    else{
        u->left = v->right;
        (*p)->right = v->left;
        v->left = *p;
        v->right = u;
        if(v->balance == 1){
            u->balance = 0;
            (*p)->balance = -1;
        }
        else if(v->balance == -1){
            u->balance = 1;
            (*p)->balance = 0;
        }
        else{
            u->balance = 0;
            (*p)->balance = 0;
        }
        v->balance = 0;
        *p = v;
    }
}

// 1 indicates that the tree grew, 0 indicates that it didn't
int insert(int key, node **root){
    int growth = 0;
    if(*root == NULL){
        *root = (node *)malloc(sizeof(node));
        (*root)->key = key;
        (*root)->balance = 0;
        (*root)->right = NULL;
        (*root)->left = NULL;
        return 1;
    }
    if(key > (*root)->key){
        growth = insert(key, &(*root)->right);
        if(growth == 1){
            (*root)->balance ++;
            if((*root)->balance == 2){
                left_rot(root);
                return 0;
            }
            if((*root)->balance == 1){
                return 1;
            }
            return 0;
        }
        return 0;
    }
    if(key < (*root)->key){
        growth = insert(key, &(*root)->left);
        if(growth == 1){
            (*root)->balance --;
            if((*root)->balance == -2){
                right_rot(root);
                return 0;
            }
            if((*root)->balance == -1){
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

//printing the symmetrical order
void printsym(node *root){
    if(root != NULL){
        printsym(root->left);
        printf("(%d, %d) ", root->key, root->balance);
        printsym(root->right);
    }
}

//printing the pre-order
void printpre(node *root){
    if(root != NULL){
        printf("(%d, %d) ", root->key, root->balance);
        printpre(root->left);
        printpre(root->right);
    }
}

int main(){
    node *root = NULL;
    int entries[10] = {2, 7, 9, 5, 10, 4, 8, 3, 1, 6};
    int i;
    
    for(i=0; i<10; i++){
        printf("Inserting %d in the tree:\n", entries[i]);
        insert(entries[i], &root);
        printpre(root);
        printf("\n\n");
    }
    
    return 0;
}