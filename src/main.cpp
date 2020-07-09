#include "system.h"

constexpr int GPIO_GREEN_LED{12};
constexpr int GPIO_RED_LED{14};
constexpr int GPIO_BLUE_LED{15};


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

void send_string_via_uart(const char* cstring) {
    using namespace system::usart;
    if (cstring == nullptr) return;

    for (int i = 0; cstring[i] != '\0'; ++i) {
        USART1->DR = cstring[i];
        while (!(USART1->SR & sr::TXE));
    }
    while (!(USART1->SR & sr::TC));
}

inline void init_usart1() {
    using namespace system;

    constexpr int USART1_TX_PIN{6};
    gpio::GPIOB->MODER |= static_cast<uint32_t>(gpio::moder::ALTMODE) << 2 * USART1_TX_PIN;
    gpio::GPIOB->OTYPER |= static_cast<uint32_t>(gpio::otyper::PUSH_PULL) << USART1_TX_PIN;
    gpio::GPIOB->OSPEEDR |= static_cast<uint32_t>(gpio::ospeedr::FAST) << 2 * USART1_TX_PIN;
    gpio::GPIOB->PUPDR |= static_cast<uint32_t>(gpio::pupdr::NO_PULL) << 2 * USART1_TX_PIN;

    constexpr int USART1_RX_PIN{7};
    gpio::GPIOB->MODER |= static_cast<uint32_t>(gpio::moder::ALTMODE) << 2 * USART1_RX_PIN;
    gpio::GPIOB->PUPDR |= static_cast<uint32_t>(gpio::pupdr::NO_PULL) << 2 * USART1_RX_PIN;

    // set alternate functions to both pins
    // TODO: create a function for that
    gpio::GPIOB->AFRL |= (uint32_t)(7 << USART1_TX_PIN * 4);
    gpio::GPIOB->AFRL |= (uint32_t)(7 << USART1_RX_PIN * 4);

    usart::USART1->CR1 &= ~(uint32_t)(usart::cr1::M);
    usart::USART1->CR2 &= (uint32_t)(usart::cr2::stop::one);
    usart::USART1->BRR = (uint32_t)(54u << 4 | 4);
    usart::USART1->CR1 |= usart::cr1::TE;
    usart::USART1->CR1 |= (uint32_t)(usart::cr1::UE);
}

extern "C" void TIM2_irq_handler() {
    using namespace system::tim;
    if (TIM2->SR & sr::UIF) {
        TIM2->SR &= (uint16_t)(~sr::UIF);
        toggle_led(GPIO_BLUE_LED);
    }
}

void init_timer() {
    using namespace system;
    // runs each 250ms
    tim::TIM2->CR1 &= ~tim::cr1::CEN;
    rcc::RCC->APB1RSTR |= (uint32_t)(1u);
    rcc::RCC->APB1RSTR &= ~(uint32_t)(1u);
    tim::TIM2->CR1 |= tim::cr1::DIR;
    tim::TIM2->PSC = CLOCK_KHZ / 2 - 1;
    tim::TIM2->ARR = 500;
    tim::TIM2->EGR |= tim::egr::UG;
    tim::TIM2->DIER |= tim::dier::UIE;
    tim::TIM2->CR1 |= tim::cr1::CEN;
}

int main() {
    using namespace system;

    rcc::RCC->AHB1ENR = rcc::ahb1enr::GPIOBEN | rcc::ahb1enr::GPIODEN;
    rcc::RCC->APB1ENR |= rcc::apb1enr::TIM2EN;
    rcc::RCC->APB2ENR |= rcc::apb2enr::USART1EN;


    // configure TIM2 interrupts in NVIC
    // TODO: create consexpr functions for setting a priority and enabling an interrupt
    nvic::NVIC->IP[7] = 0x30;
    nvic::NVIC->ISER[0] = (uint32_t)(1u << nvic::irq::TIM2);

    init_led(GPIO_GREEN_LED);
    init_led(GPIO_RED_LED);
    init_led(GPIO_BLUE_LED);
    init_timer();
    init_usart1();
    send_string_via_uart("System started!\r\n");
    turn_off_led(GPIO_GREEN_LED);

    turn_on_led(GPIO_RED_LED);
    delay(1000);
    turn_off_led(GPIO_RED_LED);

    while(1) {
        toggle_led(GPIO_GREEN_LED);
        delay(500);
    }
}
