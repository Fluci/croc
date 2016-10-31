enable_testing()

find_package(Boost 1.61 REQUIRED COMPONENTS unit_test_framework)

# Bring source files: 
# first find test files, then source files and then remove test from source files
file(GLOB TEST_FILES *.t.cpp)
file(GLOB SRC_FILES *.cpp)
list(REMOVE_ITEM SRC_FILES TEST_FILES)

add_library(CrocLib ${SRC_FILES})

add_executable(CrocTest ${TEST_FILES})

