# Entry4 visuals inventory (1402, `src/firmware/1402/payloads/entry4.bin`)

Reference: 298776 B (`0x48F18`), SHA256 `89a20f33cdfb7f0fbdb62937a7360b5c3964961e263eeb5749c646921eb1659f`.
All offsets below verified against the reference. Lengths exclude NUL unless noted.

## Tail (unencrypted file, `asm/tail.S` + `visuals/banner.c` + `visuals/tail_notices.c`)

| File off | Len | C symbol | Printed by | Notes |
|---|---|---|---|---|
| `0x48834` | 73 | `banner_ln01` | `sub_1418` #1 | `~~~~...` border |
| `0x4887E` | 67 | `banner_ln02` | #2 | GoldHEN logo 1/6 |
| `0x488C2` | 68 | `banner_ln03` | #3 | logo 2/6 |
| `0x48907` | 69 | `banner_ln04` | #4 | logo 3/6 |
| `0x4894D` | 70 | `banner_ln05` | #5 | logo 4/6 |
| `0x48994` | 70 | `banner_ln06` | #6 | logo 5/6 |
| `0x489DB` | 70 | `banner_ln07` | #7 | logo 6/6, ends `\n\n` |
| `0x48A20` | 1 | `banner_ln00` (alias) | #0 first | `\n`, shares NUL at `0x48A21` with `ln07` |
| `0x48A22` | 39 | `banner_ln08` | #8 | `Coded By` |
| `0x48A4A` | 60 | `banner_ln09` | #9 | SiSTRo logo 1/5 |
| `0x48A87` | 61 | `banner_ln10` | #10 | 2/5 |
| `0x48AC5` | 62 | `banner_ln11` | #11 | 3/5 |
| `0x48B04` | 63 | `banner_ln12` | #12 | 4/5 |
| `0x48B44` | 63 | `banner_ln13` | #13 | 5/5 |
| `0x48B84` | 51 | `banner_ln14` | #14 | tail |
| `0x48BB8` | 74 | `banner_ln15` | #15 tail-jmp | `~~~~...` + blank |
| `0x48C03` | 42 | `res_notice_installing` | `sub_1620` via print gate | `[GoldHEN] Installing GoldHEN in Kernel...\n` |
| `0x48D13` | 26 | `res_notice_already` | `sub_1653` via `sub_82A` (ops 4/2) | `GoldHEN is already loaded!` |
| `0x48D30` | 7 | `res_brand_short` | `sub_1724` crypto (ECX=8), NOT printed | `GoldHEN` magic |
| `0x411A4..0x43600` | `0x245C` zeros | — | — | removed GoldHEN menu icons (all zeros) |
| `0x48DCC` | 27 | — | unreferenced | `/lib64/ld-linux-x86-64.so.2` toolchain residue |
| `0x48F08` | 16 | — | unreferenced | `4076f0d7c64b6df0` build hash, runs to EOF |

Binary (NOT visuals): `0x48C2D..0x48D12` index tables (u8/u16 + 19 B permutation), `0x48700..0x48833` KDF blob, `0x48D40..0x48DCC` KDF/HMAC/nonce.

## Core (decrypted `core_plain`, 640536 B, `visuals/*.c`)

Menu XML: `0x39178` (13986 B, `visuals/menu.c` → `data/menu.xml`), title `Entry4` (`0x3920E`), icon `file://user/data/entry4.png` (`0x39245`).
Cheat/patch overlay XMLs: `0x45C80` (256 B, `Entry4 Cheat Menu`), `0x45D90` (258 B, `Entry4 Patch Menu`).

Boot (`visuals/boot.c`): `0x9AC46` FakePKG, `0x9AC76` FakeSelf, `0x9AC9B` `[GoldHEN] %s`, `0x9ACA9` `GoldHEN`, `0x9ACB1` `Entry4 loaded\nby Alexutzu` (25 B), `0x9ACDC` All done, `0x9ACF1` Testkit, `0x9AD1F` Kernel, `0x9AD69` SceShellCore, `0x9ADB7` SceShellUI, `0x9ADF3` SceRemotePlay.

Branding (`visuals/branding.c`): `0x887EC` TopMenu `Entry4\xa0\xa0` (10 B), `0x88516`/`0x885DA` `Entry4` (6 B each), `0x8820B` `Entry4 Cheat Menu` (17 B), `0x88652` `Entry4 Patch Menu` (17 B).

Overlay (`visuals/overlay.c`): FPS server/thread/client (`0x854D7`/`0x854F2`/`0x94D76`), `FPS: %.2lf` (`0x855C8`), IP/Thread/SOC/CPU formats, CPU avg (Neo), CPU full, VRAM shared format.

Servers (`visuals/servers.c`): FTP `220 GoldHEN FTP server v2.2` (`0x93252`), in-use/listening/no-IP/shutdown, `X-Powered-By: GoldHEN by SiSTR0` (`0x98AFC`), payloader started/received/busy/ok/fail, PayLoader/Klog/AutoRun toasts.

Cheat/patch/plugin (`visuals/cheat.c`): update threads/fail/ok, Prev/Next, not-found, `Cheats by %s`, template, patch/plugin equivalents, `Loaded %u plugin(s)`, auto-apply, date/time.

Icons (`visuals/icons.c` + `visuals/media.c`): `0x87873` `file://user/data/entry4.png` (27 B home icon), `0x9AEBF` icon0 format, `0x85818` scanlines path, widget keys, `0x6A154` 192×192 Entry4 PNG (2158 B RGBA, remainder zeros to `0x6D2FC`), `0x828F4` scanline texture PNG (1171 B).

See `data/menu.xml`, `data/banner.txt`, `include/visuals.h` for the editable sources.
