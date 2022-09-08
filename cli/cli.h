#ifndef ASYNCTASK_CLI_H
#define ASYNCTASK_CLI_H

#include <cstdio>
#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iterator>
#include <map>
#include <iomanip>
#include <memory>
#include "async_task.h"

typedef std::unique_ptr<async_task::AsyncTask> (*AsyncTaskFactory)();

/// Command line interface to instantiate hard coded asynchronous tasks.
/// You can manage tasks using commands such as start pause stop resume...
class Cli {
public:
    Cli();
    ~Cli();

    static void showUsage();
    void start();
    void addTaskType(const std::string &task_type, const std::string &description, const AsyncTaskFactory &task);
private:
    static void showTaskStatusHeader();
    static void showTaskStatusRow(unsigned int id, std::unique_ptr<async_task::AsyncTask>& task);

    void listTaskTypes();
    void startTask();
    void startTask(const std::string& taskType);
    void resumeTask(unsigned int taskId);
    void pauseTask(unsigned int taskId);
    void stopTask(unsigned int taskId);
    void statusTask(unsigned int taskId);
    void statusTasks();

    std::map<std::string, AsyncTaskFactory> task_factories;
    std::map<std::string, std::string> task_descriptions;
    std::map<unsigned int, std::unique_ptr<async_task::AsyncTask> > tasks;
    unsigned int last_task_id;
};

#endif //ASYNCTASK_CLI_H
