#ifndef __GX_CTRL_H
#define __GX_CTRL_H



#include "gx_aa55_frame.h"


typedef  struct{
	struct{
	   int16_t joystick_x;
	   int16_t joystick_y;
     float amplitude;		
		 float angle;		   		
	}fire_monitor;
	struct{
	   int16_t joystick_x;
	   int16_t joystick_y;
     float amplitude;		
		 float angle;				
	}move_ctrl;
	uint8_t dc;
	uint8_t atomization;
	uint8_t brake;
	uint8_t enable;
}A10_TYPEDEF;

typedef struct{
	struct{
	      int16_t left_speed;
	      int16_t right_speed;
		    int16_t linear_velocity;
		    int16_t angular_velocity;
	}Ctrl_DriveInfo;
	
	struct{
	      int16_t left_speed;
	      int16_t right_speed;
		    int16_t linear_velocity;
		    int16_t angular_velocity;
	}FeedBack_DriveInfo;
	
		struct{
	      uint8_t up;
	      uint8_t down;
		    uint8_t left;
		    uint8_t right;
	      uint8_t horizontal_speed;
		    uint8_t vertical_speed;
	}Ctrl_FireMonitorInfo;
			struct{
	      uint8_t up;
	      uint8_t down;
		    uint8_t left;
		    uint8_t right;
	      uint8_t horizontal_speed;
		    uint8_t vertical_speed;
	}FeedBack_FireMonitorInfo;
		
	struct{
				    uint8_t gimbal_up;
			      uint8_t gimbal_down;
			      uint8_t lightning;
			      uint8_t fire_monitor_selfwave;
			      uint8_t driver_reset;
			      uint8_t avoid_switch;
			      uint8_t reserve;
			      uint8_t warn_led;
			      uint8_t dewatering_belt;
			      uint8_t emergency_stop;
			
			
			      uint8_t gas_switch;
			      uint8_t mode_switch;
			      uint8_t spraying_switch;
			      uint8_t brake_switch;
	}Ctrl_SwitchInfo;	
	
		struct{
				    uint8_t gimbal_up;
			      uint8_t gimbal_down;
			      uint8_t lightning;
			      uint8_t fire_monitor_selfwave;
			      uint8_t driver_reset;
			      uint8_t avoid_switch;
			      uint8_t reserve;
			      uint8_t warn_led;
			      uint8_t dewatering_belt;
			      uint8_t emergency_stop;
			
			
			      uint8_t gas_switch;
			      uint8_t mode_switch;
			      uint8_t spraying_switch;
			      uint8_t brake_switch;
	}FeedBack_SwitchInfo;	

	
}CAR_DATA;




extern A10_TYPEDEF a10_data;
extern CAR_DATA   car_data;


void parse_a10_sbus(void);



#endif


