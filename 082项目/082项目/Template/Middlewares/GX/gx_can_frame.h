#ifndef 		__GX_CAN_FRAME_H
#define     __GX_CAN_FRAME_H

#include "gx_can_typedef.h"
#include "main.h"


extern CAN_GENERAL_10        can_general_10       ;
extern CAN_JOYSRICK_11       can_joystick_11;
extern CAN_HEART_12          can_heart_12         ;
extern CAN_FIRE_MONITOR_13   can_fire_monitor_13  ;
extern CAN_ENGINE_STATUS_21  can_engine_status_21 ;
extern CAN_ENGINE_STATUS_22  can_engine_status_22 ;
extern CAN_GENERAL_23        can_general_23       ;
extern CAN_GENERAL_24        can_general_24       ;
extern CAN_GENERAL_25        can_general_25       ;
extern CAN_BATTERY_INFO_26   can_battery_info_26  ;
extern CAN_WARNING_INFO_2C   can_battery_info_2C  ;

extern CAN_COMMON_FRAME      can_common_frame_tx;
extern CAN_COMMON_FRAME      can_common_frame_rx;
extern CAN_Common_Frame_P    can_common_frame_p;

uint8_t can_send(CAN_HandleTypeDef *canx,CAN_COMMON_FRAME *frame);
void gx_canFrame_init(void);











#endif