add_library(lib async_task.cpp)

# Make the header files available to the project
target_include_directories(
        lib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)