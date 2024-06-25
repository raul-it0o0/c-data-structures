#pragma once
#include <stdio.h>
#include <stdlib.h>

// ______ Structures ______
// Node
typedef struct Node {

    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;

} Node;
// Constructor
Node* init_node(int key);
// Destructor
void destroy_node(Node* node);

// Binary Search Tree
typedef struct BinarySearchTree {

    Node* root;

} BinarySearchTree;
// Constructor
BinarySearchTree* init_bst();
// Destructor
void destroy_bst(BinarySearchTree* T);

// ______ Helper functions / subroutines ______
void traverse_in_order(Node* root, void (*do_something_to_a_node)(Node* current_node));
Node* find_minimum(Node* root);
Node* find_successor(Node* root);
void root_transplant(BinarySearchTree* T, Node* old_root, Node* new_root);

// ______ Binary Search Tree query operations ______
Node* search(BinarySearchTree* T, int val);
void print_in_order(BinarySearchTree* T);

// ______ Binary Search Tree update operations ______
void insert(BinarySearchTree* T, int val);
void delete(BinarySearchTree* T, int val);