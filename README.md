# LoRaSTM32 (not finished)
## Usage
After copying the folder inside your preferred direcory, import the header file:

```
#include "[Path]/LoRa.h"
```
---
Initialize the loRa module before start of operations
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
