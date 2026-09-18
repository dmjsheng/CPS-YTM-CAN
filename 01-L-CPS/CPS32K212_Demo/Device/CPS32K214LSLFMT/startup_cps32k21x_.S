/**************************************************************************//**
 * @file     startup_BAT32A237.S
 * @brief    CMSIS Cortex-M0+ Core Device Startup File for
 *           Device BAT32A237
 * @version  1.0.0
 * @date     2020/10/24-laidi-20220620
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


 .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

.global  vectors
.global  Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
   ldr   r0, =__stack
   mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, =_sidata
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4

LoopCopyDataInit:
  ldr  r0, =__data_start__
  ldr  r3, =__data_end__
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =__bss_start__
  b  LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs  r3, #0
  str  r3, [r2]
  adds r2, r2, #4


LoopFillZerobss:
  ldr  r3, = __bss_end__
  cmp  r2, r3
  bcc  FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
    //bl __libc_init_array
/* Call the application's entry point.*/
  bl  main /*main entry*/

LoopForever:
    b LoopForever


.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  vectors, %object
  .size  vectors, .-vectors
  
  
vectors:
	.word   __stack
	.word	Reset_Handler         /* Reset Handler */
	.word	NMI_Handler           /* NMI Handler */
	.word	HardFault_Handler     /* Hard Fault Handler */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	SVC_Handler           /* SVCall Handler */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	PendSV_Handler        /* PendSV Handler */
	.word	SysTick_Handler       /* SysTick Handler */

	/* External interrupts */
/* ToDo:  Add here the vectors for the device specific external interrupts handler */
	.word	GPIOA_IRQHandler              		/*  IRQ00: Handler         */
	.word	GPIOB_IRQHandler              		/*  IRQ01: Handler         */
	.word	GPIOC_IRQHandler              		/*  IRQ02: Handler         */
	.word	GPIOD_IRQHandler              		/*  IRQ03: Handler         */
	.word	FLASH_IRQHandler              		/*  IRQ04: Handler         */
	.word	RESERVED0_IRQHandler              		/*  IRQ05: Handler         */
	.word	EUART0_RX_IRQHandler              		/*  IRQ06: Handler         */
	.word	EUART1_RX_IRQHandler              		/*  IRQ07: Handler         */
	.word	ASPI_TX_IRQHandler              		/*  IRQ08: Handler         */
	.word	CAN0_IRQHandler              		/*  IRQ09: Handler         */
	.word	ASPI_RX_IRQHandler              		/*  IRQ10: Handler         */
	.word	SPI1_IRQHandler              		/*  IRQ11: Handler         */
	.word	I2C0_IRQHandler              		/*  IRQ12: Handler         */
	.word	RESERVED1_IRQHandler              		/*  IRQ13: Handler         */
	.word	TIM10_IRQHandler              		/*  IRQ14: Handler         */
	.word	TIM11_IRQHandler              		/*  IRQ15: Handler         */
	.word	LPTIM_IRQHandler              		/*  IRQ16: Handler         */
	.word	GPIOE_IRQHandler              		/*  IRQ17: Handler         */
	.word	ETIMER_IRQHandler              		/*  IRQ18: Handler         */
	.word	TIM2_IRQHandler              		/*  IRQ19: Handler         */
	.word	EUART0_TX_IRQHandler              		/*  IRQ20: Handler         */
	.word	EUART1_TX_IRQHandler              		/*  IRQ21: Handler         */
	.word	WWDG_IRQHandler              		/*  IRQ22: Handler         */
	.word	IWDG_IRQHandler              		/*  IRQ23: Handler         */
	.word	ADC_IRQHandler              		/*  IRQ24: Handler         */
	.word	LVD_IRQHandler              		/*  IRQ25: Handler         */
	.word	VC_IRQHandler              		/*  IRQ26: Handler         */
	.word	SRAM_IRQHandler              		/*  IRQ27: Handler         */
	.word	AWK_OWIRE_IRQHandler              		/*  IRQ28: Handler         */
	.word	RESERVED2_IRQHandler              		/*  IRQ29: Handler         */
	.word	RESERVED3_IRQHandler              		/*  IRQ30: Handler         */
	.word	CLKTRIM_IRQHandler              		/*  IRQ31: Handler         */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler

   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler

   .weak      GPIOA_IRQHandler
   .thumb_set GPIOA_IRQHandler,Default_Handler

   .weak      GPIOB_IRQHandler
   .thumb_set GPIOB_IRQHandler,Default_Handler

		.weak      GPIOC_IRQHandler
   .thumb_set GPIOC_IRQHandler,Default_Handler

   .weak      GPIOD_IRQHandler
   .thumb_set GPIOD_IRQHandler,Default_Handler

		.weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      RESERVED0_IRQHandler
   .thumb_set RESERVED0_IRQHandler,Default_Handler

		.weak      EUART0_RX_IRQHandler
   .thumb_set EUART0_RX_IRQHandler,Default_Handler

   .weak      EUART1_RX_IRQHandler
   .thumb_set EUART1_RX_IRQHandler,Default_Handler

	.weak      ASPI_TX_IRQHandler
   .thumb_set ASPI_TX_IRQHandler,Default_Handler

   .weak      CAN0_IRQHandler
   .thumb_set CAN0_IRQHandler,Default_Handler

   .weak      ASPI_RX_IRQHandler
   .thumb_set ASPI_RX_IRQHandler,Default_Handler

   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler,Default_Handler

		.weak      I2C0_IRQHandler
   .thumb_set I2C0_IRQHandler,Default_Handler

   .weak      RESERVED1_IRQHandler
   .thumb_set RESERVED1_IRQHandler,Default_Handler

		.weak      TIM10_IRQHandler
   .thumb_set TIM10_IRQHandler,Default_Handler

   .weak      TIM11_IRQHandler
   .thumb_set TIM11_IRQHandler,Default_Handler

		.weak      LPTIM_IRQHandler
   .thumb_set LPTIM_IRQHandler,Default_Handler

   .weak      GPIOE_IRQHandler
   .thumb_set GPIOE_IRQHandler,Default_Handler

	.weak      ETIMER_IRQHandler
   .thumb_set ETIMER_IRQHandler,Default_Handler

   .weak      TIM2_IRQHandler
   .thumb_set TIM2_IRQHandler,Default_Handler

		.weak      EUART0_TX_IRQHandler
   .thumb_set EUART0_TX_IRQHandler,Default_Handler

   .weak      EUART1_TX_IRQHandler
   .thumb_set EUART1_TX_IRQHandler,Default_Handler

		.weak      WWDG_IRQHandler
   .thumb_set WWDG_IRQHandler,Default_Handler

   .weak      IWDG_IRQHandler
   .thumb_set IWDG_IRQHandler,Default_Handler

		.weak      ADC_IRQHandler
   .thumb_set ADC_IRQHandler,Default_Handler

   .weak      LVD_IRQHandler
   .thumb_set LVD_IRQHandler,Default_Handler

		.weak      VC_IRQHandler
   .thumb_set VC_IRQHandler,Default_Handler

   .weak      SRAM_IRQHandler
   .thumb_set SRAM_IRQHandler,Default_Handler

	.weak      AWK_OWIRE_IRQHandler
   .thumb_set AWK_OWIRE_IRQHandler,Default_Handler

   .weak      RESERVED2_IRQHandler
   .thumb_set RESERVED2_IRQHandler,Default_Handler
		
		.weak      RESERVED3_IRQHandler
   .thumb_set RESERVED3_IRQHandler,Default_Handler

   .weak      CLKTRIM_IRQHandler
   .thumb_set CLKTRIM_IRQHandler,Default_Handler
