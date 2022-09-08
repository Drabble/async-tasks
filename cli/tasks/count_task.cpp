#include "count_task.h"


CountTask::CountTask(std::string name, int total) : async_task::AsyncTask(std::move(name)), total(total), count(0) { }

void CountTask::iterate() {
    count++;
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app); // append instead of overwrite
    outfile << count;
    setProgress((int) ((float) count / (float) total * 100.f));
    if (count >= total) {
        complete();
    }
}