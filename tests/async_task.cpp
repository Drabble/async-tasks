#include <gtest/gtest.h>
#include "tasks/test_task.h"

/// Create a task, wait for it to complete and check status.
TEST(AsyncTask, SingleExecution) {
    TestTask task("Test", 100, 0);
    task.wait();
    ASSERT_EQ(task.getProgress(), 100);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::COMPLETED);
}

/// Create 1000 task, wait for them to complete and check status.
TEST(AsyncTask, MultiExecution) {
    TestTask* tasks[1000];
    for(auto & task : tasks){
        task = new TestTask("Test", 100, 0);
    }
    for(auto & task : tasks){
        task->wait();
        ASSERT_EQ(task->getProgress(), 100);
        ASSERT_EQ(task->getStatus(), async_task::AsyncTaskState::COMPLETED);
    }
}

/// Pause a task, resume it and wait for it to complete.
TEST(AsyncTask, PauseThenResumeExecution) {
    for(int i = 0; i < 10000; i++){

    // Start the task with a delay of 100 millisecond between each iteration
    TestTask task("Test", 2, 100);

    // Wait for the task to start
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Pause the task
    task.pause();

    // Wait for the iteration to finish and the task to pause
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::PAUSED);

    // Make sure the task progress stopped
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::PAUSED);

    // Resume and complete task
    task.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ASSERT_EQ(task.getProgress(), 100);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::COMPLETED);
    }
}

/// Pause a task and then stop it.
TEST(AsyncTask, PauseThenStopExecution) {
    // Start the task with a delay of 100 millisecond between each iteration
    TestTask task("Test", 2, 100);

    // Wait for the task to start
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Pause the task
    task.pause();

    // Wait for the iteration to finish and the task to pause
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::PAUSED);

    // Make sure the task progress stopped
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::PAUSED);

    // Resume and complete task
    task.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::STOPPED);
}

/// Stop a task, make sure it can't be resumed or paused
TEST(AsyncTask, StopExecution) {
    // Start the task with a delay of 100 millisecond between each iteration
    TestTask task("Test", 2, 100);

    // Wait for the task to start
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Pause the task
    task.stop();

    // Wait for the iteration to finish and the task to stop
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::STOPPED);

    // Resume should not affect task
    task.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::STOPPED);

    // Pause should not affect task
    task.pause();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_EQ(task.getProgress(), 50);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::STOPPED);
}

/// Complete a task and make sure it can't change state
TEST(AsyncTask, CompleteExecution) {
    TestTask task("Test", 100, 0);
    task.wait();
    ASSERT_EQ(task.getProgress(), 100);
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::COMPLETED);

    // Pause should not affect task
    task.pause();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::COMPLETED);

    // Stop should not affect task
    task.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::COMPLETED);

    // Resume should not affect task
    task.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_EQ(task.getStatus(), async_task::AsyncTaskState::COMPLETED);
}