/* Entry4 tail resources (file+0x411A4..0x48F18).
 *
 * Pure assembly from Entry4, not yet decompiled to C.
 * Layout (SHIFT=0 in the reference build):
 *   0x411A4..0x43600  zeroed icon block (GoldHEN icons removed, 0x245C zeros)
 *   0x43600..0x486FB  zeros (wiped GoldHEN resource area)
 *   0x486FC          cfg_len u32 LE (0x39904)
 *   0x48700..0x48833  308 B high-entropy blob (KDF/SHA tables, identical in GoldHEN)
 *   0x48834..0x48C02  banner (VISUALS: see ../visuals/banner.c, patched at build)
 *   0x48C03..0x48D37  installing notice + binary index tables + already notice + brand
 *                      (VISUALS: see ../visuals/tail_notices.c)
 *   0x48D40..0x48DCB  KDF tables + HMAC + nonce (crypto, do NOT edit)
 *   0x48DCC..0x48F17  INTERP + ELF metadata + build hash (toolchain residue)
 *
 * This file provides the NON-VISUAL tail bytes as blobs.
 * Visual ranges are excluded here and supplied by visuals C
 * sections (.visual.tail.*) so `build.py` can patch them.
 * The section layout below mirrors the file layout 1:1.
 */

    .section .tail.zeroIcons,"a",@progbits
    .global tail_zero_icons
tail_zero_icons:
    /* file+0x411A4, 0x245C zeros (removed icons) */
    .incbin "../../firmware/1402/payloads/entry4.bin", 0x411A4, 0x245C

    .section .tail.zeroGap,"a",@progbits
    .global tail_zero_gap
tail_zero_gap:
    /* file+0x43600..0x486FB zeros */
    .incbin "../../firmware/1402/payloads/entry4.bin", 0x43600, 0x50FC

    .section .tail.cfg,"a",@progbits
    .global tail_cfg_len
tail_cfg_len:
    /* file+0x486FC u32 cfg_len + 0x48700..0x48833 blob (308+4 B) */
    .incbin "../../firmware/1402/payloads/entry4.bin", 0x486FC, 0x138

    /* NOTE: 0x48834..0x48C02 (banner) + 0x48C03/0x48D13/0x48D30 (notices/brand)
     * are owned by ../visuals/banner.c + ../visuals/tail_notices.c.
     * They are intentionally NOT incbin'd here to avoid duplicate symbols. */

    .section .tail.tables,"a",@progbits
    .global tail_tables
tail_tables:
    /* file+0x48C2D..0x48D12 binary index tables (230 B, not text) */
    .incbin "../../firmware/1402/payloads/entry4.bin", 0x48C2D, 0xE6

    .section .tail.kdf,"a",@progbits
    .global tail_kdf
tail_kdf:
    /* file+0x48D40..0x48F18 KDF + HMAC + nonce + INTERP + ELF meta + hash */
    .incbin "../../firmware/1402/payloads/entry4.bin", 0x48D40, 0x1D8
