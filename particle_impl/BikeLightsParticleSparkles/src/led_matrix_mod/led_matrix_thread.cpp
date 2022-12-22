#include "led_matrix_thread.h"
#include "MAX7219LedMatrix/src/LedMatrix.h"
#include "spark_wiring_system.h"
#include "pubsub/pubsub.h"

#define NUMBER_OF_DEVICES 4
#define CS_PIN A5

LedMatrix led_matrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

static int eventspace = -1;
static event_type_t current_mode = EVENT_LED_TURN_RIGHT;
static event_type_t eventlist[] = {
    EVENT_LED_OFF,
    EVENT_LED_TURN_RIGHT,
    EVENT_LED_TURN_LEFT,
    EVENT_LED_FLASH_SLOWING_DOWN,
};

void led_thread_init(void){
    led_matrix.init();
    led_matrix.setIntensity(2);
    led_matrix.clear();
    led_matrix.commit();

    // Subscribe to led change events
    eventspace = subscribe_eventlist(eventlist, sizeof(eventlist), 16);
}

inline void event_led_turn_right_animation(void){
    for(int x = 0; x < 8; x++){
        led_matrix.clear();
        for(int y = 0; y < 63; y++){
            led_matrix.setPixel(y, x);
        }

        led_matrix.commit();
        delay(100);
    }
}

inline void event_led_turn_left_animation(void){
    for(int x = 8; x >= 0; x--){
        led_matrix.clear();
        for(int y = 0; y < 63; y++){
            led_matrix.setPixel(y, x);
        }

        led_matrix.commit();
        delay(100);
    }
}


void led_matrix_thread(void *params){
    for(;;){
        // Whenever there are any events we consume them!

        if(available_events(eventspace)){
            current_mode = consume_event(eventspace).event;
            switch (current_mode)
            {
            case EVENT_LED_OFF:
                led_matrix.clear();
                led_matrix.commit();
                break;

            default:
                break;
            }
        }

        switch (current_mode)
        {
        case EVENT_LED_TURN_RIGHT:
            event_led_turn_right_animation();
            break;

        case EVENT_LED_TURN_LEFT:
            event_led_turn_left_animation();
            break;

        case EVENT_LED_FLASH_SLOWING_DOWN:
            break;

        case EVENT_LED_OFF:
            break;

        default:
            break;
        }

    }
}