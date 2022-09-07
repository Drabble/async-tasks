#include "async_task.h"

async_task::AsyncTask::AsyncTask(std::string name) : name(std::move(name)), progress(0),
                                                     status(async_task::AsyncTaskState::RUNNING),
                                                     command(AsyncTaskCommand::PLAY) {
    thread = std::make_unique<std::thread>(threadFunc, this);
}

async_task::AsyncTask::~AsyncTask() {
    stop();
    if (thread->joinable()) {
        thread->join();
    }
    std::cout << "Successfully stopped task" << std::endl;
}

void async_task::AsyncTask::threadFunc(void *pParam) {
    auto *pThis = (AsyncTask *) pParam;

    while (true) {
        // Acquire the mutex for the condition variable
        std::unique_lock<std::mutex> lock(pThis->mutex);

        // Release the mutex and exit the thread
        switch(pThis->command){
            case AsyncTaskCommand::STOP:
                pThis->status = async_task::AsyncTaskState::STOPPED;
                lock.unlock();
                return;
            case AsyncTaskCommand::PAUSE:
                pThis->status = async_task::AsyncTaskState::PAUSED;
                pThis->condition_variable.wait(lock);
                lock.unlock();
                continue;
            case AsyncTaskCommand::PLAY:
                pThis->status = async_task::AsyncTaskState::RUNNING;
                lock.unlock();
                pThis->iterate();
                break;
            case AsyncTaskCommand::COMPLETE:
                pThis->status = async_task::AsyncTaskState::COMPLETED;
                lock.unlock();
                return;
        }

        // Relinquish the CPU
        std::this_thread::yield();
    }
}

void async_task::AsyncTask::stop() {
    command = AsyncTaskCommand::STOP;

    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.notify_one();
    lock.unlock();
}

void async_task::AsyncTask::complete() {
    command = AsyncTaskCommand::COMPLETE;

    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.notify_one();
    lock.unlock();
}

void async_task::AsyncTask::pause() {
    command = AsyncTaskCommand::PAUSE;
}

void async_task::AsyncTask::resume() {
    command = AsyncTaskCommand::PLAY;

    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.notify_one();
    lock.unlock();
}

void async_task::AsyncTask::wait() {
    thread->join();
}

int async_task::AsyncTask::getProgress() const {
    return progress;
}

std::string async_task::AsyncTask::getName() const {
    return name;
}

async_task::AsyncTaskState async_task::AsyncTask::getStatus() const {
    return status;
}

void async_task::AsyncTask::setProgress(int progress) {
    this->progress = progress;
}
