/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "hal.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config = {
#if STM32_HAS_GPIOA
  {VAL_GPIOA_MODER, VAL_GPIOA_OTYPER, VAL_GPIOA_OSPEEDR, VAL_GPIOA_PUPDR,
   VAL_GPIOA_ODR,   VAL_GPIOA_AFRL,   VAL_GPIOA_AFRH},
#endif
#if STM32_HAS_GPIOB
  {VAL_GPIOB_MODER, VAL_GPIOB_OTYPER, VAL_GPIOB_OSPEEDR, VAL_GPIOB_PUPDR,
   VAL_GPIOB_ODR,   VAL_GPIOB_AFRL,   VAL_GPIOB_AFRH},
#endif
#if STM32_HAS_GPIOC
  {VAL_GPIOC_MODER, VAL_GPIOC_OTYPER, VAL_GPIOC_OSPEEDR, VAL_GPIOC_PUPDR,
   VAL_GPIOC_ODR,   VAL_GPIOC_AFRL,   VAL_GPIOC_AFRH},
#endif
#if STM32_HAS_GPIOD
  {VAL_GPIOD_MODER, VAL_GPIOD_OTYPER, VAL_GPIOD_OSPEEDR, VAL_GPIOD_PUPDR,
   VAL_GPIOD_ODR,   VAL_GPIOD_AFRL,   VAL_GPIOD_AFRH},
#endif
#if STM32_HAS_GPIOE
  {VAL_GPIOE_MODER, VAL_GPIOE_OTYPER, VAL_GPIOE_OSPEEDR, VAL_GPIOE_PUPDR,
   VAL_GPIOE_ODR,   VAL_GPIOE_AFRL,   VAL_GPIOE_AFRH},
#endif
#if STM32_HAS_GPIOF
  {VAL_GPIOF_MODER, VAL_GPIOF_OTYPER, VAL_GPIOF_OSPEEDR, VAL_GPIOF_PUPDR,
   VAL_GPIOF_ODR,   VAL_GPIOF_AFRL,   VAL_GPIOF_AFRH},
#endif
#if STM32_HAS_GPIOG
  {VAL_GPIOG_MODER, VAL_GPIOG_OTYPER, VAL_GPIOG_OSPEEDR, VAL_GPIOG_PUPDR,
   VAL_GPIOG_ODR,   VAL_GPIOG_AFRL,   VAL_GPIOG_AFRH},
#endif
#if STM32_HAS_GPIOH
  {VAL_GPIOH_MODER, VAL_GPIOH_OTYPER, VAL_GPIOH_OSPEEDR, VAL_GPIOH_PUPDR,
   VAL_GPIOH_ODR,   VAL_GPIOH_AFRL,   VAL_GPIOH_AFRH},
#endif
#if STM32_HAS_GPIOI
  {VAL_GPIOI_MODER, VAL_GPIOI_OTYPER, VAL_GPIOI_OSPEEDR, VAL_GPIOI_PUPDR,
   VAL_GPIOI_ODR,   VAL_GPIOI_AFRL,   VAL_GPIOI_AFRH}
#endif
};
#endif

/*
 * @brief Utility definitions for jumping to bootloader.
 */
#define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))
extern uint32_t __ram0_end__;

/**
 * @brief   Early initialization code.
 * @details This initialization must be performed just after stack setup
 *          and before any other initialization.
 */
void __early_init(void) {

#if defined(BOOTLOADER_ADDRESS)
  if(*((unsigned long *)(SYMVAL(__ram0_end__) - 4)) == MAGIC_BOOTLOADER_NUMBER) { /* magic flag set */
    *((unsigned long *)(SYMVAL(__ram0_end__) - 4)) = 0; /* erase the magic */
    /* This may not work (it does not for me). */
    /* May help sometimes, item 1:
     * remap the system flash to 0 */
    // RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
    // SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_MEM_MODE);
    // SYSCFG->CFGR1 |= SYSCFG_CFGR1_MEM_MODE_0;
    /* May help sometimes, item 2:
     * forcibly write HIGH to PB8 (note this is BOOT0
     * on STM32F042 TSSOP-20 and LQFP-32 packages - check yours!).
     */
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable clock
    GPIOB->MODER |= GPIO_MODER_MODER8_0; // output mode
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_8; // pushpull
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR8; // 2MHz 
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8; // enable pullup...
    GPIOB->BSRR.H.set = (1<<8); // write high
    // asm(  // wait for a while
    //   "ldr     r0,=0x200000\n\t"
    //   "dowaitloop:\n\t"
    //   "sub     r0,#1\n\t"
    //   "bne     dowaitloop\n\t"
    // );
    /* jump */
    asm(
      "ldr     r0, =" BOOTLOADER_ADDRESS "\n\t"
      "ldr     r1, [r0, #0]\n\t"
      "mov     sp, r1\n\t"
      "ldr     r0, [r0, #4]\n\t"
      "bx      r0"
    );
  }
#endif /* BOOTLOADER_ADDRESS */

  stm32_clock_init();
}

#if HAL_USE_MMC_SPI || defined(__DOXYGEN__)
/**
 * @brief   MMC_SPI card detection.
 */
bool mmc_lld_is_card_inserted(MMCDriver *mmcp) {

  (void)mmcp;
  /* TODO: Fill the implementation.*/
  return true;
}

/**
 * @brief   MMC_SPI card write protection detection.
 */
bool mmc_lld_is_write_protected(MMCDriver *mmcp) {

  (void)mmcp;
  /* TODO: Fill the implementation.*/
  return false;
}
#endif

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {
}
