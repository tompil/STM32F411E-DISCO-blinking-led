#include "system.h"

#define GPIO_GREEN_LED 12
void delay(uint32_t ticks) {
    for (volatile uint32_t i = 0; i < ticks; ++i);
}

void main(void) {
    RCC->AHB1ENR = RCC_AHB1ENR_GPIODEN;

    GPIOD->MODER = GPIO_MODER_OUTPUT << 2 * GPIO_GREEN_LED;
    GPIOD->OTYPER = GPIO_OTYPER_PUSH_PULL << GPIO_GREEN_LED;
    GPIOD->OSPEEDR = GPIO_OSPEEDR_LOW << 2 * GPIO_GREEN_LED;
    GPIOD->PUPDR = GPIO_PUPDR_NO_PULL << 2 * GPIO_GREEN_LED;

    while(1) {
        GPIOD->ODR ^= 1u << GPIO_GREEN_LED;
        delay(500000);
    }
}
