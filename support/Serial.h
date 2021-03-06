#ifndef __HARDWARE_SERIAL_H__
#define __HARDWARE_SERIAL_H__

#include "Arduino-types.h"
#include "Stream.h"

#ifdef __cplusplus
class HardwareSerial : public Stream
{
  protected:
    uint8_t next_byte;
    uint8_t have_next_byte;

  public:
    void begin(unsigned long baud) { begin(baud, 0); }
    void begin(unsigned long, uint8_t);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() { return true; }
};

// Replace all instances of the global "Serial" object with a function call
// that returns a singleton.  That way, if "Serial" is not used at all, the
// HardwareSerial object will get optimized away.
HardwareSerial *serialWrapper(void);
#define Serial (*(serialWrapper()))

#endif /* defined(__cplusplus) */

#endif /* __HARDWARE_SERIAL_H__ */
