#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <pico/cyw43_arch.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <task.h>

#include <main.h>

void led_status(void *pvParameters) {
  stdio_init_all();
  while (1) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(250);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(250);
  }
}

int main() {
  stdio_init_all();

  xTaskCreate(led_status, "LED_STATUS", 256, NULL, 1, NULL);
  vTaskStartScheduler();
  return 0;
}

