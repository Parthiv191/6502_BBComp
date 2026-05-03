#include "fast_digital_io.h"

void _fastDigitalWriteRuntime(uint8_t pin, uint8_t val) {
    switch (pin) {
        #define _FDW_RT_CASE(p, port, pin_reg, bit)                                \
            case p: if (val) port |= (uint8_t)(1u << (bit));                       \
                    else     port &= (uint8_t)~(1u << (bit));                      \
                    break;
        FAST_PIN_TABLE(_FDW_RT_CASE)
        #undef _FDW_RT_CASE
        default: break;
    }
}

uint8_t _fastDigitalReadRuntime(uint8_t pin) {
    switch (pin) {
        #define _FDR_RT_CASE(p, port, pin_reg, bit)                                \
            case p: return (pin_reg & (uint8_t)(1u << (bit))) ? 1 : 0;
        FAST_PIN_TABLE(_FDR_RT_CASE)
        #undef _FDR_RT_CASE
        default: return 0;
    }
}
