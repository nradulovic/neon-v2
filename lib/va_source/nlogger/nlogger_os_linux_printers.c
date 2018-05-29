
#include <stdio.h>
#include <stdarg.h>

#include "logger/nlogger_x.h"

#define nlogger_va_vprintf vprintf

struct nlogger_instance p_nlogger_global =
{
    .level = NLOGGER_LEVEL_INFO
};

void p_nlogger_x_print(struct nlogger_instance * instance, 
        uint32_t level, const char * msg, ...)
{
    va_list args;

    if (instance->level >= level) {
        va_start(args, msg);
        nlogger_va_vprintf(msg, args);
        va_end(args);
    }
}

void p_nlogger_x_set_level(struct nlogger_instance * instance, uint32_t level)
{
    instance->level = level;
}
