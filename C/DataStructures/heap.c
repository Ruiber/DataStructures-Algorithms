/*
Implementing heap data structure in C.
Heap is a data structure in which one can remove the greatest element in O(1).
The  rule that defines the heap is: heap[i] <= heap[i/2], i = 1, 2, ...
*/

#include <stdio.h>

#define MAX 500

/*
heap declaration
heap[0] represents the number of elements in heap
heap starts in heap[1] and ends in heap[heap[0]]
*/
int heap[MAX] = {};

// When heap[pos] is greater than it's father.
void up(int pos, int heap[]){
    int aux;
    if(pos > 1){
        if(heap[pos] > heap[pos/2]){
            aux = heap[pos];
            heap[pos] = heap[pos/2];
            heap[pos/2] = aux;
            up(pos/2, heap);
        }
    }
}

// Inserting a node into the heap.
int insert(int key, int heap[]){
    if(heap[0] < MAX-1){
        heap[++heap[0]] = key;
        up(heap[0], heap);
        return 1;
    }
    return 0;
}

// When heap[pos] is smaller than it's children.
void down(int pos, int heap[]){
    int aux = heap[pos];
    int greatest;
    if(heap[0] >= 2*pos + 1){
        if(heap[2*pos+1] > heap[2*pos])
            greatest = 2*pos + 1;
        else   
            greatest = 2*pos;
        if(heap[pos] < heap[greatest]){
            heap[pos] = heap[greatest];
            heap[greatest] = aux;
            down(greatest, heap);
        }
    }
    else if(heap[0] == 2*pos && heap[pos] < heap[2*pos]){
        heap[pos] = heap[2*pos];
        heap[2*pos] = aux;
    }
}

// Removing the heap's root (heap[1]).
int remove_top(int heap[]){
    if(heap[0] > 0){
        heap[1] = heap[heap[0]--];
        down(1, heap);
        return 1;
    }
    return 0;
}

void print_heap(int heap[]){
    int i;
    if(heap[0] > 0){
        for(i=1; i<heap[0]; i++){
            printf("%d, ", heap[i]);
        }
        printf("%d\n", heap[i]);
    }
    else{
        printf("-1\n");
    }
}

// Example implemantation of the heap data structure.
int main(){
    insert(99, heap);
    print_heap(heap);
    insert(36, heap);
    print_heap(heap);
    insert(57, heap);
    print_heap(heap);
    insert(81, heap);
    print_heap(heap);
    insert(17, heap);
    print_heap(heap);
    insert(55, heap);
    print_heap(heap);
    insert(73, heap);
    print_heap(heap);
    insert(10, heap);
    print_heap(heap);
    insert(100, heap);
    print_heap(heap);

    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
    remove_top(heap);
    print_heap(heap);
}