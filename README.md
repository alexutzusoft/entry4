# Entry4 PS4 Jailbreak (**13.02–14.02**)

Browser exploit host for PS4 firmware 13.02, 13.04, 13.50, 13.52, 14.00, and 14.02. Serve this folder, open it in the PS4 browser, select firmware and payload, press launch.

> Tested on all supported firmwares. 14.02 is the developer's (`alexutzusoft`) daily driver and proving reliable — roughly 9/10 attempts succeed. The most common failure is a kernel panic, which is harmless unless it hits during an app update or install (that can corrupt data, but it can be fixed). Everything runs in RAM and clears on reboot — cold boot before running 14.00/14.02.

## Install

No setup needed — open `http://e4.alexutzu.pro` (mirror: `http://entry4.alexutzu.pro`) in the PS4 browser.

To self-host instead, serve this folder from a PC on the same network:

```powershell
cd Entry4
python -m http.server 8000
```

Then open `http://<PC_IP>:8000/` in the PS4 browser. Any static file host works instead of a PC. Self-hosting keeps the `/t` log posts (see Privacy) on your own machine.

Preselect a chain with `?firmware=14.00` / `?firmware=14.02`, or switch with `[version]` in the header (`13.02-13.52` → `14.00` → `14.02`). The page auto-detects from the PS4 user agent; a mismatch disables launch.

## Usage

- `[payload]`: `entry4` / `goldhen` on 13.02–13.52; `Entry4D` / `entry4` / `goldhen v2.4b18.14` on 14.02; locked to the bundled HEN on 14.00.
- `launch`: waits ~2 seconds, then runs the chain.
- `terminal (n)`: on-page log (`PROOF-OK` / `PROOF-FAIL` lines).

If a run fails, restart the browser and retry; if it keeps failing, fully power off (not Rest Mode) and try again.

## Privacy

No external telemetry. The 13.xx/14.00 chains `POST` run diagnostics to `/t` on the hosting server (disabled by default on 14.00 unless `?telemetry=1`). Nothing else leaves the console.

## Files

| Path | Description |
|---|---|
| `index.html` | Entry page |
| `src/web/` | Host UI |
| `src/firmware/13xx/` | 13.02–13.52 chain (`patches/`, `payloads/entry4.bin` + `goldhen.bin`) |
| `src/firmware/1400/` | 14.00 chain (`patches/1400.bin`, `payloads/hen.bin`) |
| `src/firmware/1402/` | 14.02 Afterglow chain (`payloads/entry4.bin`, `entry4d.bin`, `goldhen_v2.4b18.14.bin`) |
| `src/payload/` | Rebuildable 14.02 Entry4 visuals; see `src/payload/README.md` |
| `src/shared/` | Shared `int64.js` |
| `assets/` | Styles and icons |

## Build from source

No build — static files, served as-is. Only the 14.02 payload visuals need a toolchain (LLVM `clang` + Python 3):

```bat
cd src\payload
python build.py
:: out\entry4.bin replaces src\firmware\1402\payloads\entry4.bin
```

## Credits & Licenses

- 14.02 Afterglow chain from [WebKitty](https://github.com/ArabPixel/WebKitty) (Afterglow by **m0zz** / **well0nez**): `afterglow.js`, `core.js`, `memory.js` stay **AGPL-3.0-or-later** — see `src/firmware/1402/NOTICE-AGPL.md`.
- 14.00 chain from [sionga/ps4-14.00-jb](https://github.com/sionga/ps4-14.00-jb) (MIT © 2026 raw13g).
- HEN / GoldHEN payloads by **SiSTR0** (upstream licenses apply to the blobs).
- Project code is released under the [MIT License](LICENSE).
