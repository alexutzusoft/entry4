// DOM rendering and terminal output for the native Entry4 page.
export class Entry4View {
  constructor() {
    this.logLines = 0;
    this.el = {
      payloadMeta: document.getElementById("payload-meta"),
      firmwareToggle: document.getElementById("firmware-toggle"),
      stateTitle: document.getElementById("state-title"),
      stateDetail: document.getElementById("state-detail"),
      progressFill: document.getElementById("progress-fill"),
      progressText: document.getElementById("progress-text"),
      btnLaunch: document.getElementById("btn-launch"),
      logToggle: document.getElementById("log-toggle"),
      logBox: document.getElementById("log-box")
    };
  }

  updateSelection(firmware, payload, isRunning) {
    const isBundled = firmware === "14.00";
    this.el.payloadMeta.textContent = `[payload] ${payload}`;
    this.el.payloadMeta.setAttribute("aria-disabled", String(isBundled || isRunning));
    this.el.payloadMeta.title = isBundled ? `${firmware} uses its bundled HEN payload` : "select to switch payload";
    this.el.firmwareToggle.textContent = `[version] ${firmware}`;
    this.el.firmwareToggle.setAttribute("aria-pressed", String(isBundled || firmware === "14.02"));
    this.el.firmwareToggle.setAttribute("aria-label", `switch firmware; selected ${firmware}`);
    this.el.firmwareToggle.disabled = isRunning;
  }

  toggleLog() {
    if (this.logLines === 0) return;
    this.el.logBox.classList.toggle("open");
    const isOpen = this.el.logBox.classList.contains("open");
    this.el.logToggle.textContent = isOpen ? "hide terminal" : `terminal (${this.logLines})`;
  }

  setStatus(title, detail, pct) {
    if (title) this.el.stateTitle.textContent = title.toLowerCase();
    if (detail) this.el.stateDetail.textContent = detail.toLowerCase();
    if (pct !== undefined) {
      const clamped = Math.max(0, Math.min(100, pct));
      this.el.progressFill.style.width = clamped + "%";
      this.el.progressText.textContent = clamped + "%";
      this.el.progressText.hidden = clamped === 0;
    }
  }

  log(tag, detail) {
    this.logLines++;
    const line = document.createElement("div");
    line.className = "log-line";
    line.textContent = `[${String(tag).toLowerCase()}] ${String(detail || "").toLowerCase()}`;

    this.el.logBox.appendChild(line);
    this.el.logToggle.disabled = false;
    this.el.logBox.scrollTop = this.el.logBox.scrollHeight;

    const isOpen = this.el.logBox.classList.contains("open");
    if (!isOpen) {
      this.el.logToggle.textContent = `terminal (${this.logLines})`;
    }
  }

}
