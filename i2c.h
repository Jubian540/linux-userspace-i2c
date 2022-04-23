#ifndef I2C_KEYPAD_H
#define I2C_KEYPAD_H

#include <stdint.h>

class i2c_device {
    private:
        char path[32];
        int address;
        int fd;
    public:
        i2c_device(const char * path, int address);
        int read_byte(uint8_t *buf, int reg);
        ~i2c_device();
};

#endif
