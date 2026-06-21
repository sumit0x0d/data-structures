cmake_minimum_required(VERSION 3.22.1)

project(data-structures)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# Strict C89 compilation flags
add_compile_options(-Wall -Wextra -Werror -pedantic -std=c89)

# =======================================================================================
# MODULE: Array
# =======================================================================================

file(GLOB ARRAY_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/array.c")

add_library(array SHARED ${ARRAY_SOURCE})
target_include_directories(array PUBLIC include)

# =======================================================================================
# MODULE: Dynamic-Array
# =======================================================================================

file(GLOB DYNAMIC_ARRAY_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/dynamic-array.c")

add_library(dynamic-array SHARED ${DYNAMIC_ARRAY_SOURCE})
target_include_directories(dynamic-array PUBLIC include)

# =======================================================================================
# MODULE: AVL-Tree
# =======================================================================================

file(GLOB AVL_TREE_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/avl-tree.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/source/avl-tree/*.c")

add_library(avl-tree SHARED ${AVL_TREE_SOURCE})
target_include_directories(avl-tree PUBLIC include)

# =======================================================================================
# MODULE: Binary-Search-Tree
# =======================================================================================

file(GLOB BINARY_SEARCH_TREE_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/binary-search-tree.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/source/binary-search-tree/*.c")

add_library(binary-search-tree SHARED ${BINARY_SEARCH_TREE_SOURCE})
target_include_directories(binary-search-tree PUBLIC include)

# =======================================================================================
# MODULE: Red-Black-Tree
# =======================================================================================

file(GLOB RED_BLACK_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/red-black-tree.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/source/red-black-tree/*.c")

add_library(red-black-tree SHARED ${RED_BLACK_SOURCE})
target_include_directories(red-black-tree PUBLIC include)

# =======================================================================================
# MODULE: Singly-Linked-List
# =======================================================================================

file(GLOB SINGLY_LL_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/singly-linked-list.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/source/singly-linked-list/*.c")

add_library(singly-linked-list SHARED ${SINGLY_LL_SOURCE})
target_include_directories(singly-linked-list PUBLIC include)

# =======================================================================================
# MODULE: Doubly-Linked-List
# =======================================================================================

file(GLOB DOUBLY_LL_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/doubly-linked-list.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/source/doubly-linked-list/*.c")

add_library(doubly-linked-list SHARED ${DOUBLY_LL_SOURCE})
target_include_directories(doubly-linked-list PUBLIC include)

# =======================================================================================
# MODULE: XOR-Linked-List
# =======================================================================================

file(GLOB XOR_LL_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/xor-linked-list.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/source/xor-linked-list/*.c")

add_library(xor-linked-list SHARED ${XOR_LL_SOURCE})
target_include_directories(xor-linked-list PUBLIC include)

# =======================================================================================
# MODULE: Stack
# =======================================================================================

file(GLOB STACK_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/stack.c")

add_library(stack SHARED ${STACK_SOURCE})
target_include_directories(stack PUBLIC include)

# ======================================================================================
# MODULE: Circular-Buffer
# ======================================================================================

file(GLOB CIRCULAR_BUF_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/circular-buffer.c")

add_library(circular-buffer SHARED ${CIRCULAR_BUF_SOURCE})
target_include_directories(circular-buffer PUBLIC include)

# ======================================================================================
# MODULE: Hash-Table
# ======================================================================================

file(GLOB HASH_TABLE_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/hash-table.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/source/hash-table/*.c")

add_library(hash-table SHARED ${HASH_TABLE_SOURCE})
target_include_directories(hash-table PUBLIC include)

# ======================================================================================
# MODULE: Binary-Heap
# ======================================================================================

file(GLOB BINARY_HEAP_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/binary-heap.c")

add_library(binary-heap SHARED ${BINARY_HEAP_SOURCE})
target_include_directories(binary-heap PUBLIC include)

# ======================================================================================
# MODULE: Bloom-Filter
# ======================================================================================

file(GLOB BLOOM_FILTER_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/bloom-filter.c")

add_library(bloom-filter SHARED ${BLOOM_FILTER_SOURCE})
target_include_directories(bloom-filter PUBLIC include)

# ======================================================================================
# MODULE: Matrix
# ======================================================================================

file(GLOB MATRIX_SOURCE
   "${CMAKE_CURRENT_SOURCE_DIR}/source/matrix.c")

add_library(matrix SHARED ${MATRIX_SOURCE})
target_include_directories(matrix PUBLIC include)

# ======================================================================================
# TESTING
# ======================================================================================

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
   enable_testing()

   # ===================================================================================
   # Array Test
   # ===================================================================================
   add_executable(array-test test/array-test.c)
   add_test(NAME array-test COMMAND array-test)
   target_link_libraries(array-test PUBLIC array)

   # ===================================================================================
   # Dynamic-Array Test
   # ===================================================================================
   add_executable(dynamic-array-test test/dynamic-array-test.c)
   add_test(NAME dynamic-array-test COMMAND dynamic-array-test)
   target_link_libraries(dynamic-array-test PUBLIC dynamic-array)

   # ===================================================================================
   # AVL-Tree Test
   # ===================================================================================
   add_executable(avl-tree-test test/avl-tree-test.c)
   add_test(NAME avl-tree-test COMMAND avl-tree-test)
   target_link_libraries(avl-tree-test PUBLIC avl-tree)

   # ===================================================================================
   # Binary-Search-Tree Test
   # ===================================================================================
   add_executable(binary-search-tree-test test/binary-search-tree-test.c)
   add_test(NAME binary-search-tree-test COMMAND binary-search-tree-test)
   target_link_libraries(binary-search-tree-test PUBLIC binary-search-tree)

   # ===================================================================================
   # Red-Black-Tree Test
   # ===================================================================================
   add_executable(red-black-tree-test test/red-black-tree-test.c)
   add_test(NAME red-black-tree-test COMMAND red-black-tree-test)
   target_link_libraries(red-black-tree-test PUBLIC red-black-tree)

   # ===================================================================================
   # Singly-Linked-List Test
   # ===================================================================================
   add_executable(singly-linked-list-test test/singly-linked-list-test.c)
   add_test(NAME singly-linked-list-test COMMAND singly-linked-list-test)
   target_link_libraries(singly-linked-list-test PUBLIC singly-linked-list)

   # ===================================================================================
   # Doubly-Linked-List Test
   # ===================================================================================
   add_executable(doubly-linked-list-test test/doubly-linked-list-test.c)
   add_test(NAME doubly-linked-list-test COMMAND doubly-linked-list-test)
   target_link_libraries(doubly-linked-list-test PUBLIC doubly-linked-list)

   # ===================================================================================
   # XOR-Linked-List Test
   # ===================================================================================
   add_executable(xor-linked-list-test test/xor-linked-list-test.c)
   add_test(NAME xor-linked-list-test COMMAND xor-linked-list-test)
   target_link_libraries(xor-linked-list-test PUBLIC xor-linked-list)

   # ===================================================================================
   # Stack Test
   # ===================================================================================
   add_executable(stack-test test/stack-test.c)
   add_test(NAME stack-test COMMAND stack-test)
   target_link_libraries(stack-test PUBLIC stack)

   # ===================================================================================
   # Circular-Buffer Test
   # ===================================================================================
   add_executable(circular-buffer-test test/circular-buffer-test.c)
   add_test(NAME circular-buffer-test COMMAND circular-buffer-test)
   target_link_libraries(circular-buffer-test PUBLIC circular-buffer)

   # ===================================================================================
   # Hash-Table Test
   # ===================================================================================
   add_executable(hash-table-test test/hash-table-test.c)
   add_test(NAME hash-table-test COMMAND hash-table-test)
   target_link_libraries(hash-table-test PUBLIC hash-table)

   # ===================================================================================
   # Binary-Heap Test
   # ===================================================================================
   add_executable(binary-heap-test test/binary-heap-test.c)
   add_test(NAME binary-heap-test COMMAND binary-heap-test)
   target_link_libraries(binary-heap-test PUBLIC binary-heap)

   # ===================================================================================
   # Bloom-Filter Test
   # ===================================================================================
   add_executable(bloom-filter-test test/bloom-filter-test.c)
   add_test(NAME bloom-filter-test COMMAND bloom-filter-test)
   target_link_libraries(bloom-filter-test PUBLIC bloom-filter)

   # ===================================================================================
   # Matrix Test
   # ===================================================================================
   add_executable(matrix-test test/matrix-test.c)
   add_test(NAME matrix-test COMMAND matrix-test)
   target_link_libraries(matrix-test PUBLIC matrix)
endif()
