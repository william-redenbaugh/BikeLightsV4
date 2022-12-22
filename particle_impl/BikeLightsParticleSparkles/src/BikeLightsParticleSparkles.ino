#include "threads_init/threads_init.h"
#include "pubsub/pubsub.h"

SYSTEM_THREAD(ENABLED);

//#define LOGGING_USB
#ifdef LOGGING_USB
SerialLogHandler logHandler;
#endif

void setup() {
#ifdef LOGGING_USB
  waitFor(Serial.isConnected, 15000);
  Log.info("Logging initialized");
#endif
  Cellular.off();
  threads_list_init();
}

void loop() {
  delay(50000);
}