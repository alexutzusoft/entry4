#include "types.h"
#include "visuals.h"

/* Boot notices (core). Edit text, keep lengths identical. */
/* core+0x9AC46, len 0x23 -- FakePKG hooks installed */
const char core_boot_fakepkg[] __attribute__((section(".visual.core.9ac46"))) =
    "[GoldHEN] FakePKG hooks installed!\n";
_Static_assert(sizeof(core_boot_fakepkg) == 0x24, "core_boot_fakepkg len");

/* core+0x9AC76, len 0x24 -- FakeSelf hooks installed */
const char core_boot_fakeself[] __attribute__((section(".visual.core.9ac76"))) =
    "[GoldHEN] FakeSelf hooks installed!\n";
_Static_assert(sizeof(core_boot_fakeself) == 0x25, "core_boot_fakeself len");

/* core+0x9AC9B, len 0xD -- [GoldHEN] %s format */
const char core_boot_fmt[] __attribute__((section(".visual.core.9ac9b"))) =
    "[GoldHEN] %s\n";
_Static_assert(sizeof(core_boot_fmt) == 0xE, "core_boot_fmt len");

/* core+0x9ACA9, len 0x7 -- GoldHEN helper */
const char core_boot_goldhen[] __attribute__((section(".visual.core.9aca9"))) =
    "GoldHEN";
_Static_assert(sizeof(core_boot_goldhen) == 0x8, "core_boot_goldhen len");

/* core+0x9ACB1, len 0x19 -- Entry4 loaded */
const char core_boot_entry4[] __attribute__((section(".visual.core.9acb1"))) =
    "Entry4 loaded\nby Alexutzu";
_Static_assert(sizeof(core_boot_entry4) == 0x1A, "core_boot_entry4 len");

/* core+0x9ACDC, len 0x14 -- All done */
const char core_boot_alldone[] __attribute__((section(".visual.core.9acdc"))) =
    "[GoldHEN] All done!\n";
_Static_assert(sizeof(core_boot_alldone) == 0x15, "core_boot_alldone len");

/* core+0x9ACF1, len 0x2D -- Testkit fake activation */
const char core_boot_testkit[] __attribute__((section(".visual.core.9acf1"))) =
    "[GoldHEN] Testkit fake activation installed!\n";
_Static_assert(sizeof(core_boot_testkit) == 0x2E, "core_boot_testkit len");

/* core+0x9AD1F, len 0x24 -- Kernel patches installed */
const char core_boot_kernel[] __attribute__((section(".visual.core.9ad1f"))) =
    "[GoldHEN] Kernel patches installed!\n";
_Static_assert(sizeof(core_boot_kernel) == 0x25, "core_boot_kernel len");

/* core+0x9AD69, len 0x2A -- SceShellCore patches installed */
const char core_boot_shellcore[] __attribute__((section(".visual.core.9ad69"))) =
    "[GoldHEN] SceShellCore patches installed!\n";
_Static_assert(sizeof(core_boot_shellcore) == 0x2B, "core_boot_shellcore len");

/* core+0x9ADB7, len 0x28 -- SceShellUI patches installed */
const char core_boot_shellui[] __attribute__((section(".visual.core.9adb7"))) =
    "[GoldHEN] SceShellUI patches installed!\n";
_Static_assert(sizeof(core_boot_shellui) == 0x29, "core_boot_shellui len");

/* core+0x9ADF3, len 0x2B -- SceRemotePlay patches installed */
const char core_boot_remoteplay[] __attribute__((section(".visual.core.9adf3"))) =
    "[GoldHEN] SceRemotePlay patches installed!\n";
_Static_assert(sizeof(core_boot_remoteplay) == 0x2C, "core_boot_remoteplay len");

