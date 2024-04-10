#ifndef __NC60_COM_H
#define __NC60_COM_H
#include "main.h"
#include "gx_config.h"



enum UART_SEQ {
    U1_2321_NUM = 0x00,
    U4_2322_NUM = 0x01,
    U3_4851_NUM  = 0x02,
    U6_4852_NUM  = 0x03,
    U5_4853_NUM  = 0x04,
    U2_4854_NUM = 0x05,
    U7_TTL1_NUM = 0x06,
    U8_TTL2_NUM  = 0x07,
};


//#define U1_2321_NUM   0
//#define U4_2322_NUM   1

//#define U3_4851_NUM   2
//#define U6_4852_NUM   3
//#define U5_4853_NUM   4
//#define U2_4854_NUM   5

//#define U7_TTL1_NUM   6
//#define U8_TTL2_NUM   7



#define UART_BUFFER_SIZE  256



#pragma pack(1) 

typedef struct {
  __IO uint8_t  Code ;  	       
  __IO uint8_t  byteNums; 	       
  __IO uint16_t Addr ;           
  __IO uint16_t Num; 	           
  __IO uint16_t _CRC;       	     
  __IO uint8_t *ValueReg; 	      
  __IO uint16_t *PtrHoldingbase;  
  __IO uint16_t *PtrHoldingOffset;
}PduData_TypeDef;


typedef struct
{
	uint16_t CH1;
	uint16_t CH2;
	uint16_t CH3;
	uint16_t CH4;
	uint16_t CH5;
	uint16_t CH6;
	uint16_t CH7;
	uint16_t CH8;
	uint16_t CH9;
	uint16_t CH10;
	uint16_t CH11;
	uint16_t CH12;
	uint16_t CH13;
	uint16_t CH14;
	uint16_t CH15;
	uint16_t CH16;
	uint8_t  FLAG;
	

	uint8_t sbus_online;
  uint8_t offline_cnt; 

}SBUS_CH_Struct;




typedef struct
{
	enum UART_SEQ               uart_seq;
	UART_HandleTypeDef         *init_uart;
	DMA_HandleTypeDef          *init_dma_rx;
	DMA_HandleTypeDef          *init_dma_tx;
  uint8_t                    rx_buf[UART_BUFFER_SIZE]; 
	uint8_t                    tx_buf[UART_BUFFER_SIZE];
	
	__IO uint8_t               rx_count;
	__IO uint8_t               tx_count;
	__IO uint8_t               rx_state;
	__IO uint8_t               tx_state;
	
	__IO uint8_t               start;
	__IO uint8_t               end;
	
	GPIO_TypeDef               *gpiox;
  unsigned short             gpioPinx;  
}UART_UNIONTypeDef;


#pragma pack() 




void UART_UNION_Init(void);
void uart_tx(UART_UNIONTypeDef * uart_uni,uint8_t *Tx_Buf,uint16_t TxCount);
void uart_tx_dma(UART_UNIONTypeDef * uart_uni,uint8_t *Tx_Buf,uint16_t TxCount);
uint8_t sbus_receive_handler(void);
void StartReception(void);


extern UART_UNIONTypeDef uart_union[8];
extern SBUS_CH_Struct  sbus_info;
#endif





























