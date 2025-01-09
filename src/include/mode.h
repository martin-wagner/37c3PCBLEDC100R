/*
 * mode.h
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#ifndef INCLUDE_MODE_H_
#define INCLUDE_MODE_H_

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;

enum Colors {
  RED = 0,
  ORANGE,
  YELLOW,
  GREEN,
  TURQUOISE,
  BLUE,
  PINK,

  COUNT
};
extern const std::array<std::tuple<uint8_t, uint8_t, uint8_t>, Colors::COUNT> color;

// Base class for modes
class Mode
{
  public:
    virtual void reset() = 0;
    virtual void update() = 0;
};


#endif /* INCLUDE_MODE_H_ */
