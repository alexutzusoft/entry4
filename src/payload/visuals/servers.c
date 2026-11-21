#include "types.h"
#include "visuals.h"

/* Servers: FTP / BinLoader(PayLoader) / Klog / AutoRun toasts. */
/* core+0x93252, len 0x1D -- 220 GoldHEN FTP server v2.2 */
const char core_ftp_banner[] __attribute__((section(".visual.core.93252"))) =
    "220 GoldHEN FTP server v2.2\r\n";
_Static_assert(sizeof(core_ftp_banner) == 0x1E, "core_ftp_banner len");

/* core+0x931D8, len 0x1A -- FTP Port already in use */
const char core_ftp_inuse[] __attribute__((section(".visual.core.931d8"))) =
    "FTP Port %u already in use";
_Static_assert(sizeof(core_ftp_inuse) == 0x1B, "core_ftp_inuse len");

/* core+0x93C64, len 0x1E -- FTP listening on */
const char core_ftp_listening[] __attribute__((section(".visual.core.93c64"))) =
    "FTP listening on\nIP %s port %i";
_Static_assert(sizeof(core_ftp_listening) == 0x1F, "core_ftp_listening len");

/* core+0x93C3C, len 0x21 -- FTP failed to get IP */
const char core_ftp_noip[] __attribute__((section(".visual.core.93c3c"))) =
    "FTP failed to get IP.\nAborting...";
_Static_assert(sizeof(core_ftp_noip) == 0x22, "core_ftp_noip len");

/* core+0x93CA3, len 0x17 -- FTP shutting down */
const char core_ftp_shutdown[] __attribute__((section(".visual.core.93ca3"))) =
    "FTP is shutting down...";
_Static_assert(sizeof(core_ftp_shutdown) == 0x18, "core_ftp_shutdown len");

/* core+0x98AFC, len 0x82 -- X-Powered-By GoldHEN by SiSTRo */
const char core_bin_powered[] __attribute__((section(".visual.core.98afc"))) =
    "X-Powered-By: GoldHEN by SiSTRo\r\nConnection: close\r\nCache-Control: no-cache\r\nContent-Type: application/json\r\nContent-Length: %li\r\n";
_Static_assert(sizeof(core_bin_powered) == 0x83, "core_bin_powered len");

/* core+0x98DEC, len 0x25 -- <payloader> Server started */
const char core_pay_started[] __attribute__((section(".visual.core.98dec"))) =
    "<payloader> Server started at %d port";
_Static_assert(sizeof(core_pay_started) == 0x26, "core_pay_started len");

/* core+0x98C46, len 0x18 -- Payload received from */
const char core_pay_received[] __attribute__((section(".visual.core.98c46"))) =
    "Payload received from %s";
_Static_assert(sizeof(core_pay_received) == 0x19, "core_pay_received len");

/* core+0x98C28, len 0x1D -- Payload skipped. Server busy. */
const char core_pay_busy[] __attribute__((section(".visual.core.98c28"))) =
    "Payload skipped. Server busy.";
_Static_assert(sizeof(core_pay_busy) == 0x1E, "core_pay_busy len");

/* core+0x9897C, len 0x29 -- <payloader> payload launched successfully */
const char core_pay_ok[] __attribute__((section(".visual.core.9897c"))) =
    "<payloader> payload launched successfully";
_Static_assert(sizeof(core_pay_ok) == 0x2A, "core_pay_ok len");

/* core+0x989AC, len 0x2F -- <payloader> failed to launch payload */
const char core_pay_fail[] __attribute__((section(".visual.core.989ac"))) =
    "<payloader> failed to launch payload, error: %d";
_Static_assert(sizeof(core_pay_fail) == 0x30, "core_pay_fail len");

/* core+0x98A14, len 0x27 -- PayLoader failed to get IP */
const char core_pay_noip[] __attribute__((section(".visual.core.98a14"))) =
    "PayLoader failed to get IP.\nAborting...";
_Static_assert(sizeof(core_pay_noip) == 0x28, "core_pay_noip len");

/* core+0x98A3C, len 0x24 -- PayLoader listening on */
const char core_pay_listen[] __attribute__((section(".visual.core.98a3c"))) =
    "PayLoader listening on\nIP %s port %i";
_Static_assert(sizeof(core_pay_listen) == 0x25, "core_pay_listen len");

/* core+0x98A73, len 0x1D -- PayLoader shutting down */
const char core_pay_shutdown[] __attribute__((section(".visual.core.98a73"))) =
    "PayLoader is shutting down...";
_Static_assert(sizeof(core_pay_shutdown) == 0x1E, "core_pay_shutdown len");

/* core+0x9A367, len 0x16 -- Klog server on port */
const char core_klog_on[] __attribute__((section(".visual.core.9a367"))) =
    "Klog server on port %d";
_Static_assert(sizeof(core_klog_on) == 0x17, "core_klog_on len");

/* core+0x9A394, len 0x1F -- Klog server shutting down */
const char core_klog_off[] __attribute__((section(".visual.core.9a394"))) =
    "Klog server is shutting down...";
_Static_assert(sizeof(core_klog_off) == 0x20, "core_klog_off len");

/* core+0x87601, len 0x22 -- Payload removed from AutoRun */
const char core_autorun_removed[] __attribute__((section(".visual.core.87601"))) =
    "Payload removed from AutoRun queue";
_Static_assert(sizeof(core_autorun_removed) == 0x23, "core_autorun_removed len");

/* core+0x8765F, len 0x1E -- Payload added to AutoRun */
const char core_autorun_added[] __attribute__((section(".visual.core.8765f"))) =
    "Payload added to AutoRun queue";
_Static_assert(sizeof(core_autorun_added) == 0x1F, "core_autorun_added len");

/* core+0x8767E, len 0x20 -- Payload already in AutoRun */
const char core_autorun_exists[] __attribute__((section(".visual.core.8767e"))) =
    "Payload already in AutoRun queue";
_Static_assert(sizeof(core_autorun_exists) == 0x21, "core_autorun_exists len");

/* core+0x877EF, len 0x1D -- Payload launched successfully */
const char core_pay_launch_ok[] __attribute__((section(".visual.core.877ef"))) =
    "Payload launched successfully";
_Static_assert(sizeof(core_pay_launch_ok) == 0x1E, "core_pay_launch_ok len");

/* core+0x8780D, len 0x2A -- Failed to launch payload */
const char core_pay_launch_fail[] __attribute__((section(".visual.core.8780d"))) =
    "Failed to launch payload.\nInvalid payload.";
_Static_assert(sizeof(core_pay_launch_fail) == 0x2B, "core_pay_launch_fail len");

