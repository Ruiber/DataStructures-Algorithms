#include <stdio.h>
#include <stdlib.h>

//defining the tree structure
typedef struct node{
    int key;
    struct node *right;
    struct node *left;
}node;

//Searches for the key in the tree, returning the node if it's found. If you didn't find, it returns the closest node.
node *search(int key, node *root, node **parent){
    if(root == NULL) return NULL;
    if(root->key == key) return root;
    if(root->key > key){
        if(root->left != NULL){
            *parent = root;
            return search(key, root->left, parent);
        }
        else{
            return root;
        }
    }
    else{
        if(root->right != NULL){
            *parent = root;
            return search(key, root->right, parent);
        }
        else{
            return root;
        }
    }
}

int insert(int key, node **root){
    node *aux, *parent = NULL;
    aux = search(key, *root, &parent);
    
    //Empty tree
    if(aux == NULL){
        *root = (node *)malloc(sizeof(node));
        (*root)->key = key;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return 1;
    }
    if(aux->key > key){
        aux->left = (node *)malloc(sizeof(node));
        (aux->left)->key = key;
        (aux->left)->left = NULL;
        (aux->left)->right = NULL;
        return 1;
    }
    if(aux->key < key){
        aux->right = (node *)malloc(sizeof(node));
        (aux->right)->key = key;
        (aux->right)->left = NULL;
        (aux->right)->right = NULL;
        return 1;
    }
    return 0;
}

int remove_node(int key, node **root){
    node *aux, *aux2, *parent = NULL, *parent2;
    aux = search(key, *root, &parent);
    
    if(aux != NULL && aux->key == key ){  //Excluding cases where the tree is empty or when the key ins't in the tree
        if(aux->left == NULL && aux->right == NULL){  //When the node is a leaf
            if(parent == NULL){  //Removing the root
                free(*root);
                *root = NULL;
            }
            else{
                if(parent->left == aux){
                    parent->left = NULL;
                }
                else{
                    parent->right = NULL;
                }
                free(aux);
            }
        }
        else if(aux->left == NULL || aux->right == NULL){  //When the node has only one child
            if(parent == NULL){  //Node is the root
                if((*root)->left != NULL){
                    *root = (*root)->left;
                }
                else{
                    *root = (*root)->right;
                }
            }
            else{
                if(parent->right == aux){
                    if(aux->right != NULL){
                        parent->right = aux->right;
                    }
                    else{
                        parent->right = aux->left;
                    }
                }
                else{
                    if(aux->right != NULL){
                        parent->left = aux->right;
                    }
                    else{
                        parent->left = aux->left;
                    }
                }
            }
            free(aux);
        }
        else{  //When the node has two children
            parent2 = aux;
            aux2 = search(key, aux->right, &parent2);  //Finding the substitute in the right sub-tree
            if(aux2->right == NULL){
                if(parent2->left == aux2){
                    parent2->left = NULL;
                }
                else{
                    parent2->right = NULL;
                }
            }
            else{
                if(parent2->left == aux2){
                    parent2->left = aux2->right;
                }
                else{
                    parent2->right = aux2->right;
                }
            }
            aux2->right = aux->right;
            aux2->left = aux->left;
            if(parent == NULL){
                free(aux);
                *root = aux2;
            }
            else{
                if(parent->right == aux){
                    parent->right = aux2;
                    free(aux);
                }
                else{
                    parent->left = aux2;
                    free(aux);
                }
            }
        }
        return 1;
    }
    return 0;
}
    
//constructing the tree based on the pre-order and the symmetrical order
void construct(int pre[], int sym[], int fp, int lp, int fs, int ls, node **root){
    int pos_sym, i, left_size, right_size;
    int key = pre[fp];
    //this condition is considering only the cases where we have at least one element
    if(lp - fp >= 0){
        //allocating space for the new node
        *root = (node *)malloc(sizeof(node));
        (*root)->key = key;

        //searching for the key in the symmetrical order array
        for(i = fs; i <= ls; i++){
            if(sym[i] == key){
                pos_sym = i;
                break;
            }
        }

        //determining how many elements there are to the left and to the right of our key
        //in the symmetrical order array
        left_size = pos_sym - fs;
        right_size = ls - pos_sym;

        //recursively constructing the left and the right sub-trees
        construct(pre, sym, fp+1, fp + left_size, fs, pos_sym-1, &((*root)->left));
        construct(pre, sym, fp + left_size + 1, lp, pos_sym + 1, ls, &((*root)->right));
    }
    //when there isn't any element
    else{
        *root = NULL;
    }
}

//printing the symmetrical order
void printsym(node *root){
    if(root != NULL){
        printsym(root->left);
        printf("%d ", root->key);
        printsym(root->right);
    }
}

//printing the pre-order
void printpre(node *root){
    if(root != NULL){
        printf("%d ", root->key);
        printpre(root->left);
        printpre(root->right);
    }
}

int main(){
    int key;
    node *root;
    int pre[] = {40, 20, 10, 30, 80, 60, 50, 70, 90};
    int sym[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    construct(pre, sym, 0, 8, 0, 8, &root);
    printpre(root);
    printf("\n");
    printsym(root);
    printf("\n");

    
    key = 60;
    if(remove_node(key, &root)){
        printf("The key %d was succesfully removed.\nThe tree becomes:\n", key);
        printpre(root);
        printf("\n");
        printsym(root);
        printf("\n");
    }
    else{
        printf("The key %d isn't in the tree.\n", key);
    }

    return 0;
}