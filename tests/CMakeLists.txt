# Tests
add_executable(test async_task.cpp tasks/test_task.cpp)
# Link tests executable against gtest & gtest_main & lib
target_link_libraries(test GTest::gtest_main lib)

# GTest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
gtest_discover_tests(test)