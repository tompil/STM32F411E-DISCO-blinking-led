.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.word  _init_data_start
.word  _data_start
.word  _data_end
.word  _bss_start
.word  _bss_end

.section .text.__reset_handler, "ax", %progbits
.type __reset_handler, %function
__reset_handler:
  ldr  sp, =_stack_end

CopyDataSegmentToRam:
  ldr  r0, =_data_start
  ldr  r1, =_data_end
  ldr  r2, =_init_data_start
  b    LoopCopyDataToRam
CopyDataWordToRam:
  ldr  r3, [r2], #4
  str  r3, [r0], #4
LoopCopyDataToRam:
  cmp  r0, r1
  bne  CopyDataWordToRam

FillBssSegmentWithZeros:
  ldr  r0, =_bss_start
  ldr  r1, =_bss_end
  mov  r2, #0
  b    LoopFillBssSegmentWithZeros
SetBssByteToZero:
  str  r2, [r0], #4
LoopFillBssSegmentWithZeros:
  cmp  r0, r1
  bne  SetBssByteToZero

  bl   low_level_init
  bl   main
  bx   lr
.size __reset_handler, .-__reset_handler

.section .text.__default_handler, "ax", %progbits
.type __default_handler, %function
__default_handler:
InfiniteLoop:
  b    InfiniteLoop
.size __default_handler, .-__default_handler

/* interrupt vector table */
.section .isr_vector, "a", %progbits
.type __isr_vectors, %object
__isr_vectors:
  .word _stack_end
  .word __reset_handler
  .word NMI_handler
  .word HardFault_handler
  .word MemManage_handler
  .word BusFault_handler
  .word UsageFault_handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVCall_handler
  .word DebugMonitor_handler
  .word 0
  .word PendSV_handler
  .word Systick_handler
  /* external interrupts */
  .word WWDG_irq_handler
  .word PVD_irq_handler
  .word TAMP_STAMP_irq_handler
  .word RTC_WKUP_irq_handler
  .word FLASH_irq_handler
  .word RCC_irq_handler
  .word EXTI0_irq_handler
  .word EXTI1_irq_handler
  .word EXTI2_irq_handler
  .word EXTI3_irq_handler
  .word EXTI4_irq_handler
  .word DMA1_Stream0_irq_handler
  .word DMA1_Stream1_irq_handler
  .word DMA1_Stream2_irq_handler
  .word DMA1_Stream3_irq_handler
  .word DMA1_Stream4_irq_handler
  .word DMA1_Stream5_irq_handler
  .word DMA1_Stream6_irq_handler
  .word ADC_irq_handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word EXTI9_5_irq_handler
  .word TIM1_BRK_TIM9_irq_handler
  .word TIM1_UP_TIM10_irq_handler
  .word TIM1_TRG_COM_TIM11_irq_handler
  .word TIM1_CC_irq_handler
  .word TIM2_irq_handler
  .word TIM3_irq_handler
  .word TIM4_irq_handler
  .word I2C1_EV_irq_handler
  .word I2C1_ER_irq_handler
  .word I2C2_EV_irq_handler
  .word I2C2_ER_irq_handler
  .word SPI1_irq_handler
  .word SPI2_irq_handler
  .word USART1_irq_handler
  .word USART2_irq_handler
  .word 0
  .word EXTI15_10_irq_handler
  .word RTC_Alarm_irq_handler
  .word OTG_FS_WKUP_irq_handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word DMA1_Stream7_irq_handler
  .word 0
  .word SDIO_irq_handler
  .word TIM5_irq_handler
  .word SPI3_irq_handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word DMA2_Stream0_irq_handler
  .word DMA2_Stream1_irq_handler
  .word DMA2_Stream2_irq_handler
  .word DMA2_Stream3_irq_handler
  .word DMA2_Stream4_irq_handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word OTG_FS_irq_handler
  .word DMA2_Stream5_irq_handler
  .word DMA2_Stream6_irq_handler
  .word DMA2_Stream7_irq_handler
  .word USART6_irq_handler
  .word I2C3_EV_irq_handler
  .word I2C3_ER_irq_handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word FPU_irq_handler
  .word 0
  .word 0
  .word SPI4_irq_handler
  .word SPI5_irq_handler
.size __isr_vectors, .-__isr_vectors

.weak      NMI_handler
.thumb_set NMI_handler, __default_handler

.weak      HardFault_handler
.thumb_set HardFault_handler, __default_handler

.weak      MemManage_handler
.thumb_set MemManage_handler, __default_handler

.weak      BusFault_handler
.thumb_set BusFault_handler, __default_handler

.weak      UsageFault_handler
.thumb_set UsageFault_handler, __default_handler

.weak      SVCall_handler
.thumb_set SVCall_handler, __default_handler

.weak      DebugMonitor_handler
.thumb_set DebugMonitor_handler, __default_handler

.weak      PendSV_handler
.thumb_set PendSV_handler, __default_handler

.weak      Systick_handler
.thumb_set Systick_handler, __default_handler

.weak      WWDG_irq_handler
.thumb_set WWDG_irq_handler, __default_handler

.weak      PVD_irq_handler
.thumb_set PVD_irq_handler, __default_handler

.weak      TAMP_STAMP_irq_handler
.thumb_set TAMP_STAMP_irq_handler, __default_handler

.weak      RTC_WKUP_irq_handler
.thumb_set RTC_WKUP_irq_handler, __default_handler

.weak      FLASH_irq_handler
.thumb_set FLASH_irq_handler, __default_handler

.weak      RCC_irq_handler
.thumb_set RCC_irq_handler, __default_handler

.weak      EXTI0_irq_handler
.thumb_set EXTI0_irq_handler, __default_handler

.weak      EXTI1_irq_handler
.thumb_set EXTI1_irq_handler, __default_handler

.weak      EXTI2_irq_handler
.thumb_set EXTI2_irq_handler, __default_handler

.weak      EXTI3_irq_handler
.thumb_set EXTI3_irq_handler, __default_handler

.weak      EXTI4_irq_handler
.thumb_set EXTI4_irq_handler, __default_handler

.weak      DMA1_Stream0_irq_handler
.thumb_set DMA1_Stream0_irq_handler, __default_handler

.weak      DMA1_Stream1_irq_handler
.thumb_set DMA1_Stream1_irq_handler, __default_handler

.weak      DMA1_Stream2_irq_handler
.thumb_set DMA1_Stream2_irq_handler, __default_handler

.weak      DMA1_Stream3_irq_handler
.thumb_set DMA1_Stream3_irq_handler, __default_handler

.weak      DMA1_Stream4_irq_handler
.thumb_set DMA1_Stream4_irq_handler, __default_handler

.weak      DMA1_Stream5_irq_handler
.thumb_set DMA1_Stream5_irq_handler, __default_handler

.weak      DMA1_Stream6_irq_handler
.thumb_set DMA1_Stream6_irq_handler, __default_handler

.weak      ADC_irq_handler
.thumb_set ADC_irq_handler, __default_handler

.weak      EXTI9_5_irq_handler
.thumb_set EXTI9_5_irq_handler, __default_handler

.weak      TIM1_BRK_TIM9_irq_handler
.thumb_set TIM1_BRK_TIM9_irq_handler, __default_handler

.weak      TIM1_UP_TIM10_irq_handler
.thumb_set TIM1_UP_TIM10_irq_handler, __default_handler

.weak      TIM1_TRG_COM_TIM11_irq_handler
.thumb_set TIM1_TRG_COM_TIM11_irq_handler, __default_handler

.weak      TIM1_CC_irq_handler
.thumb_set TIM1_CC_irq_handler, __default_handler

.weak      TIM2_irq_handler
.thumb_set TIM2_irq_handler, __default_handler

.weak      TIM3_irq_handler
.thumb_set TIM3_irq_handler, __default_handler

.weak      TIM4_irq_handler
.thumb_set TIM4_irq_handler, __default_handler

.weak      I2C1_EV_irq_handler
.thumb_set I2C1_EV_irq_handler, __default_handler

.weak      I2C1_ER_irq_handler
.thumb_set I2C1_ER_irq_handler, __default_handler

.weak      I2C2_EV_irq_handler
.thumb_set I2C2_EV_irq_handler, __default_handler

.weak      I2C2_ER_irq_handler
.thumb_set I2C2_ER_irq_handler, __default_handler

.weak      SPI1_irq_handler
.thumb_set SPI1_irq_handler, __default_handler

.weak      SPI2_irq_handler
.thumb_set SPI2_irq_handler, __default_handler

.weak      USART1_irq_handler
.thumb_set USART1_irq_handler, __default_handler

.weak      USART2_irq_handler
.thumb_set USART2_irq_handler, __default_handler

.weak      EXTI15_10_irq_handler
.thumb_set EXTI15_10_irq_handler, __default_handler

.weak      RTC_Alarm_irq_handler
.thumb_set RTC_Alarm_irq_handler, __default_handler

.weak      OTG_FS_WKUP_irq_handler
.thumb_set OTG_FS_WKUP_irq_handler, __default_handler

.weak      DMA1_Stream7_irq_handler
.thumb_set DMA1_Stream7_irq_handler, __default_handler

.weak      SDIO_irq_handler
.thumb_set SDIO_irq_handler, __default_handler

.weak      TIM5_irq_handler
.thumb_set TIM5_irq_handler, __default_handler

.weak      SPI3_irq_handler
.thumb_set SPI3_irq_handler, __default_handler

.weak      DMA2_Stream0_irq_handler
.thumb_set DMA2_Stream0_irq_handler, __default_handler

.weak      DMA2_Stream1_irq_handler
.thumb_set DMA2_Stream1_irq_handler, __default_handler

.weak      DMA2_Stream2_irq_handler
.thumb_set DMA2_Stream2_irq_handler, __default_handler

.weak      DMA2_Stream3_irq_handler
.thumb_set DMA2_Stream3_irq_handler, __default_handler

.weak      DMA2_Stream4_irq_handler
.thumb_set DMA2_Stream4_irq_handler, __default_handler

.weak      OTG_FS_irq_handler
.thumb_set OTG_FS_irq_handler, __default_handler

.weak      DMA2_Stream5_irq_handler
.thumb_set DMA2_Stream5_irq_handler, __default_handler

.weak      DMA2_Stream6_irq_handler
.thumb_set DMA2_Stream6_irq_handler, __default_handler

.weak      DMA2_Stream7_irq_handler
.thumb_set DMA2_Stream7_irq_handler, __default_handler

.weak      USART6_irq_handler
.thumb_set USART6_irq_handler, __default_handler

.weak      I2C3_EV_irq_handler
.thumb_set I2C3_EV_irq_handler, __default_handler

.weak      I2C3_ER_irq_handler
.thumb_set I2C3_ER_irq_handler, __default_handler

.weak      FPU_irq_handler
.thumb_set FPU_irq_handler, __default_handler

.weak      SPI4_irq_handler
.thumb_set SPI4_irq_handler, __default_handler

.weak      SPI5_irq_handler
.thumb_set SPI5_irq_handler, __default_handler
