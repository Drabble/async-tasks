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
    ///
    /// An asynchronous task starts in the **RUNNING** state. It can be altered with the following commands:
    /// - `resume()` : Resumes the task if it has been paused
    /// - `pause()` : Pauses the task
    /// - `stop()` : Stops the task
    /// - `wait()` : Wait (blockingly) for the task to end
    ///
    /// In order to create an asynchronous task, `AsyncTask` can be inherited in a concrete class.
    /// Only one method called `iterate()` needs to be implemented. `iterate()` contains the logic of the task and it
    /// should run in small iterations, such that, in between each iteration the asynchronous task is able to react to
    /// commands (pause, stop, resume...). The `iterate()` method should update the progress variable using
    /// `setProgress()`, the value of progress represents a percentage. When the task is done, `iterate()` should call
    /// `complete()` to terminate the task successfully.
    class AsyncTask {
    public:
        explicit AsyncTask(std::string name);
        ~AsyncTask();

        void resume();
        void pause();
        void stop();
        void wait();

        [[nodiscard]] int getProgress() const;
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] AsyncTaskState getStatus() const;

    protected:
        virtual void iterate() {};
        void complete();
        void setProgress(int p);

    private:
        static void threadFunc(void *pParam); // the main function that is passed to the thread
        std::unique_ptr<std::thread> thread;
        std::condition_variable condition_variable; // used for pause
        std::mutex mutex; // required to wait on the condition variable
        AsyncTaskState status;
        AsyncTaskCommand command;
        std::string name;
        int progress;
    };
}

#endif //ASYNCTASKS_ASYNC_TASK_H
