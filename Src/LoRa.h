/**
  ******************************************************************************
  * @file    LoRa.h
  * @author  Enrico Alberti, Physis PEB 2023
  * @brief   Header file of LORA module.
  ******************************************************************************
  */

#include <stdint.h>

#ifndef LORA_H
#define LORA_H


//includes
#include "stm32l4xx_hal.h"


//registers
#define REG_VERSION              0x42
#define REG_OP_MODE               0x01

#define REG_FRF_MSB              0x06
#define REG_FRF_MID              0x07
#define REG_FRF_LSB              0x08


#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f

#define REG_OCP                  0x0b
#define REG_PA_CONFIG            0x09

#define REG_LNA                  0x0c
#define REG_FIFO_ADDR_PTR        0x0d
#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS            0x12
#define REG_RX_NB_BYTES          0x13
#define REG_PKT_SNR_VALUE        0x19
#define REG_PKT_RSSI_VALUE       0x1a
#define REG_RSSI_VALUE           0x1b
#define REG_MODEM_CONFIG_1       0x1d
#define REG_MODEM_CONFIG_2       0x1e
#define REG_PREAMBLE_MSB         0x20
#define REG_PREAMBLE_LSB         0x21
#define REG_PAYLOAD_LENGTH       0x22
#define REG_MODEM_CONFIG_3       0x26
#define REG_FREQ_ERROR_MSB       0x28
#define REG_FREQ_ERROR_MID       0x29
#define REG_FREQ_ERROR_LSB       0x2a
#define REG_RSSI_WIDEBAND        0x2c
#define REG_DETECTION_OPTIMIZE   0x31
#define REG_INVERTIQ             0x33
#define REG_DETECTION_THRESHOLD  0x37
#define REG_SYNC_WORD            0x39
#define REG_INVERTIQ2            0x3b
#define REG_DIO_MAPPING_1        0x40
#define REG_VERSION              0x42
#define REG_PA_DAC               0x4d

#define REG_FIFO 0x00
#define REG_OP_MODE 0x01


//stats
#define PA_RFO_PIN 0
#define PA_BOOST_PIN 1
#define PA_BOOST 0x80
#define TRUE 1
#define FALSE 0


//modes
#define MODE_LONG_RANGE_MODE     0x80
#define MODE_SLEEP               0x00
#define MODE_STDBY               0x01
#define MODE_TX                  0x03
#define MODE_RX_CONTINUOUS       0x05
#define MODE_RX_SINGLE           0x06
#define MODE_CAD                 0x07

//limits
#define MAX_PKT_LENGTH 255

//IRQ flags
#define IRQ_CAD_DONE_MASK 0x04
#define IRQ_CAD_DETECTED_MASK 0x01
#define IRQ_TX_DONE_MASK 0x08
#define IRQ_VALID_HEADER_MASK 0x10
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK 0x40
#define IRQ_RX_TIMEOUT_MASK 0x80



//values
#define LORA_BASE_FREQ 868E6


/*public functions*/


/**
 * @brief Initializes the LoRa module.
 *
 * This function initializes the LoRa module and sets default parameters
 *
 * @param hspi A pointer to the SPI_HandleTypeDef struct that contains the configuration information for the SPI peripheral.
 * @param NSS_GPIOx A pointer to the GPIO_TypeDef struct that represents the GPIO port for the chip select (NSS) pin.
 * @param NSS_GPIO_Pin The GPIO pin number for the chip select (NSS) pin.
 * @param RESET_GPIOx A pointer to the GPIO_TypeDef struct that represents the GPIO port for the reset pin.
 * @param RESET_GPIO_Pin The GPIO pin number for the reset pin.
 * @param DIO0_GPIOx A pointer to the GPIO_TypeDef struct that represents the GPIO port for the DIO0 pin.
 * @param DIO0_GPIO_Pin The GPIO pin number for the DIO0 pin.
 *
 * @return An integer value indicating the success or failure of the initialization process. A value of 0 indicates success, while any other value indicates an error.
 */
int loRaInit(SPI_HandleTypeDef *hspi, GPIO_TypeDef *NSS_GPIOx, uint16_t NSS_GPIO_Pin,
             GPIO_TypeDef *RESET_GPIOx, uint16_t RESET_GPIO_Pin,
             GPIO_TypeDef *DIO0_GPIOx, uint16_t DIO0_GPIO_Pin);


int loRaInit(SPI_HandleTypeDef*, GPIO_TypeDef*, uint16_t, GPIO_TypeDef*, uint16_t, GPIO_TypeDef*, uint16_t);
void loRaSetTxPower(int, int);
void loRaSetFrequency(uint8_t);
void loRaSleep();
void loRaIdle();
void loRaEnableCRC();
void loRaSetSyncWord(int);
void loRaSetSpreadingFactor(int);
void loRaSetSignalBandwidth(long);
long loRaGetSignalBandwidth();
int loRaGetSpreadingFactor();
void loRaSetCodingRate(int den);
uint8_t loRaReadConfig1();

void loRaFullyTransmitMode();
void loRaFullyReceiveMode();


/**
 * @brief Interrupt handler for DIO0 pin.
 *
 * This function handles interrupts generated by the DIO0 pin of the LoRa module.
 * It takes four function pointers as arguments, each of which is a callback function
 * that will be executed when a specific event occurs. The possible events and their
 * corresponding callbacks are:
 *
 * - Transmission (TX) complete: This event occurs when a transmission is complete.
 *   The TX callback function will be executed in response to this event.
 *
 * - Receive (RX) complete: This event occurs when a reception is complete.
 *   The RX callback function will be executed in response to this event.
 *
 * - Channel Activity Detection (CAD) complete: This event occurs when the LoRa module
 *   detects activity on the channel during CAD mode. The CAD callback function will be
 *   executed in response to this event. If the CAD callback function takes an integer
 *   argument, it will be passed the CAD detected status (1 if detected, 0 otherwise).
 *
 * - CRC error: This event occurs when the LoRa module detects a CRC error in the received data.
 *   The CRC error callback function will be executed in response to this event.
 *
 * @param TXcallback Pointer to the TX callback function.
 * @param RXcallback Pointer to the RX callback function.
 * @param CADCallback Pointer to the CAD callback function.
 * @param CRCErrorCallback Pointer to the CRC error callback function.
 *
 * @return None.
 */
void loRaDIO0InterruptHandler(void (*TXcallback)(void), void (*RXcallback)(void), void (*CADCallback)(int), void (*CRCErrorCallback)(void));

/**
 * Sends a LoRa packet using the specified buffer and size.
 *
 * @param explicitHeader A boolean value indicating whether the packet has an explicit header (1) or not (0).
 * @param buffer A pointer to the buffer containing the data to be sent.
 * @param size The size of the data in bytes.
 *
 * @return Returns 0 on success, or a negative error code if an error occurred.
 */
int loRaSendPacket(int explicitHeader, const uint8_t *buffer, size_t size);
int loRaSendPacketSYNC(int explicitHeader, const uint8_t *buffer, size_t size);
int loRaIsTrasmitting();
void loRaClearIRQ();
void loRaClearIRQReceive();

#endif

