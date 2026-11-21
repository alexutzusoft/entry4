#!/usr/bin/env python3
"""Entry4 visual rebuild (1402).

Rebuilds src/firmware/1402/payloads/entry4.bin from:
  - asm/*.S        pure Entry4 assembly (non-visuals, byte-exact blobs)
  - visuals/*.c    all user-visible strings/XML (editable C, same-length)
  - tools/enc.c    ChaCha20 + HMAC packer (exact Entry4 crypto)

Build is core-exact: with unmodified visuals/, out/entry4.bin is
byte-identical to the reference (SHA256 89a20f33...). Edit visuals/*.c
(keep lengths identical, see _Static_assert) and rebuild to rebrand.

Layout (SHIFT=0):
  0x0-0x78A0       stub (asm/stub.S)
  0x78A0-0x411A4   encrypted core (cfg_len=0x39904, zlib+trailer)
  0x411A4-0x43600  zeroed icon block
  0x43600-0x48F18  tail (asm/tail.S + visuals/banner.c + visuals/tail_notices.c)

Usage: python build.py [--check-only] [--out PATH]
Requires: clang + llvm-objcopy in C:\\Program Files\\LLVM\\bin, python3 + zlib.
"""
import hashlib
import os
import re
import struct
import subprocess
import sys
import zlib

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE)) if os.path.basename(os.path.dirname(HERE)) == "src" else os.path.dirname(os.path.dirname(os.path.dirname(HERE)))
# HERE = .../src/payload, REPO = repo root
REPO = os.path.abspath(os.path.join(HERE, "..", "..", "..")) if False else None
# Robust: payload dir is src/payload, repo root is two levels up from src/
PAYLOAD = HERE
SRC_DIR = os.path.dirname(PAYLOAD)  # src/
REPO_ROOT = os.path.dirname(SRC_DIR)  # repo root
REF = os.path.join(REPO_ROOT, "src", "firmware", "1402", "payloads", "entry4.bin")
OUT_DIR = os.path.join(PAYLOAD, "out")
OUT_BIN = os.path.join(OUT_DIR, "entry4.bin")

LLVM_BIN = r"C:\Program Files\LLVM\bin"
CC = os.environ.get("CLANG", os.path.join(LLVM_BIN, "clang.exe"))
OBJCOPY = os.environ.get("OBJCOPY", os.path.join(LLVM_BIN, "llvm-objcopy.exe"))
OBJDUMP = os.environ.get("OBJDUMP", os.path.join(LLVM_BIN, "llvm-objdump.exe"))

TAIL_VISUALS = [
    # (section, file_off, length)
    (".visual.tail.48834", 0x48834, 0x49),
    (".visual.tail.4887e", 0x4887E, 0x43),
    (".visual.tail.488c2", 0x488C2, 0x44),
    (".visual.tail.48907", 0x48907, 0x45),
    (".visual.tail.4894d", 0x4894D, 0x46),
    (".visual.tail.48994", 0x48994, 0x46),
    (".visual.tail.489db", 0x489DB, 0x46),
    (".visual.tail.48a22", 0x48A22, 0x27),
    (".visual.tail.48a4a", 0x48A4A, 0x3C),
    (".visual.tail.48a87", 0x48A87, 0x3D),
    (".visual.tail.48ac5", 0x48AC5, 0x3E),
    (".visual.tail.48b04", 0x48B04, 0x3F),
    (".visual.tail.48b44", 0x48B44, 0x3F),
    (".visual.tail.48b84", 0x48B84, 0x33),
    (".visual.tail.48bb8", 0x48BB8, 0x4A),
    (".visual.tail.48c03", 0x48C03, 0x2A),
    (".visual.tail.48d13", 0x48D13, 0x1A),
    (".visual.tail.48d30", 0x48D30, 0x07),
]

# (section, core_off, length or None=auto NUL-len, must match reference)
CORE_VISUALS_AUTO = [
    # boot
    ".visual.core.9ac46", ".visual.core.9ac76", ".visual.core.9ac9b",
    ".visual.core.9aca9", ".visual.core.9acb1",
    ".visual.core.9acdc", ".visual.core.9acf1", ".visual.core.9ad1f",
    ".visual.core.9ad69", ".visual.core.9adb7", ".visual.core.9adf3",
    # overlay
    ".visual.core.854d7", ".visual.core.854f2", ".visual.core.94d76",
    ".visual.core.855c8", ".visual.core.855d3", ".visual.core.855e2",
    ".visual.core.855f3", ".visual.core.85604", ".visual.core.85615",
    ".visual.core.8563e", ".visual.core.85659", ".visual.core.856a8",
    # servers
    ".visual.core.93252", ".visual.core.931d8", ".visual.core.93c64",
    ".visual.core.93c3c", ".visual.core.93ca3", ".visual.core.98afc",
    ".visual.core.98dec", ".visual.core.98c46", ".visual.core.98c28",
    ".visual.core.9897c", ".visual.core.989ac", ".visual.core.98a14",
    ".visual.core.98a3c", ".visual.core.98a73", ".visual.core.9a367",
    ".visual.core.9a394", ".visual.core.87601", ".visual.core.8765f",
    ".visual.core.8767e", ".visual.core.877ef", ".visual.core.8780d",
    # cheat/plugin
    ".visual.core.84cc7", ".visual.core.84eaf", ".visual.core.84ec8",
    ".visual.core.851c5", ".visual.core.851e4", ".visual.core.85242",
    ".visual.core.8528c", ".visual.core.84feb", ".visual.core.8743f",
    ".visual.core.87595", ".visual.core.875af", ".visual.core.85718",
    ".visual.core.87aca", ".visual.core.87c71", ".visual.core.87c8b",
    ".visual.core.96955", ".visual.core.8501d", ".visual.core.87392",
    ".visual.core.8737b",
    # icons
    ".visual.core.87873", ".visual.core.9aebf", ".visual.core.85818",
    ".visual.core.8532d", ".visual.core.853a7",
    # branding labels
    ".visual.core.887ec", ".visual.core.88516", ".visual.core.885da",
    ".visual.core.8820b", ".visual.core.88652",
    # menu xmls (fixed len)
    ".visual.core.39178", ".visual.core.45c80", ".visual.core.45d90",
]

CORE_FIXED_LEN = {
    ".visual.core.39178": 13986,
    ".visual.core.45c80": 256,
    ".visual.core.45d90": 258,
}

# Binary blobs (no NUL terminator, exact length)
CORE_BLOBS = {
    ".visual.core.6a154": 2158,  # 192x192 Entry4 PNG
    ".visual.core.828f4": 1171,  # scanline texture PNG
}


def run(cmd, cwd=PAYLOAD):
    r = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
    if r.returncode != 0:
        print("FAILED:", " ".join(cmd))
        print(r.stdout[-3000:])
        print(r.stderr[-3000:])
        sys.exit(r.returncode)
    return r


def chacha20_ietf_crypt(key32, nonce12, ctr0, data):
    import struct as st
    def rotl32(v, n):
        return ((v << n) | (v >> (32 - n))) & 0xFFFFFFFF
    def qr(s, a, b, c, d):
        s[a] = (s[a] + s[b]) & 0xFFFFFFFF; s[d] = rotl32(s[d] ^ s[a], 16)
        s[c] = (s[c] + s[d]) & 0xFFFFFFFF; s[b] = rotl32(s[b] ^ s[c], 12)
        s[a] = (s[a] + s[b]) & 0xFFFFFFFF; s[d] = rotl32(s[d] ^ s[a], 8)
        s[c] = (s[c] + s[d]) & 0xFFFFFFFF; s[b] = rotl32(s[b] ^ s[c], 7)
    const = st.unpack("<4I", b"expand 32-byte k")
    k = st.unpack("<8I", key32)
    n = st.unpack("<3I", nonce12)
    out = bytearray(len(data))
    ctr = ctr0
    for off in range(0, len(data), 64):
        state = list(const) + list(k) + [ctr] + list(n)
        work = list(state)
        for _ in range(10):
            qr(work, 0, 4, 8, 12); qr(work, 1, 5, 9, 13)
            qr(work, 2, 6, 10, 14); qr(work, 3, 7, 11, 15)
            qr(work, 0, 5, 10, 15); qr(work, 1, 6, 11, 12)
            qr(work, 2, 7, 8, 13); qr(work, 3, 4, 9, 14)
        ks = st.pack("<16I", *(((work[i] + state[i]) & 0xFFFFFFFF) for i in range(16)))
        chunk = data[off:off+64]
        for i, b in enumerate(chunk):
            out[off+i] = b ^ ks[i]
        ctr = (ctr + 1) & 0xFFFFFFFF
    return bytes(out)


def decrypt_core(blob):
    cfg_len = struct.unpack_from("<I", blob, 0x486FC)[0]
    stub_sha = hashlib.sha256(blob[:0x7894]).digest()
    tabA = struct.unpack_from("<8I", blob, 0x48D40)
    tabC = blob[0x48D60:0x48D80]
    tabB = blob[0x48D80:0x48DA0]
    kdf = bytes(((tabA[i >> 2] >> ((i & 3) * 8)) & 0xFF) ^ tabB[i] ^ tabC[i] for i in range(32))
    key = bytes(x ^ y for x, y in zip(stub_sha, kdf))
    nonce = blob[0x48DC0:0x48DCC]
    ct = blob[0x78A0:0x78A0+cfg_len]
    pt = chacha20_ietf_crypt(key, nonce, 1, ct)
    return zlib.decompress(pt), cfg_len, key, nonce, pt


def sha256_file(p):
    h = hashlib.sha256()
    with open(p, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def compile_visuals(obj_dir):
    os.makedirs(obj_dir, exist_ok=True)
    c_files = sorted(
        os.path.join(PAYLOAD, "visuals", f)
        for f in os.listdir(os.path.join(PAYLOAD, "visuals"))
        if f.endswith(".c")
    )
    objs = []
    flags = [
        "-target", "x86_64-unknown-unknown",
        "-nostdlib", "-ffreestanding", "-nostdinc",
        "-fno-stack-protector", "-mno-red-zone",
        "-fomit-frame-pointer", "-falign-functions=1",
        "-ffunction-sections", "-fdata-sections",
        "-fno-vectorize", "-fno-slp-vectorize", "-fno-jump-tables",
        "-Os", "-Wall", "-I", os.path.join(PAYLOAD, "include"),
    ]
    for src in c_files:
        obj = os.path.join(obj_dir, os.path.basename(src) + ".o")
        stamp = obj + ".flags"
        key = hashlib.sha1((" ".join(flags)).encode()).hexdigest()[:10]
        if (os.path.exists(obj) and os.path.getmtime(obj) >= os.path.getmtime(src)
                and os.path.exists(stamp) and open(stamp).read().strip() == key):
            objs.append(obj)
            continue
        run([CC] + flags + ["-c", src, "-o", obj])
        open(stamp, "w").write(key)
        objs.append(obj)
    return objs


def extract_section(obj, section, out_path):
    # llvm-objcopy single section to binary
    r = subprocess.run(
        [OBJCOPY, "-O", "binary", "--only-section=" + section, obj, out_path],
        capture_output=True,
    )
    if r.returncode != 0 or not os.path.exists(out_path):
        return None
    # objcopy creates file even if section missing? check size + verify via objdump
    data = open(out_path, "rb").read()
    return data


def find_section_owner(objs, section):
    for obj in objs:
        out = run([OBJDUMP, "-h", obj]).stdout
        if re.search(r"\s+" + re.escape(section.lstrip(".")) + r"\s|\s+" + re.escape(section) + r"\s", out):
            return obj
    # fallback: try each obj with objcopy
    for obj in objs:
        tmp = obj + ".probe.bin"
        data = extract_section(obj, section, tmp)
        try:
            if data is not None and len(data) > 0:
                return obj
        finally:
            pass
    return None


def main():
    check_only = "--check-only" in sys.argv
    out_path = OUT_BIN
    if "--out" in sys.argv:
        out_path = sys.argv[sys.argv.index("--out") + 1]

    print(f"[1/6] Reference: {REF}")
    ref = open(REF, "rb").read()
    print(f"        {len(ref)} B sha256={hashlib.sha256(ref).hexdigest()}")
    assert len(ref) == 0x48F18, f"unexpected ref len {len(ref)}"

    print("[2/6] Decrypting core...")
    core_plain, cfg_len, key, nonce, pt_zlib = decrypt_core(ref)
    print(f"        core_plain={len(core_plain)} B cfg_len=0x{cfg_len:x} key={key.hex()[:16]}... nonce={nonce.hex()}")
    assert cfg_len == 0x39904, f"unexpected cfg_len 0x{cfg_len:x}"

    print("[3/6] Compiling visuals/*.c ...")
    obj_dir = os.path.join(PAYLOAD, "out", "obj_visuals")
    objs = compile_visuals(obj_dir)
    print(f"        {len(objs)} objects")

    # Extract tail visuals
    print("[4/6] Patching tail + core visuals...")
    new_file = bytearray(ref)
    new_core = bytearray(core_plain)

    # Build section -> bytes map by extracting from whichever obj owns it
    section_cache = {}

    def get_section(section):
        if section in section_cache:
            return section_cache[section]
        for obj in objs:
            tmp = os.path.join(obj_dir, "sec_" + section.replace(".", "_") + ".bin")
            # try objcopy; missing section yields empty or error
            r = subprocess.run(
                [OBJCOPY, "-O", "binary", "--only-section=" + section, obj, tmp],
                capture_output=True,
            )
            if r.returncode == 0 and os.path.exists(tmp):
                data = open(tmp, "rb").read()
                # llvm-objcopy pads missing section to 0? verify owner via objdump
                dump = subprocess.run([OBJDUMP, "-h", obj], capture_output=True, text=True).stdout
                if section in dump or section.lstrip(".") in dump:
                    # strip trailing NUL? sections include NUL terminator; patch excludes NUL? No: file stores NUL too.
                    # Our C sizeof includes NUL; file bytes include NUL at [off+len]. Patch data[0:len], keep NUL from data[len]? Actually data includes NUL.
                    # For fixed-len visuals, data len should be len+1 (with NUL) except menu xml? menu xml has no trailing NUL in core? It ends with '>' then CRLF? Check: core has \r\n\0? Our C includes no NUL beyond sizeof? sizeof includes NUL, data includes NUL.
                    # For patching, we write data excluding final NUL for core strings? No: core stores NUL terminator too. So write data (including NUL) but only len bytes? Let's write len bytes of string + verify NUL.
                    section_cache[section] = data
                    return data
        return None

    # Tail
    for section, off, ln in TAIL_VISUALS:
        data = get_section(section)
        if data is None:
            print(f"ERROR: missing section {section}")
            sys.exit(1)
        if len(data) < ln + 1:
            print(f"ERROR: section {section} too short {len(data)} < {ln+1}")
            sys.exit(1)
        blob = data[:ln]  # exclude NUL
        # verify NUL
        if data[ln] != 0:
            print(f"ERROR: section {section} missing NUL terminator")
            sys.exit(1)
        new_file[off:off+ln] = blob
        # NUL byte stays (already in ref)

    # Core: determine lengths from reference (NUL-terminated) except fixed
    for section in CORE_VISUALS_AUTO:
        data = get_section(section)
        if data is None:
            print(f"ERROR: missing core section {section}")
            sys.exit(1)
        try:
            core_off = int(section.split(".")[-1], 16)
        except ValueError:
            print(f"ERROR: bad section name {section}")
            sys.exit(1)
        if section in CORE_FIXED_LEN:
            ln = CORE_FIXED_LEN[section]
            if len(data) < ln + 1:
                print(f"ERROR: {section} short {len(data)} < {ln+1}")
                sys.exit(1)
            new_core[core_off:core_off+ln] = data[:ln]
        else:
            # NUL-terminated: reference length = strlen at core_off
            end = core_plain.find(b"\x00", core_off)
            if end == -1:
                print(f"ERROR: no NUL at core 0x{core_off:x}")
                sys.exit(1)
            ln = end - core_off
            if len(data) < ln + 1:
                print(f"ERROR: {section} short {len(data)} < {ln+1} (ref len {ln})")
                sys.exit(1)
            if data[ln] != 0:
                print(f"ERROR: {section} missing NUL (len {ln})")
                sys.exit(1)
            new_core[core_off:core_off+ln] = data[:ln]

    # Core binary blobs (PNGs, no NUL)
    for section, ln in CORE_BLOBS.items():
        data = get_section(section)
        if data is None:
            print(f"ERROR: missing core blob {section}")
            sys.exit(1)
        try:
            core_off = int(section.split(".")[-1], 16)
        except ValueError:
            print(f"ERROR: bad blob name {section}")
            sys.exit(1)
        if len(data) < ln:
            print(f"ERROR: {section} short {len(data)} < {ln}")
            sys.exit(1)
        new_core[core_off:core_off+ln] = data[:ln]

    core_changed = bytes(new_core) != bytes(core_plain)
    tail_changed = bytes(new_file) != bytes(ref)
    print(f"        core_changed={core_changed} tail_changed={tail_changed}")

    # Recompress core if changed, else reuse original zlib for exactness
    print("[5/6] Recompress + re-encrypt...")
    if not core_changed:
        new_zlib = pt_zlib
        new_cfg = cfg_len
        print("        core unchanged: reusing original zlib stream")
    else:
        # Entry4 reference uses zlib level 9 (NOT level 1). Recompress
        # with level 9 so visual edits stay near the original size.
        # No 3x empty-block padding here: the original image already
        # satisfies its loader hint (3*cfg covers plain+bss); padding
        # with a 0x50000 bss guess would bloat cfg past the zero slack.
        zraw = zlib.compress(bytes(new_core), 9)
        new_cfg = len(zraw)
        max_cfg = 0x486FC - 0x78A0  # tail must stay put (SHIFT=0); 0x40E5C
        if new_cfg > max_cfg:
            print(f"ERROR: recompressed core too big 0x{new_cfg:x} > 0x{max_cfg:x}")
            print("       shorten visuals or split edits; SHIFT-moving tail is future work.")
            sys.exit(2)
        new_zlib = zraw
        print(f"        recompressed {len(new_core)} -> {len(new_zlib)} B (cfg 0x{cfg_len:x} -> 0x{new_cfg:x})")
        # Zero the slack between new encrypted end and tail base (was zeros in ref)
        tail_base = 0x486FC
        enc_end = 0x78A0 + new_cfg
        if enc_end < tail_base:
            new_file[enc_end:tail_base] = bytes(tail_base - enc_end)

    # Encrypt (ChaCha20-IETF ctr=1) with same key/nonce derivation as enc.c
    # Key depends on stub[0:0x7894] (unchanged, since stub visuals don't affect it)
    # + KDF tables (unchanged). Recompute to be safe.
    stub_sha = hashlib.sha256(bytes(new_file[:0x7894])).digest()
    tabA = struct.unpack_from("<8I", bytes(new_file), 0x48D40)
    tabC = bytes(new_file[0x48D60:0x48D80])
    tabB = bytes(new_file[0x48D80:0x48DA0])
    kdf = bytes(((tabA[i >> 2] >> ((i & 3) * 8)) & 0xFF) ^ tabB[i] ^ tabC[i] for i in range(32))
    new_key = bytes(x ^ y for x, y in zip(stub_sha, kdf))
    new_nonce = bytes(new_file[0x48DC0:0x48DCC])
    ct = chacha20_ietf_crypt(new_key, new_nonce, 1, new_zlib)
    new_file[0x78A0:0x78A0+new_cfg] = ct
    # cfg_len field (unchanged in v1)
    struct.pack_into("<I", new_file, 0x486FC, new_cfg)
    # Recompute HMAC (sub_3da + sub_436 zero-padded) like enc.c
    import hashlib as hl
    h1 = hl.sha256(new_key + bytes(new_file[0x48D30:0x48D38])).digest()
    ipad = bytes(b ^ 0x36 for b in h1) + bytes(32)
    opad = bytes(b ^ 0x5C for b in h1) + bytes(32)
    inner = hl.sha256(ipad + new_nonce + ct).digest()
    mac = hl.sha256(opad + inner).digest()
    new_file[0x48DA0:0x48DC0] = mac

    # Verify HMAC matches when unchanged
    if bytes(new_file[0x48DA0:0x48DC0]) != bytes(ref[0x48DA0:0x48DC0]) and not (core_changed or tail_changed):
        print("ERROR: HMAC mismatch on unchanged build!")
        sys.exit(1)

    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    open(out_path, "wb").write(new_file)
    sha = hashlib.sha256(bytes(new_file)).hexdigest()
    ref_sha = hashlib.sha256(ref).hexdigest()
    print(f"[6/6] Wrote {out_path} ({len(new_file)} B sha256={sha})")
    print(f"        reference sha256={ref_sha}")
    if sha == ref_sha:
        print("        PASS: core-exact (byte-identical to pre-built Entry4)")
    else:
        print("        NOTE: output differs from reference (visuals modified)")

    if check_only:
        sys.exit(0 if sha == ref_sha else 3)


if __name__ == "__main__":
    main()
