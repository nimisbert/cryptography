# Project :
cmake_minimum_required(VERSION 3.22.1)
project(cryptography)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
include_directories(include)

# Libraries :
add_library(helpers SHARED
    src/helpers/galois256.c
    src/helpers/bitset.c
)

add_library(des SHARED
    src/ciphers/des/des.c
    src/ciphers/des/box.c
)
target_link_libraries( des PUBLIC helpers )

add_library(aes SHARED 
    src/ciphers/aes/aes.c
    src/ciphers/aes/box.c
)
target_link_libraries( aes PUBLIC helpers )

# Executables :
add_executable(galois256-test tests/galois256-test.c)
target_link_libraries(galois256-test helpers)

add_executable(bitset-test tests/bitset-test.c)
target_link_libraries(bitset-test helpers)

add_executable(des-test tests/des-test.c)
target_link_libraries(des-test des)

add_executable(aes-test tests/aes-test.c)
target_link_libraries(aes-test aes)