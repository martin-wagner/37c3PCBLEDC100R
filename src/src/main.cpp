/*
 * main.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#include <Adafruit_NeoPixel.h>

// Define pins and settings
#define LED_PIN D4
#define NUM_LEDS 8
#define BUTTON_PIN D0      // Button to toggle display modes
#define BRIGHTNESS_PIN A0  // Analog input for brightness control

// Initialize NeoPixel object
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variables for brightness and button
int currentMode = 0; // Current display mode
bool buttonState = false;
bool lastButtonState = false;
unsigned long lastButtonPress = 0;

// Base class for modes
class Mode
{
  public:
    virtual void update() = 0; // Pure virtual function for updating the mode
};

// Mode 1: Solid color
class Mode1: public Mode
{
  private:
    bool initialized = false;

  public:
    void update() override
    {
      if (!initialized) {
        uint32_t color = strip.Color(255, 0, 0); // Red
        for (int i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, color);
        }
        strip.show();
        initialized = true;
      }
    }
};

// Mode 2: Rainbow effect (non-blocking)
class Mode2: public Mode
{
  private:
    unsigned long lastUpdate = 0;
    int rainbowIndex = 0;

  public:
    void update() override
    {
      if (millis() - lastUpdate > 50) { // Non-blocking delay
        for (int i = 0; i < strip.numPixels(); i++) {
          int pixelIndex = (i + rainbowIndex) & 255;
          strip.setPixelColor(i, Wheel(pixelIndex));
        }
        strip.show();
        rainbowIndex = (rainbowIndex + 1) & 255; // Loop through 0-255
        lastUpdate = millis();
      }
    }

    // Helper function for generating rainbow colors
    uint32_t Wheel(byte WheelPos)
    {
      WheelPos = 255 - WheelPos;
      if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
      } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
      } else {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      }
    }
};

// Mode 3: Color wipe (non-blocking)
class Mode3: public Mode
{
  private:
    unsigned long lastUpdate = 0;
    int colorWipeIndex = 0;
    uint32_t currentColor = strip.Color(0, 0, 255); // Start with blue
    int colorStep = 0; // Tracks which color to switch to

  public:
    void update() override
    {
      if (millis() - lastUpdate > 50) { // Non-blocking delay
        strip.setPixelColor(colorWipeIndex, currentColor);
        strip.show();

        // Move to the next pixel
        colorWipeIndex++;
        if (colorWipeIndex >= strip.numPixels()) {
          colorWipeIndex = 0; // Reset index
          colorStep = (colorStep + 1) % 3; // Cycle colors
          if (colorStep == 0)
            currentColor = strip.Color(0, 0, 255); // Blue
          if (colorStep == 1)
            currentColor = strip.Color(0, 255, 0); // Green
          if (colorStep == 2)
            currentColor = strip.Color(255, 0, 0); // Red
        }
        lastUpdate = millis();
      }
    }
};

// Instantiate the mode objects
Mode1 mode1;
Mode2 mode2;
Mode3 mode3;
const int modeCount = 3;

// Array of mode pointers
std::array<Mode*, modeCount> modes = { &mode1, &mode2, &mode3 };

void setup()
{
  Serial.begin(115200); // most ESP-01's use 115200 but this could vary
  Serial.println("Startup...");
  Serial.println("Version 2025-01-09");

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with pull-up

  Serial.println("Mode: " + String(currentMode));
}

void loop()
{
  // Read analog input (A0) for brightness
  int brightnessValue = analogRead(BRIGHTNESS_PIN); // 0 to 1023
  if (brightnessValue < 50) {
    brightnessValue = 50;
  }
  int brightness = map(brightnessValue, 50, 1023, 1, 255); // Map to 0-255
  strip.setBrightness(brightness);

  // Read digital input (D0) for mode toggle
  buttonState = !digitalRead(BUTTON_PIN); // Active LOW button
  if (buttonState && !lastButtonState && (millis() - lastButtonPress) > 500) {
    currentMode = (currentMode + 1) % modes.size(); // Cycle through modes
    lastButtonPress = millis(); // Debounce
    Serial.println("Mode: " + String(currentMode));
  }
  lastButtonState = buttonState;

  // Update the current mode
  modes[currentMode]->update();

  delay(10);
}
