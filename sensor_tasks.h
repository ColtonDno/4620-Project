static void updateTemperatureAndHumidity(void* pvParameters)
{
  static TickType_t prev_wake_time = 0;

  while (1)
  {
    vTaskDelayUntil(&prev_wake_time, 1000);

    if (!xSemaphoreTake(humidity_semaphore, portMAX_DELAY))
      continue;
    
    if (!xSemaphoreTake(temperature_semaphore, portMAX_DELAY))
      continue;

    AHT.getSensor(&humidity, &temperature);
    temperature = ((temperature * 9) / 5 ) + 32;

    xSemaphoreGive( temperature_semaphore );
    xSemaphoreGive( humidity_semaphore );
  }

  vTaskDelete(NULL);
}

static void updateCO(void* pvParameters)
{
  static TickType_t prev_wake_time = 0;

  while (1)
  {
    vTaskDelayUntil(&prev_wake_time, 1000);

    if (!xSemaphoreTake(carbon_mono_semaphore, portMAX_DELAY))
      continue;

    co_ppm = mq7.readPpm();

    xSemaphoreGive( carbon_mono_semaphore );
  }

  vTaskDelete(NULL);
}