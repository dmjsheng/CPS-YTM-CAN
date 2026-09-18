/* Includes ------------------------------------------------------------------*/
#include "cps32k21x.h"
#include "cps32k21x_i2c.h"
#include "cps32k21x_rcc.h"
#include "cps32k21x_systick.h"


__IO uint8_t I2C_Buffer[17] = {0};
   

/**
  * @brief  Returns the HCLK frequency     
  * @note   Each time HCLK changes, this function must be called to update the
  *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  * 
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency 
  *         and updated within this function
  * @retval HCLK frequency(unit: Hz)
  */
uint32_t RCC_GetHCLKFreq(void)
{
    return MY_SYSTEM_CORE_CLOCK;
}

/**
  * @brief  Returns the PCLK frequency     
  * @note   Each time PCLK changes, this function must be called to update the
  *         right PCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @retval PCLK frequency
  */
uint32_t RCC_GetPCLKFreq(void)
{
    /* Get HCLK source and Compute PCLK frequency ---------------------------*/
    if (RCC->PCLKDIV != 0)
    {
        return ((RCC_GetHCLKFreq() >> 1) / RCC->PCLKDIV);
    }
    else
    {
        return (RCC_GetHCLKFreq());	
    }        
}  

/**
  * @brief  Initializes the I2C according to the specified parameters in the
  *         I2C_InitTypeDef and creates the associated handle.
  * @param  hi2c : I2C handle
  * @retval HAL status
  */
StatusTypeDef I2C_Init(I2C_HandleTypeDef *hi2c)
{
    uint32_t tmpcon = 0;
	
	if (hi2c == NULL)
    {
		return STATUS_ERROR; 
    }
	
	 __HAL_I2C_DISABLE(hi2c); 
		
	 tmpcon = RCC_GetPCLKFreq() / 1000;
	 tmpcon = (uint32_t)((tmpcon - ((hi2c->Init.speedclock) << 3)) / ((hi2c->Init.speedclock) << 3));
	
	if (hi2c->Init.slave != I2C_SLAVE_MODE_DISABLE)
	{
		SET_BIT(hi2c->Instance->CR, I2C_CR_AA);
		hi2c->Instance->ADDR |= (hi2c->Init.slaveAddr << I2C_ADDR_I2CADR_Pos);

		if (hi2c->Init.broadack != I2C_BROAD_ACK_DISABLE)
        {
			SET_BIT(hi2c->Instance->ADDR, I2C_ADDR_GC);
        }
		else
        {
			CLEAR_BIT(hi2c->Instance->ADDR, I2C_ADDR_GC);
        }
	}
	else
	{
		CLEAR_BIT(hi2c->Instance->CR, I2C_CR_AA);
	}
  
	if (hi2c->Init.master != I2C_MASTER_MODE_DISABLE)
	{
		hi2c->Instance->BAUDCR = tmpcon & I2C_BAUDCR_TM;
		SET_BIT(hi2c->Instance->TIMRUN, I2C_TIMRUN_TME);
	}
 
	if (hi2c->Init.speedclock < 400)
    {
		CLEAR_BIT(hi2c->Instance->CR, I2C_CR_H1M);
    }
	else
    {
		SET_BIT(hi2c->Instance->CR, I2C_CR_H1M);
    }
  
	__HAL_I2C_ENABLE(hi2c); 
	I2C_Clear_Interrupt_Flag(hi2c);
    
    hi2c->ErrorCode = I2C_ERROR_NONE;
    hi2c->State = I2C_STATE_READY;
	hi2c->PreviousState = I2C_STATE_NONE;
 
	return STATUS_OK; 
}

/**
  * @brief  DeInitializes the I2C peripheral. 
  *         Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  hi2c : I2C handle
  * @retval HAL status
  */
StatusTypeDef I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    /* Check the I2C handle allocation */
	if (hi2c == NULL)
	{
		return STATUS_ERROR;
	}
    
    if (hi2c->Instance == I2C0)
    {
        /* Enable TIM1 reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_I2C0_RST, ENABLE);
    	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    	/* Release TIM1 from reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_I2C0_RST, DISABLE);
    }
#if 0
    else if (hi2c->Instance == I2C1)
    {
        /* Enable TIM1 reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_I2C1_RST, ENABLE);
    	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

    	/* Release TIM1 from reset state */
    	RCC_PeriphResetCmd(RCC, RCC_APBPeriph_I2C1_RST, DISABLE);
    }
#endif

	hi2c->State = I2C_STATE_BUSY;	
  
	hi2c->Instance->CR = 0;
	/* Disable the I2C */
	__HAL_I2C_DISABLE(hi2c);
  
	hi2c->ErrorCode     = I2C_ERROR_NONE;
	hi2c->State         = I2C_STATE_RESET;
	//  hi2c->PreviousState = I2C_STATE_NONE;
	hi2c->Mode          = I2C_MODE_NONE;	
	
	/* Return function status */
	return STATUS_OK;	
}

/**
  * @brief  Set i2c start status.
  * @param  hi2c : I2C handle
  * @param  NewState : ENABLE or DISABLE
  * @retval None
  */
void I2C_Start_Config(I2C_HandleTypeDef *hi2c, FunctionalState NewState)
{
	if (NewState != DISABLE)
    {
		SET_BIT(hi2c->Instance->CR, I2C_CR_STA);
    }
	else
    {
		CLEAR_BIT(hi2c->Instance->CR,I2C_CR_STA); 
    }
}

/**
  * @brief  Set i2c stop status.
  * @param  hi2c : I2C handle
  * @param  NewState : ENABLE or DISABLE
  * @retval None
  */
void I2C_Stop_Config(I2C_HandleTypeDef *hi2c, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		SET_BIT(hi2c->Instance->CR, I2C_CR_STO);
		I2C_Clear_Interrupt_Flag(hi2c);
	}
	else
    {
		CLEAR_BIT(hi2c->Instance->CR, I2C_CR_STO); 
    }
}

/**
  * @brief  Set i2c ACK status.
  * @param  hi2c : I2C handle
  * @param  NewState : ENABLE or DISABLE
  * @retval None
  */
void I2C_ACK_Config(I2C_HandleTypeDef *hi2c, FunctionalState NewState)
{
	if (NewState != DISABLE)
    {
		SET_BIT(hi2c->Instance->CR, I2C_CR_AA);
    }
	else
    {
		CLEAR_BIT(hi2c->Instance->CR, I2C_CR_AA); 
    }
}

/**
  * @brief  Get i2c Interrupt SI Flag.
  * @param  hi2c : I2C handle
  * @retval FlagStatus (SET or RESET)
  */
FlagStatus I2C_Get_Interrupt_Flag(I2C_HandleTypeDef *hi2c)
{
	return (__HAL_I2C_GET_INT_SI_FLAG(hi2c)); 
}

/**
  * @brief  Clear i2c Interrupt SI Flag.
  * @param  hi2c : I2C handle
  * @retval None
  */
void I2C_Clear_Interrupt_Flag(I2C_HandleTypeDef *hi2c)
{
	__HAL_I2C_CLEAR_INT_SI_FLAG(hi2c); 
}

/**
  * @brief  Send Byte Data.
  * @param  hi2c : I2C handle
  * @param  Data : send date  
  * @retval None
  */
void I2C_Send_Byte(I2C_HandleTypeDef *hi2c, uint8_t Data)
{
	hi2c->Instance->DATA = Data; 
	I2C_Clear_Interrupt_Flag(hi2c);
}

/**
  * @brief  Receive Byte Data.
  * @param  hi2c : I2C handle
  * @param  pData : reveive date handle
  * @retval None
  */
void I2C_Receive_Byte(I2C_HandleTypeDef *hi2c, uint8_t *pData)
{
	*pData = hi2c->Instance->DATA; 
}

/**
  * @brief  Transmits the address byte to select the slave device.
  * @param  hi2c: I2C handle
  * @param  Address: specifies the slave address which will be transmitted
  * @param  I2C_Direction: specifies whether the I2C device will be a Transmitter or a Receiver. 
  *    This parameter can be one of the following values
  *      @arg I2C_Direction_Transmitter: Transmitter mode
  *      @arg I2C_Direction_Receiver: Receiver mode
  * @retval None.
  */
void I2C_Send_Address(I2C_HandleTypeDef *hi2c, uint8_t Address, uint8_t I2C_Direction)
{
    /* Test on the direction to set/reset the read/write bit */
	if (I2C_Direction != I2C_Direction_Transmitter)
	{
		/* Set the address bit0 for read */
		Address |= I2C_Direction_Receiver;
	}
	else
	{
		/* Reset the address bit0 for write */
		Address &= (uint8_t)~((uint8_t)I2C_Direction_Receiver);
	}
	/* Send the address */
	hi2c->Instance->DATA = Address;

	I2C_Start_Config(hi2c, DISABLE);
	I2C_Clear_Interrupt_Flag(hi2c);
}

/**
  * @brief  Get the last I2C module status flag
  * @note   For detailed description of status flag 
  * @retval An I2C Status enumeration value:
  *   - I2C_SUCCESS: Get the i2c module status
  *   - I2C_WAITING: Can't get the i2c module status 
  */
I2CStatus I2C_Check_Flag(I2C_HandleTypeDef *hi2c, uint32_t *i2c_flag)
{
    I2CStatus status = I2C_WAITING;
 
    if (I2C_Get_Interrupt_Flag(hi2c) != RESET)
    {
        /* Read the I2Cx status register */
        *i2c_flag = hi2c->Instance->SR;
        
        /* I2C_SUCCESS: Get the i2c module status */
        status = I2C_SUCCESS;
    }
    /* Return status */
    return status;
}

/**
  * @brief  Checks whether the last I2C module  status flag is get or not in timeout
  * @note   For detailed description of Status flag, please refer to section I2C Flag
  * @retval An ErrorStatus enumeration value:
  *   - SUCCESS: Get the status flag
  *   - ERROR: Can't get the status flag
  */
ErrorStatus I2C_Wait_Flag(I2C_HandleTypeDef *hi2c, uint32_t *I2C_flag)
{
    uint32_t time_cnt = 0;
    uint32_t tickstart = 0;
    I2CStatus ret = I2C_WAITING;
	
    time_cnt = I2C_TIMEOUT_FLAG;
    
    /* Init tickstart for timeout management, SysTick time must enable */
    tickstart = HAL_GetTick();
	
    do
    {
        ret = I2C_Check_Flag(hi2c, I2C_flag);
    }while ((time_cnt > (HAL_GetTick() - tickstart)) && (ret == I2C_WAITING));
    
    if (ret == I2C_SUCCESS)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval status
  */
StatusTypeDef I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	uint32_t transmit_size = 0;
	uint32_t i2c_flag = 0xFF;
	
	if (hi2c->State == I2C_STATE_READY)
	{
		hi2c->State     = I2C_STATE_BUSY_TX;
		hi2c->Mode      = I2C_MODE_MASTER;
		hi2c->ErrorCode = I2C_ERROR_NONE;
	    
		I2C_Start_Config(hi2c, ENABLE);
		I2C_Wait_Flag(hi2c, &i2c_flag);
		if (i2c_flag != I2C_FLAG_MASTER_TX_START)
		{ 
			hi2c->State     = I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return STATUS_ERROR;
		}
		i2c_flag = 0xFF;
		
		I2C_Send_Address(hi2c, DevAddress, I2C_Direction_Transmitter);
		I2C_Wait_Flag(hi2c, &i2c_flag);
		if (i2c_flag != I2C_FLAG_MASTER_TX_SLAW_ACK)
		{ 
			hi2c->State     = I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return STATUS_ERROR;
		}
             
		while (transmit_size < Size)
		{
			i2c_flag = 0xFF;
			I2C_Send_Byte(hi2c, pData[transmit_size]);
			I2C_Wait_Flag(hi2c, &i2c_flag);
			if (i2c_flag != I2C_FLAG_MASTER_TX_DATA_ACK)
			{ 
				hi2c->State     = I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return STATUS_ERROR;
			}
			transmit_size++;
		} 
		I2C_Stop_Config(hi2c,ENABLE);
		hi2c->State = I2C_STATE_READY;
		return STATUS_OK;
	}
	else
    {
		return STATUS_BUSY;
    }
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode for restart read(not stop).
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval status
  */
StatusTypeDef I2C_Master_Transmit_NOStop(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	uint32_t transmit_size = 0;
	uint32_t i2c_flag = 0xFF;
	
	if (hi2c->State == I2C_STATE_READY)
	{
		hi2c->State     = I2C_STATE_BUSY_TX;
		hi2c->Mode      = I2C_MODE_MASTER;
		hi2c->ErrorCode = I2C_ERROR_NONE;
	    
		I2C_Start_Config(hi2c, ENABLE);
		I2C_Wait_Flag(hi2c, &i2c_flag);
		if (i2c_flag != I2C_FLAG_MASTER_TX_START)
		{ 
			hi2c->State     = I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return STATUS_ERROR;
		}
		i2c_flag = 0xFF;
		
		I2C_Send_Address(hi2c, DevAddress, I2C_Direction_Transmitter);
		I2C_Wait_Flag(hi2c, &i2c_flag);
		if (i2c_flag != I2C_FLAG_MASTER_TX_SLAW_ACK)
		{ 
			hi2c->State     = I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return STATUS_ERROR;
		}
             
		while (transmit_size < Size)
		{
			i2c_flag = 0xFF;
			I2C_Send_Byte(hi2c, pData[transmit_size]);
			I2C_Wait_Flag(hi2c, &i2c_flag);
			if (i2c_flag != I2C_FLAG_MASTER_TX_DATA_ACK)
			{ 
				hi2c->State     = I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return STATUS_ERROR;
			}
			transmit_size++;
		} 
		I2C_Clear_Interrupt_Flag(hi2c);
		hi2c->State = I2C_STATE_READY;
   	
		return STATUS_OK;
	}
	else
    {
		return STATUS_BUSY;
    }
}

/**
  * @brief  Receives in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted at right before call interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval status
  */
StatusTypeDef I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
	uint32_t receive_size = 0;
	uint32_t i2c_flag = 0xFF;
    
	if (hi2c->State == I2C_STATE_READY)
	{
		hi2c->State     = I2C_STATE_BUSY_RX;
		hi2c->Mode      = I2C_MODE_MASTER;
		hi2c->ErrorCode = I2C_ERROR_NONE;
	    
		I2C_Start_Config(hi2c, ENABLE);
		I2C_Wait_Flag(hi2c, &i2c_flag);
    
		if ((i2c_flag != I2C_FLAG_MASTER_RX_START) && (i2c_flag != I2C_FLAG_MASTER_RX_RESTART))
		{ 
			hi2c->State = I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return STATUS_ERROR;
		}
        
		i2c_flag = 0xFF;    
		I2C_Send_Address(hi2c, DevAddress, I2C_Direction_Receiver);
		I2C_Wait_Flag(hi2c, &i2c_flag);
		if (i2c_flag != I2C_FLAG_MASTER_RX_SLAW_ACK)
		{ 
			hi2c->State     = I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return STATUS_ERROR;
		}
        
		while ((uint16_t)receive_size < (Size - 1))
		{
			I2C_ACK_Config(hi2c, ENABLE);
			i2c_flag = 0xFF;
			I2C_Clear_Interrupt_Flag(hi2c);
			I2C_Wait_Flag(hi2c, &i2c_flag);
			if (i2c_flag != I2C_FLAG_MASTER_RX_DATA_ACK)
			{ 
				hi2c->State     = I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return STATUS_ERROR;
			}
			I2C_Receive_Byte(hi2c, &pData[receive_size]);
			receive_size++;
		}
        
		if ((uint16_t)receive_size == (Size - 1))
		{
			I2C_ACK_Config(hi2c, DISABLE);
			i2c_flag = 0xFF;
			I2C_Clear_Interrupt_Flag(hi2c);
			I2C_Wait_Flag(hi2c, &i2c_flag);
			if (i2c_flag != I2C_FLAG_MASTER_RX_DATA_NOACK)
			{ 
				hi2c->State     = I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return STATUS_ERROR;
			}
			I2C_Receive_Byte(hi2c, &pData[receive_size]);
			receive_size++;
		}
        
		I2C_Stop_Config(hi2c, ENABLE);
		if (hi2c->Init.slave == I2C_SLAVE_MODE_ENABLE)
        {
			I2C_ACK_Config(hi2c, ENABLE);
        }
        
		hi2c->State = I2C_STATE_READY;
		
		return STATUS_OK;
	}
	else
    {
		return STATUS_BUSY;
    }
}

/**
  * @brief  Transmits in slave mode an amount of data in blocking mode. 
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval status
  */
StatusTypeDef I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
	uint32_t transmit_size = 0;
	uint32_t i2c_flag = 0xFF;
  
	if (hi2c->State == I2C_STATE_READY)
	{
		hi2c->State     = I2C_STATE_BUSY_TX;
		hi2c->Mode      = I2C_MODE_SLAVE;
		hi2c->ErrorCode = I2C_ERROR_NONE;
	    
		while (transmit_size < Size)
		{
			i2c_flag = 0xFF;
			I2C_ACK_Config(hi2c, ENABLE);
			I2C_Send_Byte(hi2c, pData[transmit_size]);
			I2C_Wait_Flag(hi2c, &i2c_flag);
			if (i2c_flag == I2C_FLAG_SLAVE_TX_DATA_ACK) 
			{
				transmit_size++;
			}
			else if ((i2c_flag == I2C_FLAG_SLAVE_TX_DATA_NOACK) || (i2c_flag == I2C_FLAG_SLAVE_TX_DATA_LAST))
			{
				i2c_flag = 0xFF;
				I2C_ACK_Config(hi2c, DISABLE);
				I2C_Clear_Interrupt_Flag(hi2c);
				transmit_size++;
				break;
			}
			else
			{ 
				hi2c->State = I2C_STATE_ERROR;
				hi2c->ErrorCode = hi2c->PreviousState;
				return STATUS_ERROR;
			}
		} 
        
		I2C_ACK_Config(hi2c, ENABLE);
		hi2c->State = I2C_STATE_READY;
   
		return STATUS_OK;
	}
	else
    {
		return STATUS_BUSY;
    }
}

/**
  * @brief  Receive in slave mode an amount of data in blocking mode
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be reveive
  * @retval status
  */
StatusTypeDef I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t *Size)
{
	uint32_t i2c_flag = 0xFF;
	uint32_t receive_size = 0;

	if (hi2c->State == I2C_STATE_READY)
	{	
		hi2c->State     = I2C_STATE_BUSY_RX;
		hi2c->Mode      = I2C_MODE_SLAVE;
		hi2c->ErrorCode = I2C_ERROR_NONE;	
		I2C_ACK_Config(hi2c, ENABLE);
		I2C_Clear_Interrupt_Flag(hi2c);
		I2C_Wait_Flag(hi2c, &i2c_flag);
		while (i2c_flag == I2C_FLAG_SLAVE_RX_SDATA_ACK) 
		{
			pData[receive_size] = hi2c->Instance->DATA;
			i2c_flag = 0xFF;
			I2C_ACK_Config(hi2c, ENABLE);
			I2C_Clear_Interrupt_Flag(hi2c);
			I2C_Wait_Flag(hi2c, &i2c_flag);
			receive_size++;
		}
        
		if (i2c_flag == I2C_FLAG_SLAVE_STOP_RESTART) 
		{
			i2c_flag = 0xFF;
			I2C_ACK_Config(hi2c, ENABLE);
			I2C_Clear_Interrupt_Flag(hi2c);
		}
		else
		{ 
			hi2c->State     = I2C_STATE_ERROR;
			hi2c->ErrorCode = hi2c->PreviousState;
			return STATUS_ERROR;
		}

        /* Last Byte is received */
		hi2c->State = I2C_STATE_READY;	
		*Size = receive_size;
	}
	else
	{	
		return STATUS_BUSY;
	}
	return STATUS_OK;	
}

/**
  * @brief  This function handles I2C  interrupt request.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @retval None
  */
void I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
	uint32_t CurrentMode = hi2c->Mode;
	
	/* Master mode selected */	
	if (CurrentMode == I2C_MODE_MASTER)	
	{
		I2C_MasterCallback(hi2c);
	}
	/* Slave mode selected */
	else
	{
		I2C_SlaveCallback(hi2c);
	}
}


