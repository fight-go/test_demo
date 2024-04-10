
#include "string.h"
#include "can.h"
#include "gx_can_frame.h"
#include "gx_aa55_frame.h"

CAN_GENERAL_10        can_general_10       = {.id = 0x10};
CAN_JOYSRICK_11       can_joystick_11      = {.id = 0x11};
CAN_HEART_12          can_heart_12         = {.id = 0x12};
CAN_FIRE_MONITOR_13   can_fire_monitor_13  = {.id = 0x13};
CAN_ENGINE_STATUS_21  can_engine_status_21 = {.id = 0x21};
CAN_ENGINE_STATUS_22  can_engine_status_22 = {.id = 0x22};
CAN_GENERAL_23        can_general_23       = {.id = 0x23};
CAN_GENERAL_24        can_general_24       = {.id = 0x24};
CAN_GENERAL_25        can_general_25       = {.id = 0x25};
CAN_BATTERY_INFO_26   can_battery_info_26  = {.id = 0x26};
CAN_WARNING_INFO_2C   can_battery_info_2C  = {.id = 0x2C};

CAN_COMMON_FRAME      can_common_frame_tx;
CAN_COMMON_FRAME      can_common_frame_rx;
static CAN_RxHeaderTypeDef   RxHeader;
static uint8_t               RxData[8];

CAN_Common_Frame_P    can_common_frame_p;

void gx_canFrame_init(void)
{
	can_common_frame_p.frame[0x10] = (uint8_t*)&can_general_10;              
	can_common_frame_p.frame[0x12] = (uint8_t*)&can_heart_12;       
	can_common_frame_p.frame[0x13] = (uint8_t*)&can_fire_monitor_13;         
	can_common_frame_p.frame[0x21] = (uint8_t*)&can_engine_status_21;               
	can_common_frame_p.frame[0x22] = (uint8_t*)&can_engine_status_22;             
	can_common_frame_p.frame[0x23] = (uint8_t*)&can_general_23;        
	can_common_frame_p.frame[0x25] = (uint8_t*)&can_general_25;        
	can_common_frame_p.frame[0x26] = (uint8_t*)&can_battery_info_26;         
	can_common_frame_p.frame[0x2C] = (uint8_t*)&can_battery_info_2C;          
}


static void cpy_frame_from_car(uint8_t id)
{
	 uint8_t *buf,i;	 
	 if(can_common_frame_p.frame[id] == NULL)return;	
   buf = (uint8_t*)&can_common_frame_rx;	
	 memcpy(can_common_frame_p.frame[id],buf,9);
}



uint8_t can_send(CAN_HandleTypeDef *canx,CAN_COMMON_FRAME *frame)
{	
	  CAN_TxHeaderTypeDef   TxHeader;
    uint32_t              TxMailbox;
	  TxHeader.StdId = frame->id;
    TxHeader.ExtId = 0x01;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = 8;
    TxHeader.TransmitGlobalTime = DISABLE;
	
    if (HAL_CAN_AddTxMessage(canx, &TxHeader, frame->byte, &TxMailbox) != HAL_OK)
    {
          Error_Handler();
    }    
    return 0;		
}


static void parse_frame_from_car(uint8_t uid)
{
	static uint8_t emergency_temp = 0;
	cpy_frame_from_car(uid);	
	switch(uid)
	{
		case 0x21:
			engine_statusInfo_frame26.Payload.throttle_percent = can_engine_status_21.bytes.throttle_percent;
		  engine_statusInfo_frame26.Payload.RPM = can_engine_status_21.bytes.RPM;
		  engine_statusInfo_frame26.Payload.fuel_level_percent = can_engine_status_21.bytes.fuel_level_percent;
		  engine_statusInfo_frame26.Payload.hydraulic_oil_temperature = can_engine_status_21.bytes.hydraulic_oil_temperature;
		  engine_statusInfo_frame26.Payload.engine_coolant_temperature = can_engine_status_21.bytes.engine_coolant_temperature;
		  car_status_info_frame27.Payload.byte2_union.byte_stru.obstacle_status = can_engine_status_21.bytes.byte_stru.obstacle_status;
		  car_status_info_frame27.Payload.byte7_union.byte_stru.one_key_trip = can_engine_status_21.bytes.byte_stru.one_key_trip;
			break;
		
		case 0x22:
      engine_statusInfo_frame26.Payload.environment_temperature = can_engine_status_22.bytes.environment_temperature;
		  engine_statusInfo_frame26.Payload.engine_working_hours     = can_engine_status_22.bytes.engine_working_hours;
		break;
				
	  case 0x23:	
			general_Sensor_frame2A.Payload.front_pump_pressure = can_general_23.bytes.front_pump_pressure;
      general_Sensor_frame2A.Payload.back_pump_pressure  = can_general_23.bytes.back_pump_pressure;
      general_Sensor_frame2A.Payload.left_wheel_speed    = can_general_23.bytes.left_wheel_speed;
      general_Sensor_frame2A.Payload.right_wheel_speed   = can_general_23.bytes.right_wheel_speed;		
			break;
	  case 0x24:	
			general_Sensor_frame2A.Payload.IR_distance         = can_general_24.bytes.IR_distance;
      general_Sensor_frame2A.Payload.IR_temperature      = can_general_24.bytes.IR_temperature;
      general_Sensor_frame2A.Payload.hydraulic_oil_pressure    = can_general_24.bytes.hydraulic_oil_pressure;
      general_Sensor_frame2A.Payload.fuel_temperature   = can_general_24.bytes.fuel_oil_temperature;		
			break;
	  case 0x25:	
			general_Sensor_frame2A.Payload.common_rail_pressure         = can_general_25.bytes.common_rail_pressure;
      general_Sensor_frame2A.Payload.wind_speed      = can_general_25.bytes.wind_speed;
      general_Sensor_frame2A.Payload.outside_temperature    = can_general_25.bytes.outside_temperature;
      general_Sensor_frame2A.Payload.outside_humidity   = can_general_25.bytes.outside_humidity;		
			break;		
		case 0x26:		
      	battery_basicinfo_frame23.Payload.battery_total_voltage = can_battery_info_26.bytes.battery_total_voltage;
        battery_basicinfo_frame23.Payload.remaining_battery_power = can_battery_info_26.bytes.remaining_battery_power;		
			break;
	}
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
    Error_Handler();
  }
	
	can_common_frame_rx.id = RxHeader.StdId;
	memcpy(can_common_frame_rx.byte,RxData,RxHeader.DLC);
	parse_frame_from_car(can_common_frame_rx.id);//两次复制可优化成一次
	

}








