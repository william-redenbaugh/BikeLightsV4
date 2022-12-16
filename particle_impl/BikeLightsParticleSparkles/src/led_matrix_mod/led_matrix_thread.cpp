#include "led_matrix_thread.h"

#include "LedMatrix.h"
#include "spark_wiring_system.h"

void led_thread_init(void){
    ledMatrix.init();
    ledMatrix.setText("MAX7219 Animation Demo");
    ledMatrix.setNextText("Second text");
}

#define NUMBER_OF_DEVICES 6
#define CS_PIN A5
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

static int x = 0;
void led_matrix_thread(void *params){

    for(;;){
        ledMatrix.clear();
        ledMatrix.scrollTextLeft();
        ledMatrix.drawText();
        ledMatrix.commit();
        delay(50);
        x=x+1;
        if (x == 400) {
            ledMatrix.setNextText("Third text");
        }
    }
}