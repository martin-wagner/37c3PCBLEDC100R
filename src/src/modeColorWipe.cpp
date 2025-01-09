/*
 * modeColorWipe.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#include "modeColorWipe.h"

void ModeColorWipe::update()
{
  if (millis() - lastUpdate > 50) { // Non-blocking delay
    strip.setPixelColor(colorWipeIndex, currentColor);
    strip.show();

    // Move to the next pixel
    colorWipeIndex++;
    // next round
    if (colorWipeIndex >= strip.numPixels()) {
      colorWipeIndex = 0; // Reset index
      colorStep = (colorStep + 1) % Colors::COUNT; // Cycle colors
      currentColor = strip.Color(std::get<0>(color[colorStep]),
          std::get<1>(color[colorStep]), std::get<2>(color[colorStep]));
    }
    lastUpdate = millis();
  }
}
