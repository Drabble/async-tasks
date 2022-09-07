#include "wait_task.h"

void wait_task::iterate() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    elapsed_time++;
    setProgress((int) ((float) elapsed_time / (float) duration * 100.f));
    if (elapsed_time >= duration) {
        complete();
    }
}