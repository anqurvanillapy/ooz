#include "codegen.h"
#include "ooz/ooz.h"
#include <stdio.h>

#define PATH_MAX 4096
#define OUT_FILENAME_SIZ sizeof(char) * (PATH_MAX + 1)

typedef struct {
    char *outfile;
} codegen_t;

static codegen_t cg;

err_t
cg_init(const char *outfile)
{
    if (!outfile) {
        return ErrNullPointer;
    }

    cg.outfile = (char *)malloc(OUT_FILENAME_SIZ);
    if (!cg.outfile) {
        LOG_FATAL(ErrNoMem);
    }

    if (snprintf(cg.outfile, OUT_FILENAME_SIZ, "%s.c", outfile) < 0) {
        return ErrFilePath;
    }

    return OK;
}

#define FILE_HEADER "#include <rt.h>\n\n"

#define ENTRY_HEADER "void %s_entry(){\n"
#define ENTRY_FOOTER "}\n\n"

#define INFOTBL_TMPL "infotbl_t %s_info={\n.type=%s,\n.entry=%s_entry,\n};\n\n"

#define CLOSURE_TMPL                                                           \
    "closure_t %s={\n.type=%s,\n.info_ptr=&%s_info,\n.payload=%s,\n};\n\n"

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

static void
write_infotbl(FILE *f)
{
    fprintf(f, INFOTBL_TMPL, "v", "TypeInt", "v");
}

static void
write_closure(FILE *f)
{
    fprintf(f, CLOSURE_TMPL, "v", "ClosCtor", "v", "(void*)42");
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
    write_infotbl(f);
    write_closure(f);

    fclose(f);
    free(cg.outfile);

    return OK;
}
