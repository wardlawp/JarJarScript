cmake_minimum_required (VERSION 2.8)
project (JarJarScript)

#version number
set (JarJarScript_VERSION_MAJOR 0)
set (JarJarScript_VERSION_MINOR 1)

###############################################################################
## Interpreter
###############################################################################
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory (${SRC_DIR})
include_directories(${SRC_DIR})

add_executable (JarJarScript main.cpp)
target_link_libraries (JarJarScript JarJar)

install (TARGETS JarJarScript DESTINATION bin)


###############################################################################
## Testing
###############################################################################
set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)

file(GLOB TEST_SOURCES  
    "${TEST_DIR}/*.cpp"
)

include_directories(${TEST_DIR})
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${TEST_SOURCES})

add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests JarJar Catch)
