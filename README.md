# 6502 Breadboard Computer

A fully functional 8-bit computer built entirely on a breadboard around the **W65C02S** CPU — no PCB, no kit, just wire, logic chips, and a lot of patience. This repo documents the build: circuit design, wiring, memory mapping, and getting actual programs running on it.

**Note:** Still an ongoing project — expect this to grow as we go. 🛠️

---

## What is this?

We're building a working 6502 computer from discrete components, following in the footsteps of Ben Eater's classic series but putting our own spin on the tooling and debugging side. The CPU, EEPROM, RAM, clock, and control logic all live on breadboards, wired by hand.

To program and debug it, we built our own Arduino Mega based tool instead of buying a commercial EEPROM programmer or logic analyzer. It's grown into its own thing, so it now lives in a separate repo: **[6502_EEPROM_Programmer](https://github.com/Parthiv191/6502_EEPROM_Programmer)**. Check that out if you want to write to the EEPROM, sniff the bus, or single-step the clock.

---

## What's included here

- **A working 6502 system**
  - W65C02 CPU on breadboard
  - AT28C256 EEPROM for program storage
  - AS6C62256 SRAM for working memory
  - W65C22 VIA for I/O
  - 1 MHz clock and discrete control logic
  - 16x2 LCD for output

- **Docs and parts list** for building the same thing yourself

---

## Parts you'll need

| Part | Qty | Notes |
| --- | --- | --- |
| W65C02S CPU | 1 | [Mouser](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C02S6TPG-14) |
| W65C22 VIA | 1 | [Mouser](https://www.mouser.com/ProductDetail/Western-Design-Center-WDC/W65C22S6TPG-14) |
| AT28C256 EEPROM | 1 | [Mouser](https://www.mouser.com/ProductDetail/Microchip-Technology/AT28C256-15PU) |
| AS6C62256 SRAM | 1 | [Mouser](https://www.mouser.com/ProductDetail/Alliance-Memory/AS6C62256-55PCN) |
| Arduino Mega 2560 | 1 | For programming/debugging — [Amazon](https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Arduino-Compliant/dp/B01H4ZDYCE/) |
| 16x2 LCD | 1 | For output display |
| 1 MHz oscillator | 1 | [Jameco](https://www.jameco.com/z/MXO45-3C-1M0000-JVP-Jameco-ValuePro-1-MHz-Full-Can-Crystal-Oscillator_27861.html) |
| 74HC00 | 1 | Logic control |
| Breadboards | 3-4 | CPU, memory, and I/O boards |
| Resistors, caps, LEDs | Various | Pull-ups, decoupling, indicators |

Full parts list with more detail is in [`6502 Parts List.pdf`](./6502%20Parts%20List.pdf).

---

## Related repo

- **[6502_EEPROM_Programmer](https://github.com/Parthiv191/6502_EEPROM_Programmer)** — the Arduino Mega sketch that programs the EEPROM and sniffs the bus, plus wiring diagrams for it.

---

## Inspiration and thanks

This whole thing started from watching Ben Eater's 6502 series. His videos made computer architecture click in a way textbooks never did.

- [Ben Eater's 6502 videos](https://eater.net/6502)
- [W65C02 datasheet](https://www.westerndesigncenter.com/wdc/w65c02s-chip.php)

---

## What's next

- Wire up the W65C22 VIA for keyboard input
- Get some real programs running (past hello world)
- Map out the full 64KB memory layout
- More photos as the build progresses

---

## License

Open source for education and tinkering. Fork it, modify it, build it — see [LICENSE](LICENSE).
