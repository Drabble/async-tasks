#include "hello_task.h"

HelloTask::HelloTask(std::string name) : async_task::AsyncTask(std::move(name)) { }

void HelloTask::iterate() {
    std::cout << "World" << std::endl;
    setProgress(100);
    complete();
}