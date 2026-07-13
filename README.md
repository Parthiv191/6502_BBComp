# 6502 Breadboard Computer

A fully functional 8-bit computer built entirely on a breadboard using the W65C02S CPU. This is our hands-on project documenting everything from circuit design and wiring to programming and debugging.

**Note:** This is ongoing work. We're adding to the docs as we go.

---

## What is this?

We built a working 6502 computer from scratch using discrete components and a breadboard. Instead of buying a fancy EEPROM programmer ($200+) or logic analyzer ($200+), we used an Arduino Mega 2560 to program memory, read it back, and debug the system. It works surprisingly well and costs way less.

### Why the Arduino Mega instead of shift registers?

Ben Eater's approach uses an Arduino Nano with 74HC595 shift registers to expand I/O. We went with the Mega because:

- **54 digital pins** means we can connect directly to the address bus (16 bits), data bus (8 bits), and control lines all at once
- No bit-banging required — everything is straightforward wiring
- The debugger is more responsive and simpler to set up

---

## What's included

- **Arduino Mega programmer/debugger**
  - Reads and writes directly to the EEPROM
  - Monitors address and data buses
  - Step-through execution
  - Real-time signal tracing via serial

- **Working 6502 system**
  - W65C02 CPU on breadboard
  - AT28C256 EEPROM for programs
  - AS6C62256 SRAM for data
  - 1 MHz clock and control logic

- **Docs and schematics** for building it yourself

---

## Parts you'll need

| Part | Qty | Notes |
| --- | --- | --- |
| W65C02S CPU | 1 | [Mouser](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C02S6TPG-14) |
| Arduino Mega 2560 | 1 | [Amazon](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Arduino-Compliant/dp/B01H4ZDYCE/) |
| AT28C256 EEPROM | 1 | [Mouser](https://www.mouser.com/ProductDetail/Microchip-Technology/AT28C256-15PU) |
| AS6C62256 SRAM | 1 | [Mouser](https://www.mouser.com/ProductDetail/Alliance-Memory/AS6C62256-55PCN) |
| W65C22 VIA | 1 | [Mouser](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C22S6TPG-14) |
| 16x2 LCD | 1 | For output display |
| 1 MHz oscillator | 1 | [Jameco](https://www.jameco.com/z/MXO45-3C-1M0000-JVP-Jameco-ValuePro-1-MHz-Full-Can-Crystal-Oscillator_27861.html) |
| 74HC00 | 1 | Logic control |
| Breadboards | 3-4 | CPU, memory, and I/O boards |
| Resistors, caps, LEDs | Various | Pull-ups, decoupling, indicators |

---

## How this repo is organized

```
eeprom_programmer/     — Arduino code for programming and debugging
docs/                  — Notes on how the buses work and other details
schematics/            — Wiring diagrams
programs/              — Assembly code (hello world, demos, etc)
```

---

## Why we built it this way

We wanted something transparent and learnable. With a commercial programmer, you never see what's happening. By using the Mega, every signal is visible — you can trace exactly what's going on with the buses and control lines. No black boxes.

The 5V logic levels on the Arduino Mega line up perfectly with the W65C02S and AT28C256, so there's no voltage translation needed either.

---

## Inspiration and thanks

This whole thing started from watching Ben Eater's 6502 series. His videos made computer architecture click in a way textbooks never did.

- [Ben Eater's 6502 videos](https://eater.net/6502)
- [W65C02 datasheet](https://www.westerndesigncenter.com/wdc/w65c02s-chip.php)

---

## What's next

- Wire up the W65C22 VIA for keyboard input
- Build a Python script to upload hex files easier
- Map out the full 64KB memory layout

---

## License

Open source for education and tinkering. Fork it, modify it, build it.
