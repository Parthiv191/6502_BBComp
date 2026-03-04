#define WRITE_ENABLE 51
#define OUTPUT_ENABLE 44
#define CHIP_ENABLE  48

// Data bus
#define EEPROM_D0 22
#define EEPROM_D1 24
#define EEPROM_D2 26
#define EEPROM_D3 28
#define EEPROM_D4 30
#define EEPROM_D5 32
#define EEPROM_D6 34
#define EEPROM_D7 36

// 6502 control
#define CLOCK_PIN 52
#define RWB_PIN   29
#define RESET_PIN 50

// Address pins
#define A0_PIN  31
#define A1_PIN  33
#define A2_PIN  35
#define A3_PIN  37
#define A4_PIN  39
#define A5_PIN  41
#define A6_PIN  43
#define A7_PIN  45
#define A8_PIN  38
#define A9_PIN  40
#define A10_PIN 46
#define A11_PIN 42
#define A12_PIN 47
#define A13_PIN 53
#define A14_PIN 49
#define A15_PIN 27

// ===================== MODE CONTROL =====================
enum RunMode { MODE_SNIFF, MODE_PROG };
static RunMode mode = MODE_SNIFF;

static inline void addrPinsOutput() {
  pinMode(A0_PIN,  OUTPUT); pinMode(A1_PIN,  OUTPUT);
  pinMode(A2_PIN,  OUTPUT); pinMode(A3_PIN,  OUTPUT);
  pinMode(A4_PIN,  OUTPUT); pinMode(A5_PIN,  OUTPUT);
  pinMode(A6_PIN,  OUTPUT); pinMode(A7_PIN,  OUTPUT);
  pinMode(A8_PIN,  OUTPUT); pinMode(A9_PIN,  OUTPUT);
  pinMode(A10_PIN, OUTPUT); pinMode(A11_PIN, OUTPUT);
  pinMode(A12_PIN, OUTPUT); pinMode(A13_PIN, OUTPUT);
  pinMode(A14_PIN, OUTPUT); pinMode(A15_PIN, OUTPUT);
}

static inline void addrPinsInput() {
  pinMode(A0_PIN,  INPUT); pinMode(A1_PIN,  INPUT);
  pinMode(A2_PIN,  INPUT); pinMode(A3_PIN,  INPUT);
  pinMode(A4_PIN,  INPUT); pinMode(A5_PIN,  INPUT);
  pinMode(A6_PIN,  INPUT); pinMode(A7_PIN,  INPUT);
  pinMode(A8_PIN,  INPUT); pinMode(A9_PIN,  INPUT);
  pinMode(A10_PIN, INPUT); pinMode(A11_PIN, INPUT);
  pinMode(A12_PIN, INPUT); pinMode(A13_PIN, INPUT);
  pinMode(A14_PIN, INPUT); pinMode(A15_PIN, INPUT);
}

static inline void driveAddress(uint16_t address) {
  digitalWrite(A0_PIN,  (address & 0x0001) ? HIGH : LOW);
  digitalWrite(A1_PIN,  (address & 0x0002) ? HIGH : LOW);
  digitalWrite(A2_PIN,  (address & 0x0004) ? HIGH : LOW);
  digitalWrite(A3_PIN,  (address & 0x0008) ? HIGH : LOW);
  digitalWrite(A4_PIN,  (address & 0x0010) ? HIGH : LOW);
  digitalWrite(A5_PIN,  (address & 0x0020) ? HIGH : LOW);
  digitalWrite(A6_PIN,  (address & 0x0040) ? HIGH : LOW);
  digitalWrite(A7_PIN,  (address & 0x0080) ? HIGH : LOW);
  digitalWrite(A8_PIN,  (address & 0x0100) ? HIGH : LOW);
  digitalWrite(A9_PIN,  (address & 0x0200) ? HIGH : LOW);
  digitalWrite(A10_PIN, (address & 0x0400) ? HIGH : LOW);
  digitalWrite(A11_PIN, (address & 0x0800) ? HIGH : LOW);
  digitalWrite(A12_PIN, (address & 0x1000) ? HIGH : LOW);
  digitalWrite(A13_PIN, (address & 0x2000) ? HIGH : LOW);
  digitalWrite(A14_PIN, (address & 0x4000) ? HIGH : LOW);
  digitalWrite(A15_PIN, (address & 0x8000) ? HIGH : LOW);
}

static inline void dataPinsInput() {
  for (int pin = 22; pin <= 36; pin += 2)
    pinMode(pin, INPUT);
}

static inline void dataPinsOutput() {
  for (int pin = 22; pin <= 36; pin += 2)
    pinMode(pin, OUTPUT);
}

static inline void driveData(uint8_t data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(22 + i * 2, (data & (1 << i)) ? HIGH : LOW);
  }
}

// Control lines
static inline void ce_low()  { digitalWrite(CHIP_ENABLE,   LOW);  }
static inline void ce_high() { digitalWrite(CHIP_ENABLE,   HIGH); }
static inline void oe_low()  { digitalWrite(OUTPUT_ENABLE, LOW);  }
static inline void oe_high() { digitalWrite(OUTPUT_ENABLE, HIGH); }
static inline void we_low()  { digitalWrite(WRITE_ENABLE,  LOW);  }
static inline void we_high() { digitalWrite(WRITE_ENABLE,  HIGH); }

// ===================== PROGRAMMER MODE =====================
byte prog_readEEPROM(uint16_t address) {
  addrPinsOutput();
  dataPinsInput();

  pinMode(CHIP_ENABLE,   OUTPUT);
  pinMode(OUTPUT_ENABLE, OUTPUT);
  pinMode(WRITE_ENABLE,  OUTPUT);

  we_high(); ce_low(); oe_high();
  driveAddress(address);
  delayMicroseconds(1);
  oe_low();
  delayMicroseconds(1);

  byte data = 0;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(22 + i * 2)) data |= (1 << i);
  }

  oe_high();
  ce_high();
  return data;
}

void prog_writeEEPROM(uint16_t address, uint8_t data) {
  addrPinsOutput();
  dataPinsOutput();

  pinMode(CHIP_ENABLE,   OUTPUT);
  pinMode(OUTPUT_ENABLE, OUTPUT);
  pinMode(WRITE_ENABLE,  OUTPUT);

  ce_low(); oe_high(); we_high();
  driveAddress(address);
  driveData(data);
  delayMicroseconds(1);
  we_low();
  delayMicroseconds(1);
  we_high();

  dataPinsInput();
  uint8_t v;
  do { v = prog_readEEPROM(address); } while (v != data);
}

void prog_writePage(uint16_t baseAddr, const uint8_t *data, uint8_t len) {
  if ((baseAddr & 0x3F) + len > 64) return;

  addrPinsOutput();
  dataPinsOutput();

  pinMode(CHIP_ENABLE,   OUTPUT);
  pinMode(OUTPUT_ENABLE, OUTPUT);
  pinMode(WRITE_ENABLE,  OUTPUT);

  ce_low(); oe_high(); we_high();

  for (uint8_t i = 0; i < len; i++) {
    driveAddress(baseAddr + i);
    driveData(data[i]);
    delayMicroseconds(1);
    we_low();
    delayMicroseconds(1);
    we_high();
  }

  ce_high();
  dataPinsInput();

  uint8_t lastValue = data[len - 1];
  uint8_t v;
  do { v = prog_readEEPROM(baseAddr + len - 1); } while (v != lastValue);
}

void prog_eraseEntire() {
  Serial.print(F("Fast erase (page mode)... "));
  uint8_t empty_page[64];
  for (uint8_t i = 0; i < 64; i++) empty_page[i] = 0xEA;

  int pageCount = 0;
  for (uint16_t base = 0; base <= 0x7FC0; base += 64) {
    prog_writePage(base, empty_page, 64);
    pageCount++;
    if (pageCount % 32 == 0) {
      Serial.print(pageCount);
      Serial.print(F("/512 "));
    }
  }
  driveAddress(0x0000);
  Serial.println(F("done."));
}

void prog_dump(uint16_t base, uint16_t lines) {
  for (uint16_t l = 0; l < lines; ++l) {
    uint16_t addr = (base + l * 16) & 0x7FFF;
    uint8_t b[16];
    for (uint8_t off = 0; off < 16; ++off)
      b[off] = prog_readEEPROM(addr + off);

    char buf[80];
    sprintf(buf, "%04X:  %02X %02X %02X %02X %02X %02X %02X %02X   %02X %02X %02X %02X %02X %02X %02X %02X",
      addr,
      b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7],
      b[8],b[9],b[10],b[11],b[12],b[13],b[14],b[15]);
    Serial.println(buf);
  }
}

// ===================== SNIFF MODE =====================
static inline void sniffPins() {
  addrPinsInput();
  dataPinsInput();

  pinMode(RWB_PIN,   INPUT);
  pinMode(RESET_PIN, INPUT);

  pinMode(WRITE_ENABLE,  INPUT);
  pinMode(OUTPUT_ENABLE, INPUT);
  pinMode(CHIP_ENABLE,   INPUT);

  pinMode(CLOCK_PIN, OUTPUT);
  digitalWrite(CLOCK_PIN, LOW);
}

static inline void progPins() {
  addrPinsOutput();
  dataPinsInput();
  pinMode(CHIP_ENABLE,   OUTPUT);
  pinMode(OUTPUT_ENABLE, OUTPUT);
  pinMode(WRITE_ENABLE,  OUTPUT);
  ce_high(); oe_high(); we_high();
  pinMode(CLOCK_PIN, OUTPUT);
  digitalWrite(CLOCK_PIN, LOW);
}

static inline uint16_t readAddressBus() {
  uint16_t a = 0;
  a |= (uint16_t)digitalRead(A0_PIN)  << 0;
  a |= (uint16_t)digitalRead(A1_PIN)  << 1;
  a |= (uint16_t)digitalRead(A2_PIN)  << 2;
  a |= (uint16_t)digitalRead(A3_PIN)  << 3;
  a |= (uint16_t)digitalRead(A4_PIN)  << 4;
  a |= (uint16_t)digitalRead(A5_PIN)  << 5;
  a |= (uint16_t)digitalRead(A6_PIN)  << 6;
  a |= (uint16_t)digitalRead(A7_PIN)  << 7;
  a |= (uint16_t)digitalRead(A8_PIN)  << 8;
  a |= (uint16_t)digitalRead(A9_PIN)  << 9;
  a |= (uint16_t)digitalRead(A10_PIN) << 10;
  a |= (uint16_t)digitalRead(A11_PIN) << 11;
  a |= (uint16_t)digitalRead(A12_PIN) << 12;
  a |= (uint16_t)digitalRead(A13_PIN) << 13;
  a |= (uint16_t)digitalRead(A14_PIN) << 14;
  a |= (uint16_t)digitalRead(A15_PIN) << 15;
  return a;
}

static inline uint8_t readDataBusSniff() {
  uint8_t d = 0;
  d |= (digitalRead(EEPROM_D0) ? 1 : 0) << 0;
  d |= (digitalRead(EEPROM_D1) ? 1 : 0) << 1;
  d |= (digitalRead(EEPROM_D2) ? 1 : 0) << 2;
  d |= (digitalRead(EEPROM_D3) ? 1 : 0) << 3;
  d |= (digitalRead(EEPROM_D4) ? 1 : 0) << 4;
  d |= (digitalRead(EEPROM_D5) ? 1 : 0) << 5;
  d |= (digitalRead(EEPROM_D6) ? 1 : 0) << 6;
  d |= (digitalRead(EEPROM_D7) ? 1 : 0) << 7;
  return d;
}

// PHI2 single-step state machine
const unsigned long PULSE_HIGH_US = 5;
const unsigned long PULSE_LOW_US  = 5;
enum PulseState { IDLE, HIGHING, LOWING };
static PulseState pulseState = IDLE;
static int pulsesRemaining = 0;
static int pulsesTotal = 0;
static unsigned long lastToggleTs = 0;

static uint16_t lastAddr = 0xFFFF;

static void sampleAndPrint() {
  delayMicroseconds(3);
  uint16_t addr = readAddressBus();
  bool rwb = digitalRead(RWB_PIN);
  uint8_t data = readDataBusSniff();
  bool eepromActive = (addr & 0x8000) != 0;

  // Skip if same address as last cycle -> prevents the annoying double print
  // MIGHT NEED TO REMOVE THIS FOR LATER FUNCTION, but fine for now
  if (addr == lastAddr) return;
  lastAddr = addr;

  char buf[80];
  if (rwb && eepromActive) {
    sprintf(buf, "R  $%04X  DATA=$%02X  [EEPROM]", addr, data);
  } else if (rwb) {
    sprintf(buf, "R  $%04X  DATA=$%02X  [RAM/IO]", addr, data);
  } else {
    sprintf(buf, "W  $%04X  DATA=$%02X  [%s]", addr, data, eepromActive ? "EEPROM region" : "RAM/IO");
  }
  Serial.println(buf);
}
static void reset_sequence() {
  lastAddr = 0xFFFF;
  
  Serial.println(F("Starting Reset Sequence..."));

  pulsesRemaining = 0;
  pulseState = IDLE;
  digitalWrite(CLOCK_PIN, LOW);

  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);

  for (int i = 0; i < 2; i++) {
    delayMicroseconds(PULSE_LOW_US);
    digitalWrite(CLOCK_PIN, HIGH);
    delayMicroseconds(PULSE_HIGH_US);
    digitalWrite(CLOCK_PIN, LOW);
  }

  digitalWrite(RESET_PIN, HIGH);
  pinMode(RESET_PIN, INPUT);

  Serial.println(F("Reset complete. Clock stopped. Waiting for next command."));
}

// ===================== SERIAL COMMANDS =====================
static bool readLine(char *out, size_t cap) {
  static char buf[128];
  static size_t idx = 0;
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      buf[idx] = '\0';
      strncpy(out, buf, cap);
      out[cap-1] = '\0';
      idx = 0;
      return true;
    }
    if (idx < sizeof(buf) - 1) buf[idx++] = c;
  }
  return false;
}

static long parseNum(const char *s) {
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) return strtol(s+2, nullptr, 16);
  return strtol(s, nullptr, 16);
}

void handleCommand(const char *line) {
  char cmd[128];
  strncpy(cmd, line, sizeof(cmd));
  cmd[sizeof(cmd)-1] = '\0';
  char *tok = strtok(cmd, " ");
  if (!tok) return;

  if (strcmp(tok, "mode") == 0) {
    char *m = strtok(nullptr, " ");
    if (!m) { Serial.println(F("usage: mode sniff|prog")); return; }
    if (strcmp(m, "sniff") == 0) {
      mode = MODE_SNIFF; sniffPins();
      Serial.println(F("Mode: SNIFF"));
    } else if (strcmp(m, "prog") == 0) {
      mode = MODE_PROG; progPins();
      Serial.println(F("Mode: PROG"));
    } else {
      Serial.println(F("usage: mode sniff|prog"));
    }
    return;
  }

  if (strcmp(tok, "pulse") == 0) {
    if (mode != MODE_SNIFF) { Serial.println(F("pulse only in SNIFF mode")); return; }
    char *n = strtok(nullptr, " ");
    if (!n) { Serial.println(F("usage: pulse N")); return; }
    long k = parseNum(n);
    if (k < 1) k = 1;
    pulsesRemaining = (int)k;
    pulsesTotal = (int)k;
    pulseState = HIGHING;
    digitalWrite(CLOCK_PIN, HIGH);
    lastToggleTs = micros();
    return;
  }

  if (strcmp(tok, "reset") == 0) {
    if (mode != MODE_SNIFF) { Serial.println(F("reset only in SNIFF mode")); return; }
    reset_sequence();
    return;
  }

  if (strcmp(tok, "wr") == 0) {
    if (mode != MODE_PROG) { Serial.println(F("wr only in PROG mode")); return; }
    char *sa = strtok(nullptr, " "); char *sb = strtok(nullptr, " ");
    if (!sa || !sb) { Serial.println(F("usage: wr <addr> <byte>")); return; }
    long addr = parseNum(sa); long val = parseNum(sb);
    if (addr < 0 || addr > 0x7FFF || val < 0 || val > 0xFF) {
      Serial.println(F("range: addr 0..0x7FFF, byte 0..0xFF")); return;
    }
    prog_writeEEPROM((uint16_t)addr, (uint8_t)val);
    Serial.println(F("OK"));
    return;
  }

  if (strcmp(tok, "dump") == 0) {
    if (mode != MODE_PROG) { Serial.println(F("dump only in PROG mode")); return; }
    char *sb = strtok(nullptr, " "); char *sc = strtok(nullptr, " ");
    if (!sb) { Serial.println(F("usage: dump <base> [count]")); return; }
    long base = parseNum(sb); long count = sc ? parseNum(sc) : 1;
    if (base < 0 || base > 0x7FFF) { Serial.println(F("base 0..0x7FFF")); return; }
    if (count < 1) count = 1;
    prog_dump((uint16_t)base, (uint16_t)count);
    return;
  }

  if (strcmp(tok, "erase") == 0) {
    if (mode != MODE_PROG) { Serial.println(F("erase only in PROG mode")); return; }
    prog_eraseEntire();
    return;
  }

  Serial.println(F("Unknown command."));
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  sniffPins();
  Serial.println(F("Booted in SNIFF mode."));
  Serial.println(F("Commands: mode sniff|prog | pulse N | reset | wr <addr> <byte> | dump <base> [count] | erase"));
}

void loop() {
  char line[128];
  if (readLine(line, sizeof(line))) handleCommand(line);

  if (mode == MODE_SNIFF) {
    switch (pulseState) {
      case IDLE: break;
      case HIGHING:
        if ((micros() - lastToggleTs) >= PULSE_HIGH_US) {
          sampleAndPrint();
          digitalWrite(CLOCK_PIN, LOW);
          pulseState = LOWING;
          lastToggleTs = micros();
        }
        break;
      case LOWING:
        if ((micros() - lastToggleTs) >= PULSE_LOW_US) {
          if (--pulsesRemaining > 0) {
            digitalWrite(CLOCK_PIN, HIGH);
            pulseState = HIGHING;
            lastToggleTs = micros();
          } else {
            pulseState = IDLE;
            if (pulsesTotal > 1) Serial.println(F("Done."));
          }
        }
        break;
    }
  }
}
