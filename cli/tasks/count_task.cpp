#include "count_task.h"

void CountTask::iterate() {
    count++;
    setProgress((int) ((float) count / (float) total * 100.f));
    if (count >= total) {
        complete();
    }
}