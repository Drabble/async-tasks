#include "test_task.h"

TestTask::TestTask(std::string name, int iterations, int delay_between_iterations) :
        async_task::AsyncTask(std::move(name)),
        iterations(iterations),
        count(0),
        delay_between_iterations(delay_between_iterations) {}

void TestTask::iterate() {
    count++;
    setProgress((int) ((float) count / (float) iterations * 100.f));
    if (count >= iterations) {
        complete();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_between_iterations));
}