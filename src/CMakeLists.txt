set (CMAKE_INCLUDE_CURRENT_DIR ON) 

file(GLOB SOURCE_FILES
    "*.cpp"
)

file(GLOB INCLUDE_FILES
    "*.h"
)

add_library (JarJar 
  ${SOURCE_FILES}
  ${INCLUDE_FILES}
)

install (TARGETS JarJar DESTINATION bin)
install (FILES ${INCLUDE_FILES} DESTINATION include)
