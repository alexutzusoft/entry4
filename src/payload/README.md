# Entry4 payload source (1402)

Rebuilds `src/firmware/1402/payloads/entry4.bin` (298776 B, GoldHEN fork)
from editable C visuals + pure-assembly non-visuals. Build is **core-exact**:
with unmodified `visuals/`, `out/entry4.bin` is byte-identical to the
pre-built Entry4 (`SHA256 89a20f33cdfb7f0fbdb62937a7360b5c3964961e263eeb5749c646921eb1659f`).

## Layout

| Path | What |
|---|---|
| `visuals/` | **All visuals in C** — banner, notices, menu XML, overlay, servers, cheat/patch/plugin, icons, branding, embedded PNGs. Edit these to rebrand. |
| `asm/` | **Everything else as pure Assembly** — `stub.S` (loader 0x0-0x78A0), `tail.S` (non-visual tail blobs), `core.S` (decrypted-core anchor + visual map). Original Entry4 bytes via `.incbin`, not yet decompiled to C. |
| `include/` | `types.h` (freestanding), `visuals.h` (all visual declarations). |
| `tools/enc.c` | Exact Entry4 crypto (ChaCha20-IETF ctr=1 + custom HMAC + cfg_len). |
| `data/` | `menu.xml` (13986 B, same as `visuals/menu.c`), `banner.txt`, `VISUALS.md` (offset inventory). |
| `build.py` | Rebuild pipeline (decrypt → patch visuals → zlib-9 → re-encrypt → HMAC). |
| `out/` | Build output (`out/entry4.bin`, gitignored). |

Container (SHIFT=0): stub `0x0-0x78A0`, encrypted core `0x78A0-0x411A4` (`cfg_len 0x39904`), zeroed icons `0x411A4-0x43600`, tail `0x43600-0x48F18` (banner/notices/KDF/nonce/HMAC).
Key = `SHA256(stub[0:0x7894]) ^ KDF(tail 0x48D40/0x48D60/0x48D80)`, nonce `0x48DC0` (12 B), HMAC at `0x48DA0`. Core plain 640536 B, zlib-9 compressed.

## Build

Requires: `C:\Program Files\LLVM\bin` (`clang.exe`, `llvm-objcopy.exe`, `llvm-objdump.exe`) + Python 3 + zlib (stdlib).

```bat
cd src\payload
python build.py
:: out\entry4.bin  (core-exact if visuals unchanged)
```

`python build.py --check-only` exits 0 iff byte-identical.

## Modify visuals

All visuals are `const ... __attribute__((section(".visual.*")))` with `_Static_assert` lengths.

1. Edit e.g. `visuals/menu.c` (`Entry4` → `MyHEN`, same 6 chars), `visuals/banner.c`, `visuals/boot.c`, `visuals/overlay.c`, `visuals/servers.c`, `visuals/cheat.c`, `visuals/icons.c`, `visuals/branding.c`, `visuals/media.c` (PNG bytes).
2. **Keep lengths identical** (pad with spaces). Compile enforces via `_Static_assert`; `build.py` enforces same `strlen`/blob len.
3. Tail edits (banner/notices) patch the file directly — no recompress.
4. Core edits re-zlib (level 9) + re-encrypt; `cfg_len` may grow/shrink within the zero slack (`0x78A0+cfg ≤ 0x486FC`, 30 KB). Larger changes need SHIFT-moving tail (future work, see `tools/enc.c`).
5. Rebuild: `python build.py` → `out/entry4.bin` (working, HMAC-valid, new SHA).

To use: copy `out/entry4.bin` over `src/firmware/1402/payloads/entry4.bin` (back up the original) or point `runner.js` at it; reload the exploit page.

## Verify

- `python build.py` (unchanged) → `PASS: core-exact`, SHA matches reference.
- `tools/enc` `--decrypt` + Python `decrypt_core` round-trip == `core_plain`.
- `gate_print` slot `0x49170` (runtime BSS) + `kStateTab` targets unchanged.

Non-visuals (`asm/*.S`) are byte blobs for now; visual ownership is documented in `data/VISUALS.md`. Future work: decompile `asm/` to C function-by-function, keeping `build.py` green at each step.
