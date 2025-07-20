#ifndef Diagnostics_h
#define Diagnostics_h

#include <Arduino.h>

#include "PinSetup.h"
#include "Constants.h"

class Diagnostics {
    public:
        Diagnostics();

        /*
        * Initializes OLED
        */
        void init();

        /*
        * Run simple diagnostics on OLED
        */
        void runSimple();

        /*
        * Run comprehensive diagnostics on OLED
        */
        void runVerbose();

    private:
        void OledSetup();    
};

#endif