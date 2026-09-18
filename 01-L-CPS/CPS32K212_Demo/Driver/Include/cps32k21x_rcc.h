/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_RCC_H__
#define __CPS32K21X_RCC_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"


/** @defgroup LXT_InitTypeDef
  * @{
  */
typedef struct
{
	uint8_t LXT_CKIN_SEL;  	  /*!< CKIN输入端口选择  */
    						  
    uint8_t LXTPORT;     	  /*!< X32K_IN/X32K_OUT function selection  */
    						  
    FunctionalState LXTAON;   /*!< LXT只能使能不能禁止控制 */
    						  		
    FunctionalState LXTBYP;   /*!< LXT振荡器内部是否旁路 */
    				          
    FunctionalState LXTEN;    /*!< 外部LXT晶振使能信号 */
    						  
    uint8_t LXTSTARTUP;       /*!< 外部 32.768K 晶振稳定时间选择 */
}LXT_InitTypeDef;

/** @defgroup HXT_InitTypeDef
  * @{
  */
typedef struct
{  						
    uint8_t HXTPORT;     	   /*!< OSCIN/OSCOUT管脚配置 */
    								
    FunctionalState HXTBYP;    /*!< HXT振荡器内部是否旁路 */
    				        
    FunctionalState HXTEN;     /*!< 外部HXT晶振使能信号 */
    						
    uint8_t HXTSTARTUP;        /*!< 外部HXT晶振稳定时间选择 */
}HXT_InitTypeDef;

/* Exported types ------------------------------------------------------------*/
#define IS_RCC_ALL_PERIPH(PERIPH)   ((PERIPH) == RCC)


/** @defgroup AHBCLKEN / APBCLKEN configuration 
  * @{
  */
#define RCC_AHB_CLKMASK        (0x00000100UL)
#define RCC_APB_CLKMASK        (0x03FFFFFFUL)

#define RCC_UNLOCK_KEY         (0x55AA6699UL)
#define RCC_LOCK_KEY           (0x55AA6698UL)

/** @defgroup 定义时钟类型
  * @{
  */
#define RCC_CLKType_HIRC       ((uint32_t)0x00000001)   /*!< 内部高速时钟HIRC */
#define RCC_CLKType_HXT        ((uint32_t)0x00000002)   /*!< 外部高速晶体时钟HXT */
#define RCC_CLKType_LIRC       ((uint32_t)0x00000003)   /*!< 内部低速时钟LIRC */
#define RCC_CLKType_PLL        ((uint32_t)0x00000004)   /*!< PLL */

#define IS_RCC_CLK_TYPE(TYPE)  (((TYPE) == RCC_CLKType_HIRC) || \
                                ((TYPE) == RCC_CLKType_HXT)  || \
                                ((TYPE) == RCC_CLKType_LIRC) || \
								((TYPE) == RCC_CLKType_PLL))
                   
/** @defgroup 时钟类型使能 
  * @{
  */
#define RCC_CLKType_HIRC_EN      (BIT0)   /*!< HIRC时钟使能 */
#define RCC_CLKType_HXT_EN       (BIT1)   /*!< HXT时钟使能  */
#define RCC_CLKType_LIRC_EN      (BIT2)   /*!< LIRC时钟使能 */
#define RCC_CLKType_PLL_EN       (BIT0)   /*!< PLL时钟睡眠使能  */


/** @defgroup 系统时钟源类型 
  * @{
  */
#define RCC_SYSCLKSource_HIRC      ((uint32_t)0x00000001)   /*!< 系统时钟源：HIRC */
#define RCC_SYSCLKSource_HXT       ((uint32_t)0x00000002)   /*!< 系统时钟源：HXT  */
#define RCC_SYSCLKSource_PLL       ((uint32_t)0x00000004)   /*!< 系统时钟源：PLL  */
#define RCC_SYSCLKSource_LIRC      ((uint32_t)0x00000008)   /*!< 系统时钟源：LIRC */

#define IS_RCC_SYSCLK_SOURCE(SOURCE)  (((SOURCE) == RCC_SYSCLKSource_HIRC)|| \
                                       ((SOURCE) == RCC_SYSCLKSource_HXT) || \
                                       ((SOURCE) == RCC_SYSCLKSource_PLL) || \
									   ((SOURCE) == RCC_SYSCLKSource_LIRC))

/** @defgroup PLL输入时钟源定义
  * @{
  */
#define PLL_INPUT_SOURCE_HIRC      (0)      /*!< PLL input clock source ：HIRC */
#define PLL_INPUT_SOURCE_HXT       (0x01)   /*!< PLL input clock source ：HXT  */		


/** @defgroup PLL时钟输出频率定义(频率单位：MHz)
  * @{
  */
#define SET_PLL_FREQ_16MHz        (16u)
#define SET_PLL_FREQ_24MHz        (24u)
#define SET_PLL_FREQ_32MHz        (32u)
#define SET_PLL_FREQ_40MHz        (40u)
#define SET_PLL_FREQ_48MHz        (48u)


/** @defgroup PLL时钟稳定时间定义
  * @{
  */
#define RCC_PLL_STARTUP_PERIOD_MSK       ((uint32_t)0x07)
#define RCC_PLL_STARTUP_PERIOD_128       ((uint32_t)0x00)  /*!< 128个PLL周期 */
#define RCC_PLL_STARTUP_PERIOD_256       ((uint32_t)0x01)  /*!< 256个PLL周期 */
#define RCC_PLL_STARTUP_PERIOD_512       ((uint32_t)0x02)  /*!< 512个PLL周期 */
#define RCC_PLL_STARTUP_PERIOD_1024      ((uint32_t)0x03)  /*!< 1024个PLL周期 */
#define RCC_PLL_STARTUP_PERIOD_2048      ((uint32_t)0x04)  /*!< 2048个PLL周期 */
#define RCC_PLL_STARTUP_PERIOD_4096      ((uint32_t)0x05)  /*!< 4096个PLL周期 */
#define RCC_PLL_STARTUP_PERIOD_8192      ((uint32_t)0x06)  /*!< 8192个PLL周期 */
#define RCC_PLL_STARTUP_PERIOD_16384     ((uint32_t)0x07)  /*!< 16384个PLL周期 */

#define IS_RCC_PLL_STARTUP_PERIOD(PERIOD)    (((PERIOD) == RCC_PLL_STARTUP_PERIOD_128) || \
											  ((PERIOD) == RCC_PLL_STARTUP_PERIOD_256) || \
											  ((PERIOD) == RCC_PLL_STARTUP_PERIOD_512) || \
											  ((PERIOD) == RCC_PLL_STARTUP_PERIOD_1024) || \
											  ((PERIOD) == RCC_PLL_STARTUP_PERIOD_2048) || \
                                              ((PERIOD) == RCC_PLL_STARTUP_PERIOD_4096) || \
                                              ((PERIOD) == RCC_PLL_STARTUP_PERIOD_8192) || \
											  ((PERIOD) == RCC_PLL_STARTUP_PERIOD_16384))
                       
/** @defgroup 时钟输出源定义
  * @{
  */
#define RCC_MCO_SOURCE_SEL_MASK         (BIT10 | BIT9 | BIT8)  
#define RCC_MCO_SOURCE_SEL_HIRC         ((uint32_t)0x00)       /*!< 时钟输出源：HIRC */
#define RCC_MCO_SOURCE_SEL_HXT          ((uint32_t)0x01)       /*!< 时钟输出源：HXT  */
#define RCC_MCO_SOURCE_SEL_LIRC         ((uint32_t)0x02)       /*!< 时钟输出源：LIRC */
#define RCC_MCO_SOURCE_SEL_SYSCLK       ((uint32_t)0x04)       /*!< 时钟输出源：SYSCLK */
#define RCC_MCO_SOURCE_SEL_FCLK         ((uint32_t)0x05)       /*!< 时钟输出源：FCLK */
#define RCC_MCO_SOURCE_SEL_PLL          ((uint32_t)0x06)       /*!< 时钟输出源：PLL  */

#define IS_RCC_MCO_SOURCE_SEL(SOURCE)   (((SOURCE) == RCC_MCO_SOURCE_SEL_HIRC)|| \
									     ((SOURCE) == RCC_MCO_SOURCE_SEL_HXT) || \
										 ((SOURCE) == RCC_MCO_SOURCE_SEL_LIRC)|| \
										 ((SOURCE) == RCC_MCO_SOURCE_SEL_SYSCLK) || \
                                         ((SOURCE) == RCC_MCO_SOURCE_SEL_FCLK) || \
									     ((SOURCE) == RCC_MCO_SOURCE_SEL_PLL))
																																									
#define RCC_MCO_OUTPUT_ENABLE       (BIT12)


/** @defgroup AHB_peripheral_CLK 
  * @{
  */
#define RCC_AHBPeriph_GPIOA_CKEN        (BIT0)   /*!< GPIOA端口时钟使能 */
#define RCC_AHBPeriph_GPIOB_CKEN        (BIT1)   /*!< GPIOB端口时钟使能 */
#define RCC_AHBPeriph_GPIOC_CKEN        (BIT2)   /*!< GPIOC端口时钟使能 */
#define RCC_AHBPeriph_GPIOD_CKEN        (BIT3)   /*!< GPIOD端口时钟使能 */
#define RCC_AHBPeriph_CRC_CKEN          (BIT4)   /*!< CRC外设时钟使能   */
#define RCC_AHBPeriph_GPIOE_CKEN        (BIT6)   /*!< GPIOE外设时钟使能   */
#define RCC_AHBPeriph_FLASH_CKEN        (BIT8)   /*!< FLASH外设时钟使能 */

#define IS_RCC_AHB_PERIPH(PERIPH)    (((PERIPH) == RCC_AHBPeriph_GPIOA_CKEN) || \
                                      ((PERIPH) == RCC_AHBPeriph_GPIOB_CKEN) || \
                                      ((PERIPH) == RCC_AHBPeriph_GPIOC_CKEN) || \
                                      ((PERIPH) == RCC_AHBPeriph_GPIOD_CKEN) || \
                                      ((PERIPH) == RCC_AHBPeriph_CRC_CKEN) || \
                                      ((PERIPH) == RCC_AHBPeriph_GPIOE_CKEN) || \
                                      ((PERIPH) == RCC_AHBPeriph_FLASH_CKEN))


/** @defgroup HCLK Divide定义
  * @{
  */
#define RCC_HCLK_DIV1       (0UL)       /*!< HCLK时钟1分频 */
#define RCC_HCLK_DIV2       (1UL)       /*!< HCLK时钟2分频 */
#define RCC_HCLK_DIV4       (2UL)       /*!< HCLK时钟4分频 */
#define RCC_HCLK_DIV6       (3UL)       /*!< HCLK时钟6分频 */
#define RCC_HCLK_DIV8       (4UL)       /*!< HCLK时钟8分频 */
#define RCC_HCLK_DIV10      (5UL)       /*!< HCLK时钟10分频 */
#define RCC_HCLK_DIV12      (6UL)       /*!< HCLK时钟12分频 */
#define RCC_HCLK_DIV14      (7UL)       /*!< HCLK时钟14分频 */
#define RCC_HCLK_DIV16      (8UL)       /*!< HCLK时钟16分频 */
#define RCC_HCLK_DIV18      (9UL)       /*!< HCLK时钟18分频 */
#define RCC_HCLK_DIV20      (10UL)      /*!< HCLK时钟20分频 */
#define RCC_HCLK_DIV22      (11UL)      /*!< HCLK时钟22分频 */
#define RCC_HCLK_DIV24      (12UL)      /*!< HCLK时钟24分频 */
#define RCC_HCLK_DIV26      (13UL)      /*!< HCLK时钟26分频 */
#define RCC_HCLK_DIV28      (14UL)      /*!< HCLK时钟28分频 */
#define RCC_HCLK_DIV30      (15UL)      /*!< HCLK时钟30分频 */
#define RCC_HCLK_DIV32      (16UL)      /*!< HCLK时钟32分频 */

#define IS_RCC_HCLK_DIV(HCLKDIV)     (((HCLKDIV) >= 0x00) || ((HCLKDIV) <= 0xFF))

  

/** @defgroup APB总线外设时钟使能宏定义
  * @{
  */
#define RCC_APBPeriph_EUART0_CKEN          (BIT0)    /*!< UART0外设时钟使能 */
#define RCC_APBPeriph_EUART1_CKEN          (BIT1)    /*!< UART1外设时钟使能 */
#define RCC_APBPeriph_I2C0_CKEN            (BIT2)    /*!< I2C0外设时钟使能 */
#define RCC_APBPeriph_ASPI_CKEN            (BIT4)    /*!< ASPI外设时钟使能 */
#define RCC_APBPeriph_LPTIM_CKEN           (BIT5)    /*!< Low Power Timer外设时钟使能 */
#define RCC_APBPeriph_BASETIM_CKEN         (BIT6)    /*!< TIM10/TIM11外设时钟使能 */
#define RCC_APBPeriph_SYSCON_CKEN          (BIT7)    /*!< SYSCON外设时钟使能 */
#define RCC_APBPeriph_SPI1_CKEN            (BIT9)    /*!< SPI1外设时钟使能 */
#define RCC_APBPeriph_ETIMER_CKEN          (BIT10)   /*!< ETIMER外设时钟使能 */
#define RCC_APBPeriph_TIM2_CKEN            (BIT11)   /*!< TIM2外设时钟使能 */
#define RCC_APBPeriph_WWDG_CKEN            (BIT12)   /*!< WWDG外设时钟使能 */
#define RCC_APBPeriph_ADC_CKEN             (BIT13)   /*!< ADC外设时钟使能 */
#define RCC_APBPeriph_AWK_CKEN             (BIT14)   /*!< AWK外设时钟使能 */
#define RCC_APBPeriph_CLKTRIM_CKEN         (BIT16)   /*!< CLKTRIM外设时钟使能 */
#define RCC_APBPeriph_IWDG_CKEN            (BIT17)   /*!< IWDG外设时钟使能 */
#define RCC_APBPeriph_LVD_VC_OPA_CKEN      (BIT18)   /*!< LVD/VC/OPA外设时钟使能 */
#define RCC_APBPeriph_BEEP_CKEN            (BIT19)   /*!< BEEP外设时钟使能 */
#define RCC_APBPeriph_DEBUG_CKEN           (BIT20)   /*!< DEBUG外设时钟使能 */
#define RCC_APBPeriph_CAN0_CKEN            (BIT21)   /*!< CAN0外设时钟使能 */

#define IS_RCC_APB_PERIPH(PERIPH)          (((PERIPH) == RCC_APBPeriph_EUART0_CKEN) || \
											((PERIPH) == RCC_APBPeriph_EUART1_CKEN) || \
											((PERIPH) == RCC_APBPeriph_I2C0_CKEN) || \
											((PERIPH) == RCC_APBPeriph_ASPI_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_LPTIM_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_BASETIM_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_SYSCON_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_SPI1_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_ETIMER_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_TIM2_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_WWDG_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_ADC_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_AWK_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_CLKTRIM_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_IWDG_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_LVD_VC_OPA_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_BEEP_CKEN) || \
                                            ((PERIPH) == RCC_APBPeriph_DEBUG_CKEN) || \
											((PERIPH) == RCC_APBPeriph_CAN0_CKEN))


/** @defgroup APB_peripheral_CLK_DIV 
  * @{
  */
#define RCC_PCLK_DIV1       (0UL)       /*!< PCLK时钟1分频 */
#define RCC_PCLK_DIV2       (1UL)       /*!< PCLK时钟2分频 */
#define RCC_PCLK_DIV4       (2UL)       /*!< PCLK时钟4分频 */
#define RCC_PCLK_DIV6       (3UL)       /*!< PCLK时钟6分频 */
#define RCC_PCLK_DIV8       (4UL)       /*!< PCLK时钟8分频 */
#define RCC_PCLK_DIV10      (5UL)       /*!< PCLK时钟10分频 */
#define RCC_PCLK_DIV12      (6UL)       /*!< PCLK时钟12分频 */
#define RCC_PCLK_DIV14      (7UL)       /*!< PCLK时钟14分频 */
#define RCC_PCLK_DIV16      (8UL)       /*!< PCLK时钟16分频 */
#define RCC_PCLK_DIV18      (9UL)       /*!< PCLK时钟18分频 */
#define RCC_PCLK_DIV20      (10UL)      /*!< PCLK时钟20分频 */
#define RCC_PCLK_DIV22      (11UL)      /*!< PCLK时钟22分频 */
#define RCC_PCLK_DIV24      (12UL)      /*!< PCLK时钟24分频 */
#define RCC_PCLK_DIV26      (13UL)      /*!< PCLK时钟26分频 */
#define RCC_PCLK_DIV28      (14UL)      /*!< PCLK时钟28分频 */
#define RCC_PCLK_DIV30      (15UL)      /*!< PCLK时钟30分频 */
#define RCC_PCLK_DIV32      (16UL)      /*!< PCLK时钟32分频 */

#define IS_RCC_PCLK_DIV(PCLKDIV)     (((PCLKDIV) >= 0x00) || ((PCLKDIV) <= 0xFF))


/** @defgroup FCLK_O输出时钟分频，暂定义如下所示，如里其他分频可再行定义
  * @{
  */
#define RCC_FCLK_O_CLK_DIV1          (0UL)       /*!< FCLK_O输出时钟1分频 */
#define RCC_FCLK_O_CLK_DIV2          (1UL)       /*!< FCLK_O输出时钟2分频 */
#define RCC_FCLK_O_CLK_DIV4          (2UL)       /*!< FCLK_O输出时钟4分频 */
#define RCC_FCLK_O_CLK_DIV6          (3UL)       /*!< FCLK_O输出时钟6分频 */
#define RCC_FCLK_O_CLK_DIV8          (4UL)       /*!< FCLK_O输出时钟8分频 */
#define RCC_FCLK_O_CLK_DIV10         (5UL)       /*!< FCLK_O输出时钟10分频 */
#define RCC_FCLK_O_CLK_DIV12         (6UL)       /*!< FCLK_O输出时钟12分频 */
#define RCC_FCLK_O_CLK_DIV14         (7UL)       /*!< FCLK_O输出时钟14分频 */
#define RCC_FCLK_O_CLK_DIV16         (8UL)       /*!< FCLK_O输出时钟16分频 */
#define RCC_FCLK_O_CLK_DIV18         (9UL)       /*!< FCLK_O输出时钟18分频 */
#define RCC_FCLK_O_CLK_DIV20         (10UL)      /*!< FCLK_O输出时钟20分频 */
#define RCC_FCLK_O_CLK_DIV22         (11UL)      /*!< FCLK_O输出时钟22分频 */
#define RCC_FCLK_O_CLK_DIV24         (12UL)      /*!< FCLK_O输出时钟24分频 */
#define RCC_FCLK_O_CLK_DIV26         (13UL)      /*!< FCLK_O输出时钟26分频 */
#define RCC_FCLK_O_CLK_DIV28         (14UL)      /*!< FCLK_O输出时钟28分频 */
#define RCC_FCLK_O_CLK_DIV30         (15UL)      /*!< FCLK_O输出时钟30分频 */
#define RCC_FCLK_O_CLK_DIV32         (16UL)      /*!< FCLK_O输出时钟32分频 */

#define IS_RCC_FCLK_DIV(FCLK_DIV)    (((FCLK_DIV) >= 0x00) || ((FCLK_DIV) <= 0xFF))

#define RCC_FCLK_DIV_MASK            ((uint32_t)0x000000FF)


/** @defgroup APB & AHB peripheral RST
  * @{
  */
#define RCC_APBPeriph_EUART0_RST          (BIT0)    /*!< EUART0外设复位使能 */
#define RCC_APBPeriph_EUART1_RST          (BIT1)    /*!< EUART1外设复位使能 */
#define RCC_APBPeriph_I2C0_RST            (BIT2)    /*!< I2C0外设复位使能 */
#define RCC_APBPeriph_ASPI_RST            (BIT4)    /*!< ASPI外设复位使能 */
#define RCC_APBPeriph_LPTIM_RST           (BIT5)    /*!< Low Power Timer外设复位使能 */
#define RCC_APBPeriph_BASETIM_RST         (BIT6)    /*!< TIM10/TIM11外设复位使能 */
#define RCC_APBPeriph_SYSCON_RST          (BIT7)    /*!< SYSCON外设复位使能 */
#define RCC_APBPeriph_SPI1_RST            (BIT9)    /*!< SPI1外设复位使能 */
#define RCC_APBPeriph_ETIMER_RST          (BIT10)   /*!< ETIMER外设复位使能 */
#define RCC_APBPeriph_TIM2_RST            (BIT11)   /*!< TIM2外设复位使能 */
#define RCC_APBPeriph_WWDG_RST            (BIT12)   /*!< WWDG外设复位使能 */
#define RCC_APBPeriph_ADC_RST             (BIT13)   /*!< ADC外设复位使能 */
#define RCC_APBPeriph_AWK_RST             (BIT14)   /*!< AWK外设复位使能 */
#define RCC_APBPeriph_CLKTRIM_RST         (BIT16)   /*!< CLKTRIM外设复位使能 */
#define RCC_APBPeriph_LVD_VC_OPA_RST      (BIT18)   /*!< LVD/VC/OPA外设复位使能 */
#define RCC_APBPeriph_BEEP_RST            (BIT19)   /*!< BEEP外设复位使能 */
#define RCC_APBPeriph_DEBUG_RST           (BIT20)   /*!< DEBUG外设复位使能 */
#define RCC_APBPeriph_CAN0_RST            (BIT21)   /*!< CAN0外设复位使能 */
#define RCC_AHBPeriph_GPIOA_RST           (BIT24)   /*!< GPIOA外设复位使能 */
#define RCC_AHBPeriph_GPIOB_RST           (BIT25)   /*!< GPIOB外设复位使能 */
#define RCC_AHBPeriph_GPIOC_RST           (BIT26)   /*!< GPIOC外设复位使能 */
#define RCC_AHBPeriph_GPIOD_RST           (BIT27)   /*!< GPIOD外设复位使能 */
#define RCC_AHBPeriph_CRC_RST             (BIT28)   /*!< CRC外设复位使能 */
#define RCC_AHBPeriph_GPIOE_RST           (BIT30)   /*!< GPIOE外设复位使能 */

#define IS_RCC_PERIPHRST(PERIPH)         (((PERIPH) == RCC_APBPeriph_EUART0_RST)|| \
										  ((PERIPH) == RCC_APBPeriph_EUART1_RST) || \
										  ((PERIPH) == RCC_APBPeriph_I2C0_RST)|| \
									      ((PERIPH) == RCC_APBPeriph_ASPI_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_LPTIM_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_BASETIM_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_SYSCON_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_SPI1_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_ETIMER_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_TIM2_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_WWDG_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_ADC_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_AWK_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_CLKTRIM_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_LVD_VC_OPA_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_BEEP_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_DEBUG_RST) || \
                                          ((PERIPH) == RCC_APBPeriph_CAN0_RST) || \
                                          ((PERIPH) == RCC_AHBPeriph_GPIOA_RST) || \
                                          ((PERIPH) == RCC_AHBPeriph_GPIOB_RST) || \
                                          ((PERIPH) == RCC_AHBPeriph_GPIOC_RST) || \
                                          ((PERIPH) == RCC_AHBPeriph_GPIOD_RST) || \
                                          ((PERIPH) == RCC_AHBPeriph_CRC_RST)  || \
									      ((PERIPH) == RCC_AHBPeriph_GPIOE_RST))


/** @defgroup RST MODEL
  * @{
  */
#define RCC_MCU_RESET       	  ((uint32_t)0x01)  /*!< MCU复位，重新加载选项字节数据 */
#define RCC_CPU_RESET       	  ((uint32_t)0x02)  /*!< CPU复位，无须加载选项字节数据 */
#define IS_RCC_RST(RSTMode)  	  (((RSTMode) == RCC_MCU_RESET) || ((RSTMode) == RCC_CPU_RESET))
                          	 

/** @defgroup GET RCC RESET Source FLAG 
  * @{
  */
#define RCC_FLAG_MCU_RST      	  (BIT0)     /*!< MCU复位标志    */
#define RCC_FLAG_CPU_RST      	  (BIT1)     /*!< CPU复位标志 */
#define RCC_FLAG_WWDG_RST     	  (BIT2)     /*!< WWDG复位标志 */
#define RCC_FLAG_IWDG_RST     	  (BIT3)     /*!< IWDG复位标志 */
#define RCC_FLAG_LVD_RST      	  (BIT4)     /*!< LVD复位标志 */
#define RCC_FLAG_POR_RST      	  (BIT5)     /*!< POR复位标志 */
#define RCC_FLAG_LOCKUP_RST   	  (BIT6)     /*!< Cortex-M0+ CPU Lockup复位标志 */
#define RCC_FLAG_PAD_RST      	  (BIT7)     /*!< 外部复位引脚复位标志 */
#define RCC_FLAG_SOFT_RST      	  (BIT8)     /*!< Cortex-M0+ CPU 软件复位标志 */
#define RCC_FLAG_CMU_LOC_RST      (BIT9)     /*!< 时钟监测失锁复位标志 */
#define RCC_FLAG_LOL_RST      	  (BIT10)    /*!< PLL失锁复位标志  */

#define IS_RCC_FLAG_RST(FLAG)       (((FLAG) == RCC_FLAG_MCU_RST)|| \
									 ((FLAG) == RCC_FLAG_CPU_RST) || \
									 ((FLAG) == RCC_FLAG_WWDG_RST)|| \
									 ((FLAG) == RCC_FLAG_IWDG_RST)|| \
									 ((FLAG) == RCC_FLAG_LVD_RST) || \
                                     ((FLAG) == RCC_FLAG_POR_RST) || \
                                     ((FLAG) == RCC_FLAG_LOCKUP_RST) || \
                                     ((FLAG) == RCC_FLAG_PAD_RST) || \
                                     ((FLAG) == RCC_FLAG_SOFT_RST) || \
                                     ((FLAG) == RCC_FLAG_CMU_LOC_RST) || \
									 ((FLAG) == RCC_FLAG_LOL_RST))


/** @defgroup GET RCC FLAG 
  * @{
  */
#define RCC_FLAG_HIRCRDY       ((uint32_t)(0x01UL << 12))     /*!< HIRC Ready */
#define RCC_FLAG_HXTRDY        ((uint32_t)(0x01UL << 6))      /*!< HXT Ready  */
#define RCC_FLAG_LIRCRDY       ((uint32_t)(0x01UL << 12))     /*!< LIRC Ready */
#define RCC_FLAG_LXTRDY        ((uint32_t)(0x01UL << 6))      /*!< LXT Ready  */
#define RCC_FLAG_PLL           ((uint32_t)(0x01UL << 22))     /*!< PLL Ready  */


#define RCC_HXT_DRIVER_LEVEL3    	 ((uint32_t)0x03)
#define RCC_HXT_DRIVER_LEVEL2    	 ((uint32_t)0x02) 
#define RCC_HXT_DRIVER_LEVEL1    	 ((uint32_t)0x01) 
#define RCC_HXT_DRIVER_LEVEL0    	 ((uint32_t)0x00) 

#define IS_RCC_HXT_DRIVER(LEVEL) 	 ((((LEVEL) & 0xFFFFFFF0) == 0x00) && ((LEVEL) >= 0x00))

#define RCC_HIRC_TRIM_MASK       	 ((uint32_t)0x00000FFF)

#define RCC_HIRC_TRIM_24MHZ          ((uint32_t)0x00000001)
#define RCC_HIRC_TRIM_22P12MHZ       ((uint32_t)0x00000002)
#define RCC_HIRC_TRIM_16MHZ          ((uint32_t)0x00000003)
#define RCC_HIRC_TRIM_8MHZ           ((uint32_t)0x00000004)
#define RCC_HIRC_TRIM_4MHZ           ((uint32_t)0x00000005)


#define RCC_SYSTEMTICKTIMER_STCALIB_MASK    ((uint32_t)0x01FFFFFF)
#define RCC_SYSTEMTICKTIMER_REFCORE_CLOCK   (BIT25)

/*------------------------------ HXT -----------------------------------------*/
#define RCC_HXT_BYP_ENABLE       (BIT5)   /*!< HXT内部振荡模块旁路模式， HXT从管脚OSCIN直接输入 */
#define RCC_HXT_PORT_OSC         (BIT6)   /*!< OSCIN/OSCOUT 管脚配置: HXT管脚模式 */
#define RCC_HXT_PORT_GPIO        (0)
#define RCC_HXT_ENABLE           (BIT1)

#define RCC_HXT_STARTUP_MASK     ((uint32_t)(0x03UL << 4))

/* HXT时钟稳定时间定义 -------------------------------------------------------*/
#define RCC_HXT_STARTUP_PERIOD_1024   		(0x00)       /*!< 1024个HXT周期 */
#define RCC_HXT_STARTUP_PERIOD_2048   		(0x01UL)     /*!< 2048个HXT周期 */
#define RCC_HXT_STARTUP_PERIOD_4096   		(0x02UL)     /*!< 4096个HXT周期 */
#define RCC_HXT_STARTUP_PERIOD_16384  		(0x03UL)     /*!< 16384个HXT周期 */

#define IS_RCC_HXT_STARTUP_PERIOD(PERIOD) 	(((PERIOD) == RCC_HXT_STARTUP_PERIOD_1024) || \
											 ((PERIOD) == RCC_HXT_STARTUP_PERIOD_2048) || \
											 ((PERIOD) == RCC_HXT_STARTUP_PERIOD_4096) || \
											 ((PERIOD) == RCC_HXT_STARTUP_PERIOD_16384))

/* HXT振幅控制定义 -----------------------------------------------------------*/
#define HXT_XSEL_WEAK             (0x00)     /*!< HXT振幅控制 -->弱 */
#define HXT_XSEL_WEAKER           (0x01UL)   /*!< HXT振幅控制 -->较弱 */
#define HXT_XSEL_STRONGER         (0x02UL)   /*!< HXT振幅控制 -->较强 */
#define HXT_XSEL_STRONG           (0x03UL)   /*!< HXT振幅控制 -->强 */

/* HXT偏置电流控制定义 -------------------------------------------------------*/
#define HXT_IBSEL_WEAK            (0x00)     /*!< HXT偏置电流控制 -->弱 */
#define HXT_IBSEL_WEAKER          (0x01UL)   /*!< HXT偏置电流控制 -->较弱 */
#define HXT_IBSEL_STRONGER        (0x02UL)   /*!< HXT偏置电流控制 -->较强 */
#define HXT_IBSEL_STRONG          (0x03UL)   /*!< HXT偏置电流控制 -->强 */

/* HXT常用时钟频率定义 -------------------------------------------------------*/
#define RCC_SEL_HXT_FREQ_8MHz      (8u)      /*!< HXT晶振时钟8MHz */
#define RCC_SEL_HXT_FREQ_12MHz     (12u)     /*!< HXT晶振时钟12MHz */
#define RCC_SEL_HXT_FREQ_16MHz     (16u)     /*!< HXT晶振时钟16MHz */
#define RCC_SEL_HXT_FREQ_24MHz     (24u)     /*!< HXT晶振时钟24MHz */
#define RCC_SEL_HXT_FREQ_32MHz     (32u)     /*!< HXT晶振时钟32MHz */

/*------------------------------ LIRC ----------------------------------------*/
#define RCC_LIRC_TRIM_MASK       	  ((uint32_t)0x000001FF)
#define RCC_LIRC_TRIM_32768HZ         ((uint32_t)0x00000001)
#define RCC_LIRC_TRIM_38400HZ         ((uint32_t)0x00000002)
#define RCC_LIRC_STARTUP_MASK    	  ((uint32_t)(0x03UL << 10))

/* LIRC时钟稳定时间定义 ------------------------------------------------------*/
#define RCC_LIRC_STARTUP_PERIOD_4     		(0x00UL)   /*!< 4个LIRC周期   */
#define RCC_LIRC_STARTUP_PERIOD_16    		(0x01UL)   /*!< 16个LIRC周期  */
#define RCC_LIRC_STARTUP_PERIOD_64    		(0x02UL)   /*!< 64个LIRC周期  */
#define RCC_LIRC_STARTUP_PERIOD_256   		(0x03UL)   /*!< 256个LIRC周期 */

#define IS_RCC_LIRC_STARTUP_PERIOD(PERIOD) 	(((PERIOD) == RCC_LIRC_STARTUP_PERIOD_4) || \
											 ((PERIOD) == RCC_LIRC_STARTUP_PERIOD_16) || \
											 ((PERIOD) == RCC_LIRC_STARTUP_PERIOD_64) || \
											 ((PERIOD) == RCC_LIRC_STARTUP_PERIOD_256))


/* Exported functions --------------------------------------------------------*/
void RCC_DeInit(void);      
ErrorStatus RCC_WaitForHIRCStable(RCC_TypeDef *RCCx);   
ErrorStatus RCC_WaitForHXTStable(RCC_TypeDef *RCCx, uint32_t PERIOD); 
ErrorStatus RCC_WaitForLIRCStable(RCC_TypeDef *RCCx, uint32_t PERIOD); 
void RCC_HXT_InitStruct(HXT_InitTypeDef * HXT_InitStruct);  
void RCC_HXT_Init(RCC_TypeDef *RCCx, HXT_InitTypeDef *HXT_InitStruct); 
void RCC_SetHXTPort(RCC_TypeDef *RCCx, FunctionalState NewState);  
void RCC_SetM0IRQLatency(RCC_TypeDef *RCCx, uint32_t IRQLATENCY); 
void RCC_SystemTickTimerConfig(RCC_TypeDef *RCCx, uint8_t SKEW, uint32_t TICKTIMERSTCALIB);  
void RCC_SetSysTickRefClockCmd(RCC_TypeDef *RCCx, FunctionalState NewState);  
void RCC_ClkCmd(RCC_TypeDef *RCCx, uint32_t RCC_CLKType, FunctionalState NewState); 
void RCC_SelSysclk(RCC_TypeDef *RCCx, uint32_t RCC_SYSCLKSource); 
void RCC_ClkOutputSourceConfig(RCC_TypeDef *RCCx, uint32_t RCC_SYSCLKOutSource);  
void RCC_ClkOutputCmd(RCC_TypeDef *RCCx, FunctionalState NewState);  
void RCC_ClkFclkDiv(RCC_TypeDef *RCCx, uint8_t RCC_FCLK_O_CLK_DIV);  
uint8_t RCC_GetSysclkSource(RCC_TypeDef *RCCx);  
void RCC_SetHclkDiv(RCC_TypeDef *RCCx, uint8_t RCC_SYSCLK_DIV); 
void RCC_SetPclkDiv(RCC_TypeDef *RCCx, uint8_t RCC_HCLK_DIV); 
void RCC_AHBPeriphClockCmd(RCC_TypeDef *RCCx, uint32_t RCC_AHBPeriph, FunctionalState NewState);  
void RCC_APBPeriphClockCmd(RCC_TypeDef *RCCx, uint32_t RCC_APBPeriph, FunctionalState NewState);  
void RCC_PeriphResetCmd(RCC_TypeDef *RCCx, uint32_t RCC_PeriphRst, FunctionalState NewState);  
void RCC_ResetCmd(RCC_TypeDef *RCCx, uint32_t RCC_RSTMode, FunctionalState NewState);  
FlagStatus RCC_GetResetFlag(RCC_TypeDef *RCCx, uint32_t RCC_RST_FLAG);   
void RCC_Config_Swd_GPIO(RCC_TypeDef *RCCx, FunctionalState NewState);  
void RCC_PLL_Set_Stable_Value(RCC_TypeDef *RCCx, uint16_t PLL_Stable_Value); 
ErrorStatus RCC_HXT_Cmd(RCC_TypeDef *RCCx, FunctionalState NewState); 
ErrorStatus RCC_SysClk_SwitchTo_PLL(RCC_TypeDef *RCCx, uint8_t PLL_Source_Sel, uint8_t PLL_Freq);  
ErrorStatus RCC_SysClk_SwitchTo_HXT(RCC_TypeDef *RCCx, uint8_t HXT_Freq);

#ifdef __cplusplus
}
#endif

#endif   /* __CPS32K21X_RCC_H__ */

