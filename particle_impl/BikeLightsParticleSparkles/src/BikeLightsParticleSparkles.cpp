/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/wredenba/git/BikeLightsV4/particle_impl/BikeLightsParticleSparkles/src/BikeLightsParticleSparkles.ino"
#include "threads_init/threads_init.h"

void setup();
void loop();
#line 3 "/home/wredenba/git/BikeLightsV4/particle_impl/BikeLightsParticleSparkles/src/BikeLightsParticleSparkles.ino"
void setup() {
  Cellular.off();
  threads_list_init();
}

void loop() {
  delay(50000);
}