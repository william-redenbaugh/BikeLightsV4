#ifndef _I2C_LIB_H
#define _I2C_LIB_H

#include "i2c_lib.h"
#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/i2c/i2c_master.h>

struct i2c_host{
    int fd;
    uint32_t freq;
};

struct i2c_client{
    uint16_t device_id;
};

#endif