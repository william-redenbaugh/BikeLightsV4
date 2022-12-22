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