cmake_minimum_required(VERSION 3.22)
project(
    asyncTasks
    VERSION 0.1
    DESCRIPTION "Asynchronous task management"
)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add subdirectories
add_subdirectory(lib)
add_subdirectory(cli)
add_subdirectory(tests)

