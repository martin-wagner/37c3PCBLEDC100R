/*
 * modeRainbow.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#include "modeRainbow.h"

void ModeRainbow::update()
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

uint32_t ModeRainbow::Wheel(byte WheelPos)
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
