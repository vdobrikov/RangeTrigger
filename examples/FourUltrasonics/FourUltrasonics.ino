/*
 * Example shows 4 ultrasonic sensors usage with RangeTrigger lib
 *
 * Tested with ESP8266 based NodeMCU board. Ensure pin numbers for your board.
 *
 * Note that all sensors shares the one Trig pin (D5)
 *
 * Author Vladimir Dobrikov <hedin.mail@gmail.com>
 */

#include <RangeTrigger.h>
#include <Ultrasonic.h>

#define FOUR_METERS 23200

#define TRIG_RANGE_CM 10
#define UPDATE_PERIOD_MS 500

#define PIN_TRIGGER D5
#define PIN_ECHO1 D1
#define PIN_ECHO2 D2
#define PIN_ECHO3 D6
#define PIN_ECHO4 D7

#define PIN_LED1 D8
#define PIN_LED2 10 // SD3
#define PIN_LED3 D3
#define PIN_LED4 D0

Ultrasonic us1(PIN_TRIGGER, PIN_ECHO1, FOUR_METERS);
Ultrasonic us2(PIN_TRIGGER, PIN_ECHO2, FOUR_METERS);
Ultrasonic us3(PIN_TRIGGER, PIN_ECHO3, FOUR_METERS);
Ultrasonic us4(PIN_TRIGGER, PIN_ECHO4, FOUR_METERS);

RangeTrigger rt1(us1, &trig1, TRIG_RANGE_CM, UPDATE_PERIOD_MS);
RangeTrigger rt2(us2, &trig2, TRIG_RANGE_CM, UPDATE_PERIOD_MS);
RangeTrigger rt3(us3, &trig3, TRIG_RANGE_CM, UPDATE_PERIOD_MS);
RangeTrigger rt4(us4, &trig4, TRIG_RANGE_CM, UPDATE_PERIOD_MS);

RangeTrigger rangeTriggers[] = {rt1, rt2, rt3, rt4};

void setup() {
  Serial.begin(115200);
  delay(20);

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
}

void loop() {
  for (int i=0; i<4; i++) {
     rangeTriggers[i].loop();
  }
}

void trig1(const bool state) {
  Serial.print("Trigger1 = ");
  Serial.println(state);

  digitalWrite(PIN_LED1, state);
}

void trig2(const bool state) {
  Serial.print("Trigger2 = ");
  Serial.println(state);

  digitalWrite(PIN_LED2, state);
}

void trig3(const bool state) {
  Serial.print("Trigger3 = ");
  Serial.println(state);

  digitalWrite(PIN_LED3, state);
}

void trig4(const bool state) {
  Serial.print("Trigger4 = ");
  Serial.println(state);

  digitalWrite(PIN_LED4, state);
}
