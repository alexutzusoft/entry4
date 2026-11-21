/* Entry4 loader stub (file+0x0..0x78A0, 30880 B).
 *
 * Pure assembly from Entry4, not yet decompiled to C.
 * Byte-exact blob: assembled output must match the reference
 * src/firmware/1402/payloads/entry4.bin[0:0x78A0].
 *
 * The stub resolves libkernel via LSTAR, installs the syscall gate,
 * runs KDF + ChaCha20 + inflate (see ../tools/enc.c for the exact
 * crypto), then jumps into the decrypted core.
 *
 * Visuals are NOT here: banner/notices live in tail (see tail.S +
 * ../visuals/banner.c, ../visuals/tail_notices.c).
 */

    .section .stub.head,"ax",@progbits
    .global stub_head
stub_head:
    .incbin "../../firmware/1402/payloads/entry4.bin", 0, 0x78A0
