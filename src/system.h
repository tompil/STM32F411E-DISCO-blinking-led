#include <stdint.h>

#define REG32(reg) (*(volatile uint32_t *)(reg))
#define REG16(reg) (*(volatile uint16_t *)(reg))
#define REG8(reg) (*(volatile uint8_t *)(reg))

#define VAL32(val) ((uint32_t)(val))
#define VAL16(val) ((uint16_t)(val))
#define VAL8(val) ((uint8_t)(val))

#define __RW volatile
#define __RO const volatile
#define __WO volatile

// RCC
typedef struct {
__RW uint32_t CR;
__RW uint32_t PLLCFGR;
__RW uint32_t CFGR;
__RW uint32_t CIR;
__RW uint32_t AHB1RSTR;
__RW uint32_t AHB2RSTR;
__RW uint32_t __reserved1[2];
__RW uint32_t APB1RSTR;
__RW uint32_t APB2RSTR;
__RW uint32_t __reserved2[2];
__RW uint32_t AHB1ENR;
__RW uint32_t AHB2ENR;
__RW uint32_t __reserved3[2];
__RW uint32_t APB1ENR;
__RW uint32_t APB2ENR;
__RW uint32_t __reserved4[2];
__RW uint32_t AHB1LPENR;
__RW uint32_t AHB2LPENR;
__RW uint32_t __reserved5[2];
__RW uint32_t APB1LPENR;
__RW uint32_t APB2LPENR;
__RW uint32_t __reserved6[2];
__RW uint32_t BDCR;
__RW uint32_t CSR;
__RW uint32_t __reserved7[2];
__RW uint32_t SSCGR;
__RW uint32_t PLLI2SCFGR;
__RW uint32_t __reserved8;
__RW uint32_t DCKCFGR;
} rcc_t;

#define RCC ((rcc_t *)0x40023800)

// RCC CR
#define RCC_CR_RESET     VAL32(0x00000081)

#define RCC_CR_HSION     VAL32(0x00000001)
#define RCC_CR_HSIRDY    VAL32(0x00000002)
#define RCC_CR_HSITRIM   VAL32(0x000000F8)
#define RCC_CR_HSICAL    VAL32(0x0000FF00)
#define RCC_CR_HSEON     VAL32(0x00010000)
#define RCC_CR_HSERDY    VAL32(0x00020000)
#define RCC_CR_HSEBYP    VAL32(0x00040000)
#define RCC_CR_CSSON     VAL32(0x00080000)
#define RCC_CR_PLLON     VAL32(0x01000000)
#define RCC_CR_PLLRDY    VAL32(0x02000000)
#define RCC_CR_PLLI2SON  VAL32(0x04000000)
#define RCC_CR_PLLI2SRDY VAL32(0x08000000)

// RCC PLLCFGR
#define RCC_PLLCFGR_RESET VAL32(0x24003010)

// RCC CFGR
#define RCC_CFGR_RESET VAL32(0x00000000)

#define RCC_CFGR_SW    VAL32(0x00000003)
#define RCC_CFGR_SWS   VAL32(0x0000000C)

#define RCC_CFGR_SW_HSI VAL32(0x00)
#define RCC_CFGR_SW_HSE VAL32(0x01)
#define RCC_CFGR_SW_PLL VAL32(0x02)
#define RCC_CFGR_SWS_HSI VAL32(RCC_CFGR_SW_HSI << 2)
#define RCC_CFGR_SWS_HSE VAL32(RCC_CFGR_SW_HSE << 2)
#define RCC_CFGR_SWS_PLL VAL32(RCC_CFGR_SW_PLL << 2)

// RCC CIR
#define RCC_CIR_RESET VAL32(0x00000000)

// RCC AHB1ENR
#define RCC_AHB1ENR_GPIOAEN VAL32(0x00000001)
#define RCC_AHB1ENR_GPIOBEN VAL32(0x00000002)
#define RCC_AHB1ENR_GPIOCEN VAL32(0x00000004)
#define RCC_AHB1ENR_GPIODEN VAL32(0x00000008)
#define RCC_AHB1ENR_GPIOEEN VAL32(0x00000010)
#define RCC_AHB1ENR_GPIOHEN VAL32(0x00000080)
#define RCC_AHB1ENR_CRCEN   VAL32(0x00001000)
#define RCC_AHB1ENR_DMA1EN  VAL32(0x00200000)
#define RCC_AHB1ENR_DMA2EN  VAL32(0x00400000)

// SCB
typedef struct {
__RO uint32_t CPUDID;
__RW uint32_t ICSR;
__RW uint32_t VTOR;
__RW uint32_t AIRCR;
__RW uint32_t SCR;
__RW uint32_t CCR;
__RW uint32_t SHPR1;
__RW uint32_t SHPR2;
__RW uint32_t SHPR3;
__RW uint32_t SHCRS;
__RW uint32_t CFSR;
__RW uint32_t HFSR;
__RW uint32_t MMAR;
__RW uint32_t BFAR;
__RW uint32_t AFSR;
} scb_t;

#define SCB ((scb_t *)0xE000ED00)

#define VECT_TAB_OFFSET VAL32(0x00000000)
#define FLASH_BASE VAL32(0x08000000)

// GPIO
typedef struct {
    __RW uint32_t MODER;
    __RW uint32_t OTYPER;
    __RW uint32_t OSPEEDR;
    __RW uint32_t PUPDR;
    __RO uint32_t IDR;
    __RW uint32_t ODR;
    __WO uint32_t BSRR;
    __RW uint32_t LCKR;
    __RW uint32_t AFRL;
    __RW uint32_t AFRH;
} gpio_t;

#define GPIOD ((gpio_t *)0x40020C00)

// GPIO MODER
#define GPIO_MODER_INPUT   VAL32(0x00)
#define GPIO_MODER_OUTPUT  VAL32(0x01)
#define GPIO_MODER_ALTMODE VAL32(0x02)
#define GPIO_MODER_ANALOG  VAL32(0x03)

// GPIO OTYPER
#define GPIO_OTYPER_PUSH_PULL  VAL32(0x00)
#define GPIO_OTYPER_OPEN_DRAIN VAL32(0x01)

// GPIO OSPEEDR
#define GPIO_OSPEEDR_LOW    VAL32(0x00)
#define GPIO_OSPEEDR_MEDIUM VAL32(0x01)
#define GPIO_OSPEEDR_FAST   VAL32(0x02)
#define GPIO_OSPEEDR_HIGH   VAL32(0x03)

// GPIO PUPDR
#define GPIO_PUPDR_NO_PULL   VAL32(0x00)
#define GPIO_PUPDR_PULL_UP   VAL32(0x01)
#define GPIO_PUPDR_PULL_DOWN VAL32(0x02)
