cmake_minimum_required(VERSION 3.12)
project(tree_arithmetic)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(Heap)
add_subdirectory(Huffman_Tree)
add_subdirectory(Union-Find)
add_executable(tree_arithmetic main.cpp)