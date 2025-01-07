#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

enum ButtonStates {RELEASED, WAITING, PRESSED};

class Button
{
  private:
    uint8_t button_pin;
    uint8_t button_current_state;
    uint8_t button_state;
    uint32_t last_waiting_press;

  public:
    Button(uint8_t button_pin);

    void updateButton();
    uint8_t getState();
    uint8_t getPress();
    
};

#endif