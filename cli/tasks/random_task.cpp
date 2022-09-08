#include "random_task.h"

RandomTask::RandomTask(std::string name) : async_task::AsyncTask(std::move(name)) { }

void RandomTask::iterate() {
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app); // append instead of overwrite
    outfile << rand() << std::endl;
    setProgress(100);
    complete();
}