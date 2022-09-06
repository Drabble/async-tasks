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
#include "tasks/count_task.h"
#include "tasks/hello_task.h"

typedef async_task::AsyncTask *(*AsyncTaskFactory)();

/// Command line interface to instantiate hard coded asynchronous tasks.
/// You can manage tasks using commands such as start pause stop resume...
class Cli {
public:
    Cli();
    ~Cli();

    static void showUsage();
    void start();
private:
    static void showTaskStatusHeader();
    static void showTaskStatusRow(const std::pair<const unsigned int, async_task::AsyncTask*>& task);

    void startTask();
    void startTask(const std::string& taskType);
    void resumeTask(unsigned int taskId);
    void pauseTask(unsigned int taskId);
    void stopTask(unsigned int taskId);
    void statusTask(unsigned int taskId);
    void statusTask();

    std::map<std::string, AsyncTaskFactory> task_factories;
    std::map<unsigned int, async_task::AsyncTask*> tasks;
    unsigned int last_task_id;
};

#endif //ASYNCTASK_CLI_H
