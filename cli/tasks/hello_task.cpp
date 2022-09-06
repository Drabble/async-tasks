#include "hello_task.h"

void HelloTask::iterate() {
    std::cout << "World" << std::endl;
    setProgress(100);
    complete();
}