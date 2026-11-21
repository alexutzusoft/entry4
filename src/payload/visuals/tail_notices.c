#include "types.h"
#include "visuals.h"

/* Tail notices + brand magic (file+0x48C03..0x48D37).
 * - installing: printed by banner path (sub_1620) via print gate
 * - already: notified twice via kernel gate (sub_1653/sub_82A)
 * - brand: 8-byte magic compared by sub_1724 (crypto integrity path).
 * Keep lengths identical for core-exact rebuilds.
 */

/* file+0x48C03, len 0x2A */
const char res_notice_installing[] __attribute__((section(".visual.tail.48c03"))) =
    "[GoldHEN] Installing GoldHEN in Kernel...\n";
_Static_assert(sizeof(res_notice_installing) == 0x2B, "res_notice_installing len");

/* file+0x48D13, len 0x1A */
const char res_notice_already[] __attribute__((section(".visual.tail.48d13"))) =
    "GoldHEN is already loaded!";
_Static_assert(sizeof(res_notice_already) == 0x1B, "res_notice_already len");

/* file+0x48D30, len 0x7 */
const char res_brand_short[] __attribute__((section(".visual.tail.48d30"))) =
    "GoldHEN";
_Static_assert(sizeof(res_brand_short) == 0x8, "res_brand_short len");

