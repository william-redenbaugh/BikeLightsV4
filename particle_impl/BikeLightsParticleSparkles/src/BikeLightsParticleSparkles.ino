#include "threads_init/threads_init.h"
#include "pubsub/pubsub.h"

SYSTEM_THREAD(ENABLED);

void setup() {
  Cellular.off();
  threads_list_init();
}

void loop() {

  publish_event(EVENT_LED_TURN_RIGHT, NULL);
  delay(3000);

  publish_event(EVENT_LED_TURN_LEFT, NULL);
  delay(3000);
}