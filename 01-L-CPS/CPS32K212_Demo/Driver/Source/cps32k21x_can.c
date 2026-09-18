#include "cps32k21x_can.h"


/* =======================  Variables  ====================================== */
static const CAN_InfoType_t s_canInfo[CAN_INSTANCE_MAX] =
{
    {CAN0_IRQn, PCLKEN_CAN0, PERIPRST_CAN0},
};

static CAN_DeviceType_t s_canDevice[CAN_INSTANCE_MAX] = {0};


/**
  * @brief  Config CANx peripheral reset state
  * @param  CANx: selects the CANx peripheral
  * 	This parameter can be one of the following values: CAN0.
  * @param  NewState: new state of CANx peripheral reset
  *     This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void CAN_SetReset(CAN_TypeDef* CANx, FunctionalState NewState)
{
    MODIFY_REG32(CANx->CTRL0, CAN_CTRL0_RESET_Mask, CAN_CTRL0_RESET_Pos, NewState);
}

/*!
 * @brief Set transceiver standby state
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] state: enable state
                - ENDBLE
                - DISDBLE
 * @return 0: no error, 1: standby error
 */
uint8_t CAN_SetStandby(CAN_TypeDef* CANx, FunctionalState state)
{
    int32_t err = 0;

    if (state)
    {
        /*!< If there is any transmission, can not entry standby mode */
        if (!(CANx->CTRL0 & (CAN_CTRL0_TPE_Mask | CAN_CTRL0_TSONE_Mask | CAN_CTRL0_TSALL_Mask)))
        {
            CANx->CTRL0 |= CAN_CTRL0_STBY_Mask;
        }
        else
        {
            err = 1;
        }
    }
    else
    {
        CANx->CTRL0 &= ~CAN_CTRL0_STBY_Mask;
    }
    
    return err;
}

/** 
  * @brief  返回接收缓冲区状态
  * @param  CANx: Select the CANx peripheral.
  *         This parameter can be one of the following values: CAN0     
  * @retval 接收缓冲区状态
  */
int32_t CAN_IsMsgInReceiveBuf(CAN_TypeDef* CANx)
{
    return (READ_BIT32(CANx->CTRL0, CAN_CTRL0_RSTAT_Mask) >> CAN_CTRL0_RSTAT_Pos);
}

/*!
 * @brief CANx发送报文开始
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @param[in] amount: Transmit Secondary ALL or ONE frames
                - CAN_TRANSMIT_ONE
                - CAN_TRANSMIT_ALL
 * @return 0 : success 1: error
 */
uint8_t CAN_StartTransmission(CAN_TypeDef* CANx, CAN_TransmitBufferType type, CAN_TransmitAmountType amount)
{
    /*!< 待机时不能发送CAN报文消息 */
    if (CANx->CTRL0 & CAN_CTRL0_STBY_Mask)
    {
        return 1;
    }

    if (CAN_TRANSMIT_PRIMARY == type)   // 主发送缓冲区
    {
        CANx->CTRL0 |= CAN_CTRL0_TPE_Mask;   // 发送高优先级PTB中消息
    }
    else
    {
        if (CAN_TRANSMIT_ONE == amount)
        {
            CANx->CTRL0 |= CAN_CTRL0_TSONE_Mask;    /*!< 次发送一帧使能，即只发送一帧报文 */
        }
        else
        {
            CANx->CTRL0 |= CAN_CTRL0_TSALL_Mask;    /*!< 次发送所有帧使能，即送所有报文 */
        }
    }

    return 0;
}

/*!
 * @brief CAN Abort transmission
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @return none
 */
void CAN_AbortTransmission(CAN_TypeDef* CANx, CAN_TransmitBufferType type)
{
    if (CAN_TRANSMIT_PRIMARY == type)
    {
        CANx->CTRL0 |= CAN_CTRL0_TPA_Mask;
    }
    else
    {
        CANx->CTRL0 |= CAN_CTRL0_TSA_Mask;
    }
}

/*!
 * @brief Check transmission is busy
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @return Transmit busy flag (0: not busy, 1: busy)
 */
uint8_t CAN_IsTransmitBusy(CAN_TypeDef* CANx, CAN_TransmitBufferType type)
{
    if (CAN_TRANSMIT_PRIMARY == type)
    {
        /*!< Transmitting is not successful */
        return (1 == ((CANx->CTRL0 & CAN_CTRL0_TPE_Mask) >> CAN_CTRL0_TPE_Pos));
    }
    else
    {
        /*!< Transmission buffers are full */
        return (CAN_TRANSMIT_BUFFER_FULL == ((CANx->CTRL0 & CAN_CTRL0_TSSTAT_Mask) >> CAN_CTRL0_TSSTAT_Pos));
    }
}

/*!
 * @brief Check whether is transmitting
 *
 * @param[in] CANx: CAN module
 *              - CAN0
 * @param[in] type: CAN transmit type
 *              - CAN_TRANSMIT_PRIMARY
 *              - CAN_TRANSMIT_SECONDARY
 * @return Transmitting status (0: not transmitting, 1: transmitting)
 */
uint8_t CAN_IsTransmitting(CAN_TypeDef* CANx, CAN_TransmitBufferType type)
{
    if (CAN_TRANSMIT_PRIMARY == type)   // 主发送缓冲区
    {
        return ((CANx->CTRL0 & CAN_CTRL0_TPE_Mask) >> CAN_CTRL0_TPE_Pos);
    }
    else   // 从送缓冲区
    {
        return ((CANx->CTRL0 & (CAN_CTRL0_TSALL_Mask | CAN_CTRL0_TSONE_Mask)) != 0);
    }
}

/*!
 * @brief Check transmission is idle
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @return Transmit idle flag (0: busy, 1: idle)
 */
uint8_t CAN_IsTransmitIdle(CAN_TypeDef* CANx, CAN_TransmitBufferType type)
{
    if (CAN_TRANSMIT_PRIMARY == type)
    {
        return (0 == (CANx->CTRL0 & CAN_CTRL0_TPE_Mask));        /*!< PTB is empty */  
    }
    else
    {
        return (0 == (CANx->CTRL0 & CAN_CTRL0_TSSTAT_Mask));     /*!< STB are empty */
    }
}

/*!
 * @brief Check bus off status
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return Bus off status
 */
int32_t CAN_IsBusoff(CAN_TypeDef* CANx)
{
    return (CANx->CTRL0 & CAN_CTRL0_BUSOFF_Mask);
}

/*!
 * @brief Set CAN interrupt enable
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] intEn: CAN interrupt enable
 * @return none
 */
void CAN_SetIntEnable(CAN_TypeDef* CANx, uint32_t intEn)
{
    MODIFY_REG32(CANx->CTRL1, CAN_IE_ALL_ENABLE_Mask, 0, intEn);
}

/*!
 * @brief Set CAN error warning limit
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] ewl: error warning limit
            - (0-15)
 * @return none
 */
void CAN_SetEwl(CAN_TypeDef* CANx, uint8_t ewl)
{
    MODIFY_REG32(CANx->CTRL1, CAN_CTRL1_EWL_Mask, CAN_CTRL1_EWL_Pos, ewl);
}

/*!
 * @brief Set CAN almost full warning limit
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] afwl: almost full warning limit
 * @return none
 */
void CAN_SetAfwl(CAN_TypeDef* CANx, uint8_t afwl)
{
    MODIFY_REG32(CANx->CTRL1, CAN_CTRL1_AFWL_Mask, CAN_CTRL1_AFWL_Pos, afwl);
}

/*!
 * @brief Get CAN transmission time stamp
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return transmission time stamp
 */
uint32_t CAN_GetTts(CAN_TypeDef* CANx)
{
    return (CANx->TTS0);
}

/*!
 * @brief Enable CAN transmit PTB single shot mode
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] state: enable state
                - ENDBLE
                - DISDBLE
 * @return none
 */
void CAN_SetTpss(CAN_TypeDef* CANx, FunctionalState state)
{
    MODIFY_REG32(CANx->CTRL0, CAN_CTRL0_TPSS_Mask, CAN_CTRL0_TPSS_Pos, state);
}

/*!
 * @brief  Enable CAN transmit STB single shot mode
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] state: enable state
                - ENDBLE
                - DISDBLE
 * @return none
 */
void CAN_SetTsss(CAN_TypeDef* CANx, FunctionalState state)
{
    MODIFY_REG32(CANx->CTRL0, CAN_CTRL0_TSSS_Mask, CAN_CTRL0_TSSS_Pos, state);
}

/*!
 * @brief get CAN Transmit secondary status
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return Transmit secondary status
 */
uint32_t CAN_GetTSStat(CAN_TypeDef* CANx)
{
    return ((CANx->CTRL0 & CAN_CTRL0_TSSTAT_Mask) >> CAN_CTRL0_TSSTAT_Pos);
}

/*!
 * @brief get CAN Receiver status
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return Receiver status
 */
uint32_t CAN_GetRStat(CAN_TypeDef* CANx)
{
    return ((CANx->CTRL0 & CAN_CTRL0_RSTAT_Mask) >> CAN_CTRL0_RSTAT_Pos);
}

/*!
 * @brief get CAN Reception buffer overflow
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return Reception buffer overflow
 */
uint32_t CAN_GetRov(CAN_TypeDef* CANx)
{
    return ((CANx->CTRL0 & CAN_CTRL0_ROV_Mask) >> CAN_CTRL0_ROV_Pos);
}


/** 
  * @brief  返回CANx错误类型
  * @param  CANx: Select the CANx peripheral.
  *         This parameter can be one of the following values: CAN0     
  * @retval Kind of error
  */
uint32_t CAN_GetKoer(CAN_TypeDef* CANx)
{
    return ((CANx->ERRINFO & CAN_ERRINFO_KOER_Mask) >> CAN_ERRINFO_KOER_Pos);
}

/*!
 * @brief Set CAN FD ISO state
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] state: enable state
                - ENDBLE
                - DISDBLE
 * @return none
 */
void CAN_SetFdIso(CAN_TypeDef* CANx, FunctionalState state)
{
    MODIFY_REG32(CANx->CTRL0, CAN_CTRL0_FDISO_Mask, CAN_CTRL0_FDISO_Pos, state);
}

/*!
 * @brief Set operation mode
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] tsMode: Transmit secondary: operation mode
                - CAN_TSMODE_FIFO
                - CAN_TSMODE_PRIORITY
 * @return none
 */
void CAN_SetTSMode(CAN_TypeDef* CANx, CAN_TransmitModeType tsMode)
{
    MODIFY_REG32(CANx->CTRL0, CAN_CTRL0_TSMODE_Mask, CAN_CTRL0_TSMODE_Pos, tsMode);
}

/*!
 * @brief Set CAN Reception buffer overflow
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] rom: 1: new message will not be stored, 0: The oldest message will be overwrite 
                - CAN_RECV_OVER_WRITE
                - CAN_RECV_DISCARD
 * @return none
 */
void CAN_SetRom(CAN_TypeDef* CANx, CAN_OverflowModeType rom)
{
    MODIFY_REG32(CANx->CTRL0, CAN_CTRL0_ROM_Mask, CAN_CTRL0_ROM_Pos, rom);
}

/*!
 * @brief Enable CAN Self-Acknowledge when LBME = 1
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] state: enable state
                - ENDBLE
                - DISDBLE
 * @return none
 */
void CAN_SetSack(CAN_TypeDef* CANx, FunctionalState state)
{
    MODIFY_REG32(CANx->CTRL0, CAN_CTRL0_SACK_Mask, CAN_CTRL0_SACK_Pos, state);
}

/*!
 * @brief Enable CAN TDC
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] state: enable state
                - ENDBLE
                - DISDBLE
 * @return none
 */
void CAN_SetTdc(CAN_TypeDef* CANx, FunctionalState state)
{
    MODIFY_REG32(CANx->ERRINFO, CAN_ERRINFO_TDCEN_Mask, CAN_ERRINFO_TDCEN_Pos, state);
}

/*!
 * @brief Set CAN error warning limit
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] offset: SSP offset
 * @return none
 */
void CAN_SetSspOffet(CAN_TypeDef* CANx, uint8_t offset)
{
    MODIFY_REG32(CANx->ERRINFO, CAN_ERRINFO_SSPOFF_Mask, CAN_ERRINFO_SSPOFF_Pos, offset & 0x7F);
}

/*!
 * @brief Set CAN TIME-stamping Position
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] pos: TIME-stamping Position
                - CAN_TIME_STAMP_SOF
                - CAN_TIME_STAMP_EOF
 * @return none
 */
void CAN_SetTimePosition(CAN_TypeDef* CANx, CAN_TimeStampPosType pos)
{
    MODIFY_REG32(CANx->ACFCTRL, CAN_ACFCTRL_TIMEPOS_Mask, CAN_ACFCTRL_TIMEPOS_Pos, pos);
}

/*!
 * @brief Enable CAN TIME-stamping
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] state: enable state
                - ENDBLE
                - DISDBLE
 * @return none
 */
void CAN_EnableTime(CAN_TypeDef* CANx, FunctionalState state)
{
    MODIFY_REG32(CANx->ACFCTRL, CAN_ACFCTRL_TIMEEN_Mask, CAN_ACFCTRL_TIMEEN_Pos, state);
}

/*!
 * @brief Set CAN acceptance filter enable
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] index: filter id
 * @param[in] state: 1:enable filter, 0: disable filter
                - DISABLE
                - ENABLE
 * @return none
 */
void CAN_SetAcfEn(CAN_TypeDef* CANx, uint8_t index, FunctionalState state)
{
    if (state)
    {
        CANx->ACFCTRL |=  ((0x01UL << index) << CAN_ACFCTRL_ACFEN_Pos);
    }
    else
    {
        CANx->ACFCTRL &= ~((0x01UL << index) << CAN_ACFCTRL_ACFEN_Pos);
    }
}

/*!
 * @brief Set CAN acceptance filter index
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] index: filter id
 * @return none
 */
void CAN_SetAcfIndex(CAN_TypeDef* CANx, uint8_t index)
{
    MODIFY_REG32(CANx->ACFCTRL, CAN_ACFCTRL_ACFADR_Mask, CAN_ACFCTRL_ACFADR_Pos, index);
}

/*!
 * @brief Set CAN Filter data code
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] code: Filter data code
 * @return none
 */
void CAN_SetAcfCode(CAN_TypeDef* CANx, uint32_t code)
{
    CANx->ACFCTRL &= (~CAN_ACFCTRL_SELMASK_Mask);
    CANx->ACF = (code & CAN_ACF_ACODE_Mask);
}

/*!
 * @brief Set CAN Filter data mask + AIDE + AIDEE
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] mask: Filter data mask + AIDE + AIDEE
 * @return none
 */
void CAN_SetAcfMask(CAN_TypeDef* CANx, uint32_t mask)
{
    CANx->ACFCTRL |= CAN_ACFCTRL_SELMASK_Mask;
    CANx->ACF = mask & (CAN_ACF_ACODE_Mask | CAN_ACF_AIDE_Mask | CAN_ACF_AIDEE_Mask);
}

/*!
 * @brief Get CAN version
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return CAN version
 */
uint16_t CAN_GetVersion(CAN_TypeDef* CANx)
{
    return (CANx->VERSION & CAN_VERSION_VERSION_Mask);
}

/*!
 * @brief get receive error count
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return receive error count
 */
uint8_t CAN_GetRECnt(CAN_TypeDef* CANx)
{
    return ((CANx->ERRINFO & CAN_ERRINFO_RECNT_Mask) >> CAN_ERRINFO_RECNT_Pos);
}

/*!
 * @brief get transmit error count
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return transmit error count
 */
uint8_t CAN_GetTECnt(CAN_TypeDef* CANx)
{
    return ((CANx->ERRINFO & CAN_ERRINFO_TECNT_Mask) >> CAN_ERRINFO_TECNT_Pos);
}

/*!
 * @brief Set call back function
 *
 * @param[in] CANx: CAN type pointer
 * @param[in] callbackFunc: Event call back function
 */
void CAN_SetCallBack(CAN_TypeDef* CANx, DeviceCallback_Type callbackFunc)
{
    uint8_t instance = 0;

    instance = CAN_INDEX(CANx);

    if (callbackFunc)
    {
        s_canDevice[instance].callback = callbackFunc;
    }
}

/** 
  * @brief  CANx中断事件处理，在CANx中断服务程序中调用此函数
  * @param  CANx: Select the CANx peripheral.
  *         This parameter can be one of the following values: CAN0     
  * @retval None
  */
void CAN_HandleEvent(CAN_TypeDef* CANx)
{
    uint8_t instance = CAN_INDEX(CANx);
    CAN_DeviceType_t *device = &s_canDevice[instance];

    device->interruptFlag = (CANx->CTRL1 & CAN_IRQ_FLAG_Mask);   // 获取CANx中断标志
    CANx->CTRL1 |= device->interruptFlag;  // 清除中断标志

    if (device->callback)
    {
        device->callback(CANx, device->interruptFlag, (uint32_t)CAN_GetKoer(CANx));  // 调用回调函数
    }
}

/*!
* @brief CAN interrupt handle function
 *
 * @param[in] none
 * @return none
 */
void CAN0_IRQHandler(void)
{
    CAN_HandleEvent(CAN0);
}

/*!
 * @brief Set CAN bitrate
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] config: Bitrate config
 * @param[in] dataBitrate: Is data bit rate  0: is not data bit rate, 1: is data bitrate
 * @return none
 */
static void CAN_SetBitrate(CAN_TypeDef* CANx, const CAN_BitRateConfigType *config, uint8_t dataBitrate)
{
    if (!dataBitrate)
    {
        CANx->SBITRATE = (config->PRESC << CAN_BITRATE_PRESC_Pos) + (config->SJW << CAN_BITRATE_SJW_Pos) + (config->SEG_2 << CAN_BITRATE_SEG_2_Pos) + config->SEG_1;
    }
    else
    {
        CANx->FBITRATE = (config->PRESC << CAN_BITRATE_PRESC_Pos) + (config->SJW << CAN_BITRATE_SJW_Pos) + (config->SEG_2 << CAN_BITRATE_SEG_2_Pos) + config->SEG_1;
    }
}

/*!
 * @brief Get CAN error flag
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return error flag
 */
int32_t CAN_GetError(CAN_TypeDef* CANx)
{
    int32_t errorFlag = 0;
    uint8_t instance = 0;

    instance = CAN_INDEX(CANx);

    if (s_canDevice[instance].interruptEn)
    {
        errorFlag = s_canDevice[instance].interruptFlag;
    }
    else
    {
        errorFlag = (CANx->CTRL1 & (CAN_CTRL1_EIF_Mask | CAN_CTRL1_ROIF_Mask | CAN_CTRL1_RFIF_Mask | \
                                    CAN_CTRL1_RAFIF_Mask | CAN_CTRL1_AIF_Mask | CAN_CTRL1_EPIF_Mask | CAN_CTRL1_ALIF_Mask | CAN_CTRL1_BEIF_Mask));
    }

    return errorFlag;
}


/*!
* @brief set the CAN time clock divider (for time stamp)
*
* @param[in] canIndex: 0:can0
* @param[in] divider: CAN time clock divider, value can be
*                - 2'h0 : divider by 8
*                - 2'h1 : divider by 16
*                - 2'h2 : divider by 24
*                - 2'h3 : divider by 48
* @return none
*/
void CAN_SetTimeStampDivider(uint8_t canIndex, CAN_TimeClockDividerType divider)
{
    (void)canIndex;
    MODIFY_REG32(RCC->CANCR, RCC_CAN0_TIMCLK_DIV_Mask, RCC_CAN0_TIMCLK_DIV_Pos, (uint32_t)divider);
}

/*!
 * @brief Init CANx (GPIO, clock, bitrate, filter and interrupt setting)
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] config: CAN config
 * @return none
 */
void CAN_Init(CAN_TypeDef* CANx, CAN_ConfigType *config)
{
    uint8_t i = 0;
    
    CAN_FilterControlType *filterList = 0;
    uint8_t instance = 0;

    instance = CAN_INDEX(CANx);

    s_canDevice[instance].interruptFlag = 0;

    /* CAN and clock enable */
    if (CAN_CLKSRC_EXTERNAL_OSC == config->clockSrc)
    {
        RCC->CANCR |= (uint32_t)(0x01UL << 7);   // CAN时钟选择：外部振荡器时钟
    }
    else
    {
        RCC->CANCR &= (uint32_t)(~(0x01UL << 7));  // CAN时钟选择：AHB分频时钟
    }

    RCC->PCLKEN |= (uint32_t)(0x01UL << s_canInfo[instance].clock);   // 使能CAN0外设时钟

    /* Reset CAN */
    CAN_SetReset(CANx, ENABLE);
    
    /* Set bitrate */
    CAN_SetBitrate(CANx, config->normalBitrate, 0);
    if (config->fdModeEn)
    {
        CAN_SetFdIso(CANx, config->fdIsoEn);
        CAN_SetBitrate(CANx, config->dataBitrate, 1);

        if (config->tdcEnable)
        {
            CAN_SetTdc(CANx, config->tdcEnable);
            CAN_SetSspOffet(CANx, config->sspOffset);
        }
    }

    /* Set filters(user define or use sample setting) */
    if (config->filterList)
    {
        filterList = (CAN_FilterControlType *)config->filterList;
        for (i = 0; i < config->filterNum; i++)
        {
            if (0 != CAN_SetFilter(CANx, filterList[i].index, filterList[i].code, filterList[i].mask, filterList[i].enable))
            {

            }
        }
    }

    /* Start synchronize */
    CAN_SetReset(CANx, DISABLE);

    /* Set work mode */
    if (CAN_MODE_MONITOR == config->canMode)   // 工作模式：监听模式
    {
        CANx->CTRL0 |= CAN_CTRL0_LOM_Mask;
    }
    else if (CAN_MODE_LOOPBACK_INTERNAL == config->canMode)  // 工作模式：内部环回模式
    {
        CANx->CTRL0 |= CAN_CTRL0_LBMI_Mask;
    }
    else if (CAN_MODE_LOOPBACK_EXTERNAL == config->canMode)  // 工作模式：外部环回模式
    {
        CANx->CTRL0 |= CAN_CTRL0_LBME_Mask;
        CAN_SetSack(CANx, config->selfAckEn);
    }
    else
    {
    }

    CAN_SetAfwl(CANx, CAN_RECEIVE_FIFO_COUNT - 1);
    CAN_SetEwl(CANx, config->errorWarningLimit);

    CAN_SetTpss(CANx, config->tpss);
    CAN_SetTsss(CANx, config->tsss);

    CAN_SetTSMode(CANx, config->tsMode); /* 0->FIFO mode 1->priority decision mode */
    CAN_SetRom(CANx, config->rom); /* 0->overwrite the oldest message 1->discard new message */

    s_canDevice[instance].tsAmount = config->tsAmount;
    s_canDevice[instance].callback = config->callback;
    if (config->timeStampEn)
    {
        CAN_SetTimeStampDivider(instance, config->timeStampClk);
        s_canDevice[instance].timeStampEn = config->timeStampEn;
        CAN_SetTimePosition(CANx, config->timeStampPos);
        CAN_EnableTime(CANx, ENABLE);
    }

    CAN_SetIntEnable(CANx, config->interruptMask);
    /* Enable interrupt */
    if (config->interruptEn)
    {
        s_canDevice[instance].interruptEn = config->interruptEn;  
        NVIC_EnableIRQ(s_canInfo[instance].irq);  // 使能CAN0外设的NVIC中断
    }
}

/*!
 * @brief Uninitialize CANx
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return none
 */
void CAN_DeInit(CAN_TypeDef* CANx)
{
    uint8_t instance = 0;

    instance = CAN_INDEX(CANx);
    CAN_SetReset(CANx, ENABLE);
    
    /* CAN and clock disable */
    NVIC_DisableIRQ(s_canInfo[instance].irq);
    s_canDevice[instance].callback = 0;
    NVIC_ClearPendingIRQ(s_canInfo[instance].irq);
    RCC->PCLKEN &= (uint32_t)(~(0x01UL << s_canInfo[instance].clock));   // CAN0时钟关闭
    
    /* Enable CAN0 reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_CAN0_RST, ENABLE);
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    /* Release CAN0 from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_CAN0_RST, DISABLE);
}

/*!
 * @brief Wait transmit primary done, otherwise timeout
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return Transmit flag (0: done, 1: timeout)
 */
int32_t WaitTransmitPrimaryDone(CAN_TypeDef* CANx)
{
    uint32_t i = 0;
    int32_t ret = 0;

    do
    {
        if (CANx->CTRL1 & CAN_CTRL1_TPIF_Mask)
        {
            CANx->CTRL1 |= CAN_CTRL1_TPIF_Mask;
            break;
        }
    } while (MAX_CAN_WAIT_TIMES > i++);

    if (MAX_CAN_WAIT_TIMES <= i)
    {
        ret = 1;
    }

    return ret;
}

/*!
 * @brief Wait transmit secondary done, otherwise timeout
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @return Transmit flag (0: done, 1: timeout)
 */
int32_t WaitTransmitSecondaryDone(CAN_TypeDef* CANx)
{
    uint32_t i = 0;
    int32_t ret = 0;

    do
    {
        if (CANx->CTRL1 & CAN_CTRL1_TSIF_Mask)
        {
            CANx->CTRL1 |= CAN_CTRL1_TSIF_Mask;
            break;
        }
    } while (MAX_CAN_WAIT_TIMES > i++);

    if (MAX_CAN_WAIT_TIMES <= i)
    {
        ret = 1;
    }

    return ret;
}

/*!
 * @brief Wait transmit done
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @return Transmit flag (0: done, 1: timeout)
 */
int32_t CAN_WaitTransmissionDone(CAN_TypeDef* CANx, CAN_TransmitBufferType type)
{
    int32_t ret = 0;
    uint8_t instance = 0;

    instance = CAN_INDEX(CANx);

    if (s_canDevice[instance].interruptEn)
    {
        /* clear flag in IRQ */
    }
    else if (type == CAN_TRANSMIT_PRIMARY)
    {
        ret = WaitTransmitPrimaryDone(CANx);
    }
    else
    {
        ret = WaitTransmitSecondaryDone(CANx);
    }

    return ret;
}

/*!
 * @brief Wait for transmitting done in primary mode; or transmission buffer not full in secondary mode, otherwise timeout
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @return Transmit idle flag (0: idle, 1: timeout)
 */
uint8_t CAN_WaitTransmissionIdle(CAN_TypeDef* CANx, CAN_TransmitBufferType type)
{
    uint32_t i = 0;
    uint8_t ret = 0;

    do
    {
        if (!CAN_IsTransmitting(CANx, type))
        {
            break;
        }
    } while (MAX_CAN_WAIT_TIMES > i++);

    if (MAX_CAN_WAIT_TIMES <= i)
    {
        ret = 1;
    }

    return ret;
}

/*!
 * @brief Get payload size
 *
 * @param[in] dlcValue: DLC value
 * @return ret: payload size
 */
uint8_t CAN_GetPayloadSize(uint8_t dlcValue)
{
    uint8_t ret = 0U;

    if (8U >= dlcValue)
    {
        ret = dlcValue;
    }
    else
    {
        switch (dlcValue)
        {
            case CAN_DLC_12_BYTES:   ret = 12U;   break;
            case CAN_DLC_16_BYTES:   ret = 16U;   break;
            case CAN_DLC_20_BYTES:   ret = 20U;   break;
            case CAN_DLC_24_BYTES:   ret = 24U;   break;
            case CAN_DLC_32_BYTES:   ret = 32U;   break;
            case CAN_DLC_48_BYTES:   ret = 48U;   break;
            case CAN_DLC_64_BYTES:   ret = 64U;   break;
            default: break;
        }
    }

    return ret;
}

/*!
 * @brief 设置CAN报文消息，含发送缓冲区选择、CAN类型、CAN帧格式等设置
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] info: CAN message information
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @return none
 */
void CAN_SetMsgInfo(CAN_TypeDef* CANx, const CAN_MsgInfoType *info, CAN_TransmitBufferType type)
{
    uint8_t i = 0;
    uint8_t dataLength = 0;
    uint32_t tempControl = 0;
    uint32_t tempId = 0;
    uint32_t tempData = 0;

    /* Select transmit buffer */
    if (CAN_TRANSMIT_PRIMARY == type)  // 主发送缓冲区
    {
        CANx->CTRL0 &= (~CAN_CTRL0_TBSEL_Mask);   // 发送缓冲区选择：PTB(主发送缓冲区)
    }
    else  // 从发送缓冲区
    {
        CANx->CTRL0 |= CAN_CTRL0_TBSEL_Mask;   // 发送缓冲区选择：STB(从发送缓冲区)
    }
    
    /* Set message information */
    tempId = (info->ID & CAN_INFO_ID_Mask);   

    /* Set TTSEN, it is the same mask between ESI and TTSEN */
    if (s_canDevice[CAN_INDEX(CANx)].timeStampEn)   // 发送时间stamp使能
    {
        tempId |= CAN_INFO_ESI_Mask;
    }
    
    CANx->TBUF.ID_TTSEN = tempId;

    tempControl = (uint32_t)(info->DLC & CAN_INFO_DLC_Mask);

    // BRS为位速率切换，0：整个帧为正常/低速比特率   
    // 1: 整个帧为数据/快速比特率
    if (info->BRS)   
    {
        tempControl |= CAN_INFO_BRS_Mask;  // 整个帧为数据/快速比较率
    }
    
    if (info->RTR)   // RTR=0数据帧，RTR=1为远程帧
    {
        tempControl |= CAN_INFO_RTR_Mask;  // 远程帧
    }
    
    if (info->FDF)  // FDF=1为FD format
    {
        tempControl &= (uint32_t)(~CAN_INFO_RTR_Mask);  // CAN-FD时无远程帧，只有数据帧
        tempControl |= CAN_INFO_FDF_Mask;     // 扩展数据长度，每帧最多64个字节
    }
    
    if (info->IDE)  
    {
        tempControl |= CAN_INFO_IDE_Mask;  // 扩展帧
    }
    
    CANx->TBUF.TXCTRL = tempControl;
    if ((0 == info->RTR) && info->DLC && info->DATA)
    {
        dataLength = CAN_GetPayloadSize(info->DLC);
        if ((uint32_t)info->DATA % 4)
        {
            for (i = 0; i < dataLength; i += 4)
            {
                tempData = info->DATA[i] | (info->DATA[i + 1] << 8) |
                           (info->DATA[i + 2] << 16) | (info->DATA[i + 3] << 24);
                CANx->TBUF.DATA[i >> 2] = tempData;
            }
        }
        else
        {
            for (i = 0; i < dataLength; i += 4)
            {
                CANx->TBUF.DATA[i >> 2] = *(uint32_t *)(&info->DATA[i]);
            }
        }
    }
    
    /* Point to secondary next buffer */
    if (CAN_TRANSMIT_SECONDARY == type)
    {
        CANx->CTRL0 |= CAN_CTRL0_TSNEXT_Mask;
    }
}

/*!
 * @brief Set transmit amount for can secondary buffer
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] amount: CAN transmit amount
                - CAN_TRANSMIT_ALL
                - CAN_TRANSMIT_ONE
 * @return none
 */
void CAN_SetTransmitAmount(CAN_TypeDef* CANx, CAN_TransmitAmountType amount)
{
    uint8_t instance = 0;

    instance = CAN_INDEX(CANx);

    if (CAN_TRANSMIT_AMOUNT_MAX > amount)
    {
        s_canDevice[instance].tsAmount = amount;
    }
}

/*!
 * @brief Transmit CANx message
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] info: CAN message information
 * @param[in] type: CAN transmit type
                - CAN_TRANSMIT_PRIMARY
                - CAN_TRANSMIT_SECONDARY
 * @return 0: success, -1: busy, -2: timeout, -3: send error, -4: Transmit timeout
 */
int32_t CAN_TransmitMessage(CAN_TypeDef* CANx, const CAN_MsgInfoType *info, CAN_TransmitBufferType type)
{
    int32_t ret = 0;
    uint8_t instance = 0;

    instance = CAN_INDEX(CANx);

    if (s_canDevice[instance].interruptEn)
    {
        if (CAN_IsTransmitting(CANx, type))
        {
            ret = -1;
        }
    }
    else
    {
        if (CAN_WaitTransmissionIdle(CANx, type))
        {
            ret = -2;
        }
    }

    if (ret == 0)
    {
        //CAN_SetMsgInfo(CANx, info, type);   // 设置发送报文消息

        if (CAN_StartTransmission(CANx, type, s_canDevice[instance].tsAmount))
        {
            ret = -3;
        }
        else
        {
            if (CAN_WaitTransmissionDone(CANx, type))
            {
                ret = -4;
            }
        }
    }
    else  /* If it is busy or timeout, wait some time */
    {
    }

    (void)info;

    return ret;
}

/*!
* @brief CANx接收报文消息
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] info: CAN message information
 * @return 0: success, 1: no message
 */
uint8_t CAN_ReceiveMessage(CAN_TypeDef* CANx, CAN_MsgInfoType *info)
{
    uint8_t ret = 0;
    uint8_t dataLength = 0, i = 0;

    if (!CAN_IsMsgInReceiveBuf(CANx))
    {
        ret = 1;
    }
    else
    {
        /* Read message information */
        info->ID  = CANx->RBUF.ID_ESI  &  CAN_INFO_ID_Mask;   // 得到CAN报文帧的ID
        info->ESI = CANx->RBUF.ID_ESI  >> CAN_INFO_ESI_Pos;   // 得到错误状态指示，ESI仅包含在CAN-FD框架中，在CAN2.0框架中没有
        info->BRS = (CANx->RBUF.RXCTRL >> CAN_INFO_BRS_Pos) & 0x01;  // 得到位速率切换状态
        info->FDF = (CANx->RBUF.RXCTRL >> CAN_INFO_FDF_Pos) & 0x01;  // 得到CAN-FD指示
        info->RTR = (CANx->RBUF.RXCTRL >> CAN_INFO_RTR_Pos) & 0x01;  // 得到CAN报文帧类型，数据帧还是远程帧
        info->IDE = (CANx->RBUF.RXCTRL >> CAN_INFO_IDE_Pos) & 0x01;  // 得到标识符类型，标准帖还是扩展帧
        info->DLC = CANx->RBUF.RXCTRL  &  CAN_INFO_DLC_Mask;    // 得到数据长度

        if ((0 == info->RTR) && info->DLC && info->DATA)
        {
            dataLength = CAN_GetPayloadSize(info->DLC);
            if ((0 == info->FDF) && (8 < dataLength))
            {
                dataLength = 8;
            }
            
            if (((uint32_t)info->DATA % 4) || (8 > dataLength))
            {
                for (i = 0; i < dataLength; i++)
                {
                    info->DATA[i] = ((uint8_t *)CANx->RBUF.DATA)[i];
                }
            }
            else
            {
                for (i = 0; i < dataLength; i += 4)
                {
                    *(uint32_t *)(&info->DATA[i]) = CANx->RBUF.DATA[i >> 2];
                }
            }
        }
        //info->RTS = CANx->RBUF.RTS[0];
        info->RTS = CANx->RBUF.RTS0;
        
        /* Receive buffer release */
        CANx->CTRL0 |= CAN_CTRL0_RREL_Mask;
    }

    return ret;
}

/*!
 * @brief Set CANx filter when RESET = 1
 *
 * @param[in] CANx: CAN module
                - CAN0
 * @param[in] index:CAN filter id
                - (0-15)
 * @param[in] code: CAN filter code
 * @param[in] mask: CAN filter mask
 * @param[in] state: CAN filter enable state
                - ENDBLE
                - DISDBLE
 * @return 0: success, 1: reset error
 */
int32_t CAN_SetFilter(CAN_TypeDef* CANx, uint8_t index, uint32_t code, uint32_t mask, FunctionalState state)
{
    int32_t ret = 0;

    if (0 == (CANx->CTRL0 & CAN_CTRL0_RESET_Mask))  /* Should set RESET = 1 first */
    {
        ret = 1;
    }
    else
    {
        CAN_SetAcfEn(CANx, index, state);
        if (state)
        {
            CAN_SetAcfIndex(CANx, index);
            CAN_SetAcfCode(CANx, code);
            CAN_SetAcfMask(CANx, mask);
        }
    }

    return ret;
}

