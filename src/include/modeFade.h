/*
 * modeRainbow.h
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#ifndef INCLUDE_MODEFADE_H_
#define INCLUDE_MODEFADE_H_

#include "mode.h"

// Mode 2: Rainbow effect (non-blocking)
class ModeFade: public Mode
{
  private:
    unsigned long lastUpdate = 0;

    //0 ... 1023
    int r = 0;
    int g = 0;
    int b = 0;

    enum State {
      UP = 0,
      DOWN,
      ON,
      OFF
    };

    State stateR = State::OFF;
    State stateG = State::OFF;
    State stateB = State::OFF;
    int waitR = 0;
    int waitG = 0;
    int waitB = 0;

  public:
    void setup();

    void reset() override
    {
      lastUpdate = 0;
    }

    void update() override;

  protected:
    void fadeColor(int &color, State &state, int &wait);

    //intensity 0 ... 1023
    uint8_t brightnessCorrection(int intensity);

};

#endif /* INCLUDE_MODEFADE_H_ */
