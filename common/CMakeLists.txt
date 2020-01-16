add_library(common
    STATIC
    include/LoadShaders.h
    src/LoadShaders.cpp
)

target_include_directories(
    common
    PRIVATE
    ${GL3W_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(common PROPERTIES LINKER_LANGUAGE C)