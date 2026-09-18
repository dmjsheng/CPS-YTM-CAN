extern void qClock_SysTick(void);
extern void HAL_IncTick(void);
#include "cps32k21x.h"
#include "cps32k21x_can.h"
#include "interrupt.h"

void NMI_Handler(void)
{
    while (1) { ; }
}

void HardFault_Handler(void)
{
    while (1) { ; }
}

void SVC_Handler(void)
{
    while (1) { ; }
}

void PendSV_Handler(void)
{
    while (1) { ; }
}

void SysTick_Handler(void)
{
    HAL_IncTick();     /* 驱动 HAL_GetTick() 正常推进，彻底激活 I2C_Wait_Flag 等底层超时机制，消除死循环死锁！ */
    qClock_SysTick();  /* 每 1ms 驱动 QuarkTS 内核时基前进一次 */
}

/* CAN0_IRQHandler is defined in cps32k21x_can.c */

void GPIOA_IRQHandler(void) { }
void GPIOB_IRQHandler(void) { }
void GPIOC_IRQHandler(void) { }
void GPIOD_IRQHandler(void) { }
void GPIOE_IRQHandler(void) { }
void FLASH_IRQHandler(void) { }
void EUART0_RX_IRQHandler(void) { }
void EUART0_TX_IRQHandler(void) { }
void EUART1_RX_IRQHandler(void) { }
void EUART1_TX_IRQHandler(void) { }
void ASPI_IRQHandler(void) { }
void SPI1_IRQHandler(void) { }
void I2C0_IRQHandler(void) { }
void TIM10_IRQHandler(void) { }
void TIM11_IRQHandler(void) { }
void LPTIM_IRQHandler(void) { }
void ETIMER_IRQHandler(void) { }
void TIM2_IRQHandler(void) { }
void WWDG_IRQHandler(void) { }
void IWDG_IRQHandler(void) { }
void ADC_IRQHandler(void) { }
void LVD_IRQHandler(void) { }
void VC_IRQHandler(void) { }
void SRAM_IRQHandler(void) { }
void AWK_IRQHandler(void) { }
void CLKTRIM_IRQHandler(void) { }
