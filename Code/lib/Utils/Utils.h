#ifndef Utils_h
#define Utils_h

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

    private:
        void initLidar();
};

#endif 