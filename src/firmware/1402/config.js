// Keep the 14.02 launcher settings shared by the Afterglow runner.
// attempts mirrors WebKitty jb.js (params.attempts || 8); tries is the
// runAfterglow retry budget (default 4 in afterglow).
export const params = new URLSearchParams("log=1&attempts=8&tries=4");
const overrides = new URLSearchParams(location.search);
for (const key of new Set(overrides.keys())) {
  if (key === "firmware") continue;
  params.delete(key);
  for (const value of overrides.getAll(key)) params.append(key, value);
}
