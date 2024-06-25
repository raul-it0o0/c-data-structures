#include "binary_search_tree.h"

Node* init_node(int key) {

    Node* node = malloc(sizeof(Node));

    node->key = key;

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BinarySearchTree* init_bst() {

    BinarySearchTree* new_bst = malloc(sizeof(BinarySearchTree));

    new_bst->root = NULL;

    return new_bst;

}

void destroy_node(Node* node) {
    node->right = NULL;
    node->left = NULL;
    node->parent = NULL;
    free(node);
    node = NULL;
}

void destroy_bst(BinarySearchTree* T) {
    traverse_in_order(T->root, destroy_node);
    T->root = NULL;
    free(T);
    T = NULL;
}

Node* search(BinarySearchTree* T, int val) {

    Node* iterator = T->root;

    while ((iterator != NULL) && (iterator->key != val)) {
        if (val < iterator->key)
            // Move left
            iterator = iterator->left;
        else
            // Move right
            iterator = iterator->right;
    }

    return iterator;

}

// Find minimum of tree rooted at "root"
Node* find_minimum(Node* root) {
    Node* iterator = root;

    while (iterator->left != NULL)
        iterator = iterator->left;

    return iterator;
}

// Find successor of key at "node"
Node* find_successor(Node* node) {

    if (node->right != NULL)
        // Go right once, then go as left as possible
        return find_minimum(node->right);

    // otherwise, node either has only a left child
    // or is a leaf node
    Node* parent = node->parent;

    // while there is a parent, and I am coming from the right
    while ((parent != NULL) && (parent->right = node)) {
        // move up
        parent = parent->parent;
    }

    if (parent != NULL)
        return parent;
    else {
        printf("NO SUCCESSOR FOUND\n");
        return NULL;
    }

}

void print_node_key(Node* node) {
    printf("%d ", node->key);
    fflush(stdout);
}

// Traverses in-order the tree rooted at node "root"
void traverse_in_order(Node* root, void (*do_something_to_a_node)(Node* current_node)) {

    // breaking out of stack frame
    if (root == NULL)
        return;

    traverse_in_order(root->left, do_something_to_a_node);

    // store the right child of the root in case the root cannot get accessed anymore
    // e.g. in cases where it gets deallocated
    Node* right = root->right;

    // do something with the node (e.g. print it)
    do_something_to_a_node(root);

    traverse_in_order(right, do_something_to_a_node);

}



void print_in_order(BinarySearchTree* T) {
    traverse_in_order(T->root, print_node_key);
}

void insert(BinarySearchTree* T, int val) {

    // If tree is empty
    if (T->root == NULL) {
        Node* new_node = init_node(val);
        T->root = new_node;
        return;
    }

    // Iterate to determine the position of the new node
    Node* iterator = T->root;
    Node* iterator_parent = NULL;

    while (iterator != NULL) {
        iterator_parent = iterator;

        if (val < iterator->key)
            // Move to the left
            iterator = iterator->left;
        else if (val > iterator->key)
            // Move to the right
            iterator = iterator->right;
        else {
            // Equal, duplicates not allowed
            printf("VALUE ALREADY IN TREE. NO DUPLICATES ALLOWED\n");
            return;
        }

    }

    Node* new_node = init_node(val);

    // iterator is at the final position of new_node
    // Set the parent of the new_node
    new_node->parent = iterator_parent;

    // Have the parent point to its new child
    if (new_node->key < iterator_parent->key)
        iterator_parent->left = new_node;
    else
        iterator_parent->right = new_node;

}

void root_transplant(BinarySearchTree* T, Node* old_root, Node* new_root) {

    // 1. Have the parent of old_root point to its new child (new_root)
    // Check if old_root is the root of the tree
    if (old_root->parent == NULL)
        T->root = new_root;

    // Check which child (left, right) of the parent is old_root
    else if (old_root == old_root->parent->left)
        old_root->parent->left = new_root;
    else if (old_root == old_root->parent->right)
        old_root->parent->right = new_root;

    // 2. Have new_root point to its new parent
    // Check that new_root is not NULL
    if (new_root != NULL)
        new_root->parent = old_root->parent;

}

void delete(BinarySearchTree* T, int val) {
    Node* node = search(T, val);

    if (node == NULL) {
        printf("%d NOT FOUND IN TREE\n", val);
        return;
    }

    // check how many children "node" has
    if (node->left == NULL)
        // node has only a right child or none
        // new subtree is rooted at node->right (can be NULL)
        root_transplant(T, node, node->right);
    else if (node->right == NULL)
        // node has only a left child
        // new subtree is rooted at node->left
        root_transplant(T, node, node->left);

    else {
        // node has both children

        // find successor on node->key
        Node* successor = find_successor(node);

        // if successor is not the direct right child of node
        if (successor != node->right) {
            // new subtree rooted successor becomes rooted
            // at successor->right (can be NULL)
            root_transplant(T, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }

        root_transplant(T, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;

    }

    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    free(node);
    node = NULL;

}

int main() {

    BinarySearchTree* myBST = init_bst();

    insert(myBST, 33);
    insert(myBST, 34);
    insert(myBST, 5);
    insert(myBST, 39);
    insert(myBST, 40);
    insert(myBST, 18);
    insert(myBST, 30);
    insert(myBST, 31);

    search(myBST, 2);
    print_in_order(myBST);
    delete(myBST, 31);
    delete(myBST,39);
    delete(myBST,5);
    delete(myBST,33);

    destroy_bst(myBST);

}