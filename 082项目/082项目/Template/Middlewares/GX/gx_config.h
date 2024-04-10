#ifndef __GX_CONFIG_H
#define __GX_CONFIG_H

#include "nc60_com.h"



#define UDP      0
#define UART     1



#define DEST_IP              "192.168.3.200"
#define DEST_PORT                  8889
#define LOCAL_IP             "192.168.3.205"
#define LOCAL_PORT                 8887

#define AA55_SLAVE                    1   //AA55从机
#define AA55_CRC                      0   //不使用CRC   使用异或校验
#define AA55_PORT_TYPE              UDP
#define AA55_PORT                 U7_TTL1_NUM 

#define SBUS_REMOTER_COM          U8_TTL2_NUM        




#define BATTERY_NUMS                 16
#define GASSENSOR_NUMS                6
#define CARSENSOR_NUMS                6


#define WHEELBASE      500.0//MM
#define GEAR_RATIO     45.0
#define PERIMETER      400*3.14//MM




#endif