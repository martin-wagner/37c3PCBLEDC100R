/*
 * modeColorWipe.h
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#ifndef INCLUDE_MODECOLORWIPE_H_
#define INCLUDE_MODECOLORWIPE_H_

#include "mode.h"

// Mode 3: Color wipe (non-blocking)
class ModeColorWipe: public Mode
{
  private:
    unsigned long lastUpdate = 0;
    int colorWipeIndex = 0;
    uint32_t currentColor = strip.Color(0, 0, 255); // Start with blue
    int colorStep = 0; // Tracks which color to switch to

  public:

    void reset() override
    {
      lastUpdate = 0;
    }

    void update() override;
};


#endif /* INCLUDE_MODECOLORWIPE_H_ */
