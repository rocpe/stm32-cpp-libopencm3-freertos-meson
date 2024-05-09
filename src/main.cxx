#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
//#include <types.h>
#include <expected>
#include <vector>
#include "main.h"
#include <FreeRTOS.h>
#include <task.h>

class Pin {
  uint8_t a;
};

void
led_tesk(void* p)
{
  for (;;) {
    gpio_toggle(GPIOA, GPIO5);
    vTaskDelay(pdMS_TO_TICKS(500));
  }

}
extern void
vApplicationStackOverflowHook(xTaskHandle *pxTask, signed portCHAR *pcTaskName)
{
  for (;;);
}



int
main() {
    // Enable clock GPIOC
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOA);
    Pin a;
    Kon adsf;
    std::vector<int> asd;

    // Configure GPIO13
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO5);

    xTaskCreate(led_tesk, "led", 100, NULL, configMAX_PRIORITIES-1, NULL);
    vTaskStartScheduler();

    while (1) {
        // LED ON/OFF
        gpio_toggle(GPIOC, GPIO13);
        gpio_toggle(GPIOA, GPIO5);

        // Delay
        for (int i = 0; i < 200000; i++)
            __asm__("nop");
    }
}
