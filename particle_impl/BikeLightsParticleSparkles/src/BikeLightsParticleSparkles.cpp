/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/wredenba/git/BikeLightsV4/particle_impl/BikeLightsParticleSparkles/src/BikeLightsParticleSparkles.ino"
#include "threads_init/threads_init.h"
#include "pubsub/pubsub.h"

void setup();
void loop();
#line 4 "/home/wredenba/git/BikeLightsV4/particle_impl/BikeLightsParticleSparkles/src/BikeLightsParticleSparkles.ino"
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