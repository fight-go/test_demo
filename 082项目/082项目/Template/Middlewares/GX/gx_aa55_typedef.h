#ifndef _GX_AA55_TYPEDEF_H
#define _GX_AA55_TYPEDEF_H

#include "gx_config.h"


#include "main.h"






#pragma pack(1) 



typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				uint8_t uid;
				uint16_t device_num; 
				uint16_t version; 
				uint8_t lock_flag; 
		}Payload;
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif
		uint8_t pc_online;
    uint8_t offline_cnt;
} Heart_Frame_01;


typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				uint8_t uid;
				int32_t linear_velocity; 
				int32_t angular_velocity; 
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif
		int16_t l_speed;
		int16_t r_speed;

} Chassis_Speed_Frame_02;


typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				uint8_t uid;

			union{
			struct {
						uint8_t up : 1;
						uint8_t down : 1;
						uint8_t left : 1;
						uint8_t right : 1;
						uint8_t dc : 1;   
						uint8_t atomize : 1;  
						uint8_t reserved : 2;
				} byte_stru;
			 uint8_t byte;
			}byte1_union;
       union{
				struct {
						uint8_t return_origin : 1;
						uint8_t self_balance : 1;
						uint8_t stop : 1;
						uint8_t restart : 1;
						uint8_t reserved : 4;
				} byte_stru;
				uint8_t byte;
			}byte2_union;

				uint8_t byte3_reserved;
        uint8_t byte4_reserved;

				uint8_t byte5_horizontal_speed;  
				uint8_t byte6_vertical_speed;    

				uint8_t byte7_reserved; 
				uint8_t byte8_reserved;  
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

} Fire_monitor_Frame_03;



typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				uint8_t uid;
        union{
				struct {
						uint8_t up : 1;
						uint8_t down : 1;
						uint8_t left : 1;
						uint8_t right : 1;
						uint8_t zoom_in : 1;   
						uint8_t zoom_out : 1;  
						uint8_t reserved : 2;
				} byte_stru;
				uint8_t byte;
			}byte1_union;
        union{
				struct {
						uint8_t return_origin : 1;
						uint8_t fill_light_switch : 1;
						uint8_t windshield_wiper_switch : 1;
						uint8_t lift_pole_up : 1;
						uint8_t lift_pole_down : 1;
						uint8_t reserved : 3;
				} byte_stru;
				uint8_t byte;
			}byte2_union;

				uint8_t byte3_reserved;
       union{
				struct {
						uint8_t reserved  : 6;
						uint8_t stop      : 1;
						uint8_t restart   : 1;
				} byte_stru;
				uint8_t byte;
			}byte4_union;

				uint8_t byte5_horizontal_speed;  
				uint8_t byte6_vertical_speed;    

				uint8_t reserved[2]; 
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

} Gimbal_Frame_04;



typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				uint8_t uid;
        union{
				struct {
						uint8_t ctrl_mode : 2;//bit0~bit1: 0-UDP; 1-SBUS  2-��λ��
  					uint8_t reserved : 6;
				} byte_stru;
				uint8_t byte;
			}byte1_union;
        union{
				struct {
						uint8_t lighting : 1;
						uint8_t spraying : 1;
						uint8_t warning : 1;
						uint8_t obstacle_switch  : 1;
						uint8_t stop : 1;
						uint8_t emergency_stop : 1;
						uint8_t reserved : 2;

				} byte_stru;
				  uint8_t byte;
			}byte2_union;
       union{
				struct {
						uint8_t speed_mode : 2;
						uint8_t fog_water_mode : 2;
						uint8_t listen : 1;
						uint8_t shout : 1;
						uint8_t reserved : 2;
				} byte_stru;
				uint8_t byte;
			}byte3_union;
        union{
				struct {
						uint8_t lightning_mode : 1;
						uint8_t spraying_mode : 1;
						uint8_t gas_switch : 1;
						uint8_t driver_reset : 1;
						uint8_t motor_sync : 1;
						uint8_t buzzer_switch      : 1;
						uint8_t generator_switch   : 1;
					  uint8_t generator_enabled :1;
				}byte_stru;
				uint8_t byte;
			}byte4_union;
        union{
				struct {
						
					uint8_t hose1_detachment : 1;
					uint8_t hose2_detachment : 1;
					uint8_t hose3_detachment : 1;
					uint8_t hose4_detachment : 1;
					uint8_t hose5_detachment : 1;
					uint8_t hose6_detachment : 1;
					uint8_t hose7_detachment : 1;
					uint8_t hose8_detachment : 1;
				} byte_stru; 
				uint8_t byte;
			}byte5_union;
			union{
				struct {
						uint8_t engine_start : 1;
						uint8_t engine_stop : 1;
						uint8_t throttle_increase : 1;
					  uint8_t throttle_reduce : 1;
					  uint8_t fan_speed_increase :1;
					  uint8_t fan_speed_reduce  :1;
						uint8_t reserved : 2;

				} byte_stru; 
				uint8_t byte;
			}byte6_union;    

							union{
				struct {
						uint8_t fan_up : 1;
						uint8_t fan_down : 1;
						uint8_t fan_forward : 1;
					  uint8_t fan_reverse : 1;
					  uint8_t arm_raise :1;
					  uint8_t arm_lower  :1;
						uint8_t blade_raise : 1;
					  uint8_t blade_lower : 1;

				} byte_stru; 
				uint8_t byte;
			}byte7_union;  
							
				union{
				struct {
						uint8_t custom1 : 1;
						uint8_t custom2 : 1;
						uint8_t custom3 : 1;
					  uint8_t custom4 : 1;
					  uint8_t oneKeyTrip : 1;//
					  uint8_t custom6 : 1;
						uint8_t custom7 : 1;
					  uint8_t high_pitched_horn : 1;

				} byte_stru; 
				uint8_t byte;
			}byte8_union;  
			
			
				union{
				struct {
						uint8_t custom9  : 1;
						uint8_t custom10 : 1;
						uint8_t hydraulic_pressure_positive : 1;
					  uint8_t hydraulic_pressure_negetive : 1;
					  uint8_t custom13 : 1;
					  uint8_t custom14 : 1;
						uint8_t custom15 : 1;
					  uint8_t custom16 : 1;

				} byte_stru; 
				uint8_t byte;
			}byte9_union;  
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

} General_Frame_05;




typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
		      	uint16_t reserved[5];
						uint16_t obstacle_avoidance_distance ;
						
 
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

} System_Config_Frame_06;



typedef struct {
    uint16_t header; 
    uint8_t  length;   

	
	
	
		struct {
            int16_t right_x;
			      int16_t left_y;
			      int16_t right_y;
			      int16_t left_x;
			      uint8_t f1_gimbal_up;
			      uint8_t f2_gimbal_down;
			      uint8_t f3_lightning;
			      uint8_t f4_fire_monitor_selfwave;
			      uint8_t f5_driver_reset;
			      uint8_t f6_avoid_switch;
			      uint8_t f7;
			      uint8_t f8_warn_led;
			      uint8_t f9_dewatering_belt;
			      uint8_t f10_emergency_stop;
			
			
			      uint8_t A_gas_switch;
			      uint8_t B_mode_switch;
			      uint8_t C_spraying_switch;
			      uint8_t D_brake_switch;
			      uint8_t led_sta[2];
			      uint8_t reserve[2];
			      
			      

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

} Sbus_Forward_Frame_08;





typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				uint8_t uid;
        union{
				struct {
						uint8_t offline : 1;
						uint8_t over_current : 1;
						uint8_t over_voltage : 1;
						uint8_t under_voltage : 1;
						uint8_t over_heating : 1;   
						uint8_t reserved5 : 1;
						uint8_t reserved6 : 1;
						uint8_t reserved7 : 1;
				} byte_stru;
				uint8_t byte;
			}byte1_union;
				union{
				struct {
						uint8_t offline : 1;
						uint8_t over_current : 1;
						uint8_t over_voltage : 1;
						uint8_t under_voltage : 1;
						uint8_t over_heating : 1;   
						uint8_t reserved5 : 1;
						uint8_t reserved6 : 1;
						uint8_t reserved7 : 1;
				} byte_stru;
				uint8_t byte;
			}byte2_union;   
        union{
				struct {
						uint8_t offline : 1;
						uint8_t over_current : 1;
						uint8_t over_voltage : 1;
						uint8_t under_voltage : 1;
						uint8_t over_heating : 1;   
						uint8_t reserved5 : 1;
						uint8_t reserved6 : 1;
						uint8_t reserved7 : 1;
				} byte_stru;
				uint8_t byte;
			}byte3_union;
              union{
				struct {
						uint8_t offline : 1;
						uint8_t over_current : 1;
						uint8_t over_voltage : 1;
						uint8_t under_voltage : 1;
						uint8_t over_heating : 1;   
						uint8_t reserved5 : 1;
						uint8_t reserved6 : 1;
						uint8_t reserved7 : 1;
				} byte_stru;
				uint8_t byte;
			}byte4_union;  

				uint8_t reserved[4];    
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif
		uint8_t left_offline_cnt;
		uint8_t right_offline_cnt;

} Driver_Status_Frame_21;


typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            int16_t running_speed;
			      int16_t steering_speed;
				    int16_t driver1_speed;
			      int16_t driver2_speed;
            int16_t driver3_speed;
			      int16_t driver4_speed;
			int32_t left_wheel_distance;
			int32_t left_right_distance;
			

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}Driver_Data_Frame_22;

typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint16_t battery_total_voltage;
			      uint16_t battery_total_current;
				    uint16_t  remaining_battery_power;
				    uint8_t reserved[2]; 


		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif
    uint8_t  battery_offline_cnt;
		uint8_t  battery_offline;
}Battery_BasicInfo_Frame_23;




typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint16_t battery_single_voltage[BATTERY_NUMS];

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}Battery_Single_Voltage_Frame_24;

typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint8_t battery_single_temperature[BATTERY_NUMS];

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}Battery_Single_Temp_Frame_25;



typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint16_t throttle_percent;
            uint16_t RPM;
			      uint16_t fuel_level_percent;
			      uint8_t hydraulic_oil_temperature;
			      uint16_t engine_coolant_temperature;
			      uint16_t environment_temperature;
			      uint32_t engine_working_hours;

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}ENGINE_StatusInfo_Frame_26;


typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
       union{
				struct {
						uint8_t ctrl_mode : 2;   
						uint8_t lock_flag : 1;
					  uint8_t reserved  : 5;
				} byte_stru;
				uint8_t byte;
			}byte1_union;
			   union{
				struct {
						uint8_t lightning : 1;   
					uint8_t spraying : 1;   
					uint8_t warning : 1;   
					uint8_t obstacle_switch  : 1;   
					uint8_t emergnecy_stop : 1;   
					uint8_t stop : 1;   
					uint8_t obstacle_status : 1;   

				} byte_stru;
				uint8_t byte;
			}byte2_union;
				 
			   union{
				struct {
					uint8_t speed_mode : 2;   
					uint8_t fog_water_switch : 2;   
					uint8_t warning_sound : 2;   
					uint8_t reserved : 2;   
				} byte_stru;
				uint8_t byte;
			}byte3_union;
				 
			
			  union{
				struct {
					uint8_t lightning_mode  : 1;   
					uint8_t spraying_mode : 1;
					uint8_t gas_switch:1;
					uint8_t driver_reset :1;
					uint8_t motor_sync:1;
					uint8_t buzzer_switch:1;
					uint8_t generator_switch:1;
					uint8_t generator_enabled:1;

				} byte_stru;
				uint8_t byte;
			}byte4_union;
				
			
			
			
			
				union{
				struct{
					uint8_t hose1_detachment : 1;
					uint8_t hose2_detachment : 1;
					uint8_t hose3_detachment : 1;
					uint8_t hose4_detachment : 1;
					uint8_t hose5_detachment : 1;
					uint8_t hose6_detachment : 1;
					uint8_t hose7_detachment : 1;
					uint8_t hose8_detachment : 1;
				} byte_stru;
				uint8_t byte;
			}byte5_union;
				
				union{
				struct {
						uint8_t  fan_forward:  1;
					  uint8_t  fan_reverse:  1;
					  uint8_t  reserved:6;

				} byte_stru;
				uint8_t byte;
			}byte6_union;
				
			union{
				struct {
						uint8_t custom1 : 1;
						uint8_t custom2 : 1;
						uint8_t custom3 : 1;
					  uint8_t custom4 : 1;
					  uint8_t custom5 : 1;
					  uint8_t one_key_trip : 1;// 一键脱扣
						uint8_t custom7 : 1;
					  uint8_t custom8 : 1;
				} byte_stru;
				uint8_t byte;
			}byte7_union;
			union{
					struct {
						uint8_t custom9 : 1;
						uint8_t custom10 : 1;
						uint8_t custom11: 1;//液压正向
					  uint8_t custom12 : 1;//液压反向
					  uint8_t custom13 : 1;
					  uint8_t custom14 :1;
						uint8_t custom15 : 1;
					  uint8_t custom16 : 1;
				} byte_stru;
				uint8_t byte;
			}byte8_union;
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}Car_StatusInfo_Frame_27;




typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint16_t gas_single[GASSENSOR_NUMS];

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}GasSensor_Data_Frame_28;



typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
			union{
            struct {
                uint8_t gas_sta : 2;  // 2-bit gas status
           } gas_status[GASSENSOR_NUMS];
						uint8_t byte[GASSENSOR_NUMS/4+1];
				 }array_union; 

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}GasSensor_Status_Frame_29;


typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint16_t front_pump_pressure; 
			      uint16_t back_pump_pressure; 
			      uint16_t left_wheel_speed; 
			      uint16_t right_wheel_speed;
			      uint16_t IR_distance;
			      uint16_t IR_temperature;
			      uint16_t hydraulic_oil_pressure;
			      uint16_t fuel_temperature;
			      uint16_t common_rail_pressure;
			      uint16_t wind_speed;		
            uint16_t outside_temperature;		
            uint16_t outside_humidity;					
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}General_Sensor_Frame_2A;


typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
			union{
            struct {
                uint8_t sensor_status : 2;  
           } gas_status[CARSENSOR_NUMS];
						uint8_t byte[CARSENSOR_NUMS/4+1];
				 }array_union; 
		
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}General_Sensor_Frame_2B;



typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
			union{
					struct {
						uint8_t sensor1_angle_warning : 1;
						uint8_t sensor2_angle_warning : 1;
						uint8_t sensor3_angle_warning: 1;
					  uint8_t sensor4_angle_warning : 1;
					  uint8_t sensor5_angle_warning : 1;
					  uint8_t sensor6_angle_warning :1;
						uint8_t chassis_angle_warning : 1;
					  uint8_t arm_angle_warning : 1;
				} byte_stru;
				uint8_t byte;
			}byte1_union;


			union{
					struct {
						uint8_t temperature_sensor1_warning : 1;
						uint8_t temperature_sensor2_warning : 1;
						uint8_t temperature_sensor3_warning: 1;
					  uint8_t temperature_sensor4_warning : 1;
					  uint8_t humidity_warning : 1;
					  uint8_t high_temperature_warning :1;
						uint8_t low_temperature_warning : 1;
					  uint8_t high_humidity_warning : 1;
				} byte_stru;
				uint8_t byte;
			}byte2_union;

			
			union{
					struct {
						uint8_t obstacle_sensor1_warning : 1;
						uint8_t obstacle_sensor2_warning : 1;
						uint8_t obstacle_sensor3_warning : 1;
					  uint8_t obstacle_sensor4_warning : 1;
					  uint8_t obstacle_sensor5_warning : 1;
					  uint8_t obstacle_sensor6_warning : 1;
						uint8_t obstacle_sensor7_warning : 1;
					  uint8_t obstacle_sensor8_warning : 1;
				} byte_stru;
				uint8_t byte;
			}byte3_union;
			
			union{
					struct {
						uint8_t engine_fault : 1;
						uint8_t regenerative_cycle : 1;
						uint8_t Low_oil_pressure : 1;
					  uint8_t High_engine_coolant_temperature : 1;
					  uint8_t reserved : 1;
					  uint8_t Oil_suction_filter_blockage : 1;
						uint8_t Return_oil_filter_blockage : 1;
					  uint8_t Air_filter_blockage : 1;
				} byte_stru;
				uint8_t byte;
			}byte4_union;			
			
			union{
					struct {
						uint8_t engine_fault : 1;
						uint8_t regenerative_cycle : 1;
						uint8_t Low_oil_pressure : 1;
					  uint8_t High_engine_coolant_temperature : 1;
					  uint8_t reserved : 1;
					  uint8_t Oil_suction_filter_blockage : 1;
						uint8_t Return_oil_filter_blockage : 1;
					  uint8_t Air_filter_blockage : 1;
				} byte_stru;
				uint8_t byte;
			}byte5_union;			




			union{
					struct {
						uint8_t sensor1_low_pressure : 1;
						uint8_t sensor1_high_pressure : 1;
						uint8_t sensor2_low_pressure : 1;
						uint8_t sensor2_high_pressure : 1;
						uint8_t sensor3_low_pressure : 1;
						uint8_t sensor3_high_pressure : 1;
						uint8_t sensor4_low_pressure : 1;
						uint8_t sensor4_high_pressure : 1;
				} byte_stru;
				uint8_t byte;
			}byte6_union;						
			
			
						union{
					struct {
						uint8_t battery_low : 1;
						uint8_t battery_Severely_low : 1;
						uint8_t system_voltage_high : 1;
						uint8_t ctrl_power_lost : 1;
						uint8_t load_power_lost : 1;
						uint8_t reserved : 1;
						uint8_t battery_communication_fault : 1;
						uint8_t battery_temperature_high : 1;
				} byte_stru;
				uint8_t byte;
			}byte7_union;	
			
								union{
					struct {
						uint8_t communication_board_fault : 1;
						uint8_t communication_bomb_fault : 1;
						uint8_t communication_ptz_fault : 1;
						uint8_t communication_ladar_fault : 1;
						uint8_t communication_Ultrasonic_fault : 1;
						uint8_t communication_industrial_PC_fault : 1;
						uint8_t communication_gas_sensor_fault : 1;
						uint8_t reserved : 1;
				} byte_stru;
				uint8_t byte;
			}byte8_union;	


				union{
					struct {
						uint8_t High_Concentration_of_Combustible_Gas : 1;
						uint8_t High_Concentration_of_Harmful_Gas : 1;
						uint8_t reserved : 6;
				} byte_stru;
				uint8_t byte;
			}byte9_union;
				
				union{
					struct {
						uint8_t Navigation_System_fault : 1;
						uint8_t reserved : 7;
				} byte_stru;
				uint8_t byte;
			}byte10_union;	
			
		
		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}Warning_Frame_2C;






typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint8_t data[10];

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}Gimbal_Datapass_through_Frame_30;



typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
			      union{
						float fdata;
            uint8_t data[4];
						}Latitude; 
						union{
						float fdata;
            uint8_t data[4];
						}Longitude; 
						
						union{
						float fdata;
            uint8_t data[4];
						}Highth; 

		}Payload;
			
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif

}GPS_Frame_30;




typedef struct {
    uint16_t header; 
    uint8_t  length;   

		struct {
				    uint8_t uid;
            uint8_t byte[200];

		}Payload;
#if 	AA55_CRC == 1		
    uint8_t crc16_l; 
    uint8_t crc16_h;
#else
		uint8_t xor_check;
#endif
		
		

}Common_Frame;


typedef struct {//索引
    uint8_t *frame[0x30];
	  uint8_t len[0x30];			
}Common_Frame_P;


#pragma pack()


#endif



