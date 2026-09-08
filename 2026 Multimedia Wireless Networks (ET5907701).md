---
title: 2026 Multimedia Wireless Networks (ET5907701)

---

# <center> 2026 Multimedia Wireless Networks (ET5907701) </center>

[TOC]


# 1. Introduction

## 1.1. Person in Charge

- **Instructor**: Prof. Ray-Guang Cheng (Email: <crg@gapps.ntust.edu.tw>)
- **Teaching Assistants**:
  1.  Joshevan (Email: <m11302832@gapps.ntust.edu.tw>)
  2.  Winnie (Email: <m11402207@mail.ntust.edu.tw>)


## 1.2. Course Detail

1. [LINE group](https://line.me/R/ti/g/G-779Fj8Pw):
![image](https://hackmd.io/_uploads/B1LAF-h_fg.png)



2. Slides on [Moodle]().
3. Youtube playlist of course recordings:
    * [2025](https://www.youtube.com/playlist?list=PLNxlEcQdkOt_qHBq-W7T_eMtIJe3Ebryz)
    * 2026

4. [Q&A Google Form](https://forms.gle/ANi92ZCXxD61vP8t7).
  
  > [!IMPORTANT] 
  > This form is only opened during the course session
  <!-- > 1. You can only use NTUST gapps account to input ([NTUST gapps application instruction](https://forms.gle/WLK8a5GDFpjT9AKLA)). -->

  > [!TIP]
  > Submit your Q&A **immediately** after raising or answering question in class.

  > [!CAUTION]
  > We won't count your Q&A outside the course session.


## 1.3 Initial ToDo
1. Create a [GitHub account](https://github.com/join).
2. Provide your github account & repository to be used in this course in this [Google form](https://forms.gle/qataUNg49DX6qdiY9).
3. Read the [GitHub markdown features](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax) information.
4. Download [Visual Studio Code](https://code.visualstudio.com/download) (for study notes writing).
  
  > [!TIP]
  Read how to generate automatic [Table of Content (ToC)](https://marketplace.visualstudio.com/items?itemName=yzhang.markdown-all-in-one#table-of-contents) using [Markdown All in One](https://marketplace.visualstudio.com/items?itemName=yzhang.markdown-all-in-one) extension.

5. Create your own repository using this format: `MWN-[year]-[student ID]-[English Name]`.
    
    Ex: `MWN-2026-M11302832-Joshevan`
6. Copy the content of the [template folder](=https://github.com/Joshevanch/2026-Multimedia_Wireless_Networks/tree/main/branch-template) to your own branch & update your profile information in your README.md file.

<!-- ## Announcement (NEW!)
Dear all,
The slides for opening and Part-I are uploaded. Please refer to [Schedule](#Schedule).
Ray -->

# 2. Course Outline
## 2.1. Objectives

1. This course introduces the **basic knowledge of Quality-of-Service (QoS)**. Four main issues will be addressed:
    1. Multimedia Applications: Traffic Model 
    2. QoS Fundamentals 
    3. QoS Mechanisms 
    4. Selected Standards

  > [!NOTE]
  >We give an overview of the multimedia application. The fundamentals of Quality of Service (QoS) is then introduced. Some commonly used QoS Mechanisms will be given. Finally, we will use some popular wireless standards as examples to illustrate the usage of the QoS mechanisms. (The assessment for this part is through **Midterm Exam**).

2. **Research** & **presentation** skills practice through 4 assignments and a final project: background study notes → ns-3 setup → literature review → baseline reproduction → your own modification.

  > [!TIP]
  > Readme First: [The jobs of the future – and two skills you need to get them](https://www.weforum.org/agenda/2016/09/jobs-of-future-and-skills-you-need)

## 2.2. Schedule

**Fall 2026 — 16 weeks, Tuesdays, 9/8 – 12/22.**

Every Assignment is due **08:00 A.M. on the morning of its presentation**, in your GitHub repository.

Five presentations: 
* **[A1 — Background Study Notes](#A1-%E2%80%94-Background-Study-Notes)** (Week 4, 5 min) or **Midterm**
* **[A2 — ns-3 Setup & Traffic Model](#A2-—-ns-3-Setup-amp-Traffic-Model)** (Week 7, 10 min)
* **[A3 — Literature Review](#A3-%E2%80%94-Literature-Review)** (Week 11, 10 min)
* **[A4 — Baseline Reproduction](#A4-%E2%80%94-Baseline-Reproduction)** (Week 13, 15 min) 
* **Final Project** (Weeks 15–16, 20 min
* Each presentation followed by Q&A.

The four assignments form one chain — the topic you propose in Week 4 is the one whose modification you defend in Week 15 or 16.

| Week                   | Date  | Core Topic                                                                                                          |
|:---------------------- |:----- |:------------------------------------------------------------------------------------------------------------------- |
| **Week 1**             | 9/8   | [Opening]() — Introduction and Environment Setup                                                                    |
| **Week 2**             | 9/15  | QoS Fundamentals                                                                                                    |
| **Week 3**             | 9/22  | **[A1 — Background Study Notes](#A1-%E2%80%94-Background-Study-Notes) presentation** (5 min) *hyperlink template    |
| **Week 4**             | 9/29  | QoS Mechanisms 1                                                                                                    |
| **Week 5**             | 10/6  | QoS Mechanisms 2                                                                                                    |
| **Week 6**             | 10/13 | QoS Mechanisms 3                                                                                                    |
| **Week 7**             | 10/20 | **[A2 — ns-3 Setup & Traffic Model](#A2-—-ns-3-Setup-amp-Traffic-Model) presentation** (10 min) *hyperlink template |
| **Week 8**             | 10/27 | WiFi MAC                                                                                                            |
| **Week 9**            | 11/3 | 802.11e Enhanced Distributed Channel Access (EDCA) 1                                                                |
| **Week 10**             | 11/10  | **[A3 — Literature Review](#A3-%E2%80%94-Literature-Review) presentation** (10 min) *hyperlink template             |
| **Week 11**            | 11/17 | 802.11e Enhanced Distributed Channel Access (EDCA) 2                                                                |
| **Week 12**            | 11/24 | 802.11e Enhanced Distributed Channel Access (EDCA) 3                                                                |
| **Week 13**            | 12/1  | **[A4 — Baseline Reproduction](#A4-%E2%80%94-Baseline-Reproduction) presentation** (15 min) *hyperlink template     |
| **Week 14**            | 12/8  | 5G QoS                                                                                                              |
| **Week 15**            | 12/15 | **Final presentation** (20 mins) — first half of the class  (basic)                                                 |
| **Week 16**            | 12/22 | **Final presentation** (20 mins) · **Final report due 08:00**   (advanced)                                          |
| Juniper eLearning - I  |       | [Getting Started with Networking](https://learningportal.juniper.net/juniper/user_transcript.aspx)                  |
| Juniper eLearning - II |       | [Getting Started with Wi-Fi](https://learningportal.juniper.net/juniper/user_transcript.aspx)                       |

> [!NOTE]
> **Two paths.** Choose one in A1 and keep it to the end. The assignments, the deadlines and the grading criteria are identical on both — only the topic and the final presentation week differ.
>
> 1. **Basic — reproduce 802.11e.** Work from the assigned paper [Analysis of IEEE 802.11e for QoS support in wireless LANs](https://ieeexplore.ieee.org/document/1265851). Everything you need is covered by the Week 8–12 lectures. Final presentation in **Week 15**.
> 2. **Advanced — bring your own topic.** NTN, 5G, newer WiFi (802.11ax / 802.11be), or another QoS problem you care about — a thesis topic is welcome. You choose the paper and the simulator (ns-3 WiFi / ns-3 NTN / OAI 5G). Final presentation in **Week 16**.

## 2.3. Evaluation
Two options. They differ only in whether there is a **midterm exam** — the schedule, the assignments and the [grading criteria](#Grading-criteria-%E2%80%94-the-same-for-every-assignment) are identical in both.

**Option A — No exam**

| Component                                                    | What it measures                                          | Weight   |
| :----------------------------------------------------------- | :--------------------------------------------------------- | -------: |
| Q&A / class participation                                     | Weekly, up to 15 pts (1 pt/week)                            | **15%**  |
| [A1 — Background Study Notes](#A1-%E2%80%94-Background-Study-Notes)    | Presentation skill, paper reading, first project proposal   | **10%**  |
| [A2 — ns-3 Setup & Traffic Model](#A2-—-ns-3-Setup-amp-Traffic-Model) | ns-3 installed and a scenario on your topic running    | **15%**  |
| [A3 — Literature Review](#A3-%E2%80%94-Literature-Review)              | Papers studied, system model, revised proposal              | **15%**  |
| [A4 — Baseline Reproduction](#A4-%E2%80%94-Baseline-Reproduction)      | Reproducing the paper's result in ns-3                      | **20%**  |
| [Final Project](#Final-Project-%E2%80%94-Your-Modification)            | Your modification, results, and final report                | **25%**  |
| **Total**                                                     |                                                             | **100%** |

**Option B — with midterm exam** *(held in Week 8, 10/27)*

| Component                                                    | What it measures                                          | Weight   |
| :----------------------------------------------------------- | :--------------------------------------------------------- | -------: |
| Q&A / class participation                                     | Weekly, up to 15 pts (1 pt/week)                            | **15%**  |
| [A2 — ns-3 Setup & Traffic Model](#A2-—-ns-3-Setup-amp-Traffic-Model) | ns-3 installed and a scenario on your topic running    | **15%**  |
| [A3 — Literature Review](#A3-%E2%80%94-Literature-Review)              | Papers studied, system model, revised proposal              | **15%**  |
| [A4 — Baseline Reproduction](#A4-%E2%80%94-Baseline-Reproduction)      | Reproducing the paper's result in ns-3                      | **15%**  |
| **Midterm Exam (Week 8)**                                     | QoS Fundamentals and QoS Mechanisms (Weeks 2–6)             | **20%**  |
| [Final Project](#Final-Project-%E2%80%94-Your-Modification)            | Your modification, results, and final report                | **20%**  |
| **Total**                                                     |                                                             | **100%** |


>[!NOTE] 
> The final score of this course can be adjusted to meet the requirements from our department:
> 
> 研究所   標準平均：3.1 ~3.8    (百分數：77 ~ 85.67)
>
> Extra work for score adjustment will be given **after the Final Score is released**.

## 2.4. Assignments

Four assignments plus a final project, one per presentation week. Each deliverable is due **08:00 A.M. on the morning of its presentation** and lives in your own `MWN-2026-[student ID]-[English Name]` GitHub repository.

| Assignment                                                    | Due & presented   | Time   |
| :------------------------------------------------------------ | :---------------- | :----- |
| [A1 — Background Study Notes](#A1-%E2%80%94-Background-Study-Notes)     | Week 4 · 9/29     | 5 min  |
| [A2 — ns-3 Setup & Traffic Model](#A2-—-ns-3-Setup-amp-Traffic-Model) | Week 7 · 10/20 | 10 min |
| [A3 — Literature Review](#A3-%E2%80%94-Literature-Review)               | Week 11 · 11/17   | 10 min |
| [A4 — Baseline Reproduction](#A4-%E2%80%94-Baseline-Reproduction)       | Week 13 · 12/1    | 15 min |
| [Final Project](#Final-Project-%E2%80%94-Your-Modification)             | Week 15 *(basic)* / Week 16 *(advanced)* | 20 min |

### Grading criteria — for all assignments and the final presentation
* Basic rule: show us you results along with the evidence. You are welcome to use AI for assistance but **need to understand everything you write down on GitHub and present**.
* **50% Documents**
  * **30% Study Notes** — Markdown files in your GitHub repository.
  * **20% Rehearsal Presentation** — record yourself presenting your slides with [PowerPoint Speaker Coach](https://support.microsoft.com/en-us/powerpoint/rehearse-your-slide-show-with-speaker-coach), have an LLM review the recording and your slides, and include the feedback in your repository.
* **50% Presentation & Q&A** — the live session.


### A1 — Background Study Notes

**Week 3 · 9/22, due 08:00 A.M. — presented 5 min**

* **Purpose:** Build the shared toolkit — how to present, how to read a paper — and put your first project idea on the table.
* **Tasks:** write a study note on each of:
  1. **Five-minute presentation** ([[1]](https://www.thebalancesmb.com/mastering-the-art-of-the-5-minute-presentation-2951697), [[2]](https://www.youtube.com/watch?v=YVgS_opYacQ))
  2. **[How to Read a Paper](https://web.stanford.edu/class/ee384m/Handouts/HowtoReadPaper.pdf)**
  3. **Your project proposal** — which path you are taking (basic or advanced), the problem, and what you would measure. It is a first draft; you revise it in A3.

### A2 — ns-3 Setup & Traffic Model

**Week 7 · 10/20, due 08:00 A.M. — presented 10 min**

* **Purpose:** Get the simulator working and prove it with something of your own.
* **Tasks:**
  * **Install ns-3** and build it. Document the version, the platform, and anything that broke.
  * Study **3GPP specification for Traffic Model** ([3GPP TS 26.926](https://www.3gpp.org/ftp/Specs/archive/26_series/26.926/26926-j00.zip)). Use AI to generate the 3GPP traffic model or build-in [ns-3](https://www.nsnam.org/docs/models/html/applications.html) model to generate packets. 
  * Show a result from your own run: a throughput or delay number, a trace, a PCAP opened in Wireshark. Anything that proves the simulator is yours and running. Verify your traffic model by showing the pdf/CDF of the packet size distribution and the inter-arrival time distribution that you generated. 

### A3 — Literature Review

**Week 10 · 11/10, due 08:00 A.M. — presented 10 min**

* **Purpose:** Study the papers behind your topic and turn them into an experiment you could run.
* **Tasks:**
  * Select **1–3 IEEE papers** on your topic. For the basic path, the assigned 802.11e paper is the starting point.
  * For each paper, write down:
    * **Problem, Importance, Challenges**
    * **System Model** — Environment, Inputs, Outputs, Performance Metrics
    * **Experimental Results** — the ns-3 settings needed to reproduce them (topology, traffic model, PHY/MAC parameters, simulation time, seeds)
  * **Revise your project proposal** from A1 in light of what you read — state explicitly what changed and why.

### A4 — Baseline Reproduction

**Week 13 · 12/1, due 08:00 A.M. — presented 15 min**

* **Purpose:** Reproduce a published result. This is your baseline for the final project.
* **Tasks:**
  * Choose **one result** from your paper and reproduce it in ns-3 — same figure, same axes, plotted against the original where possible.
  * Explain the differences. A curve that does not match is a result too, as long as you can say *why*: parameter mismatch, unmodelled effect, different traffic model, too few runs.
  * Report the **parameters, seeds and number of runs** so someone else can repeat it.

### Final Project — Your Modification

**Week 15 *(basic path)* / Week 16 *(advanced path)* — presented 20 min · Final report due 12/22, 08:00 A.M.**

* **Purpose:** Change something, and show what the change did.
* **Tasks:**
  * Start from your A4 baseline and **add a modification** — a different traffic model, a different channel model, another scenario, a parameter policy, a protocol tweak.
  * Evaluate it against the baseline on the metrics you defined in A3.
  * Submit the **final report** (Markdown, in your repository): problem and motivation, related work, system model, ns-3 setup, baseline reproduction, your modification, results, limitations.


<!-- # 3. Paper Studies

## 3.1. Potential Topics for 
1. WiFi Simmulation using ns-3
2. Joint Communication and Sensing in WiFi

Reference:
1. [Learning the 802.11 Standard](https://blogs.arubanetworks.com/solutions/learning-the-802-11-standard/)
2. [RTI DDS Document](https://community.rti.com/static/documentation/connext-dds/5.2.0/doc/manuals/connext_dds/html_files/RTI_ConnextDDS_CoreLibraries_UsersManual/index.htm#UsersManual/AvailableDocs.htm%3FTocPath%3D_____2) -->


# References
- [IEEE 802.11 Documents](https://mentor.ieee.org/802.11/documents?is_dcn=Random%20access&is_group=00be&is_options=1&is_year=2021)
- [IEEE 802.11be D 1.31](https://www.ieee802.org/11/private/Draft_Standards/11be/Draft%20P802.11be_D1.31.pdf)
- [Learning the 802.11 Standard](https://blogs.arubanetworks.com/solutions/learning-the-802-11-standard/)
- [Tricks to Read and Understand 3GPP Specifications](http://www.3glteinfo.com/tricks-to-read-and-understand-3gpp-specifications/)
- [Introduction to 802.11ax](https://www.tele.soumu.go.jp/resource/j/equ/mra/pdf/30/e/15.pdf)
- [Wi-Fi 6 OFDMA: Resource unit (RU) allocations and mappings](https://blogs.cisco.com/networking/wi-fi-6-ofdma-resource-unit-ru-allocations-and-mappings)
- [GitHub Markdown Features](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Ultralearning by Scott Young](https://www.scotthyoung.com/blog/ultralearning/)
- [Time Management by Randy Pausch](https://www.youtube.com/watch?v=JKBFwR1HIFU)
- [ns-3 Tutorial](https://www.nsnam.org/docs/tutorial/html/)
- [Wireshark User's Guide](https://www.wireshark.org/docs/wsug_html_chunked/)
- Flowchart for the Simulation for Wireless QoS Systems (by GeminiLM)
![image](https://hackmd.io/_uploads/HyZ0j8h_fl.png)


# Samples
- [2019](https://hackmd.io/PT5GnfcETu-eMZWV_DHWPQ?view&fbclid=IwAR3cCQZOzJSczTz4s53SW3EXwmHf_aFAmeC0ClxvgH5bB5KVIvMuCvh3nuk#Proposal-of-final-project)
- [2020](https://hackmd.io/74Xn924wT9mlqwTU4sYB1A#Final-Project)
