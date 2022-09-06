#ifndef ASYNCTASKS_ASYNC_TASK_H
#define ASYNCTASKS_ASYNC_TASK_H

#include <thread>
#include <cstdio>
#include <iostream>
#include <memory>

/// Asynchronous task management library
namespace async_task {

    /// Commands to alter the state of the asynchronous task
    enum AsyncTaskCommand {PLAY, PAUSE, STOP, COMPLETE};

    /// States of the asynchronous task
    enum AsyncTaskState {RUNNING, PAUSED, STOPPED, COMPLETED};
    static const char *AsyncTaskStatusString[] =
            { "Running", "Paused", "Stopped", "Completed" };

    /// `AsyncTask` is an abstract class for creating finite asynchronous tasks.
    /// An asynchronous task starts in the **RUNNING** state. It can be altered with the following commands:
    /// - `resume()` : Resumes the task if it has been paused
    /// - `pause()` : Pauses the task
    /// - `stop()` : Stops the task
    /// - `wait()` : Wait (blockingly) for the task to end
    /// In order to create an asynchronous task, extend it with your custom class. You need to implement only
    /// one method called `iterate()`. Iterate must contain the logic of your asynchronous and it will be run
    /// continuously as long as the task is running. The logic of your asynchronous task should be done in small
    /// iterations, such that, in between each iteration, the asynchronous task is able to react to pause/stop commands.
    /// Inside iterate you should update the progress variable using `setProgress()`, the value represented by progress
    /// is up to you but it is recommended to use a percentage. Finally, when the task is done, you should call
    /// `complete()` to terminate the task.
    class AsyncTask {
    public:
        explicit AsyncTask(std::string name);
        ~AsyncTask();

        void resume();
        void pause();
        void stop();
        void wait();

        int getProgress() const;
        std::string getName() const;
        AsyncTaskState getStatus() const;
    protected:
        virtual void iterate() {};
        void complete();
        void setProgress(int progress);
    private:
        static void threadFunc(void *pParam);
        std::unique_ptr<std::thread> thread;
        std::condition_variable condition_variable;
        std::mutex mutex;
        AsyncTaskState status;
        AsyncTaskCommand command;
        std::string name;
        int progress;
    };
}

#endif //ASYNCTASKS_ASYNC_TASK_H
