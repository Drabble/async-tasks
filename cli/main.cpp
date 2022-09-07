#include <stdlib.h>
#include <memory>
#include "async_task.h"
#include "tasks/count_task.h"
#include "tasks/hello_task.h"
#include "cli.h"

std::unique_ptr<async_task::AsyncTask> countTaskFactory() {
    return std::make_unique<CountTask>("Count Task", 100000000);
};

std::unique_ptr<async_task::AsyncTask> helloTaskFactory() {
    return std::make_unique<HelloTask>("Hello Task");
};

int main(int argc, char **argv) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        Cli::showUsage();
        return 0;
    } else {
        Cli cli;

        cli.addTaskType("count", countTaskFactory);
        cli.addTaskType("hello", helloTaskFactory);

        cli.start();
    }
    return EXIT_SUCCESS;
}