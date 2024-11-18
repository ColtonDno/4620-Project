#include "button.h"

#define DEBOUNCEINTERVAL 25

Button::Button(uint8_t button_pin)
{
  this->button_pin = button_pin;
  pinMode(button_pin, INPUT_PULLUP);
}

// Checks if the button is pressed with debounce
void Button::updateButton()
{
  if (digitalRead(button_pin) == HIGH) 
  {
    button_current_state = RELEASED;
    button_state = RELEASED;
    return;
  }

  if (button_current_state == PRESSED)
    return;

  if (button_current_state == RELEASED)
  {
    button_current_state = WAITING;
    last_waiting_press = millis();
  }
  else if (millis() - last_waiting_press > DEBOUNCEINTERVAL)
  {
    button_current_state = PRESSED;
    button_state = PRESSED;
  }
}

uint8_t Button::getState()
{
  return button_current_state;
}

uint8_t Button::getPress()
{
  if (button_state == PRESSED)
  {
    button_state = WAITING;
    return PRESSED;
  }

  return RELEASED;
}