/*
 * modeSolidColor.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#include "modeSolidColor.h"

void ModeSolidColor::update()
{
  {
    if (!initialized) {
      uint32_t color = strip.Color(r, g, b);
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
      }
      initialized = true;
    }
    strip.show(); //always update
  }
}



