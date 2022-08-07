
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("c20")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(PDM_CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pdm-crypt-module)

#add_library( wrapper
#             SHARED
#        ${PDM_CURRENT_DIR}/src/cc20_wrapper.cpp
#        ${PDM_CURRENT_DIR}/src/empp.cpp
#        )
#target_include_directories(
#        wrapper
#        PUBLIC
#        ${PDM_CURRENT_DIR}/src/include
#        ${PDM_CURRENT_DIR}/src/lib
#        ${PDM_CURRENT_DIR}/src/lib/cpp-mmf
#        ${PDM_CURRENT_DIR}/src/lib/poly1305-donna-master
#        ${PDM_CURRENT_DIR}/src/lib/ecc
#        ${PDM_CURRENT_DIR}/src/lib/scrypt/include
#        ${PDM_CURRENT_DIR}/src/lib/scrypt
#)
#target_compile_options(
#        wrapper PUBLIC
#        -g -lpthread -marm
#)
#target_compile_definitions(wrapper PUBLIC ANDROID LINUX )

add_library(
        emppl
        SHARED
#        main.cpp
        ${PDM_CURRENT_DIR}/src/cc20_wrapper.cpp
        ${PDM_CURRENT_DIR}/src/empp.cpp
        ${PDM_CURRENT_DIR}/src/lib/cc20_file.cpp
        ${PDM_CURRENT_DIR}/src/lib/sha3.cpp
        ${PDM_CURRENT_DIR}/src/lib/cpp-mmf/memory_mapped_file.cpp
        ${PDM_CURRENT_DIR}/src/lib/poly1305-donna-master/poly1305-donna.cpp
        ${PDM_CURRENT_DIR}/src/lib/ecc/ecdh_curve25519.c
        ${PDM_CURRENT_DIR}/src/lib/ecc/curve25519.c
        ${PDM_CURRENT_DIR}/src/lib/ecc/fe25519.c
        ${PDM_CURRENT_DIR}/src/lib/ecc/bigint.c
        ${PDM_CURRENT_DIR}/src/lib/scrypt/src/hmac.c
        ${PDM_CURRENT_DIR}/src/lib/scrypt/src/pbkdf2.c
        ${PDM_CURRENT_DIR}/src/lib/scrypt/src/salsa20.c
        ${PDM_CURRENT_DIR}/src/lib/scrypt/src/scrypt.c
        ${PDM_CURRENT_DIR}/src/lib/scrypt/src/sha256.c
        ${PDM_CURRENT_DIR}/src/lib/ec.cpp
        ${PDM_CURRENT_DIR}/src/cc20core/cc20_multi.cpp
        )
target_include_directories(
        emppl
        PUBLIC
        ${PDM_CURRENT_DIR}/src/include
        ${PDM_CURRENT_DIR}/src/lib
        ${PDM_CURRENT_DIR}/src/lib/cpp-mmf
        ${PDM_CURRENT_DIR}/src/lib/poly1305-donna-master
        ${PDM_CURRENT_DIR}/src/lib/ecc
        ${PDM_CURRENT_DIR}/src/lib/scrypt/include
        ${PDM_CURRENT_DIR}/src/lib/scrypt
)
target_compile_options(
        emppl PUBLIC
        -g -lpthread -O3
)
target_compile_definitions(emppl PUBLIC ANDROID LINUX )

add_library(
        c20
        SHARED
        ${PDM_CURRENT_DIR}/../java/com/pdmnotes/com_pdmnotes_PdmCrypt.cpp
        )
target_include_directories(
        c20
        PUBLIC
        ${PDM_CURRENT_DIR}/../java/com/pdmnotes/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/cpp-mmf
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/poly1305-donna-master
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/ecc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/scrypt/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/scrypt
)
target_compile_options(
        c20 PUBLIC
        -g -lpthread
)

find_library(
              log-lib
              log
)

target_link_libraries(
        c20
#        wrapper
        emppl
        ${log-lib}
)
