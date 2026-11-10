# Assignment 3: Literature Review & Revised Project Proposal

- **Course:** 2026 Multimedia Wireless Networks
- **Student Name:** Ledrappier Abel
- **Student ID:** E115020088
- **Date:** November 10, 2026
- **Assigned Reference Paper:** S. Mangold, S. Choi, G. R. Hiertz, O. Klein, and B. Walke, *"Analysis of IEEE 802.11e for QoS support in wireless LANs,"* IEEE Wireless Communications, vol. 10, no. 6, pp. 40–50, Dec. 2003.

---

## 1. Literature Review: Analysis of IEEE 802.11e for QoS Support in WLANs

### 1.1 Problem, Importance, and Challenges

- **Legacy DCF Limitations:** The original Distributed Coordination Function (DCF) operates as an uncoordinated, best-effort listen-before-talk CSMA/CA protocol. Every station contends with identical interframe spaces (DIFS) and contention windows (CWmin = 15, CWmax = 1023 in 802.11a). It offers zero service differentiation; voice or interactive video frames compete on an equal footing with bulk file transfers.
- **Legacy PCF Failures:** The Point Coordination Function (PCF) attempted centralized polling but introduced critical design flaws:
  - **Unpredictable Beacon Delays:** Under legacy rules, a station may transmit across the Target Beacon Transmission Time (TBTT), causing up to 4.9 ms beacon jitter in 802.11a.
  - **Uncontrolled Polling Durations:** Polled stations transmit MSDUs of arbitrary length (up to 2304 bytes), preventing the Point Coordinator from enforcing deterministic bounded delays.
- **Importance:** Interactive multimedia services (VoIP, video conferencing, low-latency streaming) impose strict latency, jitter, and throughput thresholds that cannot tolerate legacy channel access delays.
- **Challenges:** Implementing distributed priority queues without inducing starvation in low-priority services, bounding channel occupancy, and preventing collision collapse in dense wireless environments.

### 1.2 System Model

- **Network Architecture:** Infrastructure QoS Basic Service Set (QBSS) with a Hybrid Coordinator (HC) co-located at the Access Point (AP) managing associated QoS-enabled Stations (QSTAs). The paper evaluates both isolated QBSS and multi-cell Overlapping QBSS (OBSS) environments.
- **PHY Layer:** IEEE 802.11a operating in the 5 GHz band. Data rate set to 24 Mb/s (OFDM), control frame transmission at 6 Mb/s. Slot time = 9 us, SIFS = 16 us, PIFS = 25 us, DIFS = 34 us.
- **Traffic Model:** Downlink packet generation from the AP/HC to stations. 512-byte MAC Service Data Units (MSDUs) with negative-exponentially distributed inter-arrival times across 4 concurrent streams per station (250 kb/s baseline per stream). Isochronous 802.11e delay evaluation uses 80-byte periodic frames (128 kb/s) and 200-byte exponential frames (160 kb/s).
- **QoS Parameters & Mapping:** 8 priority levels (IEEE 802.1D) mapped to 4 Access Categories (ACs), each handled by an independent parallel backoff entity:
  - Formula: AIFS[AC] = SIFS + AIFSN[AC] * aSlotTime

| Access Category | Target Application | AIFSN | AIFS (us) | CWmin | CWmax | TXOPlimit |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **AC_VO** | Voice | 2 | 34 us (= DIFS) | 7 | 15 | 1 MSDU |
| **AC_VI** | Video | 2 | 34 us (= DIFS) | 15 | 31 | 1 MSDU |
| **AC_BE** | Best Effort | 3 | 43 us | 31 | 1023 | 1 MSDU |
| **AC_BK** | Background | 7 | 79 us | 31 | 1023 | 1 MSDU |

- **Performance Metrics:**
  - Aggregate MAC-layer saturation throughput (Mb/s) per Access Category.
  - Complementary Cumulative Distribution Function (CCDF) of MSDU delivery delay: Prob(Delay > x) computed using the discrete Limited-Relative-Error (LRE) algorithm with a relative error bound <= 5%.

### 1.3 Key Experimental Results

- **Traffic Differentiation (Figure 8):** As aggregate offered load exceeds 4 Mb/s per AC, EDCA enforces clear priority tiers. High-priority traffic (AC_VO and AC_VI) captures up to ~14 Mb/s aggregate throughput, while lower-priority traffic (AC_BE and AC_BK) is throttled to near zero.
- **High-Density Collision Collapse (Figure 9):** When scaling the number of contending stations from 1 to 16 with fixed traffic, AC_VO throughput collapses sharply beyond 5 stations. Because CWmin = 7 is fixed and narrow, multiple voice backoff entities repeatedly select identical backoff timers, creating catastrophic collision chains.
- **HCCA Bounded Latency (Figure 10):** Under controlled access (HCCA), polled stations strictly adhere to delivery delays within the TXOPlimit in an isolated BSS. However, in Overlapping QBSS (OBSS) setups, co-channel polling collisions between unsynchronized HCs cause severe delay spikes.

> **A4 Baseline Selection:** Figure 8 is selected as the reproduction baseline for Assignment 4. It isolates EDCA differentiation mechanics without multi-AP coordination artifacts, providing a deterministic validation target for ns-3.

---

## 2. Experimental Setup for ns-3 Reproduction (Targeting Assignment 4)

| Configuration Parameter | Target Simulation Value | ns-3 Implementation Class / Attribute |
| :--- | :--- | :--- |
| **Network Topology** | 1 Access Point (HC), 3 associated STAs | `NodeContainer`, `WifiNetDevice` |
| **PHY Standard & Band** | IEEE 802.11a, 5 GHz | `WifiHelper::SetStandard(WIFI_STANDARD_80211a)` |
| **Data / Control Rates** | Data: 24 Mb/s; Control: 6 Mb/s | `ConstantRateWifiManager::DataMode("OfdmRate24Mbps")` |
| **Traffic Pattern** | 512-byte payload, exponential inter-arrival | `OnOffApplication` (DataRate varied 0–30 Mb/s) |
| **MAC Queue Configuration** | 4 QoS Access Categories | `QosTxop` (via `ns3::QosFrameExchangeManager`) |
| **AIFS Parameters** | VO=2, VI=2, BE=3, BK=7 | `ns3::QosTxop::SetAifsn(...)` |
| **Contention Windows** | VO:[7,15], VI:[15,31], BE/BK:[31,1023] | `ns3::QosTxop::SetMinCw(...)` / `SetMaxCw(...)` |
| **Bursting / TXOP Limit** | 1 MSDU per transmission opportunity | `ns3::QosTxop::SetTxopLimit(MicroSeconds(0))` |
| **Run Count & Seeds** | 10 independent seeds per load point | `RngSeedManager::SetSeed()` / `SetRun()` |

---

## 3. Revised Project Proposal (Pivot to Basic Path)

### 3.1 Motivation for Track Revision

- **Software Stack Instability:** In Assignment 1, I proposed evaluating 5G-NTN satellite channel modeling. During Assignment 2 environment verification, available third-party open-source NTN extensions for ns-3 exhibited breaking dependencies, outdated build chains, and missing documentation for multi-carrier Doppler channels.
- **Alignment with Assignment Chain:** The course assignments form an unbroken chain: A2 (Setup) -> A3 (Literature Review) -> A4 (Baseline Reproduction) -> Final Project (Modification). The native `src/wifi` module in ns-3 fully supports 802.11e EDCA, providing a stable, verifiable platform for exact baseline reproduction.

### 3.2 Proposed Final Project Modification

- **Identified Deficiency:** Figure 9 of the Mangold paper proves that static EDCA contention parameters experience severe collision collapse when the number of contending stations scales up (CWmin = 7 causes excessive collisions among voice streams).
- **Proposed Improvement:** Design and implement an *Adaptive Contention Window (A-EDCA)* mechanism based on recent literature (such as Yang Xiao's AEDCF model). The AP dynamically monitors channel busy ratios and retransmission attempt flags, broadcasting adjusted CWmin bounds in periodic Beacon elements to mitigate congestion collapse under high station density.
- **Validation Plan:** Compare the adaptive mechanism against the baseline static 802.11e implementation across 1 to 16 stations, measuring improvements in voice throughput retention and latency stability.
