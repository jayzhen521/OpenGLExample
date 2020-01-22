add_library(
    glfwsupport
    STATIC
    include/GlfwSupport.h
    include/ICallbacks.h
    src/GlfwSupport.cpp
)

target_include_directories(
    glfwsupport
    PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/util/include
)

target_link_libraries(
    glfwsupport
    PRIVATE
    debug ${GLFW_LIBRARY_DEBUG}
    optimized ${GLFW_LIBRARY_RELEASE}
    util
)