#define STB_DS_IMPLEMENTATION
#include "heap.h"

Node* init_node(int key) {

    Node* node = malloc(sizeof(Node));

    node->key = key;

    node->parent = NULL;

    return node;
}

MaxHeap init_heap() {

    MaxHeap* heap = malloc(sizeof(MaxHeap));

    // Initialize dynamic array
    heap->compact_array = NULL;

    heap->size = 0;

    return *heap;

}

int parent_index(int i) {
    return ((i-1)/2);
}

int left_child_index(int i) {
    return (2*i + 1);
}

int right_child_index(int i) {
    return (2*i + 2);
}

void sift_up(MaxHeap* H, int node_index) {
    // Procedure used in Heap operations

    if  (H->compact_array[node_index] == NULL)
        return;

    // Syntax simplifier
    Node* node = H->compact_array[node_index];

    while ((node_index > 0) && (node->key > node->parent->key)) {

        // Have the children of the old parent point to their new parent
        // Check which child (left or right) is the node being sifted up

        int index_left_child_of_parent = left_child_index(parent_index(node_index));
        int index_right_child_of_parent = right_child_index(parent_index(node_index));

        if ((index_left_child_of_parent == node_index) && (index_right_child_of_parent < H->size)) {
            // Node is the left child, check for a right child and have it point to its new parent
            H->compact_array[index_right_child_of_parent]->parent = node;
        }

        else if ((index_right_child_of_parent == node_index) && (index_left_child_of_parent < H->size)) {
            H->compact_array[index_left_child_of_parent]->parent = node;
        }

        // Store the address of the old parent (child of new node)
        Node* old_parent = node->parent;

        // Swap parent pointers
        if  (parent_index(node_index) > 0)
            // The parent of the node being sifted up is the parent of its parent
            node->parent = H->compact_array[parent_index(parent_index(node_index))];
        else
            // The node being sifted up will be the root node
            node->parent = NULL;

        old_parent->parent = node;

        // Swap order in address array
        H->compact_array[parent_index(node_index)] = node;
        H->compact_array[node_index] = old_parent;

        // Move up
        node_index = parent_index(node_index);

    }

} 

void sift_down(MaxHeap* H, int node_index) {
    // Procedure used in Heap operations

    if  (H->compact_array[node_index] == NULL)
        return;

    // Syntax simplifier
    Node* node = H->compact_array[node_index];

    while (node_index < H->size) {

        // Syntax simplifier variables
        int left = left_child_index(node_index);
        int right = right_child_index(node_index);
        int index_of_max;

       // Determine greatest value (node, or either of its children, if any)
       if ((left < H->size) && (H->compact_array[left]->key > node->key))
           index_of_max = left;
       else
           index_of_max = node_index;

       if ((right < H->size) && (H->compact_array[right]->key > node->key))
           index_of_max = right;

       if (index_of_max != node_index) {
           // Swap node with its child with the greatest value

           // Store the address of the old parent of the node being sifted down
           Node* old_parent = node->parent;

           // Swapping parent pointer
           if  (parent_index(node_index) > 0)
               // The parent of the node being sifted down is its child
               node->parent = H->compact_array[index_of_max];
           else
               node->parent = NULL;

           H->compact_array[index_of_max]->parent = old_parent;

           // Swap order in address array
           H->compact_array[node_index] = H->compact_array[index_of_max];
           H->compact_array[index_of_max] = node;

           // Move down
           node_index = index_of_max;
       }

       else
           break;
           // If we do not break we get stuck in an infinite loop evaluating the same values

    }
}

void sift_down_array(int arr[], int arr_size, int index) {

    while (index < arr_size) {
        int left = left_child_index(index);
        int right = right_child_index(index);
        int index_of_max;

        // Determine if the children of arr[i] (if any) have values greater (Max Heap) than it
        if ((left < arr_size) && (arr[left] > arr[index]))
            index_of_max = left;
        else
            index_of_max = index;

        if ((right < arr_size) && (arr[right] > arr[index_of_max]))
            index_of_max = right;

        if (index_of_max != index) {

            // Swap the two values
            int temp = arr[index];
            arr[index] = arr[index_of_max];
            arr[index_of_max] = temp;

            // Move down
            index = index_of_max;
        }
        else
            break;
            // If we do not break we get stuck in an infinite loop evaluating the same values
    }
}

int get_heap_max(MaxHeap* this) {
    // Max element in a Max Heap is the root
    return this->compact_array[0]->key;
}

void delete(MaxHeap* H, int val) {
    // Since duplicates are allowed in Heaps,
    // We delete the first occurrence of the given value

    // Find index (first occurrence) of val
    int index;
    bool found = false;

    for (index = 0; index < H->size; index++) {
        if (H->compact_array[index]->key == val) {
            found = true;
            break;
        }
    }

    if (!found) {
        printf("VALUE NOT FOUND IN HEAP\n");
        return;
    }

    // Free the node that has the value to be deleted
    free(H->compact_array[index]);

    // In the pointer array, set that element to NULL
    // (just for good practice)
    H->compact_array[index] = NULL;
    if (H->size > 1) {
        // Put the last node in the position
        // where the node that got deleted was
        H->compact_array[index] = H->compact_array[H->size - 1];

        // Set the last node to NULL and remove it from the array
        H->compact_array[H->size - 1] = NULL;
        arrdel(H->compact_array, H->size - 1);
    }

    H->size--;

    sift_down(H, index);
    sift_up(H, index);

}

void extract_max(MaxHeap *this) {
    delete(this, this->compact_array[0]->key);
}

void insert(MaxHeap* H, int val) {

    Node* new_node = init_node(val);

    // Append to compact array
    arrput(H->compact_array, new_node);
    // Increment Heap size
    H->size++;

    // Insert node at end of array
    int new_node_index = H->size - 1;

    // Link new node to parent node
    if (new_node_index == 0)
        new_node->parent = NULL;
    else
        new_node->parent = H->compact_array[parent_index(new_node_index)];
    
    // Sifting up to ensure Max Heap property is maintained
   sift_up(H, new_node_index);

}

void destroy_heap(MaxHeap *H) {

    if (H->size > 0) {
        for (int i = 0; i < H->size; i++) {
            free(H->compact_array[i]);
        }
    }

    if (H->compact_array != NULL)
        arrfree(H->compact_array);

    free(H);

}

void build_max_heap(int arr[], int arr_size) {
    // leaf nodes from n/2 to n are all leaf nodes,
    // therefore they do not need to be sifted down (source CLRS)
    for (int i = arr_size/2; i >= 0; i--)
        sift_down_array(arr, arr_size, i);

}

void heapsort(int arr[], int arr_size) {

    build_max_heap(arr, arr_size);

    // Last element is not
    for (int i = arr_size-1; i > 0; i--) {
        // Swap current element with root
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Sift down on root node,
        // considering only the sub-array arr[0] to arr[i]
        sift_down_array(arr, i, 0);
    }
}

void print_heap(const MaxHeap* H) {
    for (int i = 0; i < H->size; i++) {
        printf("%d ", H->compact_array[i]->key);
    }
    printf("\n");
}

void print_array(int arr[], int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){

    MaxHeap H = init_heap();
    insert(&H, 5);
    insert(&H, 2);
    insert(&H, 1);
    insert(&H, 6);
    insert(&H, 3);
    insert(&H, 7);

    delete(&H, 2);
    delete(&H, 3);

    int x = get_heap_max(&H);

    extract_max(&H);

    print_heap(&H);

    return 0;

}