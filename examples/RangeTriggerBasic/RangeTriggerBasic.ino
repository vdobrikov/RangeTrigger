/*
 * Example shows the basic usage of RangeTrigger lib
 * 
 * Tested with ESP8266 based NodeMCU board. Ensure pin numbers for your board.
 * 
 * Wiring:
 * HC-SR04      NodeMCU
 * --------------------
 * GND -------- GND
 * VCC -------- VIN (5V)
 * TRIG ------- D5
 * ECHO ------- D1
 * 
 * LED              NodeMCU
 * ------------------------
 * GND ------------ GND
 * VCC -- R1kohm -- D8
 * 
 * Author Vladimir Dobrikov <hedin.mail@gmail.com>
 */

#include <RangeTrigger.h>
#include <Ultrasonic.h>

#define FOUR_METERS_MAX 23200

#define TRIG_RANGE_CM 10 
#define UPDATE_PERIOD_MS 500

#define PIN_TRIGGER D5
#define PIN_ECHO D1

#define PIN_LED D8

Ultrasonic us(PIN_TRIGGER, PIN_ECHO, FOUR_METERS_MAX);
RangeTrigger rt(us, &trig, TRIG_RANGE_CM, UPDATE_PERIOD_MS);

void setup() {
  Serial.begin(115200);
  delay(20);

  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  rt.loop();
}

void trig(const bool state) {
  Serial.print("Trigger = ");
  Serial.println(state);
  
  digitalWrite(PIN_LED, state);
}

