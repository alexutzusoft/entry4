#include "types.h"
#include "visuals.h"

/* Entry4 boot banner (tail, file+0x48834..0x48C02).
 * Printed in order ln00,ln01..ln15 by stub banner_show (file+0x1418)
 * through the print gate. Edit the text, keep the _Static_assert
 * lengths identical for a core-exact rebuild (change length only
 * if you also update the linker layout + shift handling in build.py).
 */

/* file+0x48834, len 0x49 */
const char banner_ln01[] __attribute__((section(".visual.tail.48834"))) =
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
_Static_assert(sizeof(banner_ln01) == 0x4A, "banner_ln01 len");

/* file+0x4887E, len 0x43 */
const char banner_ln02[] __attribute__((section(".visual.tail.4887e"))) =
    "  _________________  .____  ________    ___ ______________ _______\n";
_Static_assert(sizeof(banner_ln02) == 0x44, "banner_ln02 len");

/* file+0x488C2, len 0x44 */
const char banner_ln03[] __attribute__((section(".visual.tail.488c2"))) =
    " /  _____________  \\ |    | \\______ \\  /   |   \\_   _____/ \\      \\\n";
_Static_assert(sizeof(banner_ln03) == 0x45, "banner_ln03 len");

/* file+0x48907, len 0x45 */
const char banner_ln04[] __attribute__((section(".visual.tail.48907"))) =
    "/   \\  ___  /   |   \\|    |  |    |  \\/    ~    \\    __)_  /   |   \\\n";
_Static_assert(sizeof(banner_ln04) == 0x46, "banner_ln04 len");

/* file+0x4894D, len 0x46 */
const char banner_ln05[] __attribute__((section(".visual.tail.4894d"))) =
    "\\    \\_\\  \\/    |    \\    |__|    `   \\    Y    /        \\/    |    \\\n";
_Static_assert(sizeof(banner_ln05) == 0x47, "banner_ln05 len");

/* file+0x48994, len 0x46 */
const char banner_ln06[] __attribute__((section(".visual.tail.48994"))) =
    " \\______  /\\_______  /_______ \\_____  /\\___|_  /_______  /\\____|__  /\n";
_Static_assert(sizeof(banner_ln06) == 0x47, "banner_ln06 len");

/* file+0x489DB, len 0x46 */
const char banner_ln07[] __attribute__((section(".visual.tail.489db"))) =
    "        \\/         \\/        \\/     \\/       \\/        \\/         \\/\n\n";
_Static_assert(sizeof(banner_ln07) == 0x47, "banner_ln07 len");

/* file+0x48A22, len 0x27 */
const char banner_ln08[] __attribute__((section(".visual.tail.48a22"))) =
    "                              Coded By\n";
_Static_assert(sizeof(banner_ln08) == 0x28, "banner_ln08 len");

/* file+0x48A4A, len 0x3C */
const char banner_ln09[] __attribute__((section(".visual.tail.48a4a"))) =
    "        _________.__  ____________________________ ________\n";
_Static_assert(sizeof(banner_ln09) == 0x3D, "banner_ln09 len");

/* file+0x48A87, len 0x3D */
const char banner_ln10[] __attribute__((section(".visual.tail.48a87"))) =
    "       /   _____/|__|/   _________    _________   \\_____   \\\n";
_Static_assert(sizeof(banner_ln10) == 0x3E, "banner_ln10 len");

/* file+0x48AC5, len 0x3E */
const char banner_ln11[] __attribute__((section(".visual.tail.48ac5"))) =
    "       \\_____  \\ |  |\\_____  \\   |    |  |       _/ /   |   \\\n";
_Static_assert(sizeof(banner_ln11) == 0x3F, "banner_ln11 len");

/* file+0x48B04, len 0x3F */
const char banner_ln12[] __attribute__((section(".visual.tail.48b04"))) =
    "       /        \\|  |/        \\  |    |  |    |   \\/    |    \\\n";
_Static_assert(sizeof(banner_ln12) == 0x40, "banner_ln12 len");

/* file+0x48B44, len 0x3F */
const char banner_ln13[] __attribute__((section(".visual.tail.48b44"))) =
    "      /_______  /|__/_______  /  |____|  |____|_  /\\_________/\n";
_Static_assert(sizeof(banner_ln13) == 0x40, "banner_ln13 len");

/* file+0x48B84, len 0x33 */
const char banner_ln14[] __attribute__((section(".visual.tail.48b84"))) =
    "              \\/            \\/                  \\/\n";
_Static_assert(sizeof(banner_ln14) == 0x34, "banner_ln14 len");

/* file+0x48BB8, len 0x4A */
const char banner_ln15[] __attribute__((section(".visual.tail.48bb8"))) =
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
_Static_assert(sizeof(banner_ln15) == 0x4B, "banner_ln15 len");

/* file+0x48A20, len 0x1: "\n", overlaps tail of banner_ln07.
 * ln07 ends with "\n\n"; ln00 re-uses its final byte. Both share the
 * NUL at file+0x48A21. Do NOT emit a separate object for ln00. */
__asm__(".global banner_ln00\n\t.set banner_ln00, banner_ln07 + 0x45\n\t");
