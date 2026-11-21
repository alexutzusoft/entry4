#include "types.h"
#include "visuals.h"

/* Cheat / Patch / Plugin updater + OSD strings. */
/* core+0x84CC7, len 0x1D -- Update Cheats Thread */
const char core_cheat_thread[] __attribute__((section(".visual.core.84cc7"))) =
    "-GoldHEN Update Cheats Thread";
_Static_assert(sizeof(core_cheat_thread) == 0x1E, "core_cheat_thread len");

/* core+0x84EAF, len 0x18 -- Failed to update Cheats */
const char core_cheat_fail[] __attribute__((section(".visual.core.84eaf"))) =
    "Failed to update Cheats.";
_Static_assert(sizeof(core_cheat_fail) == 0x19, "core_cheat_fail len");

/* core+0x84EC8, len 0xF -- Cheats updated */
const char core_cheat_ok[] __attribute__((section(".visual.core.84ec8"))) =
    "Cheats updated.";
_Static_assert(sizeof(core_cheat_ok) == 0x10, "core_cheat_ok len");

/* core+0x851C5, len 0xA -- Prev Cheat */
const char core_cheat_prev[] __attribute__((section(".visual.core.851c5"))) =
    "Prev Cheat";
_Static_assert(sizeof(core_cheat_prev) == 0xB, "core_cheat_prev len");

/* core+0x851E4, len 0xA -- Next Cheat */
const char core_cheat_next[] __attribute__((section(".visual.core.851e4"))) =
    "Next Cheat";
_Static_assert(sizeof(core_cheat_next) == 0xB, "core_cheat_next len");

/* core+0x85242, len 0x29 -- Cheats not found TitleId */
const char core_cheat_notfound[] __attribute__((section(".visual.core.85242"))) =
    "Cheats not found for this TitleId/Version";
_Static_assert(sizeof(core_cheat_notfound) == 0x2A, "core_cheat_notfound len");

/* core+0x8528C, len 0xC -- Cheats by %s */
const char core_cheat_by[] __attribute__((section(".visual.core.8528c"))) =
    "Cheats by %s";
_Static_assert(sizeof(core_cheat_by) == 0xD, "core_cheat_by len");

/* core+0x84FEB, len 0x27 -- What/how/when Cheat template */
const char core_cheat_template[] __attribute__((section(".visual.core.84feb"))) =
    "What/how/when is this Cheat: Change me!";
_Static_assert(sizeof(core_cheat_template) == 0x28, "core_cheat_template len");

/* core+0x8743F, len 0x1D -- Update Patches Thread */
const char core_patch_thread[] __attribute__((section(".visual.core.8743f"))) =
    "GoldHEN Update Patches Thread";
_Static_assert(sizeof(core_patch_thread) == 0x1E, "core_patch_thread len");

/* core+0x87595, len 0x19 -- Failed to update Patches */
const char core_patch_fail[] __attribute__((section(".visual.core.87595"))) =
    "Failed to update Patches.";
_Static_assert(sizeof(core_patch_fail) == 0x1A, "core_patch_fail len");

/* core+0x875AF, len 0x10 -- Patches updated */
const char core_patch_ok[] __attribute__((section(".visual.core.875af"))) =
    "Patches updated.";
_Static_assert(sizeof(core_patch_ok) == 0x11, "core_patch_ok len");

/* core+0x85718, len 0x2A -- Patches not found TitleId */
const char core_patch_notfound[] __attribute__((section(".visual.core.85718"))) =
    "Patches not found for this TitleId/Version";
_Static_assert(sizeof(core_patch_notfound) == 0x2B, "core_patch_notfound len");

/* core+0x87ACA, len 0x1D -- Update Plugins Thread */
const char core_plugin_thread[] __attribute__((section(".visual.core.87aca"))) =
    "GoldHEN Update Plugins Thread";
_Static_assert(sizeof(core_plugin_thread) == 0x1E, "core_plugin_thread len");

/* core+0x87C71, len 0x19 -- Failed to update Plugins */
const char core_plugin_fail[] __attribute__((section(".visual.core.87c71"))) =
    "Failed to update Plugins.";
_Static_assert(sizeof(core_plugin_fail) == 0x1A, "core_plugin_fail len");

/* core+0x87C8B, len 0x10 -- Plugins updated */
const char core_plugin_ok[] __attribute__((section(".visual.core.87c8b"))) =
    "Plugins updated.";
_Static_assert(sizeof(core_plugin_ok) == 0x11, "core_plugin_ok len");

/* core+0x96955, len 0x16 -- Loaded %u plugin(s) */
const char core_plugin_loaded_n[] __attribute__((section(".visual.core.96955"))) =
    "Loaded %u plugin(s)\n%s";
_Static_assert(sizeof(core_plugin_loaded_n) == 0x17, "core_plugin_loaded_n len");

/* core+0x8501D, len 0x19 -- GoldHEN Auto-Apply Cheats */
const char core_cheat_autoapply[] __attribute__((section(".visual.core.8501d"))) =
    "GoldHEN Auto-Apply Cheats";
_Static_assert(sizeof(core_cheat_autoapply) == 0x1A, "core_cheat_autoapply len");

/* core+0x87392, len 0x1C -- GoldHEN Update Date and Time */
const char core_datetime_title[] __attribute__((section(".visual.core.87392"))) =
    "GoldHEN Update Date and Time";
_Static_assert(sizeof(core_datetime_title) == 0x1D, "core_datetime_title len");

/* core+0x8737B, len 0x16 -- Date and Time updated */
const char core_datetime_ok[] __attribute__((section(".visual.core.8737b"))) =
    "Date and Time updated!";
_Static_assert(sizeof(core_datetime_ok) == 0x17, "core_datetime_ok len");

