#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <string.h>

#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "i2c.h"

static inline __s32 i2c_smbus_access(int file, char read_write, __u8 command,
                                     int size, union i2c_smbus_data *data)
{
	struct i2c_smbus_ioctl_data args;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;
	return ioctl(file,I2C_SMBUS,&args);
}


static inline __s32 i2c_smbus_read_byte_data(int file, __u8 command)
{
	union i2c_smbus_data data;
	if (i2c_smbus_access(file,I2C_SMBUS_READ,command,
	                     I2C_SMBUS_BYTE_DATA,&data))
		return -1;
	else
		return 0x0FF & data.byte;
}

i2c_device::i2c_device(const char * path, int address)
{
    int rc;
    strcpy(this->path, path);
    this->address = address;

    this->fd = open(this->path, O_RDWR);
    if (this->fd < 0) err(errno, "Tried to open '%s'", path);
    rc = ioctl(this->fd, I2C_SLAVE, this->address);
    if (rc < 0) err(errno, "Tried to set device address '0x%02x'", address);
}

i2c_device::~i2c_device()
{
    close(this->fd);
}

int i2c_device::read_byte(uint8_t *buf, int reg)
{
    uint8_t data;
    if (this->fd < 0) return -1;

    data = i2c_smbus_read_byte_data(this->fd, reg);
    *buf = data;
    return 0;
}
