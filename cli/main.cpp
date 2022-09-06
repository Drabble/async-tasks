#include <stdlib.h>
#include "cli.h"

int main(int argc, char **argv){
    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        Cli::showUsage();
        return 0;
    } else{
        Cli cli;
        cli.start();
    }
    return EXIT_SUCCESS;
}