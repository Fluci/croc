enable_testing()

find_package(Boost 1.46 REQUIRED COMPONENTS unit_test_framework)

# Bring source/test files: 
file(GLOB TEST_FILES *.t.cc)
file(GLOB SRC_FILES *.cpp)

add_library(CrocLib ${SRC_FILES})

add_executable(CrocTest ${TEST_FILES})
