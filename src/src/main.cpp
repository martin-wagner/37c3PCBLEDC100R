/*
 * main.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#include "modeSolidColor.h"
#include "modeRainbow.h"
#include "modeColorWipe.h"
#include "modeFade.h"

// Define pins and settings
#define LED_PIN D4
#define NUM_LEDS 8
#define BUTTON_PIN D0      // Button to toggle display modes
#define BRIGHTNESS_PIN A0  // Analog input for brightness control

// Define EEPROM address for storing the mode
#define EEPROM_MODE_ADDR 0

// Initialize NeoPixel object
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_RGB + NEO_KHZ800);

// Variables for brightness and button
uint32_t currentMode = 0; // Current display mode
bool buttonState = false;
bool lastButtonState = false;
unsigned long lastButtonPress = 0;

const std::array<std::tuple<uint8_t, uint8_t, uint8_t>, Colors::COUNT> color =
{{
  { 255, 25, 0},   //red
  { 255, 80, 0},   //orange
  { 255, 150, 0},  //yellow
  { 56, 255, 0},   //green
  { 0, 255, 112},  //turquoise
  { 0, 0, 255},    //blue
  { 232, 0, 212},  //pink
}};

// Instantiate the mode objects
ModeFade mode1;
ModeRainbow mode2;
ModeColorWipe mode3;
ModeSolidColor modeR(std::get<0>(color[RED]), std::get<1>(color[RED]), std::get<2>(color[RED]));
ModeSolidColor modeG(std::get<0>(color[GREEN]), std::get<1>(color[GREEN]), std::get<2>(color[GREEN]));
ModeSolidColor modeB(std::get<0>(color[BLUE]), std::get<1>(color[BLUE]), std::get<2>(color[BLUE]));
ModeSolidColor modeYe(std::get<0>(color[YELLOW]), std::get<1>(color[YELLOW]), std::get<2>(color[YELLOW]));
ModeSolidColor modeTk(std::get<0>(color[TURQUOISE]), std::get<1>(color[TURQUOISE]), std::get<2>(color[TURQUOISE]));
ModeSolidColor modePi(std::get<0>(color[PINK]), std::get<1>(color[PINK]), std::get<2>(color[PINK]));
const int modeCount = 9;

// Array of mode pointers
std::array<Mode*, modeCount> modes = { &mode1, &mode2, &mode3, &modeR, &modeG, &modeB, &modeYe, &modeTk, &modePi };

void setup()
{
  Serial.begin(115200); // most ESP-01's use 115200 but this could vary
  Serial.println("Startup...");
  Serial.println("Version 2025-01-09");

  EEPROM.begin(512); // Initialize EEPROM with 512 bytes
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with pull-up

  auto seed = RANDOM_REG32;
  srand(seed);
  Serial.println("Seed: " + String(seed));

  currentMode = EEPROM.read(EEPROM_MODE_ADDR);
  if (currentMode > (modes.size() - 1)) {
    currentMode = 0;
  }
  Serial.println("Mode: " + String(currentMode));

  mode1.setup();
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
    modes[currentMode]->reset();
    currentMode = (currentMode + 1) % modes.size(); // Cycle through modes
    lastButtonPress = millis(); // Debounce
    Serial.println("Mode: " + String(currentMode));

    // Save the current mode to EEPROM
    EEPROM.write(EEPROM_MODE_ADDR, currentMode);
    EEPROM.commit(); // Commit changes to EEPROM
  }
  lastButtonState = buttonState;

  // Update the current mode
  modes[currentMode]->update();

  delay(10);
}
