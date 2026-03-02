# 6502 Breadboard Computer

A fully functional 8-bit computer built from the ground up on a breadboard using the **W65C02S** CPU.  
This project demonstrates key computer architecture principles — including bus control, memory mapping, and timing — implemented entirely with discrete components and a custom-built programming/debugging tool. 

## *This is still an on-going project; this repository will be used to document our progress and anything we feel necessary.

---

## Overview

This project recreates a complete 6502 computer system using low-cost, readily available components.  
Instead of using a commercial EEPROM programmer, we utilize an **Arduino Mega 2560** as a comprehensive interface for programming, memory writing, and logic-level debugging.

> _Typical EEPROM programmers and logic analyzers can cost over $200. This system achieves the same functionality using an [ELEGOO Arduino Mega 2560](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Arduino-Compliant/dp/B01H4ZDYCE/) and a custom Arduino sketch we've developed._

### Why the Arduino Mega?
While many builders (like **Ben Eater**) use an Arduino Nano or Mini coupled with **74HC595 shift registers** to expand I/O, we opted for the **Mega 2560**. 

* **Direct Access:** With **54 digital I/O pins**, the Mega allows us to connect directly to the 16-bit address bus, 8-bit data bus, and control lines simultaneously.
* **Simplicity:** This eliminates the need for complex shift-register wiring and the "bit-banging" required to shift data in and out, making the debugger much more responsive and easier to wire.
* **Power:** The Mega provides enough pins to monitor the entire state of the CPU in real-time without hardware multiplexing or extra setup.

---

## 🧩 Features

- **Mega-Based Programmer/Debugger**
  - Uses 54-pin I/O to interface directly with the 6502 buses.
  - Writes data to EEPROM and reads back for verification.
  - Provides clock, reset, and control line management.
  - Monitors data and address buses for real-time debugging.
  - Enables step-by-step execution and signal tracing via the Serial Monitor.

- **Fully Wired 6502 System**
  - Breadboard implementation of the W65C02 CPU.
  - EEPROM used for program memory (AT28C256).
  - SRAM for data memory (AS6C62256).
  - External clock oscillator and discrete control logic.

- **Educational and Accessible Design**
  - Built entirely from off-the-shelf components.
  - No specialized tools required — just an Arduino Mega and basic wiring.
  - Clear documentation and schematics for replication.

---

## 📦 Parts List

| Component | Quantity | Description / Link |
| :--- | :--- | :--- |
| **W65C02 CPU** | 1 | [Western Design Center W65C02S6TPG-14](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C02S6TPG-14?qs=opBjA1TV903lvWo9AEKH5w%3D%3D) |
| **Arduino Mega 2560** | 1 | [ELEGOO ATmega2560 (54 I/O Pins)](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Arduino-Compliant/dp/B01H4ZDYCE/) |
| **W65C22 VIA** | 1 | [Western Design Center W65C22S6TPG-14](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C22S6TPG-14?qs=opBjA1TV9038jNZ%252Bop8JdA%3D%3D) |
| **AT28C256 EEPROM** | 1 | [Microchip AT28C256-15PU](https://www.mouser.com/ProductDetail/Microchip-Technology/AT28C256-15PU?qs=MAR/2X5XOp7eAU2/lNw9oA%3D%3D) |
| **AS6C62256 SRAM** | 1 | [Alliance Memory AS6C62256-55PCN](https://www.mouser.com/ProductDetail/Alliance-Memory/AS6C62256-55PCN?qs=LD2UibpCYJqgbIupMJnGTQ%3D%3D) |
| **16x2 LCD Display** | 1 | [White on Blue LCD](https://www.amazon.com/gp/product/B01BB4VKIE) |
| **74HC00 (NAND gate)** | 1 | Logic control for timing and addressing |
| **1 MHz Crystal Oscillator** | 1 | [Jameco MXO45-3C-1M0000-JVP](https://www.jameco.com/z/MXO45-3C-1M0000-JVP-Jameco-ValuePro-1-MHz-Full-Can-Crystal-Oscillator_27861.html) |
| **Breadboards** | 3-4 | Main CPU, memory, and I/O boards |
| **Resistors/Caps/LEDs** | Various | For pull-ups, decoupling, and indicators |

---

## 📂 Repository Structure

| Path | Description |
| :--- | :--- |
| `mega_programmer/` | Arduino Mega code for programming and bus debugging |
| `docs/` | Supporting documentation and bus explanations |
| `schematics/` | Full wiring diagrams for the Mega-to-6502 interface |
| `programs/` | Assembly programs like “Hello World” and demos |

---

## 💡 Design Philosophy

The main goal is **accessibility and transparency**. By using a high-pin-count microcontroller like the Mega, we bypass the "black box" nature of commercial programmers. You can see every bit move across the bus in your serial monitor, which is invaluable for learning how the 6502 actually thinks.

> **Note on Logic Levels:** The Arduino Mega operates at 5V, which is perfectly compatible with the W65C02S and the AT28C256 EEPROM, making it a "plug-and-play" debugging solution for this specific architecture.

---

## 🙏 Acknowledgments

This project was primarily inspired by **Ben Eater's** 8-bit computer series. While Ben uses an Arduino Nano/Mini with shift registers for his EEPROM programmer, we adapted the design to use the Mega for a more direct, "wire-per-signal" approach that reduces setup complexity.

**Resources:**
- [Ben Eater's 6502 Series](https://eater.net/6502)
- [WDC 6502 Datasheet](https://www.westerndesigncenter.com/wdc/w65c02s-chip.php)

---

## 🔧 Planned Improvements

- Integrate the W65C22 VIA for keyboard input.
- Create a Python script to automate hex file uploads to the Arduino Mega.
- Map out the full 64KB memory map including the Mega's monitor range.

---

## 🧰 License

Open-source for educational and non-commercial use. Contributions and forks are welcome.
