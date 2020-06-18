/*
Here we are building an algorithm to construct a binary search tree
when we know the average frequency in which each key is used.
This isn't very applicable, but it's an interesting algorithm worth
seeing and understanding.
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Node struct
typedef struct node{
    int key;
    struct node *left, *right;
}node;

// Function that actually generates the tree once the optimal roots are already calculated
void make_tree(int *R, int n, int first, int last, node **root){
    int k = *((R + first*(n+1)) + last);
    if(first != last){
        *root = (node *)malloc(sizeof(node));
        (*root)->key = k;
        make_tree(R, n, first, k-1, &(*root)->left);
        make_tree(R, n, k, last, &(*root)->right);
    }
    else{
        *root = NULL;
    }
}
/*
Notation
    For n entries:
        -> key[i], i = 1, ..., n: ordered, so that we construct a binary search tree;
        -> freq[i], i = 1, ..., n: it's the average frequency of the keys[i];
        -> freq_[i], i = 0, 1, ..., n:
            - for i = 0: frequency in which we get values bellow key[1];
            - for i = 1, ..., n-1: frequency in which we get values between key[i] and key[i+1];
            - for i = n: frequency in which we get values above key[n].
        -> F[i][j], i,j = 0, 1, ..., n: sum of frequencies freq[i+1] to freq[j] and freq_[i] to freq_[j];
        -> C[i][j], i,j = 0, 1, ..., n: cost of the tree with nodes i+1 to j. We calculate it by C[i][j] = C[i][k-1] + C[k][j] + F[i][j].
        Where k minimizes this sum and, consequently, is the optimal root of the tree with nodes i+1 to j;
        -> R[i][j], i,j = 1, ..., n: the optimal root for the tree with nodes i+1 to j.
    P.S.
    key[0], freq[0], R[0][j] and R[i][0] aren't going to be used.
*/
void construct(int key[], int freq[], int freq_[], int n, node **root){
    int F[n+1][n+1], C[n+1][n+1], R[n+1][n+1];
    int i, j, k, sub_root, min_cost;

    // Generating the frequency table
    for(i = 0; i <= n; i++){
        F[i][i] = freq_[i];
        for(j = i+1; j <= n; j++){
            F[i][j] = F[i][j-1] + freq[j] + freq_[j];
        }
    }

    // The cost of the empty trees is 0
    for(i = 0; i <= n; i++){
        C[i][i] = 0;
    }
    // Calculating the optimal costs and, consequently, the optimal roots.
    // We make this calculation diagonaly, where i = 0 corresponds to the main diagonal and i = n to the top right element.
    // And j goes from the top left of the diagonal to the bottom right.
    for(i = 1; i <= n; i++){
        for(j = 0; j <= n-i; j++){
            min_cost = INT_MAX;
            for(k = j+1; k <= j+i; k++){
                if(C[j][k-1] + C[k][j+i] < min_cost){
                    min_cost = C[j][k-1] + C[k][j+i];
                    sub_root = k;
                }
            }
            R[j][j+i] = sub_root;
            C[j][j+i] = C[j][sub_root-1] + C[sub_root][j+i] + F[j][j+i];
        }
    }
    R[0][0] = 0;
    make_tree(&R[0][0], n, 0, n, root);
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
    // Example with 4 entries following the pattern described above.
    int key[5] = {0, 5, 9, 16, 22};
    int freq[5] = {0, 10, 1, 3, 2};
    int freq_[5] = {2, 1, 1, 1, 1};
    node *root = NULL;

    construct(key, freq, freq_, 4, &root);
    printpre(root);
    printf("\n");
    printsym(root);
    printf("\n");

    return 0;
}