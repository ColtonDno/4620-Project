#include "WInterrupts.h"
#ifndef _SCREEN_TASKS_H_
#define _SCREEN_TASKS_H_

#include "variables.h"

void resetScreen()
{
  display.setRotation(3);
  display.fillScreen(TFT_BLACK);
  display.setTextColor(TFT_WHITE, TFT_BLACK);
  display.setTextSize(2);
}

void homePage()
{
  static uint8_t prev_option = 1;

  if (!xSemaphoreTake(menu_semaphore, portMAX_DELAY))
    return;
  // Terminal.println("Home aquired the menu mutex");
  
  if (prev_option == menu_option && previous_page == current_page)
  {
    xSemaphoreGive( menu_semaphore );
    return;
  }
  prev_option = menu_option;

  if (previous_page != 0)
    resetScreen();
  
  display.setCursor(1, 5);
  display.println("  Temperature");
  display.println("  Humidity");
  display.println("  Carbon Monoxide");

  display.setCursor(1, 5 + (16 * menu_option));
  display.print(">");

  xSemaphoreGive( menu_semaphore );
  // Terminal.println("Home released the menu mutex");
}

void drawFloatPage(float * prev, float * curr, const char * unit)
{
  if ((prev - curr) < 0.001 && previous_page == current_page)
    return;
  
  resetScreen();
  display.drawString(unit, display.drawFloat(*curr, 2, 1, 5), 5);
  prev = curr;
}

void temperaturePage()
{
  static float prev_temp = 0.0;

  if (!xSemaphoreTake(temperature_semaphore, portMAX_DELAY))
    return;
  
  drawFloatPage(&prev_temp, &temperature, "C");

  xSemaphoreGive( temperature_semaphore );
}

void humidityPage()
{
  static float prev_humid = 0.0;

  if (!xSemaphoreTake(humidity_semaphore, portMAX_DELAY))
    return;
  
  drawFloatPage(&prev_humid, &humidity, "%");

  xSemaphoreGive( humidity_semaphore );
}

void carbonMonoxidePage()
{
  static float prev_cmono = 0.0;

  if (!xSemaphoreTake(carbon_mono_semaphore, portMAX_DELAY))
    return;
  
  drawFloatPage(&prev_cmono, &co_ppm, "ppm"); // ppm

  xSemaphoreGive( carbon_mono_semaphore );
}

static void drawScreen(void* pvParameters)
{
  static TickType_t prev_wake_time = 0;
  PageFunction pages[] = {homePage, temperaturePage, humidityPage, carbonMonoxidePage};

  while (1)
  {
    vTaskDelayUntil(&prev_wake_time, 25);

    if (!xSemaphoreTake(page_semaphore, portMAX_DELAY))
      continue;
    // Terminal.println("Screen aquired the page mutex");

    pages[current_page]();
    previous_page = current_page;

    xSemaphoreGive( page_semaphore );
    // Terminal.println("Screen released the page mutex");
  }

  vTaskDelete(NULL);
}

#endif