#ifndef ASYNCTASKS_RANDOM_TASK_H
#define ASYNCTASKS_RANDOM_TASK_H

#include <fstream>
#include <cstdlib>
#include "async_task.h"

/// Asynchronous task that will append a random number and a newline to the file log.txt.
class RandomTask : public async_task::AsyncTask {
public:
    explicit RandomTask(std::string name);

    void iterate() override;
};

#endif //ASYNCTASKS_RANDOM_TASK_H
