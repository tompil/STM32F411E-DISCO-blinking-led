#include "system.h"

constexpr int GPIO_GREEN_LED{12};
constexpr int GPIO_RED_LED{14};

volatile uint32_t systick_counter;

extern "C" void Systick_handler() {
    if (systick_counter)
        --systick_counter;
}

void delay(uint32_t ms) {
    systick_counter = ms;
    while (systick_counter);
}

inline void init_led(int led_number) {
    using namespace system::gpio;
    GPIOD->MODER |= static_cast<uint32_t>(moder::OUTPUT) << 2 * led_number;
    GPIOD->OTYPER |= static_cast<uint32_t>(otyper::PUSH_PULL) << led_number;
    GPIOD->OSPEEDR |= static_cast<uint32_t>(ospeedr::LOW) << 2 * led_number;
    GPIOD->PUPDR |= static_cast<uint32_t>(pupdr::NO_PULL) << 2 * led_number;
}

inline void turn_off_led(int led_number) {
    system::gpio::GPIOD->BSRR = (uint32_t)(1u << (led_number + 16));
}

inline void turn_on_led(int led_number) {
    system::gpio::GPIOD->BSRR = (uint32_t)(1u << (led_number));
}

inline void toggle_led(int led_number) {
    system::gpio::GPIOD->ODR ^= 1u << led_number;
}

int main() {
    system::rcc::RCC->AHB1ENR = system::rcc::ahb1enr::GPIODEN;

    init_led(GPIO_GREEN_LED);
    init_led(GPIO_RED_LED);
    turn_off_led(GPIO_GREEN_LED);

    turn_on_led(GPIO_RED_LED);
    delay(1000);
    turn_off_led(GPIO_RED_LED);

    while(1) {
        toggle_led(GPIO_GREEN_LED);
        delay(500);
    }
}
