#include "led_matrix_thread.h"
#include "MAX7219LedMatrix/LedMatrix.h"
#include "spark_wiring_system.h"

#define NUMBER_OF_DEVICES 6
#define CS_PIN A5
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

void led_thread_init(void){
    ledMatrix.init();
    ledMatrix.setText("MAX7219 Animation Demo");
    ledMatrix.setNextText("Second text");
}

void led_matrix_thread(void *params){
    int x = 0;
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