add_library(
    util
    STATIC
    include/Util.h
    include/Types.h
    include/Keys.h
    src/Util.cpp
)

target_include_directories(
    util
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)