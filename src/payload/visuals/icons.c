#include "types.h"
#include "visuals.h"

/* Home-screen + overlay icons (core). */
/* Zeroed icon block file+0x411A4..0x43600 (0x245C bytes, all zeros):
 * GoldHEN menu icons removed in Entry4. Keep zeros to stay core-exact.
 * Documented here, owned by asm/tail.S (no C object). */

/* core+0x87873, len 0x1B -- LaunchPad/home icon path */
const char core_icon_launchpad[] __attribute__((section(".visual.core.87873"))) =
    "file://user/data/entry4.png";
_Static_assert(sizeof(core_icon_launchpad) == 0x1C, "icon path len");

/* core+0x9AEBF, len 0x3B -- icon0_png_path debug format */
const char core_icon_fmt[] __attribute__((section(".visual.core.9aebf"))) =
    "icon0_png_path: %s - offset: 0x%lx - size: 0x%lx - ret: %d\n";
_Static_assert(sizeof(core_icon_fmt) == 0x3C, "icon fmt len");

/* core+0x85818, len 0x1F -- scanlines overlay path */
const char core_scanlines_path[] __attribute__((section(".visual.core.85818"))) =
    "/GoldHEN/overlays/scanlines.ovl";
_Static_assert(sizeof(core_scanlines_path) == 0x20, "scanlines len");

/* core+0x8532D -- placeholder */
const char core_key_iconbox[] __attribute__((section(".visual.core.8532d"))) =
    "m_iconImageBox";
_Static_assert(sizeof(core_key_iconbox) == 0xF, "core_key_iconbox len");

/* core+0x853A7 -- placeholder */
const char core_key_topmenu[] __attribute__((section(".visual.core.853a7"))) =
    "Sce.Vsh.ShellUI.TopMenu";
_Static_assert(sizeof(core_key_topmenu) == 0x18, "core_key_topmenu len");

