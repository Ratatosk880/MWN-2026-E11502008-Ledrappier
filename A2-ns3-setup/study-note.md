# A2 — ns-3 Setup & Traffic Model (Study Note)

## 1. Environment & Setup Details

* **ns-3 Version**: ns-3.48 (Archive `ns-allinone-3.48.tar.bz2`)
* **Platform**: Linux (Ubuntu 64-bit / Debian-based distribution)
* **Installation Steps**:
  1. Downloaded and extracted the `ns-allinone-3.48.tar.bz2` archive on [ns-3 website](https://www.nsnam.org/releases/ns-3-48/).
  2. Installed core build tools and dependencies.
  3. Configured the simulator using the CMake wrapper:
     ```bash
     ./ns3 configure --enable-examples --enable-tests
     ```
  4. Built the project:
     ```bash
     ./ns3 build
     ```
* **Issues Encountered & Fixes**:
  * **Error**: `no such file or directory 'cmake'` during `./ns3 configure`.
  * **Cause**: CMake and Ninja build systems were missing on the host environment.
  * **Resolution**: Installed the missing packages via the package manager:
    ```bash
    sudo apt update && sudo apt install -y cmake ninja-build build-essential
    ```

---

## 2. Traffic Model Specification (3GPP TR 26.926)

The implemented model adheres to the **3GPP TR 26.926** technical report (Release 19) for **XR Split Rendering and Cloud Gaming** services (Clause 6.5.3, Annex B.2/B.3):
* **Frame Periodicity**: Generated periodically at 60 fps (inter-frame arrival time of $16.66\text{ ms}$).
* **Frame Size**: Modeled using a truncated Gaussian distribution ($\text{Mean} = 25\text{ KB}$, $\text{STD} = 5\text{ KB}$).
* **MTU Segmentation**: Video frames are packetized into UDP/IP datagrams capped at the standard link MTU (1488–1500 bytes).
* **Burst Behavior**: Packets belonging to the same video frame are transmitted with a short intra-burst inter-arrival time ($IAT = 0.2\text{ ms}$).

---

## 3. Source Code & Execution

* **Source File**: `scratch/a2_xr_model.cc`
* **Run Command**:
  ```bash
  ./ns3 run scratch/a2_xr_model

---

## 4. Results & Traffic Model Verification

### 4.1. Packet Capture (Wireshark)

Local execution is verified via Wireshark on the point-to-point link between nodes `10.1.1.1` and `10.1.1.2`:

![Wireshark Packet List](path/to/screenshot1.png)
*Wireshark packet list showing UDP packets: columns No., Time, Source (10.1.1.1), Destination (10.1.1.2), Length (~1500 B), and Delta Time (alternating between 0.2 ms within bursts and ~13–14 ms between bursts).*

![Wireshark IO Graphs](path/to/screenshot2.png)
*(Optional) Wireshark Statistics > I/O Graphs window showing throughput bursts repeating at 60 Hz.*

### 4.2. Statistical Distributions (PDF & CDF)

The probability density function (PDF) and cumulative distribution function (CDF) were computed using Python (`plot_cdf_pdf.py`) from `results/traffic_stats.txt`:

![Traffic Model PDF and CDF](path/to/traffic_model_cdf_pdf.png)
*Empirical distributions generated from the simulation trace.*

#### Analysis of Empirical Distributions

* **Packet Size Distribution (PDF/CDF)**:
  * The vast majority of packets peak sharply at 1488–1500 bytes (visible via the single PDF spike and the vertical jump at 1500 B on the CDF).
  * This aligns with the 3GPP MTU segmentation model: large XR video frames (20–25 KB) are sliced into full-sized MTU datagrams, with only the remaining tail fragment accounting for smaller sizes.

* **Inter-Arrival Time (IAT) Distribution (PDF/CDF)**:
  * **0.2 ms Spike**: Represents over 94% of observed intervals (observable on the PDF and the immediate jump to ~0.95 on the CDF). This reflects the intra-burst packet arrival time as consecutive fragments of a frame are dispatched.
  * **12–15 ms Plateau**: Accounts for the remaining ~5% of intervals (the plateau and upper elbow of the CDF). This corresponds to the inter-frame idle period at 60 fps ($16.66\text{ ms} - \text{burst duration}$), validating the 3GPP frame generation periodicity.
