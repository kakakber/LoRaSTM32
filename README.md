# LoRaSTM32 (not finished)
## Usage
Setup spi on cubeMX, maximum rate about 20MBps:
![Alt text](Imgs/SPImax.png "Title")
---
After copying the library folder inside your preferred directory, import the header file:

```
#include "[Path]/LoRa.h"
```
---
## loRaInit
`int loRaInit(SPI_HandleTypeDef *hspi, GPIO_TypeDef *NSS_GPIOx, uint16_t NSS_GPIO_Pin, GPIO_TypeDef *RESET_GPIOx, uint16_t RESET_GPIO_Pin, GPIO_TypeDef *DIO0_GPIOx, uint16_t DIO0_GPIO_Pin)`
	     
Initialize the loRa module before start of operations, the method receives all the spi pin and ports.
Example of usage:
```
  if (loRaInit(&hspi3, SPI_3_CS0_GPIO_Port, SPI_3_CS0_Pin, DIO0_INT_GPIO_Port, DIO0_INT_Pin, LoRa_RST_GPIO_Port, LoRa_RST_Pin)){
	  //Initialization was successful, add custom parameters
  }else{
	  //Failed init, example of response (loops while lora not initializing)
	  do{
		  HAL_Delay(1000);
	  }while(!loRaInit(&hspi3, SPI_3_CS0_GPIO_Port, SPI_3_CS0_Pin, DIO0_INT_GPIO_Port, DIO0_INT_Pin, LoRa_RST_GPIO_Port, LoRa_RST_Pin));
  }
```

---
Send a packet
