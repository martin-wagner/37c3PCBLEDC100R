/*
 * modeRainbow.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: martin
 */

#include "modeFade.h"

void ModeFade::update()
{
  if ((millis() - lastUpdate) > 50) { // Non-blocking delay
    fadeColor(r, stateR, waitR);
    fadeColor(g, stateG, waitG);
    fadeColor(b, stateB, waitB);
    auto lR = brightnessCorrection(r);
    auto lG = brightnessCorrection(g);
    auto lB = brightnessCorrection(b);

    Serial.println("Set: R" + String(lR) + ", G:" + String(lG) + ", B:" + String(lB));

    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, lR, lG, lB);
    }
    strip.show();
    lastUpdate = millis();
  }
}

void ModeFade::fadeColor(uint16_t &color, State &state, int &wait)
{
  switch (state) {
    case (State::UP): {
      if (color >= 0x3ff) // when maximum brightness is reached, set flag to start waiting time
          {
        state = State::ON;
      } else {
        color++;
      }
      break;
    }
    case (State::DOWN): {
      if (color == 0) // when minimum brightness is reached, clear flag to start waiting time
          {
        state = State::OFF;
      } else {
        color--;
      }
      break;
    }
    case (State::ON): {
      //state ON is not used, so no waiting time at maximum brightness. creation of waiting time has to be interchanged when using this
      state = State::DOWN;
      break;
    }
    case (State::OFF): {
      wait--;
      if (wait == 0) {  // returns to dimming operation and resets waiting timer
        state = State::UP;
        wait = (200 + rand()) & 0x7ff;  // maximum number is 2047
      }
      break;
    }
  }

  // as color brightness and off time is set randomly, it is possilble that all colors are going off. In this case we start dimming up instantly
  if ((r + g + b) < 30) {
    color = color + 2;
    state = State::UP;
  }
  // try to prevent color getting too white
  else if ((r + g + b) > 2300) {
    color = color - 2;
    state = State::DOWN;
  }
}

uint8_t ModeFade::brightnessCorrection(uint16_t intensity)
{
  // Normalize the intensity to the 0-1 range
  float normalized = intensity / 1023.0f;

  // Apply the CIE lightness correction
  float corrected;
  if (normalized <= 0.008856f) {
    corrected = normalized * 903.3f;
  } else {
    corrected = 116.0f * cbrtf(normalized) - 16.0f;
  }

  // Scale to the 0-255 range
  corrected = corrected / 100.0f * 255.0f;

  // Clamp the result and return
  return static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, corrected)));
}

