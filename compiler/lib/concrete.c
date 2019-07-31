#include "concrete.h"
#include "ooz/ooz.h"
#include <string.h>

char *
lex_substr(const char *txt, size_t len)
{
    char *str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str) {
        LOG_FATAL(ErrNoMem);
    }
    strncpy(str, txt, len + 1);
    str[len] = '\0';
    return str;
}
