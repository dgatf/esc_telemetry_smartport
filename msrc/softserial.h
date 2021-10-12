#ifndef SOFTSERIAL_H
#define SOFTSERIAL_H

#include <Arduino.h>
#include "constants.h"
#include "serial.h"
#include "hardserial.h"

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega32U4__)

#if defined (__AVR_ATmega32U4__)
#define PCINTx_vect PCINT0_vect
#define PCMSKx PCMSK0
#define PCINTxn PCINT3
#define PCIEx PCIE0
#else
#define PCINTx_vect PCINT2_vect
#define PCMSKx PCMSK2
#define PCINTxn PCINT23
#define PCIEx PCIE2
#endif

#if defined (__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__)
#define PORTx PORTD
#define PORTxn PORTD7
#define PINx PIND
#define PINxn PIND7
#endif

#if defined(__AVR_ATmega2560__)
#define PORTx PORTK
#define PORTxn PORTK7
#define PINx PINK
#define PINxn PINK7
#endif

#if defined(__AVR_ATmega32U4__)
#define PORTx PORTB
#define PORTxn PORTB3
#define PINx PINB
#define PINxn PINB3
#endif

#define SOFTSERIAL_IDLE 0
#define SOFTSERIAL_RECEIVING 1
#define SOFTSERIAL_SENDING 2

#define setPinLogic1 inverted_ ? PORTB &= ~_BV(PORTB4) : PORTB |= _BV(PORTB4)
#define setPinLogic0 inverted_ ? PORTB |= _BV(PORTB4) : PORTB &= ~_BV(PORTB4)

/* This needs to be fast. Fixed at 8N1 and Rx and Tx pins. Parameters: baud rate and inverted */

class SoftSerial : public AbstractSerial
{
private:
    volatile uint8_t incomingByte;
    uint8_t outgoingByte;
    volatile uint8_t bit;
    volatile uint8_t initVal;
    uint8_t delta[12];
    uint8_t initDeltaRx;
    uint8_t initDeltaTx;
    volatile uint8_t status;
    bool inverted_;

public:
    SoftSerial();
    void begin(uint32_t baud, uint8_t format);
    void initWrite();
    void PCINT2_handler();
    void TIMER0_COMPA_handler();
};

extern SoftSerial softSerial;
extern HardSerial hardSerial0;


#endif

#endif