#ifndef ASYNCTASKS_WaitTask_H
#define ASYNCTASKS_WaitTask_H

#include <iostream>
#include <thread>
#include "async_task.h"

/// Asynchronous task that will wait a number of seconds equal to the given duration.
class wait_task : public async_task::AsyncTask {
public:
    wait_task(std::string name, int duration) : async_task::AsyncTask(std::move(name)), duration(duration), elapsed_time(0) {}

    void iterate() override;

private:
    int duration; // duration is in seconds
    int elapsed_time;
};


#endif //ASYNCTASKS_WaitTask_H
