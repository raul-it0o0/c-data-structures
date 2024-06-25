#pragma once
#include <stdio.h>
#include "stb_ds.h"
#include <stdbool.h>

// ______ Structures ______
// Node
typedef struct Node {

    int key;
    struct Node* parent;

} Node;
// Constructor
Node* init_node(int key);

typedef struct MaxHeap {

    Node** compact_array;
    // an array of Node pointers (Node addresses)
    int size;

} MaxHeap;
// Constructor
MaxHeap init_heap();
// Destructor
void destroy_heap(MaxHeap *H);

// ______ Indexing ______
int parent_index(int i);
int left_child_index(int i);
int right_child_index(int i);

// ______ (Max) Heap procedures ______
void sift_up(MaxHeap* H, int node_index);
void sift_down(MaxHeap* H, int node_index);

// Procedures in simplified array form
void sift_down_array(int arr[], int arr_size, int index);

// ______ (Max) Heap operations ______
// Get maximum
int get_heap_max(MaxHeap* this);

// Insert a value
void insert(MaxHeap* H, int val);

// Heapify (turn an array into a heap through permutations)
void build_max_heap(int arr[], int arr_size);

// Delete an arbitrary value
void delete(MaxHeap* H, int val);
// Delete the root (Extract Max)
void extract_max(MaxHeap *this);

// Print heap
void print_heap(const MaxHeap* H);

// HeapSort
void heapsort(int arr[], int arr_size);