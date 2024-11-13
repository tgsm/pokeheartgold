#include "error_handling.h"

#include "global.h"

#include "error_message_reset.h"
#include "unk_02037C94.h"

static char tgsm_assert_buffer[256] = {};

void GF_AssertFail(void) {
    u32 link = 0;
    asm { mov link, lr };
    OS_SNPrintf(tgsm_assert_buffer, NELEMS(tgsm_assert_buffer), "ASSERTION FAILED: [%08X]\n", link);
    *((u32*)0x4FFFA10) = (u32)&tgsm_assert_buffer;

    if (!sub_02037D78()) {
        return;
    }

    if (OS_GetProcMode() != OS_PROCMODE_IRQ) {
        PrintErrorMessageAndReset();
    }
}

void tgsm_assert_failed(const char* condition, const char* filename, const int line) {
    OS_SNPrintf(tgsm_assert_buffer, NELEMS(tgsm_assert_buffer), "ASSERTION FAILED: %s (%s:%d)\n", condition, filename, line);
    *((u32*)0x4FFFA10) = (u32)&tgsm_assert_buffer;
}
