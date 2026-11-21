# 14.02 — licensing notice

The files `afterglow.js`, `core.js`, and `memory.js` in this directory are
vendored from [WebKitty](https://github.com/ArabPixel/WebKitty)
(`src/slopkit-afterglow/`, commit `17a30a8` — "Add PS4 14.02 Support") and
remain under their upstream license:

> GNU Affero General Public License v3.0 or later (AGPL-3.0-or-later)

Upstream credits: Afterglow by **m0zz** / **well0nez**, Slopkit by Jordy and
Sonic-Iso, Raw Game PS4 port, ArabPixel/WebKitty host integration.

The Entry4-native files in this directory (`runner.js`, `offsets.js`,
`config.js`, `int64.js` shim, `SOURCE.json`) are Entry4 code that calls into
the vendored AGPL modules. Distributing them together with the AGPL modules
means the combined 14.02 chain must be treated under AGPL-3.0-or-later terms
for that portion (source disclosure, same-license sharing). The payload blob
`payloads/hen.bin` retains its own upstream license.

Do not strip the AGPL headers from the vendored files.
