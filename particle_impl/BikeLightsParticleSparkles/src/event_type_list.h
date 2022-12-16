#ifndef _EVENT_TYPE_LIST_H
#define _EVENT_TYPE_LIST_H

typedef enum{
    EVENT_NONE = 0,
    EVENT_LED_UPDATE,
    EVENT_DISPLAY_UPDATE,
    EVENT_STATUS_LED_ON,
    EVENT_STATUS_LED_OFF
}event_type_t;

#endif