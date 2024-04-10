#ifndef __GX_CAN_TYPEDEF_H
#define __GX_CAN_TYPEDEF_H

#include "main.h"
#pragma anon_unions
#pragma pack(1) 

typedef struct {
    uint8_t id; 

		union{
			struct
			{
			struct {
						uint8_t lightning : 1;
						uint8_t spraying : 1;
						uint8_t warning : 1;
						uint8_t obstacle : 1;
						uint8_t emergency_stop : 1;   
						uint8_t stop : 1;  
						uint8_t obstacle_status : 1;
				    uint8_t high_pitched_horn:1;
				}byte0;	

			struct {
						uint8_t middle_speed : 1;
						uint8_t high_speed : 1;
						uint8_t move_enable : 1;
						uint8_t hose_detachment : 1;
						uint8_t warn_low : 1;   
						uint8_t warn_middle : 1;  
						uint8_t warn_high : 1;
				uint8_t action_self_lock:1;
				} byte1;	

			struct {
						uint8_t lightning_mode : 1;
						uint8_t spraying_mode : 1;
						uint8_t gas_switch : 1;
						uint8_t driver_reset : 1;
						uint8_t motor_sync : 1;   
						uint8_t buzzer_switch : 1;  
						uint8_t generator_switch : 1;
			    	uint8_t generator_enabled:1;
				} byte2;	
				
				
				struct {
						uint8_t winch_in : 1;
						uint8_t winch_out : 1;
						uint8_t hose1_detachment : 1;
						uint8_t hose2_detachment : 1;
						uint8_t hose3_detachment : 1;   
						uint8_t hose4_detachment : 1;  
						uint8_t hose5_detachment : 1;
					uint8_t hose6_detachment :1;
				} byte3;	
		

				struct {
						uint8_t engine_start : 1;
						uint8_t engine_stop : 1;
						uint8_t throttle_increase : 1;
					  uint8_t throttle_reduce : 1;
					  uint8_t fan_speed_increase :1;
					  uint8_t fan_speed_reduce  :1;
						uint8_t hydraulic_pressure_positive : 1;
					  uint8_t hydraulic_pressure_negetive :1;
				} byte4;				
				
				struct {
						uint8_t fan_up : 1;
						uint8_t fan_down : 1;
						uint8_t fan_forward : 1;
					  uint8_t fan_reverse : 1;
					  uint8_t arm_raise :1;
					  uint8_t arm_lower  :1;
						uint8_t blade_raise : 1;
					  uint8_t blade_lower : 1;
				} byte5;	
			
			   uint8_t reserved[2];
				}byte_stru;
			uint8_t byte[8];
			};
	

			
	
} CAN_GENERAL_10;



typedef struct 
{
   uint8_t id;
	union{
		struct
		{
	   uint8_t left_y;
	   uint8_t left_x;
	   uint8_t right_y;
	   uint8_t right_x;
	   uint8_t reserved[4];
		}byte_stru;
		uint8_t byte[8];
	};
}CAN_JOYSRICK_11;

typedef struct
{
    uint8_t id;
	  union
		{
			struct
			{
		   uint16_t obstacle_avoidance_distance;
			 union
			 {
				 struct
				 {
			     uint8_t communicationSta_remoter_mcu:1;
				   uint8_t communicationSta_remoter_energeremoter:1;
				   uint8_t reserved :6;
				 }byte_stru;
				 uint8_t byte2;
			 };
			  uint8_t reserved[4];
		  }bytes;
			uint8_t byte[8];
	};
}CAN_HEART_12;


typedef struct {
    uint8_t id;
    union {
        struct {
            union {
                struct {
                    uint8_t up : 1;
                    uint8_t down : 1;
                    uint8_t left : 1;
                    uint8_t right : 1;
                    uint8_t dc : 1;
                    uint8_t atomize : 1;
                    uint8_t self_wave_start : 1;
                    uint8_t self_wave_stop : 1;
                } byte_stru;
                uint8_t byte0;
            };
        } bytes;
        uint8_t byte[8];
    };
}CAN_FIRE_MONITOR_13;


typedef struct {
    uint8_t id;
    union {
        struct {
             uint8_t throttle_percent;
					   uint16_t RPM;
					   uint8_t fuel_level_percent;
					   uint8_t hydraulic_oil_temperature;
					   uint16_t engine_coolant_temperature;
					
					   union {
                struct {
                    uint8_t obstacle_status : 1;
                    uint8_t one_key_trip : 1;
                    uint8_t reserved : 6;
                } byte_stru;
                uint8_t byte7;
            };															
        } bytes;
        uint8_t byte[8];
    };
}CAN_ENGINE_STATUS_21;



typedef struct {
    uint8_t id;
    union {
        struct {
             uint16_t environment_temperature;
					   uint32_t engine_working_hours;
             uint8_t  reserved[2];
																			
        } bytes;
        uint8_t byte[8];
    };
}CAN_ENGINE_STATUS_22;


typedef struct {
    uint8_t id;
    union {
        struct {
            uint16_t front_pump_pressure; 
			      uint16_t back_pump_pressure; 
			      uint16_t left_wheel_speed; 
			      uint16_t right_wheel_speed;
																			
        } bytes;
        uint8_t byte[8];
    };
}CAN_GENERAL_23;



typedef struct {
    uint8_t id;
    union {
        struct {
            uint16_t IR_distance; 
			      uint16_t IR_temperature;//啥温度 
			      uint16_t hydraulic_oil_pressure; 
			      uint16_t fuel_oil_temperature;
																			
        } bytes;
        uint8_t byte[8];
    };
}CAN_GENERAL_24;


typedef struct {
    uint8_t id;
    union {
        struct {
            uint16_t common_rail_pressure; 
			      uint16_t wind_speed;
            uint16_t outside_temperature;		
            uint16_t outside_humidity;
																			
        } bytes;
        uint8_t byte[8];
    };
}CAN_GENERAL_25;

typedef struct {
    uint8_t id;
    union {
        struct {
            uint16_t battery_total_voltage; 
			      uint16_t remaining_battery_power;
            uint8_t reserved[4];
																			
        } bytes;
        uint8_t byte[8];
    };
}CAN_BATTERY_INFO_26;

typedef struct {
    uint8_t id;
    union {
        struct {
            union {
                struct {
                    uint8_t High_Concentration_of_Combustible_Gas : 1;
                    uint8_t system_voltage_low : 1;
                    uint8_t system_voltage_high : 1;
									  uint8_t reserved : 2;
									  uint8_t environment_temperature_high :1;
									  uint8_t fuel_oil_level_low :1;
								  	uint8_t emergency_warning :1;
                } byte_stru0;
                uint8_t byte0;
            };

            union {
                struct {
                    uint8_t engine_fault : 1;
                    uint8_t reserved1 : 1;
                    uint8_t Low_oil_pressure : 1;
									  uint8_t High_engine_coolant_temperature : 1;
									  uint8_t reserved4 :1;
					          uint8_t Oil_suction_filter_blockage : 1;
						        uint8_t Return_oil_filter_blockage : 1;
					          uint8_t Air_filter_blockage : 1;
                } byte_stru1;
                uint8_t byte1;
            };
          uint8_t reserved[6];
						
        } bytes;		      
          
				uint8_t byte[8];															
        };
        
    }CAN_WARNING_INFO_2C;

		
		
typedef struct 
{
  uint8_t id;
	uint8_t byte[8];
	uint8_t len;
}CAN_COMMON_FRAME;	

typedef struct {//索引
    uint8_t *frame[0x30];			
}CAN_Common_Frame_P;
		
#pragma pack() 













#endif