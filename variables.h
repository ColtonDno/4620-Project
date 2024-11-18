#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include <Seeed_Arduino_FreeRTOS.h>
#include "TFT_eSPI.h"
#include "button.h"
#define Terminal Serial

SemaphoreHandle_t temperature_semaphore = NULL,
                  humidity_semaphore    = NULL,
                  carbon_mono_semaphore = NULL;

float humidity, temperature, co_ppm;

SemaphoreHandle_t menu_semaphore = NULL;
uint8_t menu_option;
#define MENU_OPTION_COUNT 3

SemaphoreHandle_t page_semaphore = NULL;
uint8_t previous_page, current_page;

Button* up_button     = new Button(WIO_5S_UP);
Button* down_button   = new Button(WIO_5S_DOWN);
Button* left_button   = new Button(WIO_5S_LEFT);
Button* middle_button = new Button(WIO_5S_PRESS);
Button* buttons[] = {up_button, down_button, left_button, middle_button};

TFT_eSPI display;

typedef void (*PageFunction)();

#endif