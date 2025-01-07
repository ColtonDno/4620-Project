void handleAlarm(void* pvParameters)
{
  static TickType_t prev_wake_time = 0;
  static uint32_t alarm_timer;
  static uint8_t alarm_state = 0;
  uint32_t diff;

  while (1)
  {
    vTaskDelayUntil(&prev_wake_time, 25);

    if (!xSemaphoreTake(carbon_mono_semaphore, portMAX_DELAY))
      continue;

    if (co_ppm < 8.0)
    {
      analogWrite(BUZZERPIN, 0);
      xSemaphoreGive( carbon_mono_semaphore );
      continue;
    }

    if (millis() - alarm_timer < 500)
    {
      xSemaphoreGive( carbon_mono_semaphore );
      continue;
    }
    alarm_timer = millis();

    alarm_state = !alarm_state;

    if (alarm_state)
      analogWrite(BUZZERPIN, 128);
    else
      analogWrite(BUZZERPIN, 0);

    xSemaphoreGive( carbon_mono_semaphore );
  }

  vTaskDelete(NULL);
}