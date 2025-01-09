/*
 * main.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#include <Adafruit_NeoPixel.h>

// Define the pin and number of LEDs
#define LED_PIN D4
#define NUM_LEDS 8

// Initialize the NeoPixel object
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Fill the LEDs one by one with a color
void colorWipe(uint32_t color, int delay_ms) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
        strip.show();
        delay(delay_ms);
    }
}

void setup() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
}

