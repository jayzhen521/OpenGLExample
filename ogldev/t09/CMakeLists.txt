get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/../bin)

target_include_directories(gl3w PRIVATE ${GL3W_INCLUDE_DIR})

if(MSVC)
    file(GLOB INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*h)
    file (GLOB_RECURSE SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.*")
    add_executable(${ProjectId} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${INCLUDE_FILES} ${SHADER_FILES})
    source_group("Shaders" FILES ${SHADER_FILES})
else()
    add_executable(${ProjectId} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
endif()

target_include_directories(${ProjectId} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GL3W_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/common/include)

target_link_libraries(${ProjectId}
    PRIVATE
    debug ${GLFW_LIBRARY_DEBUG}
    optimized ${GLFW_LIBRARY_RELEASE}
    gl3w
    common)

if(MSVC)
    set_property(TARGET ${ProjectId} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()