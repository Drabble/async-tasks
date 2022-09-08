#include "cli.h"

Cli::Cli() : last_task_id(0) {};

Cli::~Cli() = default;

void Cli::showUsage() {
    std::cout << "Usage:" << std::endl <<
              "\tcli\t\t\t\t\tStart the command line interface" << std::endl << std::endl <<
              "Options:" << std::endl <<
              "\t-h, --help\t\t\tShow usage information" << std::endl << std::endl <<
              "Once the CLI is started, use the following commands to manage tasks:" << std::endl <<
              "\tlist\t\t\t\tShows the list of available task types" << std::endl <<
              "\tstart [task_type]\tStart the task with the given task type or any task if task type is empty"
              << std::endl <<
              "\tpause <task_id>\t\tPause the given task" << std::endl <<
              "\tresume <task_id>\tResume the given task after it has been paused" << std::endl <<
              "\tstop <task_id>\t\tStop the given task forever" << std::endl <<
              "\tstatus [task_id]\tShow the status of the given task or every task if task id is empty" << std::endl <<
              "\thelp \t\t\t\tShow usage information" << std::endl <<
              "\tquit\t\t\t\tStop the cli" << std::endl << std::endl;
}

void Cli::start() {
    while (true) {
        // Read line
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);

        // Extract the command and argument
        std::string command;
        ss >> command;
        std::string arg;
        ss >> arg;

        if (command == "start") {
            startTask(arg);
        } else if (command == "pause") {
            pauseTask(arg);
        } else if (command == "resume") {
            resumeTask(arg);
        } else if (command == "stop") {
            stopTask(arg);
        } else if (command == "status") {
            statusTask(arg);
        } else if (command == "list") {
            listTaskTypes();
        } else if (command == "help") {
            showUsage();
        } else if (command == "quit") {
            break;
        } else {
            std::cerr << "Unknown command " << command << "..." << std::endl;
        }
    }
}

void Cli::startTask(const std::string &arg) {
    // If no task type is given, we start the first task in the factory list
    if (arg.empty()) {
        if (task_factories.empty()) {
            std::cerr << "No task available..." << std::endl;
            return;
        }
        std::cout << "Starting task " << task_factories.begin()->first << "..." << std::endl;
        tasks[++last_task_id] = task_factories.begin()->second();
        std::cout << "Task " << last_task_id << " started" << std::endl;
    } else {
        if (task_factories.find(arg) == task_factories.end()) {
            std::cerr << "No task with type " << arg << "..." << std::endl;
            return;
        }
        std::cout << "Starting task " << arg << "..." << std::endl;
        tasks[++last_task_id] = task_factories[arg]();
        std::cout << "Task " << last_task_id << " started" << std::endl;
    }
}

void Cli::resumeTask(const std::string &arg) {
    unsigned int task_id;
    try {
        task_id = std::stoi(arg);
    } catch (...) {
        std::cerr << "Invalid task id given..." << std::endl;
        return;
    }
    if (tasks.find(task_id) == tasks.end()) {
        std::cerr << "No task with id " << task_id << "..." << std::endl;
        return;
    }
    std::cout << "Resuming task " << task_id << "..." << std::endl;
    tasks[task_id]->resume();
    std::cout << "Task " << task_id << " resumed" << std::endl;
}

void Cli::pauseTask(const std::string &arg) {
    unsigned int task_id;
    try {
        task_id = std::stoi(arg);
    } catch (...) {
        std::cerr << "Invalid task id given..." << std::endl;
        return;
    }
    if (tasks.find(task_id) == tasks.end()) {
        std::cerr << "No task with id " << task_id << "..." << std::endl;
        return;
    }
    std::cout << "Pausing task " << task_id << "..." << std::endl;
    tasks[task_id]->pause();
    std::cout << "Task " << task_id << " paused" << std::endl;
}

void Cli::stopTask(const std::string &arg) {
    unsigned int task_id;
    try {
        task_id = std::stoi(arg);
    } catch (...) {
        std::cerr << "Invalid task id given..." << std::endl;
        return;
    }
    if (tasks.find(task_id) == tasks.end()) {
        std::cerr << "No task with id " << task_id << "..." << std::endl;
        return;
    }
    std::cout << "Stopping task " << task_id << "..." << std::endl;
    tasks[task_id]->stop();
    std::cout << "Task " << task_id << " stopped" << std::endl;
}

void Cli::statusTask(const std::string &arg) {
    // If no task id is given, we show the status of every task
    if (arg.empty()) {
        showTaskStatusHeader();
        for (auto &task: tasks) {
            showTaskStatusRow(task.first, task.second);
        }
    } else {
        unsigned int task_id;
        try {
            task_id = std::stoi(arg);
        } catch (...) {
            std::cerr << "Invalid task id given..." << std::endl;
            return;
        }
        if (tasks.find(task_id) == tasks.end()) {
            std::cerr << "No task with id " << task_id << "..." << std::endl;
            return;
        }
        showTaskStatusHeader();
        showTaskStatusRow(task_id, tasks[task_id]);
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

void
Cli::addTaskType(const std::string &task_type, const std::string &description, const AsyncTaskFactory &task_factory) {
    task_factories[task_type] = task_factory;
    task_descriptions[task_type] = description;
}

void Cli::listTaskTypes() {
    std::cout << std::setfill('*') << std::setw(75) << "*" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    std::cout << std::setw(15) << "task type" << std::setw(60) << "description" << std::endl;
    std::cout << std::setfill('*') << std::setw(75) << "*" << std::endl;
    std::cout << std::setfill(' ') << std::fixed;
    for (auto &task_type: task_factories) {
        std::cout << std::setprecision(0) <<
                  std::setw(15) <<
                  task_type.first <<
                  std::setprecision(4) <<
                  std::setw(60) <<
                  task_descriptions[task_type.first] <<
                  std::endl;
    }
}
