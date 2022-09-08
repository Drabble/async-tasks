#ifndef ASYNCTASKS_HELLOTASK_H
#define ASYNCTASKS_HELLOTASK_H

#include <iostream>
#include "async_task.h"

/// Asynchronous task that will display "World" to the console.
class HelloTask : public async_task::AsyncTask {
public:
    explicit HelloTask(std::string name);

protected:
    void iterate() override;
};

#endif //ASYNCTASKS_HELLOTASK_H
