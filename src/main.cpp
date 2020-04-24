#include "system.h"

constexpr int GPIO_GREEN_LED{12};

volatile uint32_t systick_counter;

extern "C" void Systick_handler() {
    if (systick_counter)
        --systick_counter;
}

void delay(uint32_t ms) {
    systick_counter = ms;
    while (systick_counter);
}

int main() {
    using namespace system;
    rcc::RCC->AHB1ENR = rcc::ahb1enr::GPIODEN;

    gpio::GPIOD->MODER = static_cast<uint32_t>(gpio::moder::OUTPUT) << 2 * GPIO_GREEN_LED;
    gpio::GPIOD->OTYPER = static_cast<uint32_t>(gpio::otyper::PUSH_PULL) << GPIO_GREEN_LED;
    gpio::GPIOD->OSPEEDR = static_cast<uint32_t>(gpio::ospeedr::LOW) << 2 * GPIO_GREEN_LED;
    gpio::GPIOD->PUPDR = static_cast<uint32_t>(gpio::pupdr::NO_PULL) << 2 * GPIO_GREEN_LED;

    gpio::GPIOD->BSRR = (uint32_t)(1u << (GPIO_GREEN_LED + 16));

    while(1) {
        gpio::GPIOD->ODR ^= 1u << GPIO_GREEN_LED;
        delay(500);
    }
}
