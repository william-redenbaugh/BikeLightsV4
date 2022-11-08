#include "i2c_lib.h"
#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/i2c/i2c_master.h>

#define I2C_SLAVE_ADDR          0x24
#define I2C_SPEED               I2C_SPEED_FAST

/****************************************************************************
 * Name: host_receive
 ****************************************************************************/

static int i2c_host_receive(struct i2c_host host, struct i2c_client device, int bufid, uint8_t *buffer, size_t len,
                        bool lock)
{
  struct i2c_msg_s      msg[2];
  struct i2c_transfer_s xfer;
  int                   ret;
  uint8_t               cmd[3];
  size_t                sz = len - 1;

  if (lock)
    {
      cmd[0] = ICMD_VARLEN_TRANS(bufid);
      cmd[1] = sz & 0xff;
      cmd[2] = ((sz >> 8) & 0x3f) | 0x40;
    }
  else
    {
      cmd[0] = ICMD_FIXLEN_TRANS(bufid);
    }

  /* I2C packets */

  msg[0].frequency = host.freq;
  msg[0].addr      = device.device_id
  msg[0].buffer    = cmd;
  msg[0].length    = (lock) ? 3 : 1;
  msg[0].flags     = I2C_M_NOSTOP;

  msg[1].frequency = host.freq;
  msg[1].addr      = device.device_id;
  msg[1].buffer    = buffer;
  msg[1].length    = len;
  msg[1].flags     = I2C_M_READ;

  xfer.msgv = msg;
  xfer.msgc = 2;

  ret = ioctl(host.fd, I2CIOC_TRANSFER, (unsigned long)((uintptr_t)&xfer));

  if ((ret < 0) || (buffer[0] != 0))
    {
      printf("ERROR: failed to get the buffer%d: %d\n", bufid, ret);
      return -1;
    }

  return 0;
}

/****************************************************************************
 * Name: host_send
 ****************************************************************************/

static int i2c_host_send(struct i2c_host host, struct i2c_client device, int bufid, uint8_t *buffer, size_t len)
{
  struct i2c_msg_s      msg[2];
  struct i2c_transfer_s xfer;
  int                   ret;
  uint8_t               cmd[3];
  size_t                sz = len - 1;

  cmd[0] = ICMD_VARLEN_TRANS(bufid);
  cmd[1] = sz & 0xff;
  cmd[2] = ((sz >> 8) & 0x3f);

  /* I2C packets */

  msg[0].frequency = I2C_SPEED;
  msg[0].addr      = I2C_SLAVE_ADDR;
  msg[0].buffer    = cmd;
  msg[0].length    = 3;
  msg[0].flags     = I2C_M_NOSTOP;

  msg[1].frequency = I2C_SPEED;
  msg[1].addr      = I2C_SLAVE_ADDR;
  msg[1].buffer    = buffer;
  msg[1].length    = len;
  msg[1].flags     = I2C_M_NOSTART;

  xfer.msgv = msg;
  xfer.msgc = 2;

  ret = ioctl(fd, I2CIOC_TRANSFER, (unsigned long)((uintptr_t)&xfer));

  if (ret < 0)
    {
      printf("ERROR: failed to set the buffer%d: %d\n", bufid, ret);
      return -1;
    }

  return 0;
}
