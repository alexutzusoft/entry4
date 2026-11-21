// Keep the bundled launcher settings shared by the core and native runner.
export const params = new URLSearchParams(
  "log=1&mem=1&slots=9100000&drain=12&hx1400=1&kv=1&fam=0&telemetry=0&stage3=1&stage4=1&stage5=1&stage6=1&stage7=1&stage8=1&stage9=1&stage10=1&goldhen=1"
);
const overrides = new URLSearchParams(location.search);
for (const key of new Set(overrides.keys())) {
  if (key === "firmware") continue;
  params.delete(key);
  for (const value of overrides.getAll(key)) params.append(key, value);
}
