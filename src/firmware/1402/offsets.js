// 14.02 WebKit offsets: identical to the 13.52 module (WebKitty:
// `PS4["14.02"] = Object.assign({}, PS4["14.00"], {})`, and 14.00 itself is
// `alias_of: "13.52-webkit"`). The kernel stage is provided by afterglow.js,
// which carries its own per-firmware tables, so no kernel RVAs are required
// here.
export const REQUIRED_KEYS = [
  "fw_status",
  "wk_expm1_builtin",
  "wk_JSFunction_m_function",
  "wk_POP_RDI_RET",
  "wk_POP_RSI_RET",
  "wk_POP_RDX_RET",
  "wk_POP_RCX_RET",
  "wk_POP_RAX_RET",
  "wk_POP_R8_RET",
  "wk_POP_R9_RET",
  "wk_LEAVE_RET",
  "wk_MOV_QWORD_PTR_RDI_RAX_RET",
  "wk_MOV_RDI_RSI_30_CALL",
  "wk_POP_RAX_MOV_RAX_JMP_18",
  "wk_PUSH_RBP_MOV_RBP_RSP_10",
  "wk_MOV_RDI_RAX_8_CALL_20",
  "wk_MOV_RDX_RAX_18_CALL_10",
  "wk_PUSH_RDX_POP_RSP_RET",
  "pivot_view_sp",
  "wk_ArrayBuffer_m_impl",
  "wk_ArrayBuffer_m_contents_m_data",
  "wk___imp___error",
  "k__error",
  "k_scan_stage1",
  "k_scan_stage2",
];

export const OPTIONAL_KEYS = [
  "k_stubs",
  "wk___imp_pthread_create",
  "k_pthread_create",
  "kpatch",
  "payload",
  "alias_of",
];

export const PS4 = {
  "14.02": {
    alias_of: "13.52-webkit",
    fw_status:
      "state=14.02-afterglow " +
      "webkit=13.52-identical " +
      "kernel=afterglow (apm-UAF, own kernel stage) " +
      "payload=goldhen_v2.4b18.14.bin",
    payload: "goldhen_v2.4b18.14.bin",

    wk_expm1_builtin: 0x2586880,
    wk_JSFunction_m_function: 0x28,

    wk_POP_RDI_RET: 0x5c480,
    wk_POP_RSI_RET: 0x6e45e,
    wk_POP_RDX_RET: 0x12c5ba,
    wk_POP_RCX_RET: 0x1bade,
    wk_POP_RAX_RET: 0x10504,
    wk_POP_R8_RET: 0x9b311,
    wk_POP_R9_RET: 0x1dcfb1,
    wk_LEAVE_RET: 0x182f7,
    wk_MOV_QWORD_PTR_RDI_RAX_RET: 0x548b,
    wk_PUSH_RDX_POP_RSP_RET: 0x2abccaa,
    wk_MOV_RDI_RSI_30_CALL: 0x295f948,
    wk_POP_RAX_MOV_RAX_JMP_18: 0x1d989e3,
    wk_PUSH_RBP_MOV_RBP_RSP_10: 0x25bae0,
    wk_MOV_RDI_RAX_8_CALL_20: 0x4a0406,
    wk_MOV_RDX_RAX_18_CALL_10: 0x1ec3ada,

    pivot_view_sp: 0x38,
    wk_ArrayBuffer_m_impl: 0x10,
    wk_ArrayBuffer_m_contents_m_data: 0x10,

    wk___imp___error: 0x3cb8cc8,
    k__error: 0x1a0f0,

    k_scan_stage1: 0x40000,
    k_scan_stage2: 0x60000,
  },
};

export function offsetsFor(uaString) {
  const m = (uaString || "").match(/PlayStation\s+4[\/ ](\d+)\.(\d+)/);
  if (!m) return { key: null, off: null };

  const key = m[1] + "." + parseInt(m[2], 16).toString(16).padStart(2, "0");
  return { key, off: PS4[key] || null };
}
