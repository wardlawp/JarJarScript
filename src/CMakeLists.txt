set(SOURCE_FILES
    Tokenizer.cpp
)
set(INCLUDE_FILES
    Tokenizer.h
)

add_library (JarJar 
  ${SOURCE_FILES}
  ${INCLUDE_FILES}
)

install (TARGETS JarJar DESTINATION bin)
install (FILES ${INCLUDE_FILES} DESTINATION include)
