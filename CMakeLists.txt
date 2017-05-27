cmake_minimum_required (VERSION 2.8)
project (JarJarScript)

#version number
set (JarJarScript_VERSION_MAJOR 0)
set (JarJarScript_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

###############################################################################
## Interpreter
###############################################################################
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory (${SRC_DIR})
include_directories(${SRC_DIR})

#Add Readline if found
find_path(Readline_ROOT_DIR
    NAMES readline/readline.h
)

if(Readline_ROOT_DIR)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWITH_READLINE") 
  include_directories(${Readline_ROOT_DIR}/readline)
  set(READLINE_LIBS readline)
endif(Readline_ROOT_DIR)

add_executable (JarJarScript main.cpp)
target_link_libraries (JarJarScript JarJar ${READLINE_LIBS})

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
