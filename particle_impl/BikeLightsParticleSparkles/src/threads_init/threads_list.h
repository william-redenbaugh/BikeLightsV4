#ifndef _THREADS_LIST_H
#define _THREADS_LIST_H
#include "led_matrix_mod/led_matrix_thread.h"

#define THREAD_LIST                                                 \
    {                                                               \
        {led_matrix_thread, led_thread_init, NULL, "LED Matrix thread", 1024, 0},    \
    }

#define NUM_THREADS 1

#endif