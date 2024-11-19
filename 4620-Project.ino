#include "variables.h"
#include "screen_tasks.h"
#include "button_tasks.h"
#include "sensor_tasks.h"

TaskHandle_t Handle_screenTask;
TaskHandle_t Handle_buttonTask;
TaskHandle_t Handle_menuTask;

void setup() 
{
  Terminal.begin(115200);

  display.begin();
  resetScreen();

  digitalWrite(LED_BUILTIN, LOW);

  delay(2000);

  temperature_semaphore = xSemaphoreCreateMutex();
  humidity_semaphore    = xSemaphoreCreateMutex();
  carbon_mono_semaphore = xSemaphoreCreateMutex();

  menu_semaphore = xSemaphoreCreateMutex();
  page_semaphore = xSemaphoreCreateMutex();

  xTaskCreate(updateButtons,  "Task A",       256, NULL, 3, &Handle_buttonTask);
  xTaskCreate(handleInput,    "Task B",       256, NULL, 2, &Handle_menuTask);
  xTaskCreate(drawScreen,     "Task C",       256, NULL, 1, &Handle_screenTask);

  vTaskStartScheduler();
  while(1);
}

void loop() {}
