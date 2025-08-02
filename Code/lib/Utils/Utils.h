#ifndef Utils_h
#define Utils_h

#include <Wire.h>

class Utils {
    public:
        /*
        * Begin I2C wire communication (*call before initializePins)
        */
        void beginWire();

        /*
        * Call pinMode for all pins defined in PinSetup.h
        */
        void initializePins();

        /*
        * Attaches interrupts to all pins
        */
        void attatchInterrupts();
};

#endif 