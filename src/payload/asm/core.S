/* Entry4 decrypted core (core_plain, 640536 B, 0x9C618).
 *
 * Pure assembly from Entry4, not yet decompiled to C.
 * The core is stored encrypted+compressed in the file
 * (file+0x78A0..0x411A4, ChaCha20-IETF ctr=1, key =
 * SHA256(stub[0:0x7894]) ^ KDF(tail tables), nonce tail+0x48DC0).
 * See ../tools/enc.c + build.py for the exact crypto.
 *
 * After decrypt + zlib decompress, core_plain is a flat executable
 * image (mapped RWX by the loader). Visuals live inside it:
 *
 *   0x39178 (13984 B)  main Settings menu XML (see ../visuals/menu.c)
 *   0x45C80 (256 B)    cheat overlay XML (Entry4 Cheat Menu)
 *   0x45D90 (256 B)    patch overlay XML (Entry4 Patch Menu)
 *   0x84CC7..          cheat updater + OSD (see ../visuals/cheat.c)
 *   0x854D7..          overlay FPS/sysinfo (see ../visuals/overlay.c)
 *   0x87ACA..          plugin updater/loader (see ../visuals/cheat.c)
 *   0x87873 (27 B)     home icon path file://user/data/entry4.png
 *   0x93252..          FTP banners (see ../visuals/servers.c)
 *   0x98AFC..          BinLoader/PayLoader (see ../visuals/servers.c)
 *   0x9AC46..          boot notices: Entry4 loaded / by Alexutzu / GoldHEN...
 *                      (see ../visuals/boot.c)
 *   0x9AEBF            [+] icon0_png_path format (see ../visuals/icons.c)
 *
 * Everything else in core_plain is non-visual code/data and stays
 * as pure assembly blobs (original Entry4 bytes). build.py splits
 * core_plain into non-visual chunks (this directory) + visual
 * sections (../visuals/*.c) and re-links them to a byte-identical
 * core_plain when visuals are unchanged.
 *
 * This file is the anchor for the non-visual chunks. The actual
 * chunk objects are generated at build time from the reference
 * binary (decrypt -> split), so no 640 KB blob is stored in git.
 * See build.py: split_core() + CORE_CHUNKS.
 */

    .section .core.note,"a",@progbits
    .asciz "Entry4 core_plain non-visuals: see build.py CORE_CHUNKS"
