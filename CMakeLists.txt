cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(OpenGLExample LANGUAGES C CXX)

# find_include and find_library
if(NOT DEFINED ENV{GL3W_PATH})
    message("env variable GL3W_PATH is needed.")
endif()
if(NOT DEFINED ENV{GLFW_PATH})
    message("env variable GLFW_PATH is needed.")
endif()

find_path(GL3W_INCLUDE_DIR
    GL/gl3w.h
    HINTS
        $ENV{GL3W_PATH}/include/gl3w
)

find_path(GLFW_INCLUDE_DIR
    GLFW/glfw3.h
    HINTS
        $ENV{GLFW_PATH}/include
)

find_library(GLFW_LIBRARY_DEBUG
    glfw3dll
    HINTS
        $ENV{GLFW_PATH}/lib/Debug
)

find_library(GLFW_LIBRARY_RELEASE
    glfw3dll
    HINTS
        $ENV{GLFW_PATH}/lib/Release
)
# end find_include and find_library

#macro
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()
#end macro

add_subdirectory(gl3w)

add_subdirectory(ogldev)
