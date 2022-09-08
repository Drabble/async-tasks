#ifndef ASYNCTASK_CLI_H
#define ASYNCTASK_CLI_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>
#include "async_task.h"

typedef std::unique_ptr<async_task::AsyncTask> (*AsyncTaskFactory)();

/// Command line interface to instantiate and manage asynchronous tasks.
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
    void startTask(const std::string& arg);
    void resumeTask(const std::string& arg);
    void pauseTask(const std::string& arg);
    void stopTask(const std::string& arg);
    void statusTask(const std::string& arg);

    std::map<std::string, AsyncTaskFactory> task_factories;
    std::map<std::string, std::string> task_descriptions;
    std::map<unsigned int, std::unique_ptr<async_task::AsyncTask> > tasks;
    unsigned int last_task_id;
};

#endif //ASYNCTASK_CLI_H
