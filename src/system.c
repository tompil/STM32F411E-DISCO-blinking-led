#include "system.h"

static void init_systick(void) {
    STK->LOAD = (uint32_t)(8000 - 1);
    STK->VAL = (uint32_t)(0u);
    STK->CTRL = STK_CTRL_CLKSOURCE | STK_CTRL_TICKINT | STK_CTRL_ENABLE;
}

void low_level_init(void)
{
  RCC->CR = RCC_CR_RESET | RCC_CR_HSION;
  while(!(RCC->CR & RCC_CR_HSIRDY));

  RCC->CFGR = RCC_CFGR_RESET;
  RCC->CR &= (uint32_t)(~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON));
  RCC->PLLCFGR = RCC_PLLCFGR_RESET;
  RCC->CR &= (uint32_t)(~RCC_CR_HSEBYP);
  RCC->CIR = RCC_CIR_RESET;

  RCC->CR |= RCC_CR_HSEON;
  while(!(RCC->CR & RCC_CR_HSERDY));

  RCC->CFGR &= (uint32_t)(~(RCC_CFGR_SW));
  RCC->CFGR |= RCC_CFGR_SW_HSE;
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSE);

  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;

  init_systick();
}
