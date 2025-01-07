#ifndef _BUTTON_TASKS_H_
#define _BUTTON_TASKS_H_

#include "button.h"

static void updateMenu()
{
  if (!xSemaphoreTake(menu_semaphore, portMAX_DELAY))
    return;

  if (up_button->getPress() == PRESSED)
  {
    if (menu_option == 0)
      menu_option = MENU_OPTION_COUNT - 1;
    else
      menu_option--;

    Terminal.println(menu_option);
  }

  if (down_button->getPress() == PRESSED)
  {
    if (menu_option == MENU_OPTION_COUNT - 1)
      menu_option = 0;
    else
      menu_option++;
  }

  if (middle_button->getPress() == PRESSED)
    current_page = menu_option + 1;

  xSemaphoreGive( menu_semaphore );
}

inline void pageInput()
{
  if (left_button->getPress() == PRESSED)
    current_page = 0;
}

static void handleInput(void* pvParameters)
{
  static TickType_t prev_wake_time = 0;
  while (1)
  {
    vTaskDelayUntil(&prev_wake_time, 25);

    if (!xSemaphoreTake(page_semaphore, portMAX_DELAY))
      continue;

    if (current_page == 0)
      updateMenu();
    else
      pageInput();

    xSemaphoreGive( page_semaphore );
  }

  vTaskDelete(NULL);
}

static void updateButtons(void* pvParameters)
{
  static TickType_t prev_wake_time = 0;
  while (1)
  {
    for (int i = 0; i < 4; i++)
      buttons[i]->updateButton();
      
    vTaskDelayUntil(&prev_wake_time, 25);
  }

  vTaskDelete(NULL);
}

#endif