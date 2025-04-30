#define NOB_IMPLEMENTATION
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

int main(int argc, char **argv) {

	NOB_GO_REBUILD_URSELF(argc, argv);

	Nob_Cmd cmd = {0};

	nob_cmd_append(&cmd, "cc", "-o", "main", "main.c");

	if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;

	return 0;
}
