#include <Arduino.h>
#include "OS/OSThreadKernel.h"
#include "OS/OSMutexKernel.h"
#include "SPI.h"
#include "LedMatrix.h"

#define MATRIX_DISPLAY_STACK_SIZE 512
uint8_t matrix_display_stack[MATRIX_DISPLAY_STACK_SIZE];
os_thread_id_t matrix_display_thread_handler;

#define SENSOR_COLLECTION_STACK_SIZE 512
uint8_t sensor_collection_thread_stack[SENSOR_COLLECTION_STACK_SIZE];
os_thread_id_t sensor_collection_thread_handler;

#define PRIMARY_STATE_MACHINE_THREAD_STACK_SIZE 512
uint8_t primary_statemachine_thread_stack[PRIMARY_STATE_MACHINE_THREAD_STACK_SIZE];
os_thread_id_t primary_statemachine_thread_handler;

#define NUMBER_OF_DEVICES 4
#define CS_PIN PA_4
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

void init_thread(void);
static void matrix_display_task(void *args);
static void sensor_collection_thread(void *args);
static void primary_statemachine_thread(void *args);

void setup() {
  HAL_Init();
  SystemClock_Config();
  os_init();

  init_thread();
}

void init_thread(void){
  matrix_display_thread_handler = os_add_thread((thread_func_t)matrix_display_task, NULL, MATRIX_DISPLAY_STACK_SIZE, matrix_display_stack);
  primary_statemachine_thread_handler = os_add_thread((thread_func_t)primary_statemachine_thread, NULL, PRIMARY_STATE_MACHINE_THREAD_STACK_SIZE, primary_statemachine_thread_stack);
  sensor_collection_thread_handler = os_add_thread((thread_func_t)sensor_collection_thread, NULL, SENSOR_COLLECTION_STACK_SIZE, sensor_collection_thread_stack);
}

static void matrix_display_task(void *arg){
  UNUSED(arg);
  // Init ledmatrix
  ledMatrix.init();
  ledMatrix.clear();
  ledMatrix.setIntensity(0);

  for(int x = 0; x < 32; x++){
    for(int y = 0; y < 8; y++){
      ledMatrix.setPixel(x, y);
      ledMatrix.commit();
    }
    //os_thread_delay_ms(100);
  }
  for(;;){

    for(int n = 0; n < 15; n++){
      ledMatrix.setIntensity(n);
      os_thread_delay_ms(200);
    }
    for(int n = 15; n > 0; n--){
      ledMatrix.setIntensity(n);
      os_thread_delay_ms(200);
    }

    os_thread_delay_ms(100);
  }
}


static void sensor_collection_thread(void *args){
  for(;;){

  }
}

static void primary_statemachine_thread(void *args){
  for(;;){

  }
}

void loop() {
  os_thread_delay_ms(100);
}