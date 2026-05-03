// Provides:
//   void    fastDigitalWrite(uint8_t pin, uint8_t val);
//   uint8_t fastDigitalRead(uint8_t pin);


#ifndef FAST_DIGITAL_IO_H
#define FAST_DIGITAL_IO_H

#include <stdint.h>
#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void _fast_dw_invalid_pin(void)
    __attribute__((error(
        "fastDigitalWrite/Read: pin is not in the supported set"
        "Supported pins are 22, 24, 26-53 "
        )));


// Each row is X(arduino_pin, PORTx_register, PINx_register, bit_index)
#define FAST_PIN_TABLE(X) \
    X(22, PORTA, PINA, 0)                         \
    X(24, PORTA, PINA, 2)                         \
    X(26, PORTA, PINA, 4)                         \
    X(27, PORTA, PINA, 5)                         \
    X(28, PORTA, PINA, 6)                         \
    X(29, PORTA, PINA, 7)                         \
    X(30, PORTC, PINC, 7)                         \
    X(31, PORTC, PINC, 6)                         \
    X(32, PORTC, PINC, 5)                         \
    X(33, PORTC, PINC, 4)                         \
    X(34, PORTC, PINC, 3)                         \
    X(35, PORTC, PINC, 2)                         \
    X(36, PORTC, PINC, 1)                         \
    X(37, PORTC, PINC, 0)                         \
    X(38, PORTD, PIND, 7)                         \
    X(39, PORTG, PING, 2)                         \
    X(40, PORTG, PING, 1)                         \
    X(41, PORTG, PING, 0)                         \
    X(42, PORTL, PINL, 7)                         \
    X(43, PORTL, PINL, 6)                         \
    X(44, PORTL, PINL, 5)                         \
    X(45, PORTL, PINL, 4)                         \
    X(46, PORTL, PINL, 3)                         \
    X(47, PORTL, PINL, 2)                         \
    X(48, PORTL, PINL, 1)                         \
    X(49, PORTL, PINL, 0)                         \
    X(50, PORTB, PINB, 3)                         \
    X(51, PORTB, PINB, 2)                         \
    X(52, PORTB, PINB, 1)                         \
    X(53, PORTB, PINB, 0)
// should prolly add more maybe

static __attribute__((always_inline))
void _fastDigitalWriteConst(uint8_t pin, uint8_t val) {
    switch (pin) {
        #define _FDW_CASE(p, port, pin_reg, bit)                                   \
            case p: if (val) port |= (uint8_t)(1u << (bit));                       \
                    else     port &= (uint8_t)~(1u << (bit));                      \
                    break;
        FAST_PIN_TABLE(_FDW_CASE)
        #undef _FDW_CASE
        default: _fast_dw_invalid_pin();
    }
}

static __attribute__((always_inline)) inline
uint8_t _fastDigitalReadConst(uint8_t pin) {
    switch (pin) {
        #define _FDR_CASE(p, port, pin_reg, bit)                                   \
            case p: return (pin_reg & (uint8_t)(1u << (bit))) ? 1 : 0;
        FAST_PIN_TABLE(_FDR_CASE)
        #undef _FDR_CASE
        default: _fast_dw_invalid_pin(); return 0;
    }
}

void    _fastDigitalWriteRuntime(uint8_t pin, uint8_t val);
uint8_t _fastDigitalReadRuntime(uint8_t pin);

#define fastDigitalWrite(pin, val)                                    \
    do {                                                              \
        if (__builtin_constant_p(pin)) {                              \
            _fastDigitalWriteConst((pin), (val));                     \
        } else {                                                      \
            _fastDigitalWriteRuntime((pin), (val));                   \
        }                                                             \
    } while (0)

#define fastDigitalRead(pin)                                          \
    (__builtin_constant_p(pin)                                        \
        ? _fastDigitalReadConst((pin))                                \
        : _fastDigitalReadRuntime((pin)))

#ifdef __cplusplus
}
#endif

#endif
