Afterglow (WebKitty src/slopkit-afterglow) carries its kernel stage internally:
per-firmware FIRMWARE / BOOTSTRAP_TABLE / PATCH_TABLE tables inside
afterglow.js. No external .bin kpatch is required for the jailbreak-only
path used here; the bundled HEN is loaded locally by runner.js from
../payloads/hen.bin. Upstream has no 1402.bin in src/kpatches.
