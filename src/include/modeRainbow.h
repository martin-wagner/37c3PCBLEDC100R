/*
 * modeRainbow.h
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#ifndef INCLUDE_MODERAINBOW_H_
#define INCLUDE_MODERAINBOW_H_

#include "mode.h"

// Mode 2: Rainbow effect (non-blocking)
class ModeRainbow: public Mode
{
  private:
    unsigned long lastUpdate = 0;
    int rainbowIndex = 0;

  public:
    void reset() override
    {
      lastUpdate = 0;
    }

    void update() override;

  protected:
    // Helper function for generating rainbow colors
    uint32_t Wheel(byte WheelPos);
};

#endif /* INCLUDE_MODERAINBOW_H_ */
