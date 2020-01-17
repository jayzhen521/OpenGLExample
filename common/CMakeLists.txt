add_library(common
    STATIC
    include/LoadShaders.h
    include/Pipeline.h
    include/Config.h
    src/LoadShaders.cpp
    src/Pipeline.cpp
)

target_include_directories(
    common
    PRIVATE
    ${GL3W_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    $ENV{GLM_PATH}
)

set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)