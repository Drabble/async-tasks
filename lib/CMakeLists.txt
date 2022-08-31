add_library(lib library.cpp)

# Make the header files available to the project
target_include_directories(
        lib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)