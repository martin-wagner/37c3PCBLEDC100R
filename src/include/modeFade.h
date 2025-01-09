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
    uint16_t r = 512;
    uint16_t g = 111;
    uint16_t b = 0;

    enum State {
      UP = 0,
      DOWN,
      ON,
      OFF
    };

    State stateR = State::UP;
    State stateG = State::UP;
    State stateB = State::OFF;
    int waitR = 0;
    int waitG = 0;
    int waitB = 100;

  public:
    void reset() override
    {
      lastUpdate = 0;
    }

    void update() override;

  protected:
    void fadeColor(uint16_t &color, State &state, int &wait);

    //intensity 0 ... 1023
    uint8_t brightnessCorrection(uint16_t intensity);

};

#endif /* INCLUDE_MODEFADE_H_ */
