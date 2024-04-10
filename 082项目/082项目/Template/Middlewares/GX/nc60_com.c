#include "nc60_com.h"
#include "usart.h"

#include <stdarg.h>
#include "stdio.h"    
#include "string.h"   






UART_UNIONTypeDef uart_union[8];
	
	UART_UNIONTypeDef *puart_union[]=
{

   [U1_2321_NUM] = &uart_union[U1_2321_NUM],
   [U4_2322_NUM] = &uart_union[U4_2322_NUM],
   [U3_4851_NUM] = &uart_union[U3_4851_NUM],
   [U6_4852_NUM] = &uart_union[U6_4852_NUM],
	 [U5_4853_NUM] = &uart_union[U5_4853_NUM],
	 [U2_4854_NUM] = &uart_union[U2_4854_NUM],
	 [U7_TTL1_NUM] = &uart_union[U7_TTL1_NUM],
	 [U8_TTL2_NUM] = &uart_union[U8_TTL2_NUM],
};



void uart_tx_dma(UART_UNIONTypeDef * uart_uni,uint8_t *Tx_Buf,uint16_t TxCount)
{
	if(uart_uni->gpiox!=0)
	 HAL_GPIO_WritePin(uart_uni->gpiox,uart_uni->gpioPinx,GPIO_PIN_SET);

	 //HAL_UART_Transmit_DMA(&huart1,"hello\r\n", 7);	
	 //HAL_UART_Transmit_DMA(&huart1,Tx_Buf, TxCount);	
   HAL_UART_Transmit_DMA(uart_uni->init_uart,Tx_Buf, TxCount);	
	 HAL_Delay(10);
}


void uart_tx(UART_UNIONTypeDef * uart_uni,uint8_t *Tx_Buf,uint16_t TxCount)
{
	if(uart_uni->gpiox!=0)
	 HAL_GPIO_WritePin(uart_uni->gpiox,uart_uni->gpioPinx,GPIO_PIN_RESET);
	
  HAL_UART_Transmit(uart_uni->init_uart, Tx_Buf, TxCount, 0xffff);
	if(uart_uni->gpiox!=0)
	 HAL_GPIO_WritePin(uart_uni->gpiox,uart_uni->gpioPinx,GPIO_PIN_SET);
}


void UART_UNION_Init(void)
{
  uart_union[U1_2321_NUM].uart_seq = U1_2321_NUM; 
	uart_union[U1_2321_NUM].init_uart =&huart1; 
	uart_union[U1_2321_NUM].init_dma_rx =&hdma_usart1_rx;  
	
	uart_union[U4_2322_NUM].uart_seq = U4_2322_NUM; 
	uart_union[U4_2322_NUM].init_uart =&huart4;
	uart_union[U4_2322_NUM].init_dma_rx =&hdma_uart4_rx; 
		
	uart_union[U3_4851_NUM].uart_seq = U3_4851_NUM; 
	uart_union[U3_4851_NUM].init_uart =&huart3;
  uart_union[U3_4851_NUM].init_dma_rx =&hdma_usart3_rx; 	
  uart_union[U3_4851_NUM].gpiox = GPIOD;
	uart_union[U3_4851_NUM].gpioPinx  = GPIO_PIN_10;
	
	
	uart_union[U6_4852_NUM].uart_seq = U6_4852_NUM; 
	uart_union[U6_4852_NUM].init_uart =&huart6;
	uart_union[U6_4852_NUM].init_dma_rx =&hdma_usart6_rx;
	uart_union[U6_4852_NUM].gpiox = GPIOC;
	uart_union[U6_4852_NUM].gpioPinx  = GPIO_PIN_8;
	
	uart_union[U5_4853_NUM].uart_seq = U5_4853_NUM; 
	uart_union[U5_4853_NUM].init_uart =&huart5;
	//uart_union[U5_4853_NUM].init_dma_rx =&hdma_uart5_rx;//cause Lwip fault
	uart_union[U5_4853_NUM].gpiox = GPIOD;
	uart_union[U5_4853_NUM].gpioPinx  = GPIO_PIN_3;	
	
	uart_union[U2_4854_NUM].uart_seq = U2_4854_NUM; 
	uart_union[U2_4854_NUM].init_uart =&huart2;
	uart_union[U2_4854_NUM].init_dma_rx =&hdma_usart2_rx;
	uart_union[U2_4854_NUM].gpiox = GPIOD;
	uart_union[U2_4854_NUM].gpioPinx  = GPIO_PIN_4;
	
	uart_union[U7_TTL1_NUM].uart_seq = U7_TTL1_NUM; 
	uart_union[U7_TTL1_NUM].init_uart =&huart7;
	uart_union[U7_TTL1_NUM].init_dma_rx =&hdma_uart7_rx;
	
	uart_union[U8_TTL2_NUM].uart_seq = U8_TTL2_NUM; 
	uart_union[U8_TTL2_NUM].init_uart =&huart8;
	uart_union[U8_TTL2_NUM].init_dma_rx = &hdma_uart8_rx;
	


	
	
}


void StartReception(void)
{
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_union[U1_2321_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart2, uart_union[U2_4854_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	
  if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart3, uart_union[U3_4851_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	
	
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart4, uart_union[U4_2322_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart5, uart_union[U5_4853_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart6, uart_union[U6_4852_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	
 if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart7, uart_union[U7_TTL1_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart8, uart_union[U8_TTL2_NUM].rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
}

void UserDataTreatment(UART_UNIONTypeDef * uart_uni)
{
    uint16_t i;
	  uart_uni->rx_state = 2;
  	uart_uni->rx_count = UART_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(uart_uni->init_dma_rx);	
	  HAL_UART_DMAStop(uart_uni->init_uart);    	
	 if (HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(uart_uni->init_uart, uart_uni->rx_buf, UART_BUFFER_SIZE))
  {
    Error_Handler();
  }
	
  	
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	uint8_t i;
	for(i=0;i<8;i++)
	 if(huart==uart_union[i].init_uart)
      UserDataTreatment(&uart_union[i]);

}




