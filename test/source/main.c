
#include <stdio.h>

#include "port/nport_platform.h"
#include "logger/nlogger.h"
#include "test_narch.h"
#include "test_nlist_sll.h"
#include "test_nlist_dll.h"
#include "test_ndebug_enabled.h"
#include "test_ndebug_disabled.h"
#include "test_nbits.h"
#include "test_nbitarray.h"

int main(void)
{
    nlogger_info("Port platform ID: %s\n", nport_platform_id);
    test_narch();
    test_nlist_sll();
    test_nlist_dll();
    test_ndebug_enabled();
    test_ndebug_disabled();
    test_nbits();
    test_nbitarray();
    
    return 0;
}
