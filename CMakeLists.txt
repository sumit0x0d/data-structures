cmake_minimum_required(VERSION 3.22.1)

project(data-structures)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# add_compile_options(-Wall -Wextra -g -Werror)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")

# Collect sources into named variables
file(GLOB ARRAY_SOURCE
     "${CMAKE_SOURCE_DIR}/source/array.c")
file(GLOB AVL_TREE_SOURCE
     "${CMAKE_SOURCE_DIR}/source/avl-tree.c"
     "${CMAKE_SOURCE_DIR}/source/avl-tree/*.c")
file(GLOB BINARY_HEAP_SOURCE
     "${CMAKE_SOURCE_DIR}/source/binary-heap.c")
file(GLOB BLOOM_FILTER_SOURCE
     "${CMAKE_SOURCE_DIR}/source/bloom-filter.c")
file(GLOB CIRCULAR_BUF_SOURCE
     "${CMAKE_SOURCE_DIR}/source/circular-buffer.c")
file(GLOB DOUBLY_LL_SOURCE
     "${CMAKE_SOURCE_DIR}/source/doubly-linked-list.c" 
     "${CMAKE_SOURCE_DIR}/source/doubly-linked-list/*.c")
file(GLOB DYNAMIC_ARRAY_SOURCE
     "${CMAKE_SOURCE_DIR}/source/dynamic-array.c")
file(GLOB HASH_TABLE_SOURCE
     "${CMAKE_SOURCE_DIR}/source/hash-table.c"
     "${CMAKE_SOURCE_DIR}/source/hash-table/*.c")
file(GLOB SINGLY_LL_SOURCE
     "${CMAKE_SOURCE_DIR}/source/singly-linked-list.c"
     "${CMAKE_SOURCE_DIR}/source/singly-linked-list/*.c")
file(GLOB MATRIX_SOURCE
     "${CMAKE_SOURCE_DIR}/source/matrix.c")
file(GLOB RED_BLACK_SOURCE
     "${CMAKE_SOURCE_DIR}/source/red-black-tree.c"
     "${CMAKE_SOURCE_DIR}/source/red-black-tree/*.c")
file(GLOB STACK_SOURCE
     "${CMAKE_SOURCE_DIR}/source/stack.c")
# file(GLOB TRIE_SOURCE
#    "${CMAKE_SOURCE_DIR}/source/trie.c")
file(GLOB XOR_LL_SOURCE
     "${CMAKE_SOURCE_DIR}/source/xor-linked-list.c"
     "${CMAKE_SOURCE_DIR}/source/xor-linked-list/*.c")

add_library(array SHARED ${ARRAY_SOURCE})
add_library(avl-tree SHARED ${AVL_TREE_SOURCE})
add_library(binary-heap SHARED ${BINARY_HEAP_SOURCE})
add_library(bloom-filter SHARED ${BLOOM_FILTER_SOURCE})
add_library(circular-buffer SHARED ${CIRCULAR_BUF_SOURCE})
add_library(doubly-linked-list SHARED ${DOUBLY_LL_SOURCE})
add_library(dynamic-array SHARED ${DYNAMIC_ARRAY_SOURCE})
add_library(hash-table SHARED ${HASH_TABLE_SOURCE})
add_library(singly-linked-list SHARED ${SINGLY_LL_SOURCE})
add_library(matrix SHARED ${MATRIX_SOURCE})
add_library(red-black-tree SHARED ${RED_BLACK_SOURCE})
add_library(stack SHARED ${STACK_SOURCE})
# add_library(trie SHARED ${TRIE_SOURCE})
add_library(xor-linked-list SHARED ${XOR_LL_SOURCE})

target_include_directories(array PUBLIC include)
target_include_directories(avl-tree PUBLIC include)
target_include_directories(binary-heap PUBLIC include)
target_include_directories(bloom-filter PUBLIC include)
target_include_directories(circular-buffer PUBLIC include)
target_include_directories(doubly-linked-list PUBLIC include)
target_include_directories(dynamic-array PUBLIC include)
target_include_directories(singly-linked-list PUBLIC include)
target_include_directories(hash-table PUBLIC include)
target_include_directories(matrix PUBLIC include)
target_include_directories(red-black-tree PUBLIC include)
target_include_directories(stack PUBLIC include)
# target_include_directories(trie PUBLIC include)
target_include_directories(xor-linked-list PUBLIC include)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    enable_testing()
    add_executable(data-structures-test test/data-structures-test.c)
    add_test(NAME data-structures-test COMMAND data-structures-test)
#     set_target_properties(array-test PROPERTIES OUTPUT_NAME array)
    target_link_libraries(data-structures-test PUBLIC array)
endif()
