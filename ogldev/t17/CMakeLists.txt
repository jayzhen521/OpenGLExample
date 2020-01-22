get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/../bin)

if(MSVC)
    file(GLOB INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*h)
    file(GLOB_RECURSE SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.*")
    file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp)
    add_executable(${ProjectId} ${SRC_FILES} ${INCLUDE_FILES} ${SHADER_FILES})
    source_group("Shaders" FILES ${SHADER_FILES})
else()
    add_executable(${ProjectId} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
endif()

target_include_directories(${ProjectId} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/glfwsupport/include
    ${CMAKE_SOURCE_DIR}/util/include
    ${GLFW_INCLUDE_DIR}
    ${GL3W_INCLUDE_DIR}
    $ENV{GLM_PATH})

target_link_libraries(${ProjectId}
    PRIVATE
    common
    glfwsupport
    util)

if(MSVC)
    set_property(TARGET ${ProjectId} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()