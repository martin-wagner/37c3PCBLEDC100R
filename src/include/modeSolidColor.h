/*
 * modeSolidColor.h
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#ifndef INCLUDE_MODESOLIDCOLOR_H_
#define INCLUDE_MODESOLIDCOLOR_H_

#include "mode.h"

// Mode 1: Solid color
class ModeSolidColor: public Mode
{
  private:
    bool initialized = false;
    const uint8_t r;
    const uint8_t g;
    const uint8_t b;

  public:
    ModeSolidColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {};

    void reset() override
    {
      initialized = false;
    }

    void update() override;
};



#endif /* INCLUDE_MODESOLIDCOLOR_H_ */
