add_executable(cli main.cpp cli.cpp tasks/count_task.cpp tasks/hello_task.cpp)
target_link_libraries(cli lib)