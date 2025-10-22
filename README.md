# 🧠 6502 Breadboard Computer

A fully functional 8-bit computer built from the ground up on a breadboard using the **W65C02S** CPU.  
This project demonstrates key computer architecture principles — including bus control, memory mapping, and timing — implemented entirely with discrete components and a custom-built programming/debugging tool.

---

## 🚀 Overview

This project recreates a complete 6502 computer system using low-cost, readily available components.  
A custom microcontroller interface handles programming, memory writing, and logic-level debugging — eliminating the need for expensive commercial analyzers or EEPROM programmers.

> 💡 _Typical EEPROM programmers and logic analyzers can cost over $200. This system achieves the same functionality using a $10 microcontroller and open-source software._

The project is designed to be educational, replicable, and fully transparent — ideal for anyone learning about computer architecture or interested in retro computing. _We are also learning, and would love to hear your feedback!_

---

## 🧩 Features

- **Custom Programmer/Debugger Interface**
  - Writes data to EEPROM and reads back for verification
  - Provides clock, reset, and control line management
  - Monitors data and address buses for debugging
  - Enables step-by-step execution and signal tracing

- **Fully Wired 6502 System**
  - Breadboard implementation of the W65C02 CPU
  - EEPROM used for program memory (AT28C256)
  - SRAM for data memory (AS6C62256)
  - External clock oscillator and discrete control logic

- **Educational and Accessible Design**
  - Built entirely from off-the-shelf components
  - No specialized tools required — only basic wiring and a microcontroller
  - Clear documentation and schematics for replication

---

## 📦 Parts List

| Component                        | Quantity | Description / Link                                                                                                                                        |
| -------------------------------- | -------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **W65C02 CPU**                   | 1        | [Western Design Center W65C02S6TPG-14](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C02S6TPG-14?qs=opBjA1TV903lvWo9AEKH5w%3D%3D)     |
| **W65C22 VIA**                   | 1        | [Western Design Center W65C22S6TPG-14](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C22S6TPG-14?qs=opBjA1TV9038jNZ%252Bop8JdA%3D%3D) |
| **AT28C256 EEPROM**              | 1        | [Microchip AT28C256-15PU](https://www.mouser.com/ProductDetail/Microchip-Technology/AT28C256-15PU?qs=MAR/2X5XOp7eAU2/lNw9oA%3D%3D)                        |
| **AS6C62256 SRAM**               | 1        | [Alliance Memory AS6C62256-55PCN](https://www.mouser.com/ProductDetail/Alliance-Memory/AS6C62256-55PCN?qs=LD2UibpCYJqgbIupMJnGTQ%3D%3D)                   |
| **16x2 LCD Display**             | 1        | [White on Blue LCD](https://www.amazon.com/gp/product/B01BB4VKIE)                                                                                         |
| **74HC00 (NAND gate)**           | 1        | Logic control for timing and addressing                                                                                                                   |
| **1 MHz Crystal Oscillator**     | 1        | [Jameco MXO45-3C-1M0000-JVP](https://www.jameco.com/z/MXO45-3C-1M0000-JVP-Jameco-ValuePro-1-MHz-Full-Can-Crystal-Oscillator_27861.html)                   |
| **Breadboards**                  | 3        | Main CPU, memory, and I/O boards                                                                                                                          |
| **Resistors (220Ω, 1kΩ, 10kΩ)**  | Various  | For pull-ups and LED indicators                                                                                                                           |
| **Capacitors (0.1µF)**           | Various  | Power decoupling                                                                                                                                          |
| **LEDs, buttons, potentiometer** | Assorted | Indicators and LCD contrast control                                                                                                                       |

(Full list sourced from _6502 Parts List - Sheet1.pdf_)

---

## 📂 Repository Structure

| Path                          | Description                                                   |
| ----------------------------- | ------------------------------------------------------------- |
| `eeprom_programmer/`          | Custom microcontroller code for programming and bus debugging |
| `docs/` _(coming soon)_       | Supporting documentation and bus explanations                 |
| `schematics/` _(coming soon)_ | Full wiring diagrams and pin mappings                         |
| `programs/` _(coming soon)_   | Assembly programs like “Hello World” and demos                |
| `images/` _(coming soon)_     | Build photos and breadboard layout                            |

---

## 💡 Design Philosophy

The main goal is **accessibility and transparency** — to make a 6502 computer build achievable without expensive hardware or specialized equipment.  
By leveraging a microcontroller as a universal interface, the design bridges the gap between hardware fundamentals and practical embedded systems engineering.

---

## 🔧 Planned Improvements

- Add I/O expansion via VIA chip integration
- Develop an interactive terminal interface
- Improve timing precision with hardware clock division
- Upload schematics and signal timing diagrams

---

## 🧰 License

Open-source for educational and non-commercial use. Contributions and forks are welcome.
