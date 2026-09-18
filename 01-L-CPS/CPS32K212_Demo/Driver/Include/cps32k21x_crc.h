/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPS32K21X_CRC_H__  
#define __CPS32K21X_CRC_H__


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_public.h"
#include "cps32k21x_rcc.h"


/** 
  * @brief  CRC Init structure definition
  * @note   This structure is used with CRC
  */
typedef struct
{
    uint32_t MSBLSB_Sel;       /*!<MSB/LSB选择 */

    uint32_t CRC_Poly_Sel;     /*!<CRC多项式选择 */

    uint32_t Monitor_En;       /*!<CRC监测使能 */

    uint32_t Monitor_RW;       /*!<CRC监测读取/写入选择 */ 
    
    uint32_t MonitorSource;    /*!<CRC监测源 */ 
} CRC_InitTypeDef;  

/*----------------------------- MSBLSB选择 -----------------------------------*/
#define MSBLSB_SELECT_MSB      (BIT30)
#define MSBLSB_SELECT_LSB      (0)


/*--------------------------- CRC多项式选择 ----------------------------------*/
#define CRC_POLY_SEL_Mask         ((uint32_t)(0x07UL << 24))
#define CRC_POLY_SEL_None         (0)                         /*!<CRC多项式选择：未执行任何计算 */
#define CRC_POLY_SEL_CRC8         ((uint32_t)(0x01UL << 24))  /*!<CRC多项式选择：CRC-8 */ 
#define CRC_POLY_SEL_CRC16        ((uint32_t)(0x02UL << 24))  /*!<CRC多项式选择：CRC16 */ 
#define CRC_POLY_SEL_CRC_CCITT    ((uint32_t)(0x03UL << 24))  /*!<CRC多项式选择：CRC-CCITT */ 
#define CRC_POLY_SEL_CRC32        ((uint32_t)(0x04UL << 24))  /*!<CRC多项式选择：CRC-32 */ 
#define CRC_POLY_SEL_CRC32C       ((uint32_t)(0x05UL << 24))  /*!<CRC多项式选择：CRC-32C */ 


/*---------------------------- CRC监测使能 -----------------------------------*/
#define CRC_MONITOR_ENABLE    (BIT23)   /*!<CRC监测使能 */ 
#define CRC_MONITOR_DISABLE   (0)       /*!<CRC监测禁止 */ 


/*------------------------ CRC监测读取/写入选择 ------------------------------*/
#define CRC_MONITOR_WRITE     (BIT22)   /*!<CRC监测写入操作 */ 
#define CRC_MONITOR_READ      (0)       /*!<CRC监测读取操作 */ 


/*---------------------------- CRC监测源 -------------------------------------*/
#define CRC_MONITOR_SOURCE_ROM      (BIT21)   /*!<CRC监测源选择ROM */ 
#define CRC_MONITOR_SOURCE_PERIPH   (0)       /*!<CRC监测源选择外设 */ 


/* Exported functions --------------------------------------------------------*/  
void CRC_DeInit(void);
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct);
void CRC_Init(CRC_TypeDef* CRCx, CRC_InitTypeDef* CRC_InitStruct);
void CRC_DATAOUT_Clear(CRC_TypeDef* CRCx);
uint8_t CRC_Poly_CRC8_Calculate(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen);
ErrorStatus CRC_Poly_CRC8_Check(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint8_t crc_for_check);
uint16_t CRC_Poly_CRC16_Calculate(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen);
ErrorStatus CRC_Poly_CRC16_Check(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint16_t crc_for_check);
uint16_t CRC_Poly_CRC16_CCIT_Calculate(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen);
ErrorStatus CRC_Poly_CRC16_CCIT_Check(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint16_t crc_for_check);
uint32_t CRC_Poly_CRC32_Calculate_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen);
ErrorStatus CRC_Poly_CRC32_Check_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check);
uint32_t CRC_Poly_CRC32_Calculate_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen);
ErrorStatus CRC_Poly_CRC32_Check_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check);
uint32_t CRC_Poly_CRC32C_Calculate_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen);
ErrorStatus CRC_Poly_CRC32C_Check_Data8(CRC_TypeDef* CRCx, uint8_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check);
uint32_t CRC_Poly_CRC32C_Calculate_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen);
ErrorStatus CRC_Poly_CRC32C_Check_Data32(CRC_TypeDef* CRCx, uint32_t* pBuffer, uint16_t DataLen, uint32_t crc_for_check);
void CRC_Poly_Switch_Config(CRC_TypeDef* CRCx, uint32_t Select_Poly);
void CRC_Monitor_Cmd(CRC_TypeDef* CRCx, FunctionalState NewState);
void CRC_Monitor_RW_Config(CRC_TypeDef* CRCx, uint32_t RWSel);
void CRC_Monitor_Source_Config(CRC_TypeDef* CRCx, uint32_t MonitorSrc);
void CRC_MonitorAddress_Load(CRC_TypeDef* CRCx, uint32_t periphAddr);


#ifdef __cplusplus
}
#endif


#endif /* __CPS32K21X_CRC_H__ */

