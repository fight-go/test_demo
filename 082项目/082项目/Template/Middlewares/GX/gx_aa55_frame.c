#include "gx_aa55_frame.h"
#include "gx_can_frame.h"
#include "nc60_com.h"
#include "basic_tool.h"
#include <string.h>
#include "app_udp.h"
#include "gx_ctrl.h"



Heart_Frame_01                  heart_frame01;
Chassis_Speed_Frame_02          chasssis_speed_frame02;
Fire_monitor_Frame_03           fire_monitor_frame03;
Gimbal_Frame_04                 gimbal_frame04;
General_Frame_05                general_frame05;
System_Config_Frame_06          system_config_frame06;
Sbus_Forward_Frame_08           sbus_forward_frame08;


Driver_Status_Frame_21          driver_status_frame21          = {.header = 0x55AA, .length = sizeof(driver_status_frame21.Payload), .Payload.uid = 0x21};
Driver_Data_Frame_22            driver_data_frame22            = {.header = 0x55AA, .length = sizeof(driver_data_frame22.Payload), .Payload.uid = 0x22};
Battery_BasicInfo_Frame_23      battery_basicinfo_frame23      = {.header = 0x55AA, .length = sizeof(battery_basicinfo_frame23.Payload), .Payload.uid = 0x23};
Battery_Single_Voltage_Frame_24 battery_single_vlotage_frame24 = {.header = 0x55AA, .length = sizeof(battery_single_vlotage_frame24.Payload), .Payload.uid = 0x24};
Battery_Single_Temp_Frame_25    battery_single_temp_frame25    = {.header = 0x55AA, .length = sizeof(battery_single_temp_frame25.Payload), .Payload.uid = 0x25};
ENGINE_StatusInfo_Frame_26      engine_statusInfo_frame26      = {.header = 0x55AA, .length = sizeof(engine_statusInfo_frame26.Payload), .Payload.uid = 0x26};


Car_StatusInfo_Frame_27         car_status_info_frame27        = {.header = 0x55AA, .length = sizeof(car_status_info_frame27.Payload), .Payload.uid = 0x27};
GasSensor_Data_Frame_28         gassensor_data_frame28         = {.header = 0x55AA, .length = sizeof(gassensor_data_frame28.Payload), .Payload.uid = 0x28};
GasSensor_Status_Frame_29       gassensor_status_frame29       = {.header = 0x55AA, .length = sizeof(gassensor_status_frame29.Payload), .Payload.uid = 0x29};

General_Sensor_Frame_2A         general_Sensor_frame2A         = {.header = 0x55AA, .length = sizeof(general_Sensor_frame2A.Payload), .Payload.uid = 0x2A};
General_Sensor_Frame_2B         general_Sensor_frame2B         = {.header = 0x55AA, .length = sizeof(general_Sensor_frame2B.Payload), .Payload.uid = 0x2B};
Warning_Frame_2C                warning_frame2C                = {.header = 0x55AA, .length = sizeof(warning_frame2C.Payload), .Payload.uid = 0x2C};



Common_Frame rec_frame;



Common_Frame_P p_frame;

void gx_aa55Frame_init(void)
{
	p_frame.frame[0x01] = (uint8_t*)&heart_frame01;                 p_frame.len[0x01] = sizeof(Heart_Frame_01)-2;
	p_frame.frame[0x02] = (uint8_t*)&chasssis_speed_frame02;        p_frame.len[0x02] = sizeof(Chassis_Speed_Frame_02);
	p_frame.frame[0x03] = (uint8_t*)&fire_monitor_frame03;          p_frame.len[0x03] = sizeof(Fire_monitor_Frame_03);
	p_frame.frame[0x04] = (uint8_t*)&gimbal_frame04;                p_frame.len[0x04] = sizeof(Gimbal_Frame_04);
	p_frame.frame[0x05] = (uint8_t*)&general_frame05;               p_frame.len[0x05] = sizeof(General_Frame_05);
	p_frame.frame[0x06] = (uint8_t*)&system_config_frame06;         p_frame.len[0x06] = sizeof(System_Config_Frame_06);
	p_frame.frame[0x08] = (uint8_t*)&sbus_forward_frame08;          p_frame.len[0x08] = sizeof(Sbus_Forward_Frame_08);
	p_frame.frame[0x21] = (uint8_t*)&driver_status_frame21;         p_frame.len[0x21] = sizeof(Driver_Status_Frame_21);
	p_frame.frame[0x22] = (uint8_t*)&driver_data_frame22;           p_frame.len[0x22] = sizeof(Driver_Data_Frame_22);
	p_frame.frame[0x23] = (uint8_t*)&battery_basicinfo_frame23;     p_frame.len[0x23] = sizeof(Battery_BasicInfo_Frame_23);
	p_frame.frame[0x24] = (uint8_t*)&battery_single_vlotage_frame24; p_frame.len[0x24] = sizeof(Battery_Single_Voltage_Frame_24);
	p_frame.frame[0x25] = (uint8_t*)&battery_single_temp_frame25;   p_frame.len[0x25] = sizeof(Battery_Single_Temp_Frame_25);
	p_frame.frame[0x26] = (uint8_t*)&engine_statusInfo_frame26;     p_frame.len[0x26] = sizeof(engine_statusInfo_frame26);
	
	
	p_frame.frame[0x27] = (uint8_t*)&car_status_info_frame27;       p_frame.len[0x27] = sizeof(Car_StatusInfo_Frame_27);
	p_frame.frame[0x28] = (uint8_t*)&gassensor_data_frame28;        p_frame.len[0x28] = sizeof(GasSensor_Data_Frame_28);
	p_frame.frame[0x29] = (uint8_t*)&gassensor_status_frame29;      p_frame.len[0x29] = sizeof(GasSensor_Status_Frame_29);
	
  p_frame.frame[0x2A] = (uint8_t*)&general_Sensor_frame2A;        p_frame.len[0x2A] = sizeof(General_Sensor_Frame_2A);
	p_frame.frame[0x2B] = (uint8_t*)&general_Sensor_frame2B;        p_frame.len[0x2B] = sizeof(General_Sensor_Frame_2B);
	p_frame.frame[0x2C] = (uint8_t*)&warning_frame2C;               p_frame.len[0x2C] = sizeof(Warning_Frame_2C);
}






static void cpy_frame_from_remoter(uint8_t uid)
{
	 uint8_t *buf,i;	 
	 if(p_frame.frame[uid] == NULL)return;	

   if(uid!=0x08)
	 {		 
     buf = (uint8_t*)&rec_frame;
	   memcpy(p_frame.frame[uid],buf,p_frame.len[uid]);		 
		 return;
	 }
	 
	 	   for(i=1;i<88;i++)
		   if((rec_frame.Payload.byte[i] == 0x0f)&&(rec_frame.Payload.byte[i+1] == 0x00))
			 {
			     uint8_t data_check;
				    if(rec_frame.Payload.byte[i+28] == sum_check(rec_frame.Payload.byte+i+1,26))
						{
							  uint8_t *buf = (uint8_t *)&sbus_forward_frame08.Payload;
						    for(uint8_t j =0;j<26;j++)
							  buf[j] = rec_frame.Payload.byte[2+i+j];
							  memcpy(p_frame.frame[uid]+3,buf,26);
							  return;
						}			 
			 } 
}




static void parse_frame_from_remoter(uint8_t uid)
{
	static uint8_t emergency_temp = 0;
	cpy_frame_from_remoter(uid);	
	switch(uid)
	{
		case 0x01:
				heart_frame01.offline_cnt = 0;
			  heart_frame01.pc_online = 1;
			break;
		case 0x03:
				can_fire_monitor_13.byte[0] = fire_monitor_frame03.Payload.byte1_union.byte;
			  can_fire_monitor_13.byte[1] = fire_monitor_frame03.Payload.byte2_union.byte;
			break;
		
	  case 0x05:
			  car_status_info_frame27.Payload.byte1_union.byte_stru.ctrl_mode  =  general_frame05.Payload.byte1_union.byte_stru.ctrl_mode;
        car_status_info_frame27.Payload.byte2_union.byte_stru.lightning  =  general_frame05.Payload.byte2_union.byte_stru.lighting;
        car_status_info_frame27.Payload.byte2_union.byte_stru.spraying  =  general_frame05.Payload.byte2_union.byte_stru.spraying;
        car_status_info_frame27.Payload.byte2_union.byte_stru.warning  =  general_frame05.Payload.byte2_union.byte_stru.warning;
        car_status_info_frame27.Payload.byte2_union.byte_stru.obstacle_switch  =  general_frame05.Payload.byte2_union.byte_stru.obstacle_switch;
		   
		
		
     		can_general_10.byte_stru.byte0.lightning = general_frame05.Payload.byte2_union.byte_stru.lighting;
        can_general_10.byte_stru.byte0.spraying = general_frame05.Payload.byte2_union.byte_stru.spraying;	
        can_general_10.byte_stru.byte0.warning = general_frame05.Payload.byte2_union.byte_stru.warning;
        can_general_10.byte_stru.byte0.obstacle = general_frame05.Payload.byte2_union.byte_stru.obstacle_switch;	
        can_general_10.byte_stru.byte0.emergency_stop = 	car_data.Ctrl_SwitchInfo.emergency_stop;
        can_general_10.byte_stru.byte0.stop    = general_frame05.Payload.byte2_union.byte_stru.stop; 	
        car_status_info_frame27.Payload.byte3_union.byte_stru.speed_mode  =general_frame05.Payload.byte3_union.byte_stru.speed_mode;
		    car_status_info_frame27.Payload.byte4_union.byte_stru.generator_switch = general_frame05.Payload.byte4_union.byte_stru.generator_switch;
		    car_status_info_frame27.Payload.byte4_union.byte_stru.generator_enabled  =general_frame05.Payload.byte4_union.byte_stru.generator_enabled;
        can_general_10.byte_stru.byte1.middle_speed = (general_frame05.Payload.byte3_union.byte_stru.speed_mode == 1);
        can_general_10.byte_stru.byte1.high_speed =   (general_frame05.Payload.byte3_union.byte_stru.speed_mode == 2);  
        //can_general_10.byte_stru.byte1.move_enable =  general_frame05.Payload.byte4_union.byte_stru.move_enable;
		    can_general_10.byte_stru.byte1.hose_detachment = general_frame05.Payload.byte8_union.byte_stru.oneKeyTrip;


//		    can_general_10.byte_stru.byte1.warn_low    = 
//		    can_general_10.byte_stru.byte1.warn_middle = 
//		    can_general_10.byte_stru.byte1.warn_high   =
//		    can_general_10.byte_stru.byte1.action_self_lock
		
		    can_general_10.byte[2] =  general_frame05.Payload.byte4_union.byte;
		    //can_general_10.byte_stru.byte3.winch_in
		    //can_general_10.byte_stru.byte3.winch_out
		    can_general_10.byte_stru.byte3.hose1_detachment = general_frame05.Payload.byte5_union.byte_stru.hose1_detachment;
				can_general_10.byte_stru.byte3.hose2_detachment = general_frame05.Payload.byte5_union.byte_stru.hose2_detachment;
				can_general_10.byte_stru.byte3.hose3_detachment = general_frame05.Payload.byte5_union.byte_stru.hose3_detachment;
				can_general_10.byte_stru.byte3.hose4_detachment = general_frame05.Payload.byte5_union.byte_stru.hose4_detachment;
				can_general_10.byte_stru.byte3.hose5_detachment = general_frame05.Payload.byte5_union.byte_stru.hose5_detachment;
				can_general_10.byte_stru.byte3.hose6_detachment = general_frame05.Payload.byte5_union.byte_stru.hose6_detachment;
				
				can_general_10.byte[4] = general_frame05.Payload.byte6_union.byte ;
								can_general_10.byte_stru.byte4.hydraulic_pressure_negetive = general_frame05.Payload.byte9_union.byte_stru.hydraulic_pressure_negetive;
								can_general_10.byte_stru.byte4.hydraulic_pressure_positive = general_frame05.Payload.byte9_union.byte_stru.hydraulic_pressure_positive;
				can_general_10.byte[5] = general_frame05.Payload.byte7_union.byte;
				
		
			break;	
			
		case 0x06:			  
       can_heart_12.bytes.obstacle_avoidance_distance = system_config_frame06.Payload.obstacle_avoidance_distance;
		   can_heart_12.bytes.byte_stru.communicationSta_remoter_mcu = heart_frame01.pc_online;
			break;	
			
			
			
		case 0x08:			  
			  if((emergency_temp ==2)&&(sbus_forward_frame08.Payload.f10_emergency_stop==0))
					car_data.Ctrl_SwitchInfo.emergency_stop = !car_data.Ctrl_SwitchInfo.emergency_stop;
			    emergency_temp  = sbus_forward_frame08.Payload.f10_emergency_stop;	
          can_joystick_11.byte_stru.left_x  =  sbus_forward_frame08.Payload.left_x/8+1;
				  can_joystick_11.byte_stru.right_x  =  sbus_forward_frame08.Payload.right_x/8+1;
				  can_joystick_11.byte_stru.left_y  =  sbus_forward_frame08.Payload.left_y/8+1;
				  can_joystick_11.byte_stru.right_y  =  sbus_forward_frame08.Payload.right_y/8+1;
		
			break;
	}
}

static uint8_t check_frame(uint8_t* rx_buf,uint8_t len)
{
	
   uint16_t data_check;
   uint8_t i,j;
	 Common_Frame *rec_frame_p;
	 uint8_t *buf;
#if AA55_CRC == 0	
	 for(i=0;i<len;i++)
	{
	 if((rx_buf[i]<<8)+(rx_buf[i+1]) == 0xAA55)	
	 {
	   rec_frame_p  =  (Common_Frame*)&rx_buf[i];	
     data_check   =   xor_check(rx_buf+i+2,rx_buf[i+2]+1); 	
		 if(data_check == rx_buf[rec_frame_p->length+3+i])	
		 {   
			   buf = (uint8_t*)&rec_frame;	
				 for(j=0;j<rec_frame_p->length+4+AA55_CRC;j++)//异或+4  CRC+5
				 buf[j] = rx_buf[i+j];	 
			   parse_frame_from_remoter(rec_frame_p->Payload.uid);	
		 }		      		 
	 }
  }
#endif
	
#if AA55_CRC == 1	
	 for(i=0;i<len;i++)
	{
	 if((rx_buf[i]<<8)+(rx_buf[i+1]) == 0xAA55)	
	 {
	   rec_frame_p  =  (Common_Frame*)&rx_buf[i];	
     data_check   =   crc16_check(rx_buf+i+2,rx_buf[i+2]+1); 	
		 if(data_check == rx_buf[rec_frame_p->length+3+i]+(rx_buf[rec_frame_p->length+4+i]<<8))	
		 {   
			   buf = (uint8_t*)&rec_frame;	
				 for(j=0;j<rec_frame_p->length+4+AA55_CRC;j++)
				 buf[j] = rx_buf[i+j];	 
	       cpy_frame_from_remoter(rec_frame_p->Payload.uid);	
			   parse_frame();
		 }		      		 
	 }
  }
#endif		
}

void gx_send_frame(uint8_t uid) 
{
   static uint8_t gx_chn =U1_2321_NUM;
	 uint16_t crc_check;
	 if(p_frame.frame[uid] == NULL)return;
	
#if AA55_PORT_TYPE == UART	
	#if AA55_CRC == 1
		 crc_check = crc16_check(frame[uid]+2, p_frame.frame[uid][2]+1); 
		 p_frame.frame[uid][p_frame.frame[uid][2]+3] = crc_check;
		 p_frame.frame[uid][p_frame.frame[uid][2]+4] = crc_check>>8;
		 uart_tx(&uart_union[gx_chn], p_frame.frame[uid],p_frame.frame[uid][2]+5);	
	#endif
		 
	#if AA55_CRC == 0	
		 crc_check = xor_check(p_frame.frame[uid]+2, p_frame.frame[uid][2]+1); 
		 p_frame.frame[uid][p_frame.frame[uid][2]+3] = crc_check;
		 uart_tx_dma(&uart_union[gx_chn], p_frame.frame[uid],p_frame.frame[uid][2]+4);	
	#endif
#endif

#if AA55_PORT_TYPE == UDP	
	#if AA55_CRC == 1
		 crc_check = crc16_check(frame[uid]+2, p_frame.frame[uid][2]+1); 
		 p_frame.frame[uid][p_frame.frame[uid][2]+3] = crc_check;
		 p_frame.frame[uid][p_frame.frame[uid][2]+4] = crc_check>>8;
		 gx_udp_send(p_frame.frame[uid],p_frame.frame[uid][2]+5);	
	#endif
		 
	#if AA55_CRC == 0	
		 crc_check = xor_check(p_frame.frame[uid]+2, p_frame.frame[uid][2]+1); 
		 p_frame.frame[uid][p_frame.frame[uid][2]+3] = crc_check; 
		 gx_udp_send(p_frame.frame[uid],p_frame.frame[uid][2]+4);	
	#endif	  		
#endif

}


uint8_t gx_aa55_receive_handler(uint8_t* rx_buf,uint8_t len)
{
  check_frame(rx_buf,len);
}





