
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("main")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
set(PDM_CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pdm-crypt-module)

add_library( # Sets the name of the library.
             main

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             main.cpp
        ${PDM_CURRENT_DIR}/src/cc20_wrapper.cpp

        )

target_include_directories(
        main
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
        main PUBLIC
        -g -lpthread -marm
)

target_compile_definitions(main PUBLIC ANDROID LINUX )

add_library( # Sets the name of the library.
        wrapper

        # Sets the library as a shared library.
        SHARED
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
        wrapper
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
        wrapper PUBLIC
        -g -lpthread -m64
)

target_compile_definitions(wrapper PUBLIC ANDROID LINUX )
#
#add_library( # Sets the name of the library.
#        emp
#
#        # Sets the library as a shared library.
#        SHARED
#        ${PDM_CURRENT_DIR}/src/empp.cpp
#        )
#target_include_directories(
#        emp
#        PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/cpp-mmf
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/poly1305-donna-master
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/ecc
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/scrypt/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/scrypt
#)
#target_compile_options(
#        emp PUBLIC
#        -g -lpthread -m64
#)
#
#target_compile_definitions(emp PUBLIC ANDROID LINUX )
# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       main

                       # Links the target library to the log library
                       # included in the NDK.
#        ${log-lib} wrapper emp)
${log-lib} wrapper )
