# 🧠 6502 Breadboard Computer

A custom 8-bit computer built entirely on a breadboard using the classic **MOS 6502** microprocessor.  
This project demonstrates low-level computer architecture concepts — including clock generation, memory interfacing, and data bus control — while keeping everything accessible and affordable.

---

## 🚀 Overview

This project recreates a functioning 6502-based computer from scratch using only discrete components, an EEPROM, and a standard **Arduino**.  
The Arduino acts as both a **logic analyzer** and **EEPROM programmer**, eliminating the need for expensive development tools.  

> 🧩 *Commercial EEPROM programmers and logic analyzers typically cost over $200 — this project replaces all of that with a $10 Arduino and custom firmware.*

---

## 🛠 Features

- **Custom Arduino Interface:**  
  Developed entirely from scratch to handle:
  - EEPROM read/write operations  
  - Data bus and address line control  
  - Clock and reset signal management  
  - Real-time bus monitoring for debugging  

- **Fully Wired 6502 System:**  
  - Breadboard implementation of the 6502 CPU  
  - Custom clock circuit for timing  
  - EEPROM wired as program memory  
  - Data and address buses manually routed and documented  

- **Low-Cost Architecture Education Platform:**  
  - Learn computer fundamentals: buses, timing, read/write cycles, and memory mapping  
  - Modify and expand with I/O, RAM, or display modules  

---

## 📂 Repository Contents

| Path | Description |
|------|--------------|
| `arduino/` | Arduino sketch used to control, program, and debug the 6502 |
| `docs/` *(coming soon)* | Supporting documents on bus setup, address mapping, and control logic |
| `schematics/` *(coming soon)* | Breadboard wiring and clock circuit diagrams |
| `programs/` *(coming soon)* | Example 6502 programs such as “Hello World” |
| `images/` *(coming soon)* | Build photos and wiring references |

---

## 💡 Why This Matters

Developing the Arduino software from scratch not only replaced expensive lab equipment but also made the project **accessible for anyone interested in building their own computer**.  
By open-sourcing both the hardware design and the programming tools, this project serves as a **blueprint for low-budget computer engineering and embedded systems experimentation**.

---

## 🔧 Future Work

- Add RAM and I/O expansion modules  
- Upload schematics and detailed bus documentation  
- Add sample assembly programs  
- Improve timing accuracy with hardware clock division  

---

## 📸 Coming Soon
Pictures and wiring diagrams of the full breadboard setup, along with EEPROM and clock connections.
