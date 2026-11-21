#include "types.h"
#include "visuals.h"

/* Branding labels (core). */
/* core+0x887EC, len 0xA -- TopMenu home tile label (Entry4+NBSPs) */
const char core_topmenu_label[] __attribute__((section(".visual.core.887ec"))) =
    "Entry4\xc2\xa0\xc2\xa0";
_Static_assert(sizeof(core_topmenu_label) == 0xB, "core_topmenu_label len");

/* core+0x88516, len 0x6 -- About Entry4 (southbridge) */
const char core_about_entry4_a[] __attribute__((section(".visual.core.88516"))) =
    "Entry4";
_Static_assert(sizeof(core_about_entry4_a) == 0x7, "core_about_entry4_a len");

/* core+0x885DA, len 0x6 -- About Entry4 (goldhen_menu) */
const char core_about_entry4_b[] __attribute__((section(".visual.core.885da"))) =
    "Entry4";
_Static_assert(sizeof(core_about_entry4_b) == 0x7, "core_about_entry4_b len");

/* core+0x8820B, len 0x11 -- Entry4 Cheat Menu (code string) */
const char core_cheat_title[] __attribute__((section(".visual.core.8820b"))) =
    "Entry4 Cheat Menu";
_Static_assert(sizeof(core_cheat_title) == 0x12, "core_cheat_title len");

/* core+0x88652, len 0x11 -- Entry4 Patch Menu (code string) */
const char core_patch_title[] __attribute__((section(".visual.core.88652"))) =
    "Entry4 Patch Menu";
_Static_assert(sizeof(core_patch_title) == 0x12, "core_patch_title len");

