/**
 * Entry4 Application Controller
 * Minimal, lowercase, unadorned, 2-second pre-launch wait.
 * Supports switching payloads between entry4 and goldhen.
 * Launch stays disabled until the page settles (window load + 2x rAF +
 * 800ms minimum) so an early tap can't catch the heap mid-parse.
 */

import { detectFirmware, supportsFirmware, loadRuntime } from "./firmware-registry.js";
import { Entry4View } from "./app-view.js";

export class Entry4App {
  constructor() {
    this.isRunning = false;
    this.isWarmedUp = false;
    this.warmupStart = Date.now();
    this.warmupTimer = null;
    this.payloads = { "13.02-13.52": "entry4", "14.02": "entry4d" };
    this.firmware = "13.02-13.52";
    const requested = new URLSearchParams(window.location.search).get("firmware");
    if (requested === "14.00" || requested === "14.02") this.firmware = requested;
    this.detectedFirmware = null;
    this.countdownTimer = null;
    this.view = new Entry4View();

    this.el = this.view.el;

    this.init();
  }

  init() {
    this.el.logToggle.disabled = this.view.logLines === 0;
    this.detectEnvironment();
    this.setupListeners();
    this.setupWarmupGate();
    this.updateAvailabilityUI();
    this.updatePayloadUI();
  }

  setupWarmupGate() {
    // Manual launch only: keep the button locked until the page settles.
    // window load + 2x rAF proves first paint is done; 800ms minimum covers
    // JIT/GC churn after DOMContentLoaded on the ps4 browser.
    let settled = false;
    const onSettled = () => {
      if (settled) return;
      settled = true;
      const remaining = Math.max(0, 800 - (Date.now() - this.warmupStart));
      this.warmupTimer = setTimeout(() => {
        this.isWarmedUp = true;
        this.warmupTimer = null;
        this.updateAvailabilityUI();
      }, remaining);
    };
    const afterLoad = () => {
      if (typeof requestAnimationFrame === "function") {
        requestAnimationFrame(() => requestAnimationFrame(onSettled));
      } else {
        setTimeout(onSettled, 32);
      }
    };
    if (document.readyState === "complete") {
      afterLoad();
    } else {
      window.addEventListener("load", afterLoad, { once: true });
      // Safety: a stalled asset must not lock the button forever.
      setTimeout(afterLoad, 5000);
    }
  }

  get activePayload() {
    if (this.isBundledFirmware) return "bundled hen";
    if (this.firmware === "14.02" && this.payloads[this.firmware] === "goldhen") {
      return "goldhen v2.4b18.14";
    }
    if (this.payloads[this.firmware] === "entry4d") {
      return "Entry4D";
    }
    return this.payloads[this.firmware];
  }

  get isBundledFirmware() {
    return this.firmware === "14.00";
  }

  detectEnvironment() {
    this.detectedFirmware = detectFirmware(navigator.userAgent);

    if (this.detectedFirmware) {
      if (this.detectedFirmware === "14.00" || this.detectedFirmware === "14.02") {
        this.firmware = this.detectedFirmware;
      }
    }
  }

  setupListeners() {
    this.el.payloadMeta.addEventListener("click", () => {
      if (!this.isRunning) this.togglePayload();
    });

    this.el.btnLaunch.addEventListener("click", () => {
      this.handleLaunch();
    });

    this.el.firmwareToggle.addEventListener("click", () => this.toggleFirmware());

    this.el.logToggle.addEventListener("click", () => {
      this.toggleLog();
    });
  }

  togglePayload() {
    if (this.isRunning || this.isBundledFirmware) return;
    if (this.firmware === "14.02") {
      const cur = this.payloads[this.firmware];
      const next = cur === "entry4d" ? "entry4" : cur === "entry4" ? "goldhen" : "entry4d";
      this.payloads[this.firmware] = next;
    } else {
      const payload = this.payloads[this.firmware] === "entry4" ? "goldhen" : "entry4";
      this.payloads[this.firmware] = payload;
    }
    this.updatePayloadUI();
    this.log("payload", `switched payload to ${this.activePayload}`);
  }

  updatePayloadUI() {
    this.view.updateSelection(this.firmware, this.activePayload, this.isRunning);
    this.updateAvailabilityUI();
  }

  toggleFirmware() {
    if (this.isRunning) return;
    // Cycle: legacy 13xx -> 14.00 -> 14.02 -> legacy 13xx.
    this.firmware = this.firmware === "13.02-13.52" ? "14.00"
      : this.firmware === "14.00" ? "14.02" : "13.02-13.52";
    this.updatePayloadUI();
    this.log("firmware", `selected ${this.firmware}`);
  }

  get canLaunch() {
    return supportsFirmware(this.firmware, this.detectedFirmware);
  }

  updateAvailabilityUI() {
    this.el.btnLaunch.disabled = this.isRunning || !this.canLaunch || !this.isWarmedUp;
    if (this.isRunning) return;
    if (!this.canLaunch) {
      const supportedDevice = supportsFirmware("13.02-13.52", this.detectedFirmware) ||
        supportsFirmware("14.00", this.detectedFirmware) ||
        supportsFirmware("14.02", this.detectedFirmware);
      this.setStatus(supportedDevice ? "firmware mismatch" : "unsupported device",
        supportedDevice
          ? `selected ${this.firmware}; detected ps4 ${this.detectedFirmware}. select the matching firmware.`
          : "requires a ps4 on 13.02, 13.04, 13.50, 13.52, 14.00, or 14.02.", 0);
      return;
    }
    if (!this.isWarmedUp) {
      this.setStatus("warming up", "waiting for the page to settle... press launch when ready.", 0);
      return;
    }
    this.el.stateTitle.textContent = "ready";
    this.el.stateDetail.textContent = this.firmware === "14.00"
      ? "14.00 experimental · bundled hen. cold boot before a live run."
      : this.firmware === "14.02"
        ? `14.02 experimental · afterglow + ${this.activePayload}. cold boot before a live run.`
        : `payload: ${this.activePayload}. press launch to run.`;
  }

  toggleLog() {
    this.view.toggleLog();
  }

  handleLaunch() {
    if (this.isRunning) return;
    if (!this.isWarmedUp || !this.canLaunch) {
      this.updateAvailabilityUI();
      return;
    }
    this.isRunning = true;
    this.el.btnLaunch.disabled = true;
    this.updatePayloadUI();

    // 2-second mandatory wait
    const waitTimeMs = 2000;
    const startTime = Date.now();

    this.setStatus("arming", `waiting 2 seconds (${this.activePayload})...`, 2);

    this.countdownTimer = setInterval(() => {
      const elapsed = Date.now() - startTime;
      const remaining = Math.max(0, waitTimeMs - elapsed);
      const secondsLeft = (remaining / 1000).toFixed(1);

      this.el.btnLaunch.textContent = `starting (${secondsLeft}s)`;
      this.el.stateDetail.textContent = `waiting ${secondsLeft}s...`;

      if (remaining <= 0) {
        clearInterval(this.countdownTimer);
        this.countdownTimer = null;
        this.el.btnLaunch.textContent = "running...";
        this.startChain();
      }
    }, 50);
  }

  async startChain() {
    if (!this.canLaunch) {
      this.isRunning = false;
      this.updateAvailabilityUI();
      return;
    }
    const ui = {
      setStatus: (title, detail, pct) => this.setStatus(title, detail, pct),
      log: (tag, detail) => this.log(tag, detail),
      complete: (success, msg) => this.complete(success, msg)
    };
    try {
      if (this.firmware === "14.00" || this.firmware === "14.02") {
        this.setStatus(`starting ${this.firmware}`, "starting the experimental browser chain...", 5);
      }
      const { runExploit } = await loadRuntime(this.firmware);
      await runExploit(ui, this.payloads[this.firmware]);
    } catch (err) {
      this.log("error", String(err).toLowerCase());
      this.complete(false, err.message || "module load error");
    }
  }

  setStatus(title, detail, pct) {
    this.view.setStatus(title, detail, pct);
  }

  log(tag, detail) {
    this.view.log(tag, detail);
  }

  complete(success, message) {
    this.isRunning = false;
    this.el.btnLaunch.disabled = !this.canLaunch || !this.isWarmedUp;
    this.el.firmwareToggle.disabled = false;
    this.el.payloadMeta.setAttribute("aria-disabled", String(this.isBundledFirmware));

    if (success) {
      this.el.btnLaunch.textContent = "re-run";
      this.setStatus("jailbreak complete", (message || `${this.activePayload} active.`).toLowerCase(), 100);
    } else {
      this.el.btnLaunch.textContent = "retry";
      this.setStatus("try again", "restart your browser and try a few more times. if it still doesn't work, restart your console.", 100);
    }
  }
}
