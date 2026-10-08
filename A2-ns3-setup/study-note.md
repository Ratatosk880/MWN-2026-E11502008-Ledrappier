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
