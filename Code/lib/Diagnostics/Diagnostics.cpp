#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "PinSetup.h"
#include "Constants.h"
#include "Diagnostics.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Diagnostics::Diagnostics() {
}

void Diagnostics::OledSetup(){
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display_handler.display();
  delay(2000);
 
  display_handler.clearDisplay();

  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.display();
}

void Diagnostics::init() {
    OledSetup();
}


/*
* Run simple diagnostics on OLED
*/
void Diagnostics::runSimple() {
    display_handler.setCursor(0,0);
    display_handler.clearDisplay();
    display_handler.println("simple test");  
    display_handler.display();
}

/*
* Run comprehensive diagnostics on OLED
*/
void Diagnostics::runVerbose() {
    
}
