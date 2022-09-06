#include "cli.h"

std::unique_ptr<async_task::AsyncTask> countTaskFactory() { return std::make_unique<CountTask>("Count Task", 100000000); };
std::unique_ptr<async_task::AsyncTask> helloTaskFactory() { return std::make_unique<HelloTask>("Hello Task"); };

Cli::Cli() : last_task_id(0) {
    task_factories["count"] = countTaskFactory;
    task_factories["hello"] = helloTaskFactory;
};

Cli::~Cli() = default;

void Cli::showUsage() {
    std::cout << "Usage:" << std::endl <<
        "\tcli" << std::endl << std::endl <<
        "Options:" << std::endl <<
        "\t-h, --help\toutput usage information" << std::endl << std::endl <<
        "How to use:" << std::endl <<
        "There are four types of asynchronous tasks available." << std::endl <<
        "\tcount\tCounts to 100'000'000 and stops" << std::endl <<
        "\tread\tPause the task, it can be resumed" << std::endl <<
        "\thello\tPrints World to stdout" << std::endl <<
        "Use the following commands to use tasks." << std::endl <<
        "\tstart [task_type_id]\tStart" << std::endl <<
        "\tpause <task_id>\tPause the task, it can be resumed" << std::endl <<
        "\tresume <task_id>\tResume the task after has been paused" << std::endl <<
        "\tstop <task_id>\tStop the task forever" << std::endl <<
        "\tstatus [task_id]\tShow the status of the given task or every task if no id given" << std::endl <<
        "\tquit\t\tStop the cli" << std::endl << std::endl;
}

void Cli::start() {
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);

        std::string command;
        ss >> command;

        if (command == "start") {
            std::string task_type;
            ss >> task_type;
            if (task_type.empty()) {
                startTask();
            } else {
                startTask(task_type);
            }
        } else if (command == "pause") {
            unsigned int task_id = 0;
            ss >> task_id;
            pauseTask(task_id);
        } else if (command == "resume") {
            unsigned int task_id = 0;
            ss >> task_id;
            resumeTask(task_id);
        } else if (command == "stop") {
            unsigned int task_id = 0;
            ss >> task_id;
            stopTask(task_id);
        } else if (command == "status") {
            unsigned int task_id = 0;
            ss >> task_id;
            if (!task_id) {
                statusTask();
            } else {
                statusTask(task_id);
            }
        } else if (command == "quit") {
            break;
        } else {
            printf("Unknown command %s...\n", command.c_str());
        }
    }
}

void Cli::startTask() {
    if (task_factories.empty()) {
        printf("No task available...\n");
        return;
    }
    printf("Starting task %s...\n", task_factories.begin()->first.c_str());
    tasks[++last_task_id] = task_factories.begin()->second();
    printf("Task started with id %d...\n", last_task_id);
}

void Cli::startTask(const std::string &taskType) {
    if (task_factories.find(taskType) == task_factories.end()) {
        printf("No task with type %s...\n", taskType.c_str());
        return;
    }
    printf("Starting task %s...\n", taskType.c_str());
    tasks[++last_task_id] = task_factories[taskType]();
    printf("Task started with id %d...\n", last_task_id);
}

void Cli::resumeTask(unsigned int task_id) {
    if (tasks.find(task_id) == tasks.end()) {
        printf("No task with id %d...\n", task_id);
        return;
    }
    printf("Resuming task with id %d...\n", task_id);
    tasks[task_id]->resume();
    printf("Task with id %d resumed ...\n", task_id);
}

void Cli::pauseTask(unsigned int task_id) {
    if (tasks.find(task_id) == tasks.end()) {
        printf("No task with id %d...\n", task_id);
        return;
    }
    printf("Pausing task with id %d...\n", task_id);
    tasks[task_id]->pause();
    printf("Task with id %d paused...\n", task_id);
}

void Cli::stopTask(unsigned int task_id) {
    if (tasks.find(task_id) == tasks.end()) {
        printf("No task with id %d...\n", task_id);
        return;
    }
    printf("Stopping task with id %d...\n", task_id);
    tasks[task_id]->stop();
    printf("Task with id %d stopped...\n", task_id);
}

void Cli::statusTask(unsigned int task_id) {
    if (tasks.find(task_id) == tasks.end()) {
        printf("No task with id %d...\n", task_id);
        return;
    }
    showTaskStatusHeader();
    showTaskStatusRow(task_id, tasks[task_id]);
}

void Cli::statusTask() {
    showTaskStatusHeader();
    for (auto &task: tasks) {
        showTaskStatusRow(task.first, task.second);
    }
}

void Cli::showTaskStatusHeader() {
    int colWidth = 15;
    std::cout << std::setfill('*') << std::setw(4 * colWidth) << "*" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    std::cout << std::setw(colWidth) << "id" << std::setw(colWidth) << "status" << std::setw(colWidth) <<
              "progress" << std::setw(colWidth) << "type" << std::endl;
    std::cout << std::setfill('*') << std::setw(4 * colWidth) << "*" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
}

void Cli::showTaskStatusRow(const unsigned int id, std::unique_ptr<async_task::AsyncTask> &task) {
    int colWidth = 15;
    std::cout << std::setprecision(0) <<
              std::setw(colWidth) <<
              id <<
              std::setprecision(4) <<
              std::setw(colWidth) <<
              async_task::AsyncTaskStatusString[task->getStatus()] <<
              std::setw(colWidth)
              << std::to_string(task->getProgress()) + "%" << std::setw(colWidth) << task->getName()
              << std::endl;
}
