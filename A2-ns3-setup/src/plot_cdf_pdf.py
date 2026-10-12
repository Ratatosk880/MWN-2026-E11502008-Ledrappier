import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("traffic_stats.txt", skip_header=1)
packet_sizes = data[:, 1]
inter_arrivals = data[1:, 2]

fig, axs = plt.subplots(2, 2, figsize=(11, 8))

# 1. Packet Size PDF
axs[0, 0].hist(packet_sizes, bins=30, density=True, color='royalblue', edgecolor='black')
axs[0, 0].set_title("3GPP TR 26.926 - Packet Size PDF")
axs[0, 0].set_xlabel("Size (Bytes)")
axs[0, 0].set_ylabel("Probability Density")

# 2. Packet Size CDF
sorted_size = np.sort(packet_sizes)
cdf_size = np.arange(1, len(sorted_size) + 1) / len(sorted_size)
axs[0, 1].plot(sorted_size, cdf_size, color='darkblue', linewidth=2)
axs[0, 1].set_title("3GPP TR 26.926 - Packet Size CDF")
axs[0, 1].set_xlabel("Size (Bytes)")
axs[0, 1].set_ylabel("CDF")

# 3. Inter-arrival Time PDF
axs[1, 0].hist(inter_arrivals, bins=40, density=True, color='salmon', edgecolor='black')
axs[1, 0].set_title("3GPP TR 26.926 - Inter-Arrival Time PDF")
axs[1, 0].set_xlabel("Interval (ms)")
axs[1, 0].set_ylabel("Probability Density")

# 4. Inter-arrival Time CDF
sorted_ia = np.sort(inter_arrivals)
cdf_ia = np.arange(1, len(sorted_ia) + 1) / len(sorted_ia)
axs[1, 1].plot(sorted_ia, cdf_ia, color='crimson', linewidth=2)
axs[1, 1].set_title("3GPP TR 26.926 - Inter-Arrival Time CDF")
axs[1, 1].set_xlabel("Interval (ms)")
axs[1, 1].set_ylabel("CDF")

plt.tight_layout()
plt.savefig("traffic_model_cdf_pdf.png")
print("Graphique généré dans results/traffic_model_cdf_pdf.png")
