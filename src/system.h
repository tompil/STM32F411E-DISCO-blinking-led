#include <cstdint>

#define REG32(reg) (*(volatile uint32_t*)(reg))
#define REG16(reg) (*(volatile uint16_t*)(reg))
#define REG8(reg) (*(volatile uint8_t*)(reg))

#define VAL32(val) ((uint32_t)(val))
#define VAL16(val) ((uint16_t)(val))
#define VAL8(val) ((uint8_t)(val))

#define __RW volatile
#define __RO const volatile
#define __WO volatile

// TODO: investigate possibility to use alignas instead of the padding members

namespace system {
constexpr uint32_t CLOCK_KHZ { 100000 };

namespace rcc {
    struct rcc_t {
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
    };

    volatile rcc_t* const RCC { reinterpret_cast<rcc_t*>(0x40023800) };

    namespace cr {
        constexpr uint32_t RESET { 0x00000081 };
        constexpr uint32_t HSION { 0x00000001 };
        constexpr uint32_t HSIRDY { 0x00000002 };
        constexpr uint32_t HSITRIM { 0x000000F8 };
        constexpr uint32_t HSICAL { 0x0000FF00 };
        constexpr uint32_t HSEON { 0x00010000 };
        constexpr uint32_t HSERDY { 0x00020000 };
        constexpr uint32_t HSEBYP { 0x00040000 };
        constexpr uint32_t CSSON { 0x00080000 };
        constexpr uint32_t PLLON { 0x01000000 };
        constexpr uint32_t PLLRDY { 0x02000000 };
        constexpr uint32_t PLLI2SON { 0x04000000 };
        constexpr uint32_t PLLI2SRDY { 0x08000000 };
    } // namespace rcc::cr

    namespace pllcfgr {
        constexpr uint32_t RESET { 0x24003010 };
    } // namespace rcc::pllcfgr

    namespace cfgr {
        constexpr uint32_t RESET { 0x00000000 };

        constexpr uint32_t SW { 0x00000003 };
        constexpr uint32_t SWS { 0x0000000C };

        enum class sw : uint32_t {
            HSI = 0x00,
            HSE = 0x01,
            PLL = 0x02
        };

        enum class sws : uint32_t {
            HSI = static_cast<uint32_t>(sw::HSI) << 2,
            HSE = static_cast<uint32_t>(sw::HSE) << 2,
            PLL = static_cast<uint32_t>(sw::PLL) << 2
        };
    } // namespace rcc::cfgr

    namespace cir {
        constexpr uint32_t RESET { 0x00000000 };
    } // namespace rcc::cir

    namespace ahb1enr {
        constexpr uint32_t GPIOAEN { 0x00000001 };
        constexpr uint32_t GPIOBEN { 0x00000002 };
        constexpr uint32_t GPIOCEN { 0x00000004 };
        constexpr uint32_t GPIODEN { 0x00000008 };
        constexpr uint32_t GPIOEEN { 0x00000010 };
        constexpr uint32_t GPIOHEN { 0x00000080 };
        constexpr uint32_t CRCEN { 0x00001000 };
        constexpr uint32_t DMA1EN { 0x00200000 };
        constexpr uint32_t DMA2EN { 0x00400000 };
    } // namespace ahb1enr

    namespace apb1enr {
        constexpr uint32_t TIM2EN { 0x00000001 };
    } // namespace apb1enr

    namespace apb2enr {
        constexpr uint32_t USART1EN { 0x00000010 };
    } // namespace apb2enr
} // namespace rcc

namespace scb {
    struct scb_t {
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
    };

    volatile scb_t* const SCB { reinterpret_cast<scb_t*>(0xE000ED00) };
} // namespace scb

constexpr uint32_t VECT_TAB_OFFSET { 0x00000000 };
constexpr uint32_t FLASH_BASE { 0x08000000 };

namespace gpio {
    struct gpio_t {
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
    };

    volatile gpio_t* const GPIOA { reinterpret_cast<gpio_t*>(0x40020000) };
    volatile gpio_t* const GPIOB { reinterpret_cast<gpio_t*>(0x40020400) };
    volatile gpio_t* const GPIOD { reinterpret_cast<gpio_t*>(0x40020C00) };

    enum class moder : uint32_t {
        INPUT = 0x00,
        OUTPUT = 0x01,
        ALTMODE = 0x02,
        ANALOG = 0x03
    };

    enum class otyper : uint32_t {
        PUSH_PULL = 0x00,
        OPEN_DRAIN = 0x01
    };

    enum class ospeedr : uint32_t {
        LOW = 0x00,
        MEDIUM = 0x01,
        FAST = 0x02,
        HIGH = 0x03
    };

    enum class pupdr : uint32_t {
        NO_PULL = 0x00,
        PULL_UP = 0x01,
        PULL_DOWN = 0x02
    };
} // namespace gpio

namespace stk {
    struct stk_t {
        __RW uint32_t CTRL;
        __RW uint32_t LOAD;
        __RW uint32_t VAL;
        __RO uint32_t CALIB;
    };

    volatile stk_t* const STK { reinterpret_cast<stk_t*>(0xE000E010) };

    namespace ctrl {
        constexpr uint32_t COUNTFLAG { 1u << 16 };
        constexpr uint32_t CLKSOURCE { 1u << 2 };
        constexpr uint32_t TICKINT { 1u << 1 };
        constexpr uint32_t ENABLE { 1u << 0 };
    } // namespace stk::ctrl

    namespace load {
        constexpr uint32_t RELOAD { 0x00FFFFFF };
    } // namespace stk::load

    namespace val {
        constexpr uint32_t CURRENT { 0x00FFFFFF };
    } // namespace stk::val

    namespace calib {
        constexpr uint32_t NOREF { 1u << 31 };
        constexpr uint32_t SKEW { 1u << 30 };
        constexpr uint32_t TENMS { 0x00FFFFFF };
    } // namespace stk::calib
} // namespace stk

namespace nvic {
    struct nvic_t {
        __RW uint32_t ISER[8];
        uint32_t __reserved0[24];
        __RW uint32_t ICER[8];
        uint32_t __reserved1[24];
        __RW uint32_t ISPR[8];
        uint32_t __reserved2[24];
        __RW uint32_t ICPR[8];
        uint32_t __reserved3[24];
        __RW uint32_t IABR[8];
        uint32_t __reserved4[56];
        __RW uint8_t IP[240];
        uint32_t __reserved5[644];
        __WO uint32_t STIR;
    };

    volatile nvic_t* const NVIC { reinterpret_cast<volatile nvic_t*>(0xE000E100) };

    namespace irq {
        constexpr uint32_t TIM2 { 28 };
    } // namespace irq
} // namespace nvic

namespace tim {
    // the struct applies only for timer TIM2, TIM3, TIM4 & TIM5
    // TODO: parametrize the struct, timers 2 with 5 and 3 with need different members' sizes
    struct tim_t {
        __RW uint16_t CR1;
        uint16_t __reserved0;
        __RW uint16_t CR2;
        uint16_t __reserved1;
        __RW uint16_t SMCR;
        uint16_t __reserved2;
        __RW uint16_t DIER;
        uint16_t __reserved3;
        __RW uint16_t SR;
        uint16_t __reserved4;
        __RW uint16_t EGR;
        uint16_t __reserved5;
        __RW uint16_t CCMR1;
        uint16_t __reserved6;
        __RW uint16_t CCMR2;
        uint16_t __reserved7;
        __RW uint16_t CCER;
        uint16_t __reserved8;
        __RW uint32_t CNT; // 16 bits for TIM3 & TIM4
        __RW uint16_t PSC;
        uint16_t __reserved9;
        __RW uint32_t ARR; // 16 bits for TIM3 & TIM4
        uint32_t __reserved10;
        __RW uint32_t CCR1; // 16 bits for TIM3 & TIM4
        __RW uint32_t CCR2; // 16 bits for TIM3 & TIM4
        __RW uint32_t CCR3; // 16 bits for TIM3 & TIM4
        __RW uint32_t CCR4; // 16 bits for TIM3 & TIM4
        uint32_t __reserved11;
        __RW uint16_t DCR;
        uint16_t __reserved12;
        __RW uint16_t DMAR;
        uint16_t __reserved13;
        __RW uint16_t OR;
        uint16_t __reserved14;
    };

    volatile tim_t* const TIM2 { reinterpret_cast<volatile tim_t*>(0x40000000) };

    namespace cr1 {
        constexpr uint16_t CEN { 0x0001 };
        constexpr uint16_t DIR { 0x0010 };
    } // namespace cr1

    namespace dier {
        constexpr uint16_t UIE { 0x0001 };
    } // namespace dier

    namespace sr {
        constexpr uint16_t UIF { 0x0001 };
    } // namespace sr

    namespace egr {
        constexpr uint16_t UG { 0x0001 };
    } // namespace egr
} // namespace tim

namespace usart {
    struct usart_t {
        __RW uint32_t SR; // some bits are read-only, other are rc_w0
        __RW uint32_t DR;
        __RW uint32_t BRR;
        __RW uint32_t CR1;
        __RW uint32_t CR2;
        __RW uint32_t CR3;
        __RW uint32_t GTPR;
    };

    volatile usart_t* const USART1 { reinterpret_cast<volatile usart_t*>(0x40011000) };

    namespace sr {
        constexpr uint16_t PE { 1u << 0 };
        constexpr uint16_t FE { 1u << 1 };
        constexpr uint16_t NF { 1u << 2 };
        constexpr uint16_t ORE { 1u << 3 };
        constexpr uint16_t IDLE { 1u << 4 };
        constexpr uint16_t RXNE { 1u << 5 };
        constexpr uint16_t TC { 1u << 6 };
        constexpr uint16_t TXE { 1u << 7 };
        constexpr uint16_t LBD { 1u << 8 };
        constexpr uint16_t CTS { 1u << 9 };
    }

    namespace cr1 {
        constexpr uint16_t SBK { 1u << 0 };
        constexpr uint16_t RWU { 1u << 1 };
        constexpr uint16_t RE { 1u << 2 };
        constexpr uint16_t TE { 1u << 3 };
        constexpr uint16_t IDLEIE { 1u << 4 };
        constexpr uint16_t RXNEIE { 1u << 5 };
        constexpr uint16_t TCIE { 1u << 6 };
        constexpr uint16_t TXEIE { 1u << 7 };
        constexpr uint16_t PEIE { 1u << 8 };
        constexpr uint16_t PS { 1u << 9 };
        constexpr uint16_t PCE { 1u << 10 };
        constexpr uint16_t WAKE { 1u << 11 };
        constexpr uint16_t M { 1u << 12 };
        constexpr uint16_t UE { 1u << 13 };
        constexpr uint16_t OVER8 { 1u << 15 };
    } // namespace cr1

    namespace cr2 {
        constexpr uint16_t ADD { 0x000F };
        constexpr uint16_t LBDL { 0x0020 };
        constexpr uint16_t LBDIE { 0x0040 };
        constexpr uint16_t LBCL { 0x0100 };
        constexpr uint16_t CPHA { 0x0200 };
        constexpr uint16_t CPOL { 0x0400 };
        constexpr uint16_t CLKEN { 0x0800 };
        constexpr uint16_t STOP { 0x3000 };
        constexpr uint16_t LINEN { 0x4000 };

        enum class stop : uint16_t {
            one = 0x0 << 12,
            half = 0x1 << 12,
            two = 0x2 << 12,
            one_and_half = 0x3 << 12
        };
    } // namespace cr2

    namespace brr {
        constexpr uint16_t DIV_Fraction { 0x000F };
        constexpr uint16_t DIV_Mantissa { 0xFFF0 };
    } // namespace brr
} // namespace usart
} // namespace system
