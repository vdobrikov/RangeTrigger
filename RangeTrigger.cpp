#include "RangeTrigger.h"
#include <arduino.h>

byte RangeTrigger::idCounter = 0;

RangeTrigger::RangeTrigger(Ultrasonic& ultrasonic, TriggerFunction trigFunc, int trigRangeCm) {
    init(ultrasonic, trigFunc, trigRangeCm, DEFAULT_UPDATE_PERIOD_MS);
}

RangeTrigger::RangeTrigger(Ultrasonic& ultrasonic, TriggerFunction trigFunc, int trigRangeCm, int updatePeriodMs) {
    init(ultrasonic, trigFunc, trigRangeCm, updatePeriodMs);
}

void RangeTrigger::init(Ultrasonic& ultrasonic, TriggerFunction trigFunc, int trigRangeCm, int updatePeriodMs) {
    this->ultrasonic = &ultrasonic;
    this->trigFunc = trigFunc;
    this->trigRangeCm = trigRangeCm;
    this->updatePeriodMs = updatePeriodMs;

    id = RangeTrigger::idCounter;
    RangeTrigger::idCounter = RangeTrigger::idCounter + 1;
    state = false;
    upcomingState = false;
    ensureBuffer = 0;
    lastUpdateTimestamp = 0;
}

void RangeTrigger::loop() {
    uint32_t currentTimestamp = millis();
    if (currentTimestamp - lastUpdateTimestamp > updatePeriodMs) {
        int range = ultrasonic->Ranging(CM);
        RANGETRIGGER_PRINT(id);
        RANGETRIGGER_PRINT(":  range = ");
        RANGETRIGGER_PRINTLN(range);
        if (isnan(range)) {
            return;
        }

        upcomingState = range < trigRangeCm;
        verifyUpcomingState();
        lastUpdateTimestamp = currentTimestamp;
    }
}

void RangeTrigger::verifyUpcomingState() {
    if (upcomingState != state) {
        if (ensureBuffer >= MAX_ENSURE_BUFFER) {
            toggleState();
        } else {
            ensureBuffer++;
            RANGETRIGGER_PRINT(id);
            RANGETRIGGER_PRINT(": inc: ensureBuffer = ");
            RANGETRIGGER_PRINTLN(ensureBuffer);
        }
    } else {
        if (ensureBuffer > 0) {
            ensureBuffer--;
            RANGETRIGGER_PRINT(id);
            RANGETRIGGER_PRINT(": dec: ensureBuffer = ");
            RANGETRIGGER_PRINTLN(ensureBuffer);
        }
    }
}

void RangeTrigger::toggleState() {
    ensureBuffer = 0;
    state = upcomingState;
    RANGETRIGGER_PRINT(id);
    RANGETRIGGER_PRINT(": state changed: ");
    RANGETRIGGER_PRINTLN(state);

    trigFunc(state);
}
