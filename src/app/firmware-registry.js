// Keep firmware routing separate from either exploit's runtime.
export const LEGACY_FIRMWARES = ["13.02", "13.04", "13.50", "13.52"];
export const MODERN_FIRMWARES = ["14.00", "14.02"];

export function detectFirmware(userAgent) {
  const match = /PlayStation\s+4[\/ ](\d+)\.(\d+)/.exec(userAgent);
  return match ? match[1] + "." + match[2].padStart(2, "0") : null;
}

export function supportsFirmware(selection, detected) {
  if (selection === "14.00") return detected === "14.00";
  if (selection === "14.02") return detected === "14.02";
  return selection === "13.02-13.52" && LEGACY_FIRMWARES.includes(detected);
}

// Keep runtime imports lazy: unsupported devices must never load a runtime.
export async function loadRuntime(selection) {
  if (selection === "14.00") return import("../firmware/1400/runner.js");
  if (selection === "14.02") return import("../firmware/1402/runner.js");
  if (selection === "13.02-13.52") return import("../firmware/13xx/runner.js");
  throw new Error("Unsupported firmware selection: " + selection);
}
