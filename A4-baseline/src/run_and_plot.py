import subprocess
import csv
import numpy as np
import matplotlib.pyplot as plt

NS3_BIN = "./ns3"
RUNS = [1, 2, 3, 4, 5]
FIG8_LOADS = [0.5, 1.5, 3.0, 3.75, 4.5, 6.0, 7.5, 9.0, 12.0, 15.0, 18.0, 30.0]
FIG9_STAS = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16]

# Points de référence extraits des Figures 8 et 9 de Mangold et al. (2003)
ORIG_FIG8_X = [0, 1.5, 3, 3.75, 4.5, 6, 7.5, 9, 12, 15, 18, 30]
ORIG_FIG8 = {
    "VO": [0, 1.5, 3.0, 3.75, 4.5, 6.0, 7.4, 9.0, 12.0, 12.8, 12.8, 12.8],
    "VI": [0, 1.5, 3.0, 3.75, 4.5, 6.0, 5.8, 4.6, 2.1, 1.4, 1.4, 1.4],
    "BE": [0, 1.5, 3.0, 3.75, 4.4, 1.5, 0.8, 0.5, 0.15, 0.05, 0.05, 0.05],
    "BK": [0, 1.5, 3.0, 0.1, 0.1, 0.4, 0.1, 0.1, 0.1, 0.05, 0.05, 0.05],
}

ORIG_FIG9_X = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16]
ORIG_FIG9 = {
    "VO": [1.0, 1.0, 2.9, 4.0, 4.7, 4.5, 3.7, 2.9, 2.3, 1.8, 1.4, 1.1, 0.7, 0.4],
    "VI": [1.0, 2.0, 2.9, 3.9, 3.6, 1.5, 1.1, 0.9, 0.7, 0.6, 0.5, 0.4, 0.25, 0.15],
    "BE": [1.0, 2.0, 2.9, 3.3, 0.05, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02],
    "BK": [1.0, 2.0, 2.9, 0.4, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01],
}

def run_sim(cmd_args):
    cmd = [NS3_BIN, "run", "--no-build", f"a4-80211e-baseline {cmd_args}"]
    out = subprocess.check_output(cmd, text=True).strip().splitlines()[-1]
    parts = out.split(",")
    return parts[0], float(parts[1]), int(parts[2]), [float(x) for x in parts[3:]]

# 1. Compilation préalable
subprocess.check_call([NS3_BIN, "build", "a4-80211e-baseline"])

rows = []
for load in FIG8_LOADS:
    for r in RUNS:
        res = run_sim(f"--scenario=fig8 --offeredPerAcMbps={load} --run={r}")
        rows.append(res)
        print("FIG8", load, "run", r, res[3])

for n in FIG9_STAS:
    for r in RUNS:
        res = run_sim(f"--scenario=fig9 --nStas={n} --run={r}")
        rows.append(res)
        print("FIG9", n, "run", r, res[3])

with open("results_a4.csv", "w", newline="") as f:
    w = csv.writer(f)
    w.writerow(["scenario", "x", "run", "VO", "VI", "BE", "BK"])
    for sc, x, r, vals in rows:
        w.writerow([sc, x, r] + vals)

def aggregate(scenario, xs):
    means = {k: [] for k in ["VO", "VI", "BE", "BK"]}
    stds = {k: [] for k in ["VO", "VI", "BE", "BK"]}
    for x in xs:
        subset = [vals for sc, xv, _, vals in rows if sc == scenario and abs(xv - x) < 1e-6]
        arr = np.array(subset)
        for idx, k in enumerate(["VO", "VI", "BE", "BK"]):
            means[k].append(arr[:, idx].mean())
            stds[k].append(arr[:, idx].std())
    return means, stds

def plot_comparison(xs, means, orig_x, orig_y, xlabel, ylabel, title, filename, xlim):
    plt.figure(figsize=(8, 5.5))
    colors = {"VO": "#d62728", "VI": "#1f77b4", "BE": "#2ca02c", "BK": "#9467bd"}
    markers = {"VO": "x", "VI": "o", "BE": "+", "BK": "D"}
    for k in ["VO", "VI", "BE", "BK"]:
        plt.plot(xs, means[k], color=colors[k], marker=markers[k], linewidth=2, label=f"ns-3 AC_{k}")
        plt.plot(orig_x, orig_y[k], color=colors[k], linestyle="--", alpha=0.55, label=f"Paper AC_{k}")
    plt.plot([0, 14], [0, 14], "k:", label="Total offer per AC")
    plt.xlim(xlim)
    plt.ylim(0, 14)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True, linestyle=":", alpha=0.6)
    plt.legend(ncol=2, fontsize=8)
    plt.tight_layout()
    plt.savefig(filename, dpi=200)

m8, _ = aggregate("fig8", FIG8_LOADS)
plot_comparison(FIG8_LOADS, m8, ORIG_FIG8_X, ORIG_FIG8,
                "Offered traffic per AC (3 streams each) (Mb/s)",
                "Throughput per AC (3 streams each) (Mb/s)",
                "Figure 8 Reproduction: EDCA Throughput vs. Offered Load",
                "fig8_reproduction.png", (0, 30))

m9, _ = aggregate("fig9", FIG9_STAS)
plot_comparison(FIG9_STAS, m9, ORIG_FIG9_X, ORIG_FIG9,
                "Number of transmitting stations, each offering 4 x 1 (Mb/s)",
                "Throughput per AC (Mb/s)",
                "Figure 9 Reproduction: EDCA Throughput vs. Number of Stations",
                "fig9_reproduction.png", (1, 16))
