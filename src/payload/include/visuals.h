#ifndef ENTRY4_VISUALS_H
#define ENTRY4_VISUALS_H

#include "types.h"

/* All user-visible assets. Each object lives in its own
 * .visual.* section so build.py can extract + patch it at an
 * exact file/core offset. Lengths are pinned by _Static_assert:
 * keep new text the SAME length for a core-exact rebuild.
 *
 * Tail offsets are file offsets (unencrypted).
 * Core offsets are decrypted-core offsets (core_plain).
 */

/* ---- tail banner (file+0x48834..0x48C02, 15 strings + ln00 alias) ---- */
extern const char banner_ln01[];
extern const char banner_ln02[];
extern const char banner_ln03[];
extern const char banner_ln04[];
extern const char banner_ln05[];
extern const char banner_ln06[];
extern const char banner_ln07[];
/* banner_ln00 aliases tail byte of banner_ln07 (see banner.c) */
extern const char banner_ln08[];
extern const char banner_ln09[];
extern const char banner_ln10[];
extern const char banner_ln11[];
extern const char banner_ln12[];
extern const char banner_ln13[];
extern const char banner_ln14[];
extern const char banner_ln15[];

/* ---- tail notices + brand (file+0x48C03..0x48D37) ---- */
extern const char res_notice_installing[]; /* [GoldHEN] Installing... */
extern const char res_notice_already[];    /* GoldHEN is already loaded! */
extern const char res_brand_short[];       /* GoldHEN (crypto magic) */

/* ---- core menu XMLs ---- */
extern const char core_menu_xml[];          /* 0x39178, 13986 B */
extern const char core_cheat_overlay_xml[]; /* 0x45C80, 256 B */
extern const char core_patch_overlay_xml[]; /* 0x45D90, 258 B */

/* ---- core boot notices (0x9AC46..0x9ADF3) ---- */
extern const char core_boot_fakepkg[];
extern const char core_boot_fakeself[];
extern const char core_boot_fmt[];
extern const char core_boot_goldhen[];
extern const char core_boot_entry4[];   /* Entry4 loaded */
extern const char core_boot_alldone[];
extern const char core_boot_testkit[];
extern const char core_boot_kernel[];
extern const char core_boot_shellcore[];
extern const char core_boot_shellui[];
extern const char core_boot_remoteplay[];

/* ---- core overlay (FPS / sysinfo) ---- */
extern const char core_ov_fps_server[];
extern const char core_ov_fps_thread[];
extern const char core_ov_fps_client[];
extern const char core_ov_fps_fmt[];
extern const char core_ov_ip_fmt[];
extern const char core_ov_thread_fmt[];
extern const char core_ov_soc_fmt[];
extern const char core_ov_cpu_fmt[];
extern const char core_ov_cpuavg_neo[];
extern const char core_ov_cpuavg[];
extern const char core_ov_cpuusage[];
extern const char core_ov_vram_fmt[];

/* ---- core servers (FTP / BinLoader / Klog / AutoRun) ---- */
extern const char core_ftp_banner[];
extern const char core_ftp_inuse[];
extern const char core_ftp_listening[];
extern const char core_ftp_noip[];
extern const char core_ftp_shutdown[];
extern const char core_bin_powered[];
extern const char core_pay_started[];
extern const char core_pay_received[];
extern const char core_pay_busy[];
extern const char core_pay_ok[];
extern const char core_pay_fail[];
extern const char core_pay_noip[];
extern const char core_pay_listen[];
extern const char core_pay_shutdown[];
extern const char core_klog_on[];
extern const char core_klog_off[];
extern const char core_autorun_removed[];
extern const char core_autorun_added[];
extern const char core_autorun_exists[];
extern const char core_pay_launch_ok[];
extern const char core_pay_launch_fail[];

/* ---- core cheat / patch / plugin ---- */
extern const char core_cheat_thread[];
extern const char core_cheat_fail[];
extern const char core_cheat_ok[];
extern const char core_cheat_prev[];
extern const char core_cheat_next[];
extern const char core_cheat_notfound[];
extern const char core_cheat_by[];
extern const char core_cheat_template[];
extern const char core_patch_thread[];
extern const char core_patch_fail[];
extern const char core_patch_ok[];
extern const char core_patch_notfound[];
extern const char core_plugin_thread[];
extern const char core_plugin_fail[];
extern const char core_plugin_ok[];
extern const char core_plugin_loaded_n[];
extern const char core_cheat_autoapply[];
extern const char core_datetime_title[];
extern const char core_datetime_ok[];

/* ---- core icons ---- */
extern const char core_icon_launchpad[]; /* file://user/data/entry4.png */
extern const char core_icon_fmt[];       /* [+] icon0_png_path format */
extern const char core_scanlines_path[];
extern const char core_key_iconbox[];
extern const char core_key_topmenu[];

/* ---- core branding labels ---- */
extern const char core_topmenu_label[];  /* TopMenu tile (Entry4+NBSPs) */
extern const char core_about_entry4_a[];
extern const char core_about_entry4_b[];
extern const char core_cheat_title[];    /* Entry4 Cheat Menu (code) */
extern const char core_patch_title[];    /* Entry4 Patch Menu (code) */

/* ---- core embedded media (binary blobs, no NUL) ---- */
extern const unsigned char core_icon_192[];     /* 192x192 Entry4 PNG */
extern const unsigned char core_tex_scanlines[]; /* scanline texture PNG */

#endif /* ENTRY4_VISUALS_H */
