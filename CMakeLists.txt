cmake_minimum_required(VERSION 3.22.1)
project( cryptography )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm")

include_directories( include ${catkin_INCLUDE_DIRS} )

file( GLOB_RECURSE cryptography_C_HEADERS include/*.h )
file( GLOB_RECURSE cryptography_C_SOURCES src/*.c )
file( GLOB_RECURSE cryptography_C_EXAMPLE examples/*.c )

add_library(
    cryptography SHARED
    src/scytale.c
#    src/polybius.c
#    src/sha.c
#    src/sha-1.c
#    src/aes.c
#    src/vigenere.c
)

# unit-test
add_executable( scy_test examples/scy_test.c )
target_link_libraries( scy_test cryptography )
add_dependencies( scy_test cryptography )




# mains 
add_executable( scytale examples/scy_main.c )
target_link_libraries( scytale cryptography )
add_dependencies( scytale cryptography )

# Test Polybius 
#add_executable( test_polybius examples/test_polybius.c)
#target_link_libraries( test_polybius cryptographylib)
#add_dependencies( test_polybius cryptographylib)

# Test SHA-1
#add_executable( test_sha_1 examples/test_sha_1.c )
#target_link_libraries( test_sha_1 cryptographylib )
#add_dependencies( test_sha_1 cryptographylib)








#add_executable( aes_nist_appendixA examples/aes_nist_appendixA.c)
#target_link_libraries( aes_nist_appendixA ccrypt)
#add_dependencies( aes_nist_appendixA ccrypt)

#add_executable( aes_nist_appendixB examples/aes_nist_appendixB.c)
#target_link_libraries( aes_nist_appendixB ccrypt)
#add_dependencies( aes_nist_appendixB ccrypt)

#add_executable( aes_nist_appendixC examples/aes_nist_appendixC.c)
#target_link_libraries(aes_nist_appendixC ccrypt)
#add_dependencies( aes_nist_appendixC ccrypt)

#add_executable( vigenere_main examples/vigenere_main.c)
#target_link_libraries( vigenere_main ccrypt)
#add_dependencies( vigenere_main ccrypt)
