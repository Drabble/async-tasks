#include <gtest/gtest.h>
#include "tasks/wait_task.h"

TEST(AsyncTask, SimpleExecution) {
    wait_task wait_task("Test", 3);
    ASSERT_EQ(wait_task.getProgress(), 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for the task to start
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 33);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 66);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 100);
    ASSERT_EQ(wait_task.getStatus(), async_task::AsyncTaskState::COMPLETED);
}

TEST(AsyncTask, PauseExecution) {
    wait_task wait_task("Test", 3);
    ASSERT_EQ(wait_task.getProgress(), 0);
    std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for the task to start
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 33);
    wait_task.pause();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 66);
    ASSERT_EQ(wait_task.getStatus(), async_task::AsyncTaskState::PAUSED);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 66);
    wait_task.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for the task to start
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 100);
    ASSERT_EQ(wait_task.getStatus(), async_task::AsyncTaskState::COMPLETED);
}

TEST(AsyncTask, StopExecution) {
    wait_task wait_task("Test", 3);
    ASSERT_EQ(wait_task.getProgress(), 0);
    std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for the task to start
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 33);
    wait_task.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 66);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ASSERT_EQ(wait_task.getProgress(), 66);
    ASSERT_EQ(wait_task.getStatus(), async_task::AsyncTaskState::STOPPED);
}

TEST(AsyncTask, StartAfterStopExecution) {
    wait_task wait_task("Test", 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for the task to start
    wait_task.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Wait for the task to stop
    ASSERT_EQ(wait_task.getStatus(), async_task::AsyncTaskState::STOPPED);
    wait_task.resume();
    std::this_thread::yield();
    ASSERT_EQ(wait_task.getStatus(), async_task::AsyncTaskState::STOPPED);
}