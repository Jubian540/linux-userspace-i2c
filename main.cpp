#include "i2c.h"
#include <stdint.h>
#include <iostream>

int main()
{
    i2c_device test_dev("/dev/i2c-0", 0x08);
    uint8_t data;

    if (test_dev.read_byte(&data, 0x7c) != 0) {
            std::cout<<"read error"<<std::endl;
            return -1;
    }

    std::cout<<"data: "<<data<<std::endl;

    return 0;
}
