#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <expected>
#include <vector>
#include "main.h"
#include <FreeRTOS.h>
#include <task.h>



void
led_tesk(void* p)
{
  for (;;) {
    gpio_toggle(GPIOA, GPIO5);
    gpio_toggle(GPIOC, GPIO13);
    vTaskDelay(pdMS_TO_TICKS(100));
  }

}

int
main() {
    // Enable clock GPIOA/C
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOC);

    // Configure GPIO5/13
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO5);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

    xTaskCreate(led_tesk, "led", 100, NULL, configMAX_PRIORITIES-1, NULL);
    vTaskStartScheduler();

    while (1) {

    }
}
