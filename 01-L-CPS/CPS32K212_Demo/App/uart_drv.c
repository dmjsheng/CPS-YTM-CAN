#include "uart_drv.h"

int _write(int file, char *ptr, int len)
{
    (void)file;
    for (int i = 0; i < len; i++)
    {
        if (ptr[i] == '\n')
        {
            EUART_Transmit_Data(EUART0, '\r');
        }
        EUART_Transmit_Data(EUART0, (uint8_t)ptr[i]);
    }
    return len;
}

int fputc(int ch, FILE *f)
{
    (void)f;
    if ((uint8_t)ch == '\n')
    {
        EUART_Transmit_Data(EUART0, '\r');
    }
    EUART_Transmit_Data(EUART0, (uint8_t)ch);
    return ch;
}

void Init_UART(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EUART_InitTypeDef EUART_InitStruct;

    cps_ddl_memclr(&GPIO_InitStruct, sizeof(GPIO_InitStruct));
    cps_ddl_memclr(&EUART_InitStruct, sizeof(EUART_InitStruct));

    /* 开启 EUART0 和 GPIOB 时钟 */
    RCC_APBPeriphClockCmd(RCC, RCC_APBPeriph_EUART0_CKEN, ENABLE);
    RCC_AHBPeriphClockCmd(RCC, RCC_AHBPeriph_GPIOB_CKEN, ENABLE);

    EUART_DeInit(EUART0);

    /* PB3 -> EUART0_TX */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_EUART0_TX_PB3);

    /* PB2 -> EUART0_RX */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource2, GPIO_AF_EUART0_RX_PB2);

    EUART_Soft_Reset(EUART0);

    EUART_InitStruct.SysclkFreq = SYSCLK_FREQ_48Mz;
    EUART_InitStruct.BaudRate = EUART_BaudRate_115200;
    EUART_InitStruct.WordLength = WordLength_8bit;
    EUART_InitStruct.StopBits = StopBits_1bit;
    EUART_InitStruct.ParitySel = Parity_None;
    EUART_InitStruct.WorkMode = WorkMode_TxRx;
    EUART_InitStruct.IDLE_Type = IDLE_TYPE_AfterStop;
    EUART_Init(EUART0, &EUART_InitStruct);

    EUART_ITConfig(EUART0, EUART_IT_RIE, DISABLE);
    NVIC_DisableIRQ(EUART0_TX_IRQn);
    NVIC_DisableIRQ(EUART0_RX_IRQn);

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("\r\n=======================================================\r\n");
    printf("   CPS32K214 CAN & OLED & UART Interactive Demo      \r\n");
    printf("   SysClk: 48MHz | CAN Baud: 500kbps | UART: 115200   \r\n");
    printf("   SW2 (PC14): Send CAN Frame 1 (ID:0x123)            \r\n");
    printf("   SW3 (PC15): Send CAN Frame 2 (ID:0x222)            \r\n");
    printf("   CAN RX: Auto Interrupted & Refreshed to OLED/UART   \r\n");
    printf("=======================================================\r\n");
}
