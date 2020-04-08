#include "system.h"

#define GPIO_GREEN_LED 12

volatile uint32_t systick_counter;

void Systick_handler(void) {
    if (systick_counter)
        --systick_counter;
}

void delay(uint32_t ms) {
    systick_counter = ms;
    while (systick_counter);
}

void main(void) {
    RCC->AHB1ENR = RCC_AHB1ENR_GPIODEN;

    GPIOD->MODER = GPIO_MODER_OUTPUT << 2 * GPIO_GREEN_LED;
    GPIOD->OTYPER = GPIO_OTYPER_PUSH_PULL << GPIO_GREEN_LED;
    GPIOD->OSPEEDR = GPIO_OSPEEDR_LOW << 2 * GPIO_GREEN_LED;
    GPIOD->PUPDR = GPIO_PUPDR_NO_PULL << 2 * GPIO_GREEN_LED;

    GPIOD->BSRR = (uint32_t)(1u << (GPIO_GREEN_LED + 16));

    while(1) {
        GPIOD->ODR ^= 1u << GPIO_GREEN_LED;
        delay(500);
    }
}
