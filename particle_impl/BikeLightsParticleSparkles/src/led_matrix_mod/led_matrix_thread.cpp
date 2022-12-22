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

    // Subscribe to led change events
    eventspace = subscribe_eventlist(eventlist, sizeof(eventlist), 16);
    Log.info("eventspace: %d", eventspace);

    // Initialize LED matrix
    led_matrix.init();
    led_matrix.setIntensity(15);
    led_matrix.clear();
    led_matrix.commit();
}

int event_led_turn_x = 0;
inline void event_led_turn_right_animation(void){

    led_matrix.clear();
    for(int y = 0; y < 63; y++){
        led_matrix.setPixel(y, event_led_turn_x);
    }

    event_led_turn_x++;
    if(event_led_turn_x == 8)
        event_led_turn_x = 0;

    led_matrix.commit();
    delay(50);
}

inline void event_led_turn_left_animation(void){

    led_matrix.clear();
    for(int y = 0; y < 63; y++){
        led_matrix.setPixel(y, event_led_turn_x);
    }

    event_led_turn_x--;
    if(event_led_turn_x == -1)
        event_led_turn_x = 7;

    led_matrix.commit();
    delay(50);
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
            delay(100);
            break;

        case EVENT_LED_OFF:
            delay(100);
            break;

        default:
            break;
        }
    }
}