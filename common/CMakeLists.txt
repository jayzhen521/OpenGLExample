add_library(common
    STATIC
    include/LoadShaders.h
    include/Pipeline.h
    include/Config.h
    include/Camera.h
    include/Texture.h
    include/Vertex.h
    include/Image.h
    src/LoadShaders.cpp
    src/Pipeline.cpp
    src/Camera.cpp
    src/Texture.cpp
    src/Vertex.cpp
    src/Image.cpp
)

target_include_directories(
    common
    PRIVATE
    ${GL3W_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    $ENV{GLM_PATH}
    ${STB_INCLUDE_DIR}
)

set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)