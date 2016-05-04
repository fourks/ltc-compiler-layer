#ifndef __ARDUINO_KOSAGI_H__
#define __ARDUINO_KOSAGI_H__

#include <stdint.h>
#include <stdbool.h>

enum analog_reference_type {
  DEFAULT = 0,
  INTERNAL = 1,
  INTERNAL1V1 = 2,
  INTERNAL2V56 = 3,
  EXTERNAL = 4,
};

enum irq_mode {
  LOW = 0,
  CHANGE = 1,
  RISING = 2,
  FALLING = 3,
  HIGH = 4,
};

enum pin_mode {
  INPUT = 0,
  OUTPUT = 1,
  INPUT_PULLUP = 2,
  INPUT_PULLDOWN = 3,
};

/* Program lifetime */
#if !defined(ARDUINO_OS) /* These are not syscalls */
void init(void);
void loop(void);
void setup(void);
#endif /* !ARDUINO_OS */

/* Generic IO */
void pinMode(int pin, enum pin_mode mode);

/* Digital IO */
void digitalWrite(int pin, int value);
int digitalRead(int pin);

/* Analog IO */
void analogWrite(int pin, int value);
void analogReference(enum analog_reference_type type);
int analogRead(int pin);

/* Interrupt handling */
void attachInterrupt(int irq, void (*func)(void), enum irq_mode mode);
void detachInterrupt(int irq);

/* Tone production */
void tone(int pin, unsigned int frequency, unsigned long duration
#if !defined(ARDUINO_OS)
    = 0
#endif /* !ARDUINO_OS */
);
void noTone(int pin);

/* Simple communication protocols */
void shiftOut(int dataPin, int clockPin, int bitOrder, uint8_t val);
uint8_t shiftIn(int dataPin, int clockPin, int bitOrder);
unsigned long pulseIn(int pin, uint8_t state, unsigned long timeout
#if !defined(ARDUINO_OS)
    = 1000000
#endif /* !ARDUINO_OS */
);
unsigned long pulseInLong(int pin, uint8_t state, unsigned long timeout
#if !defined(ARDUINO_OS)
    = 1000000
#endif /* !ARDUINO_OS */
);

/* Time */
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long msecs);
void delayMicroseconds(unsigned int usecs);

/* Math */
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);
double pow(double base, double exponent);
double sqrt(double x);

/* Trig */
double cos(double rad);
double tan(double rad);
double sin(double rad);

/* Characters */
bool isAlphaNumeric(int c);
bool isAlpha(int c);
bool isAscii(int c);
bool isWhitespace(int c);
bool isControl(int c);
bool isDigit(int c);
bool isGraph(int c);
bool isLowerCase(int c);
bool isPrintable(int c);
bool isPunct(int c);
bool isSpace(int c);
bool isUppercase(int c);
bool isHexadecimalDigit(int c);
int toAscii(int c);
int toLowerCase(int c);
int toUpperCase(int c);

/* So Random */
long random(long min, long max);
#if !defined(ARDUINO_OS)
/* Non OS-version uses overloaded version */
static inline long random(long max) {
  return random(0, max);
}
#endif
long randomSeed(unsigned long seed);

/* Bits and Bytes */
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))

#endif /* __ARDUINO_KOSAGI_H__ */
