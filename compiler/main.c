#include "lib/codegen.h"
#include "ooz/log.h"

int
main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    err_t err;

    err = cg_init("hello.ooz");
    if (err != OK) {
        LOG_FATAL(err);
    }

    err = cg_writefile();
    if (err != OK) {
        LOG_FATAL(err);
    }

    return 0;
}
