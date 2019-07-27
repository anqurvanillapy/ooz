#include "codegen.h"
#include "ooz/log.h"
#include <stdio.h>

#define PATH_MAX 4096

typedef struct {
    char outfile[PATH_MAX + 1];
} codegen_t;

static codegen_t cg;

err_t
cg_init(const char *outfile)
{
    if (!outfile) {
        return ErrNullPointer;
    }
    if (snprintf(cg.outfile, sizeof(cg.outfile), "%s.c", outfile) < 0) {
        return ErrFilePath;
    }
    return OK;
}

#define FILE_HEADER "#include <rt.h>\n"

#define ENTRY_HEADER "void %s_entry(){\n"
#define ENTRY_FOOTER "}\n"

static void
write_file_header(FILE *f)
{
    fprintf(f, FILE_HEADER);
}

static void
write_entry(FILE *f)
{
    fprintf(f, ENTRY_HEADER, "v");
    fprintf(f, ENTRY_FOOTER);
}

err_t
cg_writefile()
{
    FILE *f = fopen(cg.outfile, "w");

    if (!f) {
        return ErrOpenFile;
    }

    write_file_header(f);
    write_entry(f);

    fclose(f);
    return OK;
}
