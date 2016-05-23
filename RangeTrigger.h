#ifndef RangeTrigger_H
#define RangeTrigger_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Ultrasonic.h"

//#define RANGETRIGGER_DEBUG

#if defined(RANGETRIGGER_DEBUG)
#define RANGETRIGGER_PRINT(str) Serial.print(str)
#define RANGETRIGGER_PRINTLN(str) Serial.println(str)
#else
#define RANGETRIGGER_PRINT(str)
#define RANGETRIGGER_PRINTLN(str)
#endif

#define DEFAULT_UPDATE_PERIOD_MS 500 // 1/2 sec
#define MAX_ENSURE_BUFFER 1

class RangeTrigger;

typedef void (*TriggerFunction)(const bool);

class RangeTrigger {
    private:
        Ultrasonic* ultrasonic;
        int trigRangeCm;
        int updatePeriodMs;
        TriggerFunction trigFunc;

        uint32_t lastUpdateTimestamp;
        bool state;
        bool upcomingState;
        byte ensureBuffer;

        static byte idCounter;
        byte id;

        void init(Ultrasonic&, TriggerFunction, int, int);
        void verifyUpcomingState();
        void toggleState();

    public:
        RangeTrigger(Ultrasonic&, TriggerFunction, int);
        RangeTrigger(Ultrasonic&, TriggerFunction, int, int);
        void loop();
};

#endif // RangeTrigger_H
