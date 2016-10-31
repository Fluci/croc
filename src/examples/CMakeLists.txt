# Bring the headers, relatively to build directory
include_directories(../../src/lib)

# Bring source files
file(GLOB SRC_FILES *.cpp)

# define executable
add_executable(RandomRealDemo ${SRC_FILES})

# link library
target_link_libraries(RandomRealDemo CrocLib)

