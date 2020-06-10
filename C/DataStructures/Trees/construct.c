#include <stdio.h>
#include <stdlib.h>

//defining the tree structure
typedef struct node{
    int key;
    struct node *right;
    struct node *left;
}node;

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

//example
int main(){
    node *root;
    int pre[] = {40, 20, 10, 30, 90, 60, 50, 70, 80, 100};
    int sym[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    construct(pre, sym, 0, 9, 0, 9, &root);

    return 0;
}