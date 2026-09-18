# Flexcan_Demo

---

## Function Description

This example demonstrates the use of FlexCAN and self-testing.

- The mailbox number defined by **TX_STD_MAILBOX** (Mailbox-1) sends a standard frame message with the ID **TX_MSG_ID** (0x103) every 100ms.
- The mailbox number defined by **TX_EXT_MAILBOX** (Mailbox-3) sends an extended frame message with the ID **TX_EXT_ID** (0x70013) every 100ms.
- The mailbox number defined by **RX_STD_MAILBOX** (Mailbox-0) receives messages with the ID **RX_STD_MSG_ID** (0x102).
- The mailbox number defined by **RX_EXT_MAILBOX** (Mailbox-2) receives messages with the ID **RX_EXT_MSG_ID** (0x70012).
- The nominal baud rate is 500Kbps.
- Connect the CAN tool's CANH & CANL lines to the on-board CAN channel's CANH & CANL (J7).
- Each message with a matching ID will be printed via UART.
- The entire routine will stop if the count of received messages reaches 10.

---

## Hardware Requirements

+ **EVB**: YTM32B1LE0-EVB-Q64
+ **Debugger**: J-LINK v9.2 or later version

---

## Software Requirements

+ **SDK**      : YTM32B1LE0_1_4_0 or later version
+ **GCC**      : GNU GCC v10.3 or later version
+ **Keil/MDK** : ARM Keil/MDK v5.36 or later version
+ **IAR***     : IAR v8.4 or later version
+ **VS Code**  : Microsoft Visual Studio Code IDE v1.76 or later version(GNU GCC toolchain, CMake v3.25, ninja, Cortex-Debug extensions installation required)
+ **J-LINK** : SEGGER JLINK v6.96 or later version, YTM32B1LE0 patch(support package) installation required.
+ **Ozone**  : SEGGER Ozone v3.28 or later version.
  
---