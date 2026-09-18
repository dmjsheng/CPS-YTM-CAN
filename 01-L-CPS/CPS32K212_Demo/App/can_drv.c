#include "can_drv.h"
#include "gpio_drv.h"
#include <string.h>

#define CAN_RX_QUEUE_SIZE 16u

static volatile uint8_t s_rx_head = 0u;
static volatile uint8_t s_rx_tail = 0u;
static can_frame_t s_rx_queue[CAN_RX_QUEUE_SIZE];

/* 必须 4 字节对齐，防止硬件 FIFO 读取异常或内存对齐错误 */
static uint32_t s_sendDataBuff[8 / 4];
static uint32_t s_recvDataBuff[8 / 4];
static CAN_MsgInfoType s_sendMsgInfo;
static CAN_MsgInfoType s_recvMsgInfo;

/* 针对汽车照明网络 DBC 的硬件接收过滤器表 */
static CAN_FilterControlType s_canFilterList[] = {
    {0, ENABLE, 0x00000100UL, 0x00000000UL}, /* 0x100 BCM_Lamp_Cmd (接收上位机/BCM总控指令) */
    {1, ENABLE, 0x00000202UL, 0x00000000UL}, /* 0x202 RightLamp_Status (接收云途右车灯状态) */
    {2, DISABLE, 0x00000201UL, 0x00000000UL}, /* 0x201 LeftLamp_Status (本板发出的反馈，必须禁用自发自收，防止队列被自己刷爆) */
    {3, DISABLE, 0x00000000UL, 0x1FFFFFFFUL}, /* 禁用全通，防止总线杂波灌满队列 */
};

/* CAN0 中断底层回调函数 */
static void CAN0_DeviceCallback(void *device, uint32_t wpara, uint32_t lpara) {
  (void)lpara;
  CAN_TypeDef *CANx = (CAN_TypeDef *)device;

  /* 接收报文中断 (带安全防死锁计数) */
  if (wpara & CAN_CTRL1_RIF_Mask) {
    uint32_t timeoutCount = 0u;
    while ((0 != CAN_IsMsgInReceiveBuf(CANx)) && (timeoutCount < 5000u)) {
      timeoutCount++;
      CAN_ReceiveMessage(CANx, &s_recvMsgInfo);

      uint8_t next_head = (uint8_t)((s_rx_head + 1u) % CAN_RX_QUEUE_SIZE);
      if (next_head != s_rx_tail) /* 队列未满 */
      {
        s_rx_queue[s_rx_head].id = s_recvMsgInfo.ID;
        s_rx_queue[s_rx_head].dlc =
            (s_recvMsgInfo.DLC > 8u) ? 8u : s_recvMsgInfo.DLC;
        memcpy(s_rx_queue[s_rx_head].data, (const void *)s_recvDataBuff,
               s_rx_queue[s_rx_head].dlc);
        s_rx_head = next_head;
      }
    }
  }
}

void Init_CAN(void) {
  GPIO_InitTypeDef GPIO_InitStruct;
  CAN_ConfigType can_InitStruct;
  CAN_BitRateConfigType BaudRateConfig;

  cps_ddl_memclr(&GPIO_InitStruct, sizeof(GPIO_InitStruct));
  cps_ddl_memclr(&can_InitStruct, sizeof(can_InitStruct));
  cps_ddl_memclr(&BaudRateConfig, sizeof(BaudRateConfig));

  /* 1. 开启时钟 */
  RCC_AHBPeriphClockCmd(RCC, RCC_AHBPeriph_GPIOA_CKEN, ENABLE);
  RCC_AHBPeriphClockCmd(RCC, RCC_AHBPeriph_GPIOB_CKEN, ENABLE);
  RCC_APBPeriphClockCmd(RCC, RCC_APBPeriph_CAN0_CKEN, ENABLE);

  /* 2. CAN0 引脚初始化 (完全按照官方 EVB Demo 规范) */
  /* PB0 -> CAN0_RX */
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_CAN0_RX_PB0);

  /* PB1 -> CAN0_TX (官方推荐复用，连 CAN 收发芯片) */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_CAN0_TX_PB1);

  /* PA7 -> CAN0 收发使能 (低电平使能收发器处于非待机模式) */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_ResetBits(GPIOA, GPIO_Pin_7);

  /* 3. CAN 500Kbps @ 48MHz CANCLK (采样点 ~75%) */
  BaudRateConfig.PRESC = 5;  /* 48MHz / (5 + 1) = 8MHz */
  BaudRateConfig.SEG_1 = 10; /* tSeg1 = 12 */
  BaudRateConfig.SEG_2 = 3;  /* tSeg2 = 4 */
  BaudRateConfig.SJW = 2;

  /* 4. CAN 模块工作参数 (精简中断掩码，仅开启接收中断，彻底杜绝仲裁/位错误中断风暴死锁) */
  can_InitStruct.interruptEn = ENABLE;
  can_InitStruct.interruptMask = (CAN_CTRL1_RIE_Mask | CAN_CTRL1_ROIE_Mask);
  can_InitStruct.canMode = CAN_MODE_NORMAL;
  can_InitStruct.clockSrc = CAN_CLKSRC_AHB;
  can_InitStruct.tpss = DISABLE;
  can_InitStruct.tsss = DISABLE;
  can_InitStruct.filterNum = 4;
  can_InitStruct.filterList = s_canFilterList;
  can_InitStruct.callback = CAN0_DeviceCallback;
  can_InitStruct.normalBitrate = &BaudRateConfig;
  can_InitStruct.tsAmount = CAN_TRANSMIT_ALL;

  s_sendMsgInfo.DATA = (uint8_t *)s_sendDataBuff;
  s_recvMsgInfo.DATA = (uint8_t *)s_recvDataBuff;

  CAN_Init(CAN0, &can_InitStruct);

  /* 5. 使能 NVIC CAN0 中断 */
  NVIC_SetPriority(CAN0_IRQn, 1);
  NVIC_EnableIRQ(CAN0_IRQn);
}

bool CAN_Send_Msg(uint32_t id, const uint8_t *data, uint8_t dlc) {
  if (dlc > 8u) {
    dlc = 8u;
  }

  /* 检查主发送邮箱 (PTB) 是否正在发送上一帧 */
  if (CAN_IsTransmitting(CAN0, CAN_TRANSMIT_PRIMARY)) {
    uint32_t timeout = 500u;
    while ((CAN_IsTransmitting(CAN0, CAN_TRANSMIT_PRIMARY)) && (timeout > 0u)) {
      timeout--;
    }
    if (timeout == 0u) {
      /* 如果超时（如总线无应答反复重传），中止当前 PTB 传输释放邮箱，避免硬件永久占死 */
      CAN0->CTRL0 |= CAN_CTRL0_TPA_Mask;
      return false;
    }
  }

  /* 临界区保护：设置报文并触发硬件发送，杜绝与接收中断并发访问 CTRL0 的冲突 */
  __disable_irq();
  s_sendMsgInfo.ID = id;
  s_sendMsgInfo.IDE = 0u; /* 标准帧 */
  s_sendMsgInfo.FDF = 0u; /* CAN 2.0 格式 */
  s_sendMsgInfo.RTR = 0u; /* 数据帧 */
  s_sendMsgInfo.DLC = dlc;
  memcpy((void *)s_sendDataBuff, data, dlc);

  CAN_SetMsgInfo(CAN0, &s_sendMsgInfo, CAN_TRANSMIT_PRIMARY);
  CAN_StartTransmission(CAN0, CAN_TRANSMIT_PRIMARY, CAN_TRANSMIT_ALL);
  __enable_irq();
  return true;
}

bool CAN_Get_Rx_Msg(can_frame_t *msg) {
  /* 临界区保护：从环形缓冲区安全出队 */
  __disable_irq();

  if (s_rx_head == s_rx_tail) {
    __enable_irq();
    return false;
  }

  *msg = s_rx_queue[s_rx_tail];
  s_rx_tail = (uint8_t)((s_rx_tail + 1u) % CAN_RX_QUEUE_SIZE);
  __enable_irq();
  return true;
}
