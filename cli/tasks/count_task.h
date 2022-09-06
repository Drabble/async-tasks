#ifndef ASYNCTASKS_COUNT_TASK_H
#define ASYNCTASKS_COUNT_TASK_H

#include <iostream>
#include <thread>
#include "async_task.h"

/// Asynchronous task that will count to the given total value.
/// Each iteration increases the counter and the current progress of the task.
class CountTask : public async_task::AsyncTask {
public:
    CountTask(std::string name, int total) : async_task::AsyncTask(std::move(name)), total(total), count(0) {}

    void iterate() override;

private:
    int total;
    int count;
};

#endif //ASYNCTASKS_COUNT_TASK_H
