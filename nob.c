#include <string.h>
#define NOB_STRIP_PREFIX
#define NOB_IMPLEMENTATION
#include "src/nob.h"

#define SRC_FILES "src/main.c"
#define BUILD_FOLDER "build"
#define PROGRAM_NAME "cadet"
#define CFLAGS "-Wall", "-Wextra", "-Wswitch-enum", "-I./src/"

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    if (!mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    Cmd cmd = {0};

    char* prog_path = temp_sprintf("./%s/%s", BUILD_FOLDER, PROGRAM_NAME);
    cmd_append(&cmd, "cc", CFLAGS);
    cmd_append(&cmd, "-o", prog_path);
    cmd_append(&cmd, SRC_FILES);

    if (!cmd_run_sync_and_reset(&cmd)) return 1;

    char* nob_p_name = shift(argv, argc);
    if (argc >= 1) {
        char* command = shift(argv, argc);
        if (strcmp(command, "run") == 0) {
            cmd_append(&cmd, prog_path);
            if (!cmd_run_sync_and_reset(&cmd)) return 1;
        } else {
            nob_log(ERROR, temp_sprintf("unknown command %s\n", command));
            return 1;
        }
    }

    return 0;
}
