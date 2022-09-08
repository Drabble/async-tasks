#include "cli.h"

Cli::Cli() : last_task_id(0) { };

Cli::~Cli() = default;

void Cli::showUsage() {
    std::cout << "Usage:" << std::endl <<
        "\tcli\t\t\t\t\tStart the command line interface" << std::endl << std::endl <<
        "Options:" << std::endl <<
        "\t-h, --help\t\t\tShow usage information" << std::endl << std::endl <<
        "Once the CLI is started, use the following commands to manage tasks:" << std::endl <<
        "\tlist\t\t\t\tShows the list of available task types" << std::endl <<
        "\tstart [task_type]\tStart the task with the given task type or any task if task type is empty" << std::endl <<
        "\tpause <task_id>\t\tPause the given task" << std::endl <<
        "\tresume <task_id>\tResume the given task after it has been paused" << std::endl <<
        "\tstop <task_id>\t\tStop the given task forever" << std::endl <<
        "\tstatus [task_id]\tShow the status of the given task or every task if task id is empty" << std::endl <<
        "\tquit\t\t\t\tStop the cli" << std::endl << std::endl;
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
                statusTasks();
            } else {
                statusTask(task_id);
            }
        } else if (command == "list") {
            listTaskTypes();
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

void Cli::statusTasks() {
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

void Cli::addTaskType(const std::string &task_type, const std::string &description, const AsyncTaskFactory &task_factory) {
    task_factories[task_type] = task_factory;
    task_descriptions[task_type] = description;
}

void Cli::listTaskTypes() {
    for(auto& task_type : task_factories){
        std::cout << task_type.first << "\t-\t" << task_descriptions[task_type.first] << std::endl;
    }
}
