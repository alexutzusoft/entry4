#include "types.h"
#include "visuals.h"

/* Main Settings menu XML (core+0x39178, 13986 B, CRLF).
 * title="Entry4", icon="file://user/data/entry4.png".
 * To rebrand: edit title/icon below, KEEP TOTAL LENGTH identical
 * (pad with spaces) for a core-exact rebuild. */
const char core_menu_xml[] __attribute__((section(".visual.core.39178"))) =
    "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n<system_settings version=\"1.0\" plugin=\"settings_root_plugin\">\r\n\r\n  <setting_list id=\"id_goldhen_menu\" title=\"Entry4\" initial_focus_to=\"id_goldhen_toggle_ftp\" i"
    "con=\"file://user/data/entry4.png\">\r\n\r\n    <setting_list id=\"id_goldhen_debug_settings\" title=\"Debug Settings\">\r\n      <link id=\"id_game_package_installer\" title=\"Package Installer\" file=\"PkgInstaller/"
    "data/pkginstaller.xml\"/>\r\n      <list id=\"id_goldhen_debug_settings_source\" title=\"Package source\" left_margin=\"94\">\r\n        <list_item id=\"id_goldhen_debug_settings_source_usb\" title=\"Usb [ usb:/ ]\""
    " value=\"0\"/>\r\n        <list_item id=\"id_goldhen_debug_settings_source_hdd\" title=\"Hdd [ hdd:/data/pkg/ ]\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_debug_settings_source_both\" title=\"All\" value=\""
    "2\"/>\r\n      </list>\r\n      <toggle_switch id=\"id_goldhen_debug_settings_search_subdirectories\" title=\"Enable Search Subdirectories\" value=\"0\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_de"
    "bug_settings_bgft_enabled\" title=\"Enable Background Installation\" value=\"0\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_debug_settings_info_visible\" title=\"Show Package Info\" value=\"0\" lef"
    "t_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_debug_settings_path_visible\" title=\"Show Package Path\" value=\"0\" left_margin=\"94\"/>\r\n      <list id=\"id_goldhen_debug_settings_enabled\" title=\"Enab"
    "le Debug Settings\" description=\"\xe2\x9a\xa0 Debug options are useful for developers. Enabling or disabling an option may cause an unexpected behaviour on your console. Use at your own risk.\">\r\n        <list_i"
    "tem id=\"id_goldhen_debug_settings_enabled_off\" title=\"Off\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_debug_settings_enabled_mini\" title=\"Mini Menu\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_"
    "debug_settings_enabled_full\" title=\"Full Menu\" value=\"2\"/>\r\n      </list>\r\n      <toggle_switch id=\"id_goldhen_game_debug_settings_enabled\" title=\"Enable Game Debug Settings\" value=\"0\"/>\r\n    </settin"
    "g_list>\r\n\r\n    <setting_list id=\"id_goldhen_cheat_settings\" title=\"Cheat Settings\">\r\n\r\n      <toggle_switch id=\"id_goldhen_toggle_cheat_menu\" title=\"Enable Cheat Menu\" value=\"1\"/>\r\n      <list id=\"id_"
    "goldhen_cheat_menu_combo\" title=\"Cheat Menu Combo\" left_margin=\"94\">\r\n        <list_item id=\"id_goldhen_cheat_menu_combo_off\" title=\"Off\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_cheat_menu_comb"
    "o_share\" title=\"Long press Share button\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_cheat_menu_combo_ps\" title=\"Fast double press PS button\" value=\"2\"/>\r\n      </list>\r\n      <toggle_switch id=\"id"
    "_goldhen_toggle_cheat_menu_game_options\" title=\"Show Cheat Menu on Game Options\" value=\"1\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_cheat_autoapply\" title=\"Enable Auto-Apply on Game Sta"
    "rt\" description=\"You can't change this value while a game is running.\" value=\"0\" left_margin=\"94\"/>\r\n\r\n      <list id=\"id_goldhen_cheat_settings_titleid\" title=\"Show TitleID\">\r\n        <list_item id=\""
    "id_goldhen_cheat_settings_titleid_off\" title=\"Off\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_cheat_settings_titleid_titleid\" title=\"Only TitleId\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_ch"
    "eat_settings_titleid_appver\" title=\"Only AppVer\" value=\"2\"/>\r\n        <list_item id=\"id_goldhen_cheat_settings_titleid_titleid_appver\" title=\"TitleId &amp; AppVer\" value=\"3\"/>\r\n      </list>\r\n\r\n      "
    "<button id=\"id_goldhen_cheat_download\" title=\"Update cheat archive\" second_title=\"An internet connection may be needed for this feature.\"/>\r\n      <list id=\"id_goldhen_cheat_download_settings_source\" "
    "title=\"Cheat source\" description=\"Net: Install from Github.&#13;Usb: Install from usb:/UPDATE/cheats.zip.&#13;Hdd: Install from /user/data/GoldHEN/UPDATE/cheats.zip.\" left_margin=\"94\">\r\n        <list_"
    "item id=\"id_goldhen_cheat_download_settings_source_github\" title=\"Net [ GitHub ]\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_cheat_download_settings_source_usb\" title=\"Usb [ usb:/UPDATE/cheats.zip"
    " ]\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_cheat_download_settings_source_hdd\" title=\"Hdd [ hdd:.../UPDATE/cheats.zip ]\" value=\"2\"/>\r\n      </list>\r\n      <list id=\"id_goldhen_cheat_download_s"
    "ettings_selection\" title=\"Cheat selection\" description=\"Installed Games: Install cheats for games you have installed.&#13;All Cheats: Install all cheats in repository.\" left_margin=\"94\">\r\n        <lis"
    "t_item id=\"id_goldhen_cheat_download_settings_selection_installed\" title=\"Installed Games\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_cheat_download_settings_selection_all\" title=\"All Cheats\" valu"
    "e=\"1\"/>\r\n      </list>\r\n\r\n    </setting_list>\r\n\r\n    <setting_list id=\"id_goldhen_plugin_settings\" title=\"Plugin Settings\">\r\n      <toggle_switch id=\"id_goldhen_plugin_settings_enabled\" title=\"Enable "
    "Plugins Loader\" second_title=\"Enable plugins based on the plugins.ini file. You can't change this value while a game is running.\" value=\"0\"/>\r\n      <toggle_switch id=\"id_goldhen_aio_fix_plugin_settin"
    "gs_enabled\" title=\"Enable AIO Fix Plugin\" second_title=\"Enable plugin for all games without plugins.ini. You can't change this value while a game is running.\" value=\"0\" third_title=\"It can be activate"
    "d only if the aio fix plugin is installed at /data/GoldHEN/plugins/aio_fix_505.prx.\"/>\r\n      <toggle_switch id=\"id_goldhen_game_patch_plugin_settings_enabled\" title=\"Enable Game Patch Plugin\" second_"
    "title=\"Enable plugin for all games without plugins.ini. You can't change this value while a game is running.\" value=\"0\" third_title=\"It can be activated only if the patch plugin is installed at /data/"
    "GoldHEN/plugins/game_patch.prx.\"/>\r\n\r\n      <button id=\"id_goldhen_patch_download\" title=\"Update patch archive\" second_title=\"An internet connection may be needed for this feature.\"/>\r\n      <list id="
    "\"id_goldhen_patch_download_settings_source\" title=\"Patch source\" description=\"Net: Install from illusion's Github.&#13;Usb: Install from usb:/UPDATE/plugins.zip.&#13;Hdd: Install from /user/data/GoldH"
    "EN/UPDATE/plugins.zip.\" left_margin=\"94\">\r\n        <list_item id=\"id_goldhen_patch_download_settings_source_github\" title=\"Net [ GitHub ]\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_patch_download"
    "_settings_source_usb\" title=\"Usb [ usb:/UPDATE/patch1.zip ]\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_patch_download_settings_source_hdd\" title=\"Hdd [ hdd:.../UPDATE/patch1.zip ]\" value=\"2\"/>\r\n "
    "     </list>\r\n      <list id=\"id_goldhen_patch_download_settings_selection\" title=\"Patch selection\" description=\"Installed Games: Install cheats for games you have installed.&#13;All Cheats: Install a"
    "ll cheats in repository.\" left_margin=\"94\">\r\n        <list_item id=\"id_goldhen_patch_download_settings_selection_installed\" title=\"Installed Games\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_patch"
    "_download_settings_selection_all\" title=\"All Patches\" value=\"1\"/>\r\n      </list>\r\n\r\n      <button id=\"id_goldhen_plugin_download\" title=\"Update plugin archive\" second_title=\"An internet connection may"
    " be needed for this feature.\"/>\r\n      <list id=\"id_goldhen_plugin_download_settings_source\" title=\"Plugin source\" description=\"Net: Install from Github.&#13;Usb: Install from usb:/UPDATE/plugins.zip."
    "&#13;Hdd: Install from /user/data/GoldHEN/UPDATE/plugins.zip.\" left_margin=\"94\">\r\n        <list_item id=\"id_goldhen_plugin_download_settings_source_github\" title=\"Net [ GitHub ]\" value=\"0\"/>\r\n        "
    "<list_item id=\"id_goldhen_plugin_download_settings_source_usb\" title=\"Usb [ usb:/UPDATE/plugins.zip ]\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_plugin_download_settings_source_hdd\" title=\"Hdd [ "
    "hdd:.../UPDATE/plugins.zip ]\" value=\"2\"/>\r\n      </list>\r\n    </setting_list>\r\n\r\n    <setting_list id=\"id_goldhen_game_overlay\" title=\"Game Overlay Settings\">\r\n      <toggle_switch id=\"id_goldhen_game"
    "_overlay_fps_enabled\" title=\"Enable FPS Counter\" description=\"You can't change this value while a game is running.\" value=\"0\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_fps_visible\" title=\"Sh"
    "ow FPS Counter\" value=\"0\" left_margin=\"94\"/>\r\n\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sysinfos_enabled\" title=\"Enable SysInfo\" description=\"You can't change this value while a game is runni"
    "ng.\" value=\"0\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sysinfos_ram_usage_visible\" title=\"Show RAM Usage\" value=\"1\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sys"
    "infos_vram_usage_visible\" title=\"Show VRAM Usage\" value=\"1\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sysinfos_cpu_usage_visible\" title=\"Show CPU Usage\" value=\"1\" left_margi"
    "n=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sysinfos_cpu_usage_avg_visible\" title=\"Show CPU Usage Average\" value=\"1\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay"
    "_sysinfos_cpu_temp_visible\" title=\"Show CPU Temp\" value=\"1\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sysinfos_soc_temp_visible\" title=\"Show SOC Temp\" value=\"1\" left_margin="
    "\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sysinfos_thread_count_visible\" title=\"Show Thread Count\" value=\"1\" left_margin=\"94\"/>\r\n      <toggle_switch id=\"id_goldhen_game_overlay_sysinfo"
    "s_ip_address_visible\" title=\"Show IP Address\" value=\"1\" left_margin=\"94\"/>\r\n\r\n      <list id=\"id_goldhen_game_overlay_text_position\" title=\"Text Position\">\r\n        <list_item id=\"id_goldhen_game_over"
    "lay_text_position_left\" title=\"Left\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_text_position_right\" title=\"Right\" value=\"1\"/>\r\n      </list>\r\n\r\n      <list id=\"id_goldhen_game_overla"
    "y_text_colour\" title=\"Text Color\">\r\n        <list_item id=\"id_goldhen_game_overlay_text_colour_white\" title=\"White\" value=\"0\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_text_colour_green\" title"
    "=\"Green\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_text_colour_red\" title=\"Red\" value=\"2\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_text_colour_yellow\" title=\"Yellow\" value=\""
    "3\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_text_colour_magenta\" title=\"Magenta\" value=\"4\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_text_colour_cyan\" title=\"Cyan\" value=\"5\"/>\r\n      "
    "</list>\r\n\r\n      <toggle_switch id=\"id_goldhen_game_overlay_scanlines_enabled\" title=\"Enable Scanlines\" value=\"0\" />\r\n      <list id=\"id_goldhen_game_overlay_scanlines_opacity\" title=\"Opacity Level\" l"
    "eft_margin=\"94\">\r\n        <list_item id=\"id_goldhen_game_overlay_scanlines_opacity_1\" title=\"1\" value=\"1\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_scanlines_opacity_2\" title=\"2\" value=\"2\"/>\r\n"
    "        <list_item id=\"id_goldhen_game_overlay_scanlines_opacity_3\" title=\"3\" value=\"3\"/>\r\n        <list_item id=\"id_goldhen_game_overlay_scanlines_opacity_4\" title=\"4\" value=\"4\"/>\r\n        <list_item"
    " id=\"id_goldhen_game_overlay_scanlines_opacity_5\" title=\"5\" value=\"5\"/>\r\n      </list>\r\n    </setting_list>\r\n\r\n    <setting_list id=\"id_goldhen_servers_settings\" title=\"Servers Settings\">\r\n      <togg"
    "le_switch id=\"id_goldhen_toggle_ftp\" title=\"Enable FTP Server\" second_title=\"Listening on port 2121. Autodecrypt enabled. MTRW to enable R/W on system partitions.\" third_title=\"Credits: xerpi, idc, vo"
    "rtex, Al-Azif &amp; hippie68\" value=\"0\"/>\r\n      <toggle_switch id=\"id_goldhen_toggle_binloader\" title=\"Enable PayLoader Server\" second_title=\"Listening on port 9090. Supporting ELF and BIN formats vi"
    "a TCP and HTTP POST.\" value=\"0\"/>\r\n\r\n      <setting_list id=\"id_goldhen_klog_settings\" title=\"KLog Server\">\r\n        <toggle_switch id=\"id_goldhen_toggle_klog_tty_redirect\" title=\"Enable TTY Redirect\""
    " second_title=\"Shows user prints in klog. It could give some lag in case of excess of logs.\" value=\"0\"/>\r\n      </setting_list>\r\n    </setting_list>\r\n\r\n  <setting_list id=\"id_goldhen_utils\" title=\"Uti"
    "lities\">\r\n    <setting_list id=\"id_goldhen_utils_payloader\" title=\"PayLoader\">\r\n      <setting_list id=\"id_goldhen_utils_payloader_launchpad\" title=\"LaunchPad\"  second_title=\"List of payloads to be la"
    "unched manually. Paths: /data/payloads /usbX/payloads /disc/payloads /disc/extras/payloads\"></setting_list>\r\n      <setting_list id=\"id_goldhen_utils_payloader_autorun\" title=\"AutoRun Queue\"  second_t"
    "itle=\"List of payloads to be launched automatically. Hold L1 during boot to skip.\"></setting_list>\r\n    </setting_list>\r\n  </setting_list>\r\n\r\n    <setting_list id=\"id_goldhen_settings\" title=\"Settings"
    "\">\r\n      <toggle_switch id=\"id_goldhen_toggle_app_suspend\" title=\"Enable Rest Mode Support\" description=\"Keeps GoldHEN alive after suspension\" key=\"/SYSTEM/POWER/suspend_to_ram\"/>\r\n      <toggle_swit"
    "ch id=\"id_goldhen_toggle_pppoe_patch\" title=\"Enable PPPoE Patch\" second_title=\"Prevents the console from being exploited again via PPPwn, which could cause instability.\" value=\"0\"/>\r\n      <toggle_swi"
    "tch id=\"id_goldhen_toggle_bdapp_autokill\" title=\"Enable BD-App AutoKill\" second_title=\"BD-App will be automatically closed whenever GoldHEN is started.\" value=\"0\"/>\r\n      <toggle_switch id=\"id_goldhe"
    "n_toggle_bdapp_autoeject\" title=\"Enable AutoEject\" second_title=\"BD will be automatically ejected whenever GoldHEN is started.\" value=\"0\" left_margin=\"94\"/>\r\n      <setting_list id=\"id_goldhen_datetim"
    "e_settings\" title=\"Date and Time\">\r\n        <button id=\"id_goldhen_datetime_update\" title=\"Update Date and Time\" second_title=\"An internet connection may be needed for this feature.\"/>\r\n        <list "
    "id=\"id_goldhen_datetime_update_source\" title=\"Update Source\" left_margin=\"94\">\r\n          <list_item id=\"id_goldhen_datetime_update_source_net\" title=\"Net [ time1.google.com ]\" value=\"0\"/>\r\n          "
    "<list_item id=\"id_goldhen_datetime_update_source_fakedate\" title=\"Fake Date [ 2025/01/01 ]\" value=\"1\"/>\r\n        </list>\r\n        <toggle_switch id=\"id_goldhen_datetime_autoupdate\" title=\"Enable Auto "
    "Update Date and Time\" second_title=\"An update will be made at every GoldHEN startup.\" value=\"0\"/>\r\n      </setting_list>\r\n    </setting_list>\r\n\r\n  </setting_list>\r\n\r\n</system_settings>\r\n";
_Static_assert(sizeof(core_menu_xml) == 0x36A3, "menu xml len");

/* Overlay XML (core+0x45C80, 256 B) */
const char core_cheat_overlay_xml[] __attribute__((section(".visual.core.45c80"))) =
    "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n<system_settings version=\"1.0\" plugin=\"settings_root_plugin\">\r\n    <setting_list id=\"id_goldhen_cheat_menu\" title=\"Entry4 Cheat Menu\">\r\n        <spacer id=\"s1\""
    " height=\"10\" />\r\n    </setting_list>\r\n</system_settings>";
_Static_assert(sizeof(core_cheat_overlay_xml) == 0x101, "core_cheat_overlay_xml len");

/* Overlay XML (core+0x45D90, 258 B) */
const char core_patch_overlay_xml[] __attribute__((section(".visual.core.45d90"))) =
    "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n<system_settings version=\"1.0\" plugin=\"settings_root_plugin\">\r\n    <setting_list id=\"id_goldhen_patch_menu\" title=\"Entry4 Patch Menu\">\r\n        <spacer id=\"s1\""
    " height=\"10\" />\r\n    </setting_list>\r\n</system_settings>\r\n";
_Static_assert(sizeof(core_patch_overlay_xml) == 0x103, "core_patch_overlay_xml len");

