#ifndef _THREADS_LIST_H
#define _THREADS_LIST_H
#include "led_matrix_mod/led_matrix_thread.h"
#include "pubsub/pubsub.h"
#include "bluetooth_interface_module/bluetooth_interface_module.h"
#define THREAD_LIST                                                 \
    {                                                               \
        {led_matrix_thread, led_thread_init, NULL, "LED Matrix thread", 1024, 0},    \
        {event_management_thread, event_management_module_init, NULL, "Event management thread", 2048, 20}, \
        {bluetooth_interface_thread, bluetooth_interface_init, NULL, "Bluetooth Interface Thread", 2048, 20},\
    }

#define NUM_THREADS 3

#endif