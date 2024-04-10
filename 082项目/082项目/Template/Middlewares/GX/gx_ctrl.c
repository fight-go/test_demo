#include "gx_ctrl.h"
#include "math.h"

CAR_DATA car_data;



A10_TYPEDEF a10_sbus_data;
void parse_a10_sbus(void)
{   
	 a10_sbus_data.move_ctrl.joystick_x = sbus_forward_frame08.Payload.right_x-1000;
	 a10_sbus_data.move_ctrl.joystick_y = 1000-sbus_forward_frame08.Payload.right_y;
	 a10_sbus_data.fire_monitor.joystick_x = sbus_forward_frame08.Payload.left_x-1000;
	 a10_sbus_data.fire_monitor.joystick_y = 1000-sbus_forward_frame08.Payload.left_y;
	
	 a10_sbus_data.move_ctrl.angle = atan2(a10_sbus_data.move_ctrl.joystick_x,a10_sbus_data.move_ctrl.joystick_y);
	 if(fabs(a10_sbus_data.move_ctrl.angle)<0.05) a10_sbus_data.move_ctrl.angle = 0;
	 if(fabs(a10_sbus_data.move_ctrl.angle)>3.1) a10_sbus_data.move_ctrl.angle = 3.14159;//正前正后滤波
	
	 a10_sbus_data.move_ctrl.amplitude = sqrt(a10_sbus_data.move_ctrl.joystick_x*a10_sbus_data.move_ctrl.joystick_x+a10_sbus_data.move_ctrl.joystick_y*a10_sbus_data.move_ctrl.joystick_y);
  
	 double attenuation_factor = 1-fabs(a10_sbus_data.move_ctrl.angle)/1.57;
	 attenuation_factor = fabs(attenuation_factor);
	 attenuation_factor= (attenuation_factor<0.4)?0.4:attenuation_factor;
		
	 double vx = a10_sbus_data.move_ctrl.amplitude * sin(a10_sbus_data.move_ctrl.angle)*attenuation_factor;
   double vy = a10_sbus_data.move_ctrl.amplitude * cos(a10_sbus_data.move_ctrl.angle)*attenuation_factor;
	 
	 car_data.Ctrl_DriveInfo.left_speed = (vy + vx)*attenuation_factor;
   car_data.Ctrl_DriveInfo.right_speed =(vy - vx)*attenuation_factor;
	 	 
	 car_data.Ctrl_FireMonitorInfo.up    = a10_sbus_data.fire_monitor.joystick_y>100;
	 car_data.Ctrl_FireMonitorInfo.down  = a10_sbus_data.fire_monitor.joystick_y<-100;
	 car_data.Ctrl_FireMonitorInfo.left  = a10_sbus_data.fire_monitor.joystick_x<-100;
	 car_data.Ctrl_FireMonitorInfo.right = a10_sbus_data.fire_monitor.joystick_x>100;
	 car_data.Ctrl_FireMonitorInfo.vertical_speed   = fabs(a10_sbus_data.fire_monitor.joystick_y/10.0);
	 car_data.Ctrl_FireMonitorInfo.horizontal_speed = fabs(a10_sbus_data.fire_monitor.joystick_x/10.0);
		
}











