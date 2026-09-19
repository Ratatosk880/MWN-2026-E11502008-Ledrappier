# A1 - Background

---

## 1. Five-Minute Presentation: Designing Effective Slides

Based on the tutorial by Jennie Goforth (Design Lab), here is a summary of the 5 core tips for creating clean, impactful, and visually engaging presentation slides:

### Tip 1: Keep It Simple
* **Audience Attention:** The primary goal is to have the audience focused on the speaker, not distracted by the slides.
* **Avoid Complex Templates:** Pre-made themes and templates are often overused, generic, or unnecessarily complicated. 
* **Start from Scratch:** Don't hesitate to begin with a blank canvas to ensure slides stay minimal and purposeful.

### Tip 2: Never Read from Your Slides
* **Cognitive Load:** The human brain struggles to process spoken audio and read written text at the same time. If slides are text-heavy, the audience stops listening.
* **Minimize Words:** Limit slide text to concise keywords or phrases that support memory retention.
* **Readability:** Use large, clear, and easy-to-read fonts so people at the back of the room can see effortlessly.
* **One Point Per Slide:** Avoid bulleted lists that reveal multiple points at once, as the audience will read ahead instead of focusing on what you are currently saying. Split points across separate slides.

### Tip 3: Use Beautiful Photos
* **Emotional Connection:** High-quality visuals evoke emotional responses that reinforce your message.
* **Full-Bleed Layout:** A single high-impact image stretched edge-to-edge across the slide is often the most effective design choice.
* **Authenticity & Quality:** Avoid cliché stock photography. Use clear images with a minimum resolution of $1920 \times 1280\text{ px}$ to prevent pixelation.
* **Licensing:** Ensure you have appropriate rights or permissions to use each image.
* **Rule of Thirds:** Position the image's focal point along grid intersections to create dynamic composition and leave clean negative space for minimal text.

### Tip 4: Keep Data Simple
* **Purpose of Data:** Data is persuasive, but standard charts and infographics are frequently overcrowded with tiny labels and extraneous detail.
* **Declutter & Adapt:** Instead of pasting an intricate infographic, extract only the essential data points relevant to your core argument and recreate a cleaner, simplified graphic.
* **Fidelity:** Always ensure simplified representations remain strictly accurate and faithful to the original data source.

### Tip 5: Repetition (Visual Consistency)
* **Cohesion:** Repeating consistent design choices throughout the deck gives the presentation a professional, unified look.
* **Typography:** Select a single font family for the entire deck.
* **Color Palette:** Limit your visual palette to $2\text{–}3$ complementary colors and apply them consistently.
* **Layout:** Maintain uniform structural layouts and alignment across all slides.

---

## 2. How to Read a Paper
Based on S. Keshav’s "three-pass" method for efficiently reading research papers and conducting literature surveys.

### The Three-Pass Approach

* **First Pass (Bird's-Eye View):**
  * **Duration:** 5 to 10 minutes.
  * **Procedure:** Read title, abstract, and introduction carefully; scan section and subsection headings; read the conclusions; glance through references.
  * **Objective (The Five Cs):**
    * **Category:** Type of paper (measurement, analysis, prototype).
    * **Context:** Related work and theoretical foundations used.
    * **Correctness:** Validity of the underlying assumptions.
    * **Contributions:** Main findings and claimed contributions.
    * **Clarity:** Quality of writing and readability.
  * **Decision:** Determine whether to stop reading, set it aside, or continue to Pass 2.

* **Second Pass (Grasp Content, Ignore Details):**
  * **Duration:** Up to 1 hour.
  * **Procedure:** Read with care while skipping complex mathematical proofs or low-level mechanisms; annotate key points and margins.
  * **Visuals & Graphs:** Scrutinize figures, diagrams, and axes labels; verify whether results include error bars and demonstrate statistical significance.
  * **Outcome:** Ability to summarize the main arguments with supporting evidence. If stuck, choose whether to abandon, revisit later, or move to Pass 3.

* **Third Pass (In-Depth Understanding & Virtual Re-implementation):**
  * **Duration:** 4 to 5 hours for beginners, ~1 hour for experienced readers.
  * **Procedure:** Virtually re-implement the paper by adopting the authors' assumptions and recreating the work from scratch.
  * **Critical Analysis:** Challenge every statement and assumption; identify implicit assumptions, missing citations, or methodological flaws.
  * **Outcome:** Ability to reconstruct the entire structure from memory, recognize limitations, and formulate ideas for future research.

---

### Doing a Literature Survey

* **Step 1:** Use academic search engines (e.g., Google Scholar, CiteSeer) with targeted keywords to identify 3–5 recent papers. Apply Pass 1 to each and check their "Related Work" sections for recent survey papers.
* **Step 2:** If no survey exists, identify recurring citations and prominent authors across the bibliographies to pinpoint leading researchers and key venues.
* **Step 3:** Browse recent conference proceedings of top venues identified in Step 2, run two passes through selected candidate papers, and iteratively expand the survey via referenced seminal papers.

---

## 3. Project Proposal (Draft)

* **Chosen Path:** Basic Path (based on the paper *"Analysis of IEEE 802.11e for QoS support in wireless LANs"*).
* **The Problem:** The original paper uses an artificial traffic model (constant packet sizes and smooth arrivals) to test 802.11e. The goal is to investigate how network quality changes when using multimedia traffic (like real voice and video from the 3GPP specification) instead of the paper's simple traffic.
* **What I Would Measure:** 
  * Throughput (data speed) for each priority level (Voice, Video, Best Effort, Background).
  * Packet delay (latency) and jitter.
  * Packet loss rate when traffic becomes bursty.
