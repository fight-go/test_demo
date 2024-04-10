#include "main.h"
#include "gx_config.h"



SBUS_CH_Struct  sbus_info;


uint8_t sbus_receive_handler(void)
{	
	UART_UNIONTypeDef * uart_uni;
	uart_uni = &uart_union[SBUS_REMOTER_COM];
			if (uart_uni->rx_state == 2)
    {	
			if ((uart_uni->rx_buf[23] == 0)&&(uart_uni->rx_buf[0] == 0x0f)&&(uart_uni->rx_count == 25))
			{
				sbus_info.offline_cnt  = 0;
        sbus_info.sbus_online = 1;
        sbus_info.CH1  = ((int16_t)uart_uni->rx_buf[ 1] >> 0 | ((int16_t)uart_uni->rx_buf[ 2] << 8 )) & 0x07FF;
        sbus_info.CH2  = ((int16_t)uart_uni->rx_buf[ 2] >> 3 | ((int16_t)uart_uni->rx_buf[ 3] << 5 )) & 0x07FF;
        sbus_info.CH3  = ((int16_t)uart_uni->rx_buf[ 3] >> 6 | ((int16_t)uart_uni->rx_buf[ 4] << 2 ) | (int16_t)uart_uni->rx_buf[ 5] << 10 ) & 0x07FF;
        sbus_info.CH4  = ((int16_t)uart_uni->rx_buf[ 5] >> 1 | ((int16_t)uart_uni->rx_buf[ 6] << 7 )) & 0x07FF;
        sbus_info.CH5  = ((int16_t)uart_uni->rx_buf[ 6] >> 4 | ((int16_t)uart_uni->rx_buf[ 7] << 4 )) & 0x07FF;
        sbus_info.CH6  = ((int16_t)uart_uni->rx_buf[ 7] >> 7 | ((int16_t)uart_uni->rx_buf[ 8] << 1 ) | (int16_t)uart_uni->rx_buf[9] << 9 ) & 0x07FF;
        sbus_info.CH7  = ((int16_t)uart_uni->rx_buf[ 9] >> 2 | ((int16_t)uart_uni->rx_buf[10] << 6 )) & 0x07FF;
        sbus_info.CH8  = ((int16_t)uart_uni->rx_buf[10] >> 5 | ((int16_t)uart_uni->rx_buf[11] << 3 )) & 0x07FF;
        sbus_info.CH9  = ((int16_t)uart_uni->rx_buf[12] << 0 | ((int16_t)uart_uni->rx_buf[13] << 8 )) & 0x07FF;
        sbus_info.CH10 = ((int16_t)uart_uni->rx_buf[13] >> 3 | ((int16_t)uart_uni->rx_buf[14] << 5 )) & 0x07FF;
        sbus_info.CH11 = ((int16_t)uart_uni->rx_buf[14] >> 6 | ((int16_t)uart_uni->rx_buf[15] << 2 ) | (int16_t)uart_uni->rx_buf[16] << 10 ) & 0x07FF;
        sbus_info.CH12 = ((int16_t)uart_uni->rx_buf[16] >> 1 | ((int16_t)uart_uni->rx_buf[17] << 7 )) & 0x07FF;
        sbus_info.CH13 = ((int16_t)uart_uni->rx_buf[17] >> 4 | ((int16_t)uart_uni->rx_buf[18] << 4 )) & 0x07FF;
        sbus_info.CH14 = ((int16_t)uart_uni->rx_buf[18] >> 7 | ((int16_t)uart_uni->rx_buf[19] << 1 ) | (int16_t)uart_uni->rx_buf[20] << 9 ) & 0x07FF;
        sbus_info.CH15 = ((int16_t)uart_uni->rx_buf[20] >> 2 | ((int16_t)uart_uni->rx_buf[21] << 6 )) & 0x07FF;
        sbus_info.CH16 = ((int16_t)uart_uni->rx_buf[21] >> 5 | ((int16_t)uart_uni->rx_buf[22] << 3 )) & 0x07FF;
			  uart_uni->rx_state = 0;
			  uart_uni->rx_count = 0;		
        uart_uni->rx_buf[0] = 0x00;				
        return 1;
			}
			else
			{
				sbus_info.offline_cnt =  (sbus_info.offline_cnt++>100)?100:sbus_info.offline_cnt;
				sbus_info.sbus_online = sbus_info.offline_cnt<50;
				uart_uni->rx_state = 0;
			  uart_uni->rx_count = 0;
				return 2;
			}
				
    }
    else 
    {  
  			sbus_info.offline_cnt =  (sbus_info.offline_cnt++>100)?100:sbus_info.offline_cnt;
				sbus_info.sbus_online = sbus_info.offline_cnt<50;     
        return 0;
    }


}















