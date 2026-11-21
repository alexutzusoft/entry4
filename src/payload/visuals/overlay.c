#include "types.h"
#include "visuals.h"

/* Game overlay strings (FPS, sysinfo, temps). */
/* core+0x854D7, len 0x1A -- FPS socket server */
const char core_ov_fps_server[] __attribute__((section(".visual.core.854d7"))) =
    "?GoldHEN FPS Socket Server";
_Static_assert(sizeof(core_ov_fps_server) == 0x1B, "core_ov_fps_server len");

/* core+0x854F2, len 0x1A -- FPS monitor thread */
const char core_ov_fps_thread[] __attribute__((section(".visual.core.854f2"))) =
    "GoldHEN FPS Monitor Thread";
_Static_assert(sizeof(core_ov_fps_thread) == 0x1B, "core_ov_fps_thread len");

/* core+0x94D76, len 0x19 -- FPS socket client */
const char core_ov_fps_client[] __attribute__((section(".visual.core.94d76"))) =
    "GoldHEN FPS Socket Client";
_Static_assert(sizeof(core_ov_fps_client) == 0x1A, "core_ov_fps_client len");

/* core+0x855C8, len 0xA -- FPS: %.2lf */
const char core_ov_fps_fmt[] __attribute__((section(".visual.core.855c8"))) =
    "FPS: %.2lf";
_Static_assert(sizeof(core_ov_fps_fmt) == 0xB, "core_ov_fps_fmt len");

/* core+0x855D3, len 0xE -- IP Address format */
const char core_ov_ip_fmt[] __attribute__((section(".visual.core.855d3"))) =
    "IP Address: %s";
_Static_assert(sizeof(core_ov_ip_fmt) == 0xF, "core_ov_ip_fmt len");

/* core+0x855E2, len 0x10 -- Thread Count format */
const char core_ov_thread_fmt[] __attribute__((section(".visual.core.855e2"))) =
    "Thread Count: %i";
_Static_assert(sizeof(core_ov_thread_fmt) == 0x11, "core_ov_thread_fmt len");

/* core+0x855F3, len 0x10 -- SOC Temp format */
const char core_ov_soc_fmt[] __attribute__((section(".visual.core.855f3"))) =
    "SOC Temp: %i\xc2\xb0 C";
_Static_assert(sizeof(core_ov_soc_fmt) == 0x11, "core_ov_soc_fmt len");

/* core+0x85604, len 0x10 -- CPU Temp format */
const char core_ov_cpu_fmt[] __attribute__((section(".visual.core.85604"))) =
    "CPU Temp: %i\xc2\xb0 C";
_Static_assert(sizeof(core_ov_cpu_fmt) == 0x11, "core_ov_cpu_fmt len");

/* core+0x85615, len 0x28 -- CPU avg Neo Mode */
const char core_ov_cpuavg_neo[] __attribute__((section(".visual.core.85615"))) =
    "CPU Usage Average: %2.0f%%  ( Neo Mode )";
_Static_assert(sizeof(core_ov_cpuavg_neo) == 0x29, "core_ov_cpuavg_neo len");

/* core+0x8563E, len 0x1A -- CPU avg */
const char core_ov_cpuavg[] __attribute__((section(".visual.core.8563e"))) =
    "CPU Usage Average: %2.0f%%";
_Static_assert(sizeof(core_ov_cpuavg) == 0x1B, "core_ov_cpuavg len");

/* core+0x85659, len 0x4E -- CPU Usage full */
const char core_ov_cpuusage[] __attribute__((section(".visual.core.85659"))) =
    "CPU Usage: %2.0f%%  (%2.0f%% %2.0f%% %2.0f%% %2.0f%% %2.0f%% %2.0f%% %2.0f%% )";
_Static_assert(sizeof(core_ov_cpuusage) == 0x4F, "core_ov_cpuusage len");

/* core+0x856A8, len 0x20 -- VRAM/RAM usage (shared) */
const char core_ov_vram_fmt[] __attribute__((section(".visual.core.856a8"))) =
    "VRAM: %2.0f%%  ( %u MB / %u MB )";
_Static_assert(sizeof(core_ov_vram_fmt) == 0x21, "core_ov_vram_fmt len");

