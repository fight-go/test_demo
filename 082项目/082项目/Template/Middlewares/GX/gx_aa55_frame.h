#ifndef __GX_AA55_FRAME_H
#define __GX_AA55_FRAME_H

#include "gx_aa55_typedef.h"
#include "lwip/udp.h"
#include "lwip/def.h"
#include "lwip/memp.h"
#include "lwip/inet_chksum.h"
#include "lwip/ip_addr.h"
#include "lwip/ip6.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"
#include "lwip/icmp.h"
#include "lwip/icmp6.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/dhcp.h"

#define ERROR_OK           0x00
#define ERROR_01_HEAD      0x01
#define ERROR_02_LENGTH    0x02
#define ERROR_03_CHECKSUM  0x03







extern Heart_Frame_01                   heart_frame01;
extern Chassis_Speed_Frame_02          chasssis_speed_frame02;
extern Fire_monitor_Frame_03           fire_monitor_frame03;
extern Gimbal_Frame_04                 gimbal_frame04;
extern General_Frame_05                general_frame05;
extern System_Config_Frame_06          system_config_frame06;
extern Sbus_Forward_Frame_08           sbus_forward_frame08;
extern Driver_Status_Frame_21          driver_status_frame21;
extern Driver_Data_Frame_22            driver_data_frame22;
extern Battery_BasicInfo_Frame_23      battery_basicinfo_frame23;
extern Battery_Single_Voltage_Frame_24 battery_single_vlotage_frame24;
extern Battery_Single_Temp_Frame_25    battery_single_temp_frame25;
extern ENGINE_StatusInfo_Frame_26      engine_statusInfo_frame26;
extern Car_StatusInfo_Frame_27         car_status_info_frame27;
extern GasSensor_Data_Frame_28         gassensor_data_frame28;
extern GasSensor_Status_Frame_29       gassensor_status_frame29;

extern General_Sensor_Frame_2A         general_Sensor_frame2A;        
extern General_Sensor_Frame_2B         general_Sensor_frame2B;         
extern Warning_Frame_2C                warning_frame2C; 


extern GPS_Frame_30                     gps_frame30;
extern Common_Frame_P p_frame;

void gx_aa55Frame_init(void);
uint8_t gx_aa55_receive_handler(uint8_t* rx_buf,uint8_t len);
uint8_t gx_check_frame(uint8_t* rx_buf,uint8_t len);
void gx_send_frame(uint8_t uid);



#endif