
/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/i2c/i2c_master.h>
#include "rgbMatrixI2CDriver/rgbMatrix.h"

#include <pthread.h>
#include "pubsub-c/pubsub.h"
#include "led_matrix_runtime/led_matrix_runtime.h"
#include "thread_init/threads_init.h"
#include "statemachine/statemachine_test.h"

int main(int argc, FAR char *argv[])
{
  ps_init();
  test_sm();
  threads_list_init();

  while (1)
  {
    usleep(100000);
  }
  return 0;
}
