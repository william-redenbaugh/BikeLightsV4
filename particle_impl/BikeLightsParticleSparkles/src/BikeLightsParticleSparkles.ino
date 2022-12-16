#include "threads_init/threads_init.h"

void setup() {
  Cellular.off();
  threads_list_init();
}

void loop() {
  delay(50000);
}