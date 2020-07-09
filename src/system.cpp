#include "system.h"

static void init_systick()
{
    using namespace system::stk;
    STK->LOAD = (uint32_t)(system::CLOCK_KHZ - 1);
    STK->VAL = (uint32_t)(0u);
    STK->CTRL = ctrl::CLKSOURCE | ctrl::TICKINT | ctrl::ENABLE;
}

extern "C" void low_level_init()
{
    using namespace system::rcc;

    RCC->CR = cr::RESET | cr::HSION;
    while (!(RCC->CR & cr::HSIRDY))
        ;

    RCC->CFGR = cfgr::RESET;
    RCC->CR &= (uint32_t)(~(cr::HSEON | cr::CSSON | cr::PLLON));
    RCC->PLLCFGR = pllcfgr::RESET;
    RCC->CR &= (uint32_t)(~cr::HSEBYP);
    RCC->CIR = cir::RESET;

    RCC->CR |= cr::HSEON;
    while (!(RCC->CR & cr::HSERDY))
        ;

    RCC->PLLCFGR = (uint32_t)0x24003010; // reset value

    RCC->PLLCFGR &= (uint32_t)(~0x00437FF);
    // set PLLSRC = HSE, PLLP = 2, PLLN = 100, PLLM = 4
    RCC->PLLCFGR |= (uint32_t)((1 << 22) | (0x00 << 17) | (100 << 6) | 4);

    RCC->CR |= cr::PLLON;
    while (!(RCC->CR & cr::PLLRDY))
        ;
    RCC->CFGR &= (uint32_t)(~(7 << 10));
    RCC->CFGR |= (uint32_t)(4 << 10);
    uint32_t* const FLASH_ACR { reinterpret_cast<uint32_t*>(0x40023C00 + 0x00) };
    *FLASH_ACR &= (uint32_t)(~(0xF));
    *FLASH_ACR |= 0x03;

    RCC->CFGR &= (uint32_t)(~(cfgr::SW));
    RCC->CFGR |= static_cast<uint32_t>(cfgr::sw::PLL);
    while ((RCC->CFGR & (uint32_t)cfgr::SWS) != static_cast<uint32_t>(cfgr::sws::PLL))
        ;

    system::scb::SCB->VTOR = system::FLASH_BASE | system::VECT_TAB_OFFSET;

    init_systick();
}
