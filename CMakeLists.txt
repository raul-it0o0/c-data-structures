cmake_minimum_required(VERSION 3.27)
project(C_Data_Structures LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(Heap src/heap.c)
add_executable(BST src/binary_search_tree.c)
add_executable(Single_Linked_List src/single_linked_list.c)

target_include_directories(Heap PUBLIC include)
target_include_directories(BST PUBLIC include)
target_include_directories(Single_Linked_List PUBLIC include)
