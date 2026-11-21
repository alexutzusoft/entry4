/* enc.c -- Standalone Entry4 packager & verifier (no external dependencies).
 *
 * Implements the exact Entry4 14.02 stub crypto/container format:
 *   1. Zlib compress core_plain (or ingest precompressed --zlib stream) with
 *      RFC 1950/1951 empty-block padding if 3*cfg_len < plain_len + bss_size.
 *   2. Compute key1 = SHA256(stub[0x0000..0x7894]).
 *   3. Derive 32-byte key from key1 ^ tabA_bytes ^ tabB ^ tabC (@ 0x48D40+shift).
 *   4. ChaCha20-IETF encrypt (ctr=1) zlib stream at [0x78A0..0x78A0+cfg_len).
 *   5. Compute sub_3da/sub_436 non-standard zero-padded HMAC over
 *      (nonce[0..12] || ciphertext[0..cfg_len]) and write k_check32 @ 0x48DA0+shift.
 *   6. Write cfg_len @ 0x486FC+shift and ensure trailing size covers .stub.bss.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/* ---- File layout base constants (before SHIFT) ---- */
#define STUB_HASH_END 0x7894u
#define CORE_OFF      0x78A0u
#define OFF_CFG_LEN   0x486FCu
#define OFF_BRAND     0x48D30u
#define OFF_TABA      0x48D40u
#define OFF_TABC      0x48D60u
#define OFF_TABB      0x48D80u
#define OFF_CHECK32   0x48DA0u
#define OFF_NONCE     0x48DC0u
#define OFF_BSS_END   0x49200u

static u32 le32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}
static void wr_le32(u8 *p, u32 v) {
    p[0] = (u8)v; p[1] = (u8)(v >> 8); p[2] = (u8)(v >> 16); p[3] = (u8)(v >> 24);
}
static void wr_be32(u8 *p, u32 v) {
    p[0] = (u8)(v >> 24); p[1] = (u8)(v >> 16); p[2] = (u8)(v >> 8); p[3] = (u8)v;
}
static u32 rotr32(u32 x, u32 n) { return (x >> n) | (x << (32 - n)); }
static u32 rotl32(u32 x, u32 n) { return (x << n) | (x >> (32 - n)); }

/* ---- SHA-256 ---- */
static const u32 SHA_K[64] = {
    0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
    0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
    0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
    0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
    0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
    0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
    0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
    0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u
};

typedef struct {
    u32 h[8];
    u64 total;
    u8 buf[64];
    size_t idx;
} Sha256;

static void sha_init(Sha256 *s) {
    static const u32 iv[8] = {
        0x6a09e667u,0xbb67ae85u,0x3c6ef372u,0xa54ff53au,
        0x510e527fu,0x9b05688cu,0x1f83d9abu,0x5be0cd19u
    };
    memcpy(s->h, iv, sizeof(iv));
    s->total = 0;
    s->idx = 0;
}

static void sha_block(Sha256 *s, const u8 *b) {
    u32 w[64], a, b0, c, d, e, f, g, h, t1, t2;
    for (int i = 0; i < 16; i++)
        w[i] = ((u32)b[4*i]<<24)|((u32)b[4*i+1]<<16)|((u32)b[4*i+2]<<8)|(u32)b[4*i+3];
    for (int i = 16; i < 64; i++) {
        u32 s0 = rotr32(w[i-15],7) ^ rotr32(w[i-15],18) ^ (w[i-15]>>3);
        u32 s1 = rotr32(w[i-2],17) ^ rotr32(w[i-2],19) ^ (w[i-2]>>10);
        w[i] = w[i-16] + s0 + w[i-7] + s1;
    }
    a=s->h[0]; b0=s->h[1]; c=s->h[2]; d=s->h[3];
    e=s->h[4]; f=s->h[5]; g=s->h[6]; h=s->h[7];
    for (int i = 0; i < 64; i++) {
        u32 S1 = rotr32(e,6) ^ rotr32(e,11) ^ rotr32(e,25);
        u32 ch = (e & f) ^ ((~e) & g);
        t1 = h + S1 + ch + SHA_K[i] + w[i];
        u32 S0 = rotr32(a,2) ^ rotr32(a,13) ^ rotr32(a,22);
        u32 maj = (a & b0) ^ (a & c) ^ (b0 & c);
        t2 = S0 + maj;
        h=g; g=f; f=e; e=d+t1; d=c; c=b0; b0=a; a=t1+t2;
    }
    s->h[0]+=a; s->h[1]+=b0; s->h[2]+=c; s->h[3]+=d;
    s->h[4]+=e; s->h[5]+=f;  s->h[6]+=g; s->h[7]+=h;
}

static void sha_update(Sha256 *s, const u8 *d, size_t len) {
    s->total += len;
    while (len > 0) {
        size_t take = 64 - s->idx;
        if (take > len) take = len;
        memcpy(s->buf + s->idx, d, take);
        s->idx += take; d += take; len -= take;
        if (s->idx == 64) { sha_block(s, s->buf); s->idx = 0; }
    }
}

static void sha_final(Sha256 *s, u8 out[32]) {
    u64 bits = s->total * 8;
    u8 pad = 0x80;
    sha_update(s, &pad, 1);
    pad = 0;
    while (s->idx != 56) sha_update(s, &pad, 1);
    u8 len8[8];
    wr_be32(len8, (u32)(bits >> 32));
    wr_be32(len8 + 4, (u32)bits);
    sha_update(s, len8, 8);
    for (int i = 0; i < 8; i++) wr_be32(out + 4*i, s->h[i]);
}

/* Entry4 custom MAC (sub_3da + sub_436 zero-padded 64B pads) */
static void compute_entry4_mac(u8 out[32], const u8 key32[32], const u8 brand8[8],
                               const u8 nonce12[12], const u8 *ct, size_t ct_len) {
    Sha256 s;
    u8 hmac_key[32], ipad[64], opad[64], inner[32];

    /* sub_3da: sha256(key[0..32] || brand[0..8]) */
    sha_init(&s);
    sha_update(&s, key32, 32);
    sha_update(&s, brand8, 8);
    sha_final(&s, hmac_key);

    /* sub_436: zero-padded 64B ipad/opad */
    memset(ipad, 0, 64);
    memset(opad, 0, 64);
    for (int i = 0; i < 32; i++) {
        ipad[i] = hmac_key[i] ^ 0x36u;
        opad[i] = hmac_key[i] ^ 0x5cu;
    }
    sha_init(&s);
    sha_update(&s, ipad, 64);
    sha_update(&s, nonce12, 12);
    sha_update(&s, ct, ct_len);
    sha_final(&s, inner);

    sha_init(&s);
    sha_update(&s, opad, 64);
    sha_update(&s, inner, 32);
    sha_final(&s, out);
}

/* ---- ChaCha20-IETF ---- */
static void chacha20_crypt(const u8 key[32], const u8 nonce[12], u32 ctr, u8 *buf, size_t len) {
    u32 st[16], w[16];
    st[0]=0x61707865u; st[1]=0x3320646eu; st[2]=0x79622d32u; st[3]=0x6b206574u;
    for (int i = 0; i < 8; i++) st[4+i] = le32(key + 4*i);
    st[12] = ctr;
    for (int i = 0; i < 3; i++) st[13+i] = le32(nonce + 4*i);

    for (size_t off = 0; off < len; off += 64) {
        memcpy(w, st, sizeof(w));
        for (int r = 0; r < 10; r++) {
            #define QR(a,b,c,d) do { \
                w[a]+=w[b]; w[d]=rotl32(w[d]^w[a],16); \
                w[c]+=w[d]; w[b]=rotl32(w[b]^w[c],12); \
                w[a]+=w[b]; w[d]=rotl32(w[d]^w[a],8);  \
                w[c]+=w[d]; w[b]=rotl32(w[b]^w[c],7);  } while(0)
            QR(0,4,8,12); QR(1,5,9,13); QR(2,6,10,14); QR(3,7,11,15);
            QR(0,5,10,15); QR(1,6,11,12); QR(2,7,8,13); QR(3,4,9,14);
            #undef QR
        }
        u8 ks[64];
        for (int i = 0; i < 16; i++) wr_le32(ks + 4*i, w[i] + st[i]);
        size_t n = (len - off < 64) ? (len - off) : 64;
        for (size_t i = 0; i < n; i++) buf[off + i] ^= ks[i];
        st[12]++;
    }
}

/* ---- Standalone zlib stored-block fallback encoder (zero deps) ---- */
static u32 adler32_calc(const u8 *d, size_t len) {
    u32 a = 1, b = 0;
    for (size_t i = 0; i < len; i++) {
        a += d[i]; if (a >= 65521u) a -= 65521u;
        b += a;    if (b >= 65521u) b -= 65521u;
    }
    return (b << 16) | a;
}

static u8 *zlib_encode_stored(const u8 *in, size_t len, size_t *out_len) {
    size_t nblocks = len ? ((len + 65534u) / 65535u) : 1u;
    size_t cap = 2 + len + nblocks * 5 + 4;
    u8 *out = (u8 *)malloc(cap);
    if (!out) return NULL;
    size_t p = 0;
    out[p++] = 0x78; out[p++] = 0x01;
    size_t off = 0;
    do {
        size_t chunk = len - off;
        if (chunk > 65535u) chunk = 65535u;
        int final = (off + chunk == len);
        u16 l16 = (u16)chunk, nl16 = (u16)~l16;
        out[p++] = (u8)(final ? 1 : 0);
        out[p++] = (u8)l16; out[p++] = (u8)(l16 >> 8);
        out[p++] = (u8)nl16; out[p++] = (u8)(nl16 >> 8);
        if (chunk) memcpy(out + p, in + off, chunk);
        p += chunk; off += chunk;
    } while (off < len);
    wr_be32(out + p, adler32_calc(in, len));
    p += 4;
    *out_len = p;
    return out;
}

/* Pad a zlib stream [CMF FLG ... ADLER32] cleanly at offset 2 with 5-byte
 * empty non-final DEFLATE stored blocks (00 00 00 FF FF) so cfg_len*3 >= min_3x. */
static u8 *pad_zlib_to_3x(const u8 *z, size_t zlen, size_t min_buf, size_t *out_len) {
    size_t need_z = (min_buf + 2) / 3;
    if (zlen >= need_z) {
        u8 *copy = (u8 *)malloc(zlen);
        if (copy) memcpy(copy, z, zlen);
        *out_len = zlen;
        return copy;
    }
    size_t extra_blocks = (need_z - zlen + 4) / 5;
    size_t new_len = zlen + extra_blocks * 5;
    u8 *out = (u8 *)malloc(new_len);
    if (!out) return NULL;
    out[0] = z[0]; out[1] = z[1];
    size_t p = 2;
    for (size_t i = 0; i < extra_blocks; i++) {
        out[p++] = 0x00; out[p++] = 0x00; out[p++] = 0x00;
        out[p++] = 0xFF; out[p++] = 0xFF;
    }
    memcpy(out + p, z + 2, zlen - 2);
    *out_len = new_len;
    return out;
}

static u8 *read_file_all(const char *path, size_t *sz_out) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0) { fclose(f); return NULL; }
    u8 *buf = (u8 *)malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t n = sz ? fread(buf, 1, (size_t)sz, f) : 0;
    fclose(f);
    if (n != (size_t)sz) { free(buf); return NULL; }
    *sz_out = n;
    return buf;
}

static int write_file_all(const char *path, const u8 *buf, size_t len) {
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    size_t n = len ? fwrite(buf, 1, len, f) : 0;
    fclose(f);
    return (n == len) ? 0 : -1;
}

static void derive_key(const u8 *blob, size_t shift, u8 key_out[32]) {
    Sha256 s;
    u8 k1[32];
    sha_init(&s);
    sha_update(&s, blob, STUB_HASH_END);
    sha_final(&s, k1);
    const u8 *tabA = blob + OFF_TABA + shift;
    const u8 *tabC = blob + OFF_TABC + shift;
    const u8 *tabB = blob + OFF_TABB + shift;
    for (int i = 0; i < 32; i++) {
        u8 k2 = tabA[i] ^ tabB[i] ^ tabC[i];
        key_out[i] = k1[i] ^ k2;
    }
}

static size_t detect_shift(const u8 *blob, size_t len) {
    if (len >= OFF_BRAND + 8 && memcmp(blob + OFF_BRAND, "GoldHEN\0", 8) == 0)
        return 0;
    for (size_t off = OFF_BRAND; off + 8 <= len; off += 4) {
        if (memcmp(blob + off, "GoldHEN\0", 8) == 0)
            return off - OFF_BRAND;
    }
    return 0;
}

static int cmd_decrypt(const char *in_path, const char *out_path, long force_shift) {
    size_t len = 0;
    u8 *blob = read_file_all(in_path, &len);
    if (!blob) { fprintf(stderr, "enc: cannot read %s\n", in_path); return 1; }
    size_t shift = (force_shift >= 0) ? (size_t)force_shift : detect_shift(blob, len);
    if (len < OFF_NONCE + shift + 12) {
        fprintf(stderr, "enc: image too small for tail @ shift=0x%zx\n", shift);
        free(blob); return 1;
    }
    u32 cfg_len = le32(blob + OFF_CFG_LEN + shift);
    if ((size_t)CORE_OFF + cfg_len > OFF_CFG_LEN + shift) {
        fprintf(stderr, "enc: cfg_len 0x%x overlaps tail!\n", cfg_len);
        free(blob); return 1;
    }
    u8 key[32], mac[32];
    derive_key(blob, shift, key);
    const u8 *nonce = blob + OFF_NONCE + shift;
    compute_entry4_mac(mac, key, blob + OFF_BRAND + shift, nonce, blob + CORE_OFF, cfg_len);
    if (memcmp(mac, blob + OFF_CHECK32 + shift, 32) != 0) {
        fprintf(stderr, "enc: HMAC MISMATCH at shift=0x%zx\n", shift);
        free(blob); return 1;
    }
    u8 *pt = (u8 *)malloc(cfg_len);
    if (!pt) { free(blob); return 1; }
    memcpy(pt, blob + CORE_OFF, cfg_len);
    chacha20_crypt(key, nonce, 1, pt, cfg_len);
    if (out_path && write_file_all(out_path, pt, cfg_len) != 0) {
        fprintf(stderr, "enc: cannot write %s\n", out_path);
        free(pt); free(blob); return 1;
    }
    printf("enc: verify OK (shift=0x%zx, cfg_len=0x%x (%u B), zlib=%02x %02x, hmac=MATCH)\n",
           shift, cfg_len, cfg_len, pt[0], pt[1]);
    free(pt); free(blob);
    return 0;
}

int main(int argc, char **argv) {
    if (argc >= 3 && strcmp(argv[1], "--decrypt") == 0) {
        long shift = -1;
        const char *out_p = (argc >= 4 && argv[3][0] != '-') ? argv[3] : NULL;
        for (int i = 3; i + 1 < argc; i++) {
            if (strcmp(argv[i], "--shift") == 0) shift = strtol(argv[++i], NULL, 0);
        }
        return cmd_decrypt(argv[2], out_p, shift);
    }

    if (argc < 4) {
        fprintf(stderr,
                "Usage:\n"
                "  %s <stub.bin> <core_plain.bin> <out_entry4.bin> [--zlib <core.zlib>] [--shift <hex>] [--bss <hex>] [--verify]\n"
                "  %s --decrypt <entry4.bin> [out_core.zlib] [--shift <hex>]\n",
                argv[0], argv[0]);
        return 1;
    }

    const char *stub_path = argv[1];
    const char *core_path = argv[2];
    const char *out_path  = argv[3];
    const char *zlib_path = NULL;
    long force_shift = -1;
    size_t bss_size = 0x50000u;
    int do_verify = 0;

    for (int i = 4; i < argc; i++) {
        if (strcmp(argv[i], "--zlib") == 0 && i + 1 < argc) zlib_path = argv[++i];
        else if (strcmp(argv[i], "--shift") == 0 && i + 1 < argc) force_shift = strtol(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--bss") == 0 && i + 1 < argc) bss_size = (size_t)strtoull(argv[++i], NULL, 0);
        else if (strcmp(argv[i], "--verify") == 0) do_verify = 1;
    }

    size_t stub_len = 0, core_len = 0;
    u8 *stub = read_file_all(stub_path, &stub_len);
    u8 *core_plain = read_file_all(core_path, &core_len);
    if (!stub || !core_plain) {
        fprintf(stderr, "enc: failed reading input files\n");
        free(stub); free(core_plain); return 1;
    }

    size_t zraw_len = 0;
    u8 *zraw = zlib_path ? read_file_all(zlib_path, &zraw_len)
                         : zlib_encode_stored(core_plain, core_len, &zraw_len);
    if (!zraw || zraw_len < 6) {
        fprintf(stderr, "enc: failed obtaining zlib stream\n");
        free(stub); free(core_plain); free(zraw); return 1;
    }

    /* Guarantee stub's 3 * cfg_len kmem allocation covers core_plain + .core.bss */
    size_t zlen = 0;
    u8 *zbuf = pad_zlib_to_3x(zraw, zraw_len, core_len + bss_size + 0x1000u, &zlen);
    free(zraw);
    if (!zbuf) { free(stub); free(core_plain); return 1; }

    size_t shift = (force_shift >= 0) ? (size_t)force_shift : detect_shift(stub, stub_len);
    if (CORE_OFF + zlen > OFF_CFG_LEN + shift) {
        fprintf(stderr, "enc: compressed core (0x%zx) exceeds stub slot [0x%x..0x%zx)!\n",
                zlen, CORE_OFF, (size_t)OFF_CFG_LEN + shift);
        free(zbuf); free(stub); free(core_plain); return 1;
    }

    /* Ensure output file length guarantees afterglow mmap 0x4000 rounding covers .stub.bss */
    size_t min_out_len = OFF_BSS_END + shift;
    size_t out_len = (stub_len > min_out_len) ? stub_len : min_out_len;
    u8 *out = (u8 *)calloc(1, out_len);
    if (!out) { free(zbuf); free(stub); free(core_plain); return 1; }
    memcpy(out, stub, stub_len);

    wr_le32(out + OFF_CFG_LEN + shift, (u32)zlen);
    u8 key[32], mac[32];
    derive_key(out, shift, key);
    const u8 *nonce = out + OFF_NONCE + shift;

    /* ChaCha20 encrypt in place at CORE_OFF, then HMAC over nonce || ciphertext */
    memcpy(out + CORE_OFF, zbuf, zlen);
    chacha20_crypt(key, nonce, 1, out + CORE_OFF, zlen);
    compute_entry4_mac(mac, key, out + OFF_BRAND + shift, nonce, out + CORE_OFF, zlen);
    memcpy(out + OFF_CHECK32 + shift, mac, 32);

    if (write_file_all(out_path, out, out_len) != 0) {
        fprintf(stderr, "enc: failed writing %s\n", out_path);
        free(out); free(zbuf); free(stub); free(core_plain); return 1;
    }
    printf("enc: packed %s (%zu B, core=0x%zx B @ 0x%x, 3x=%zu B >= %zu B, shift=0x%zx)\n",
           out_path, out_len, zlen, CORE_OFF, zlen * 3, core_len + bss_size, shift);

    free(out); free(zbuf); free(stub); free(core_plain);
    if (do_verify) return cmd_decrypt(out_path, NULL, (long)shift);
    return 0;
}
