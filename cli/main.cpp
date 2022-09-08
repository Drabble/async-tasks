#include <stdlib.h>
#include <memory>
#include "async_task.h"
#include "tasks/count_task.h"
#include "tasks/hello_task.h"
#include "tasks/random_task.h"
#include "cli.h"

std::unique_ptr<async_task::AsyncTask> countTaskFactory() {
    return std::make_unique<CountTask>("Count Task", 100);
};

std::unique_ptr<async_task::AsyncTask> helloTaskFactory() {
    return std::make_unique<HelloTask>("Hello Task");
};

std::unique_ptr<async_task::AsyncTask> randomTaskFactory() {
    return std::make_unique<RandomTask>("Random Task");
};

int main(int argc, char **argv) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        Cli::showUsage();
        return 0;
    } else {
        Cli cli;

        cli.addTaskType("count", "Count to 100'000'000",countTaskFactory);
        cli.addTaskType("hello", "Print \"World\" to stdout", helloTaskFactory);
        cli.addTaskType("random", "Append a random integer to the log.txt file", randomTaskFactory);

        cli.start();
    }
    return EXIT_SUCCESS;
}