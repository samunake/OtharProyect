#define CS_HIGH()     	 GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define CS_LOW()     	 GPIO_ResetBits(GPIOB, GPIO_Pin_2)
/* if CS is low the card is selected */
#define CHECK_CARD()	(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)== 0 ? 1 : 0)
#define CHECK_WRE		 1

 
#define _USE_WRITE	1	/* 1: Enable disk_write function */
#define _USE_IOCTL	1	/* 1: Enable disk_ioctl fucntion */






