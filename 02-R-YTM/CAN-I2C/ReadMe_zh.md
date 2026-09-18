# Flexcan_Demo

---

## 功能描述

该示例演示了 FlexCAN 的使用, 以及自测试。

- 使用 **TX_STD_MAILBOX** 定义的邮箱号（邮箱-1）每 100ms 发送一次 ID 为 **TX_MSG_ID**（0x103）的标准帧消息。
- 使用 **TX_EXT_MAILBOX** 定义的邮箱号（邮箱-3）每 100ms 发送一次 ID 为 **TX_EXT_ID**（0x70013）的拓展帧消息。
- 使用 **RX_STD_MAILBOX** 定义的邮箱号（邮箱-0）接收 ID 为 **RX_STD_MSG_ID**（0x102）的消息。
- 使用 **RX_EXT_MAILBOX** 定义的邮箱号（邮箱-2）接收 ID 为 **RX_EXT_MSG_ID**（0x70012）的消息。
- 波特率（标称）为 500Kbps
- 将 CAN 工具 CANH&CANL 线连接到板载 CAN 通道 CANH&CANL（J7）。
- 每个匹配的 ID 消息都将通过 UART 打印。
- 如果接收到的消息计数达到 10，则整个例程将停止。

---

## 硬件需求

+ **开发板**: YTM32B1LE0-EVB-Q64
+ **调试器**: J-LINK v9.2 或更高版本

---

## 软件需求

+ **SDK**     : YTM32B1LE0_1_4_0 或更高版本
+ **GCC**     : GNU GCC v10.3 或更高版本
+ **Keil/MDK**: ARM Keil/MDK v5.36 或更高版本
+ **IAR**     : IAR v8.40 或更高版本
+ **VS Code** : Microsoft Visual Studio Code IDE v1.76 或更高版本（GNU GCC 工具链，CMake v3.25，ninja，Cortex-Debug 扩展安装）
+ **J-LINK**  : SEGGER JLINK v6.96 或更高版本，需要安装 YTM32B1LE0 补丁（支持包）
+ **Ozone**   : SEGGER Ozone v3.28 或更高版本

---