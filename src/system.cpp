#include "system.h"

static void init_systick() {
    using namespace system::stk;
    STK->LOAD = (uint32_t)(system::CLOCK_KHZ - 1);
    STK->VAL = (uint32_t)(0u);
    STK->CTRL = ctrl::CLKSOURCE | ctrl::TICKINT |ctrl::ENABLE;
}

extern "C" void low_level_init()
{
  using namespace system::rcc;

  RCC->CR = cr::RESET | cr::HSION;
  while(!(RCC->CR & cr::HSIRDY));

  RCC->CFGR = cfgr::RESET;
  RCC->CR &= (uint32_t)(~(cr::HSEON | cr::CSSON | cr::PLLON));
  RCC->PLLCFGR = pllcfgr::RESET;
  RCC->CR &= (uint32_t)(~cr::HSEBYP);
  RCC->CIR = cir::RESET;

  RCC->CR |= cr::HSEON;
  while(!(RCC->CR & cr::HSERDY));

  RCC->CFGR &= (uint32_t)(~(cfgr::SW));
  RCC->CFGR |= static_cast<uint32_t>(cfgr::sw::HSE);
  while ((RCC->CFGR & (uint32_t)cfgr::SWS ) != static_cast<uint32_t>(cfgr::sws::HSE));

  system::scb::SCB->VTOR = system::FLASH_BASE | system::VECT_TAB_OFFSET;

  init_systick();
}
