#ifndef ASYNCTASKS_WaitTask_H
#define ASYNCTASKS_WaitTask_H

#include <iostream>
#include <thread>
#include "async_task.h"

/// Asynchronous task that will run x iterations before completing.
/// The task will wait *delay_between_iterations* milliseconds between each iteration.
class TestTask : public async_task::AsyncTask {
public:
    TestTask(std::string name, int iterations, int delay_between_iterations);

    void iterate() override;

private:
    int iterations;
    int count;
    int delay_between_iterations;
};


#endif //ASYNCTASKS_WaitTask_H
