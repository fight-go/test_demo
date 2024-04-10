/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "shell.h"
#include "app_udp.h"
#include "gx_aa55_frame.h"
#include "gx_can_frame.h"
#include "can.h"
#include "gx_ctrl.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId gxAA55SendfromCarHandle;
osThreadId gxAA55RecfromRemoterHandle;
osThreadId sbusReceiveHandle;
osThreadId comMbHHandle;
osThreadId driverCtrlHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void GX_AA55_Send_From_CAR_Task(void const * argument);
void GX_AA55_REC_Task(void const * argument);
void SBUS_REC_Task(void const * argument);
void Common_Host_Task(void const * argument);
void Driver_Control_Task(void const * argument);

extern void MX_LWIP_Init(void);
extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of gxAA55SendfromCar */
  osThreadDef(gxAA55SendfromCar, GX_AA55_Send_From_CAR_Task, osPriorityNormal, 0, 1024);
  gxAA55SendfromCarHandle = osThreadCreate(osThread(gxAA55SendfromCar), NULL);

  /* definition and creation of gxAA55RecfromRemoter */
  osThreadDef(gxAA55RecfromRemoter, GX_AA55_REC_Task, osPriorityHigh, 0, 1024);
  gxAA55RecfromRemoterHandle = osThreadCreate(osThread(gxAA55RecfromRemoter), NULL);

  /* definition and creation of sbusReceive */
  osThreadDef(sbusReceive, SBUS_REC_Task, osPriorityHigh, 0, 1024);
  sbusReceiveHandle = osThreadCreate(osThread(sbusReceive), NULL);

  /* definition and creation of comMbH */
  osThreadDef(comMbH, Common_Host_Task, osPriorityNormal, 0, 1024);
  comMbHHandle = osThreadCreate(osThread(comMbH), NULL);

  /* definition and creation of driverCtrl */
  osThreadDef(driverCtrl, Driver_Control_Task, osPriorityHigh, 0, 1024);
  driverCtrlHandle = osThreadCreate(osThread(driverCtrl), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();

  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
	userShellInit();
	udpecho_init();
 
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_GX_AA55_Send_From_CAR_Task */
/**
* @brief Function implementing the gxAA55SendfromCar thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GX_AA55_Send_From_CAR_Task */
void GX_AA55_Send_From_CAR_Task(void const * argument)
{
  /* USER CODE BEGIN GX_AA55_Send_From_CAR_Task */
  /* Infinite loop */ 
	while(heart_frame01.pc_online == 0)
	osDelay(10000);
  for(;;)
  {
		gx_send_frame(0x21);
		gx_send_frame(0x22);
		gx_send_frame(0x23);
		gx_send_frame(0x24);
		gx_send_frame(0x25);
		gx_send_frame(0x26);
		gx_send_frame(0x27);
		gx_send_frame(0x28);
		gx_send_frame(0x29);
		gx_send_frame(0x2A);
		gx_send_frame(0x2B);
		
    heart_frame01.pc_online = heart_frame01.offline_cnt++>0x50?0x00:0x01; 
		heart_frame01.offline_cnt = heart_frame01.offline_cnt>0x60?0x55:heart_frame01.offline_cnt;
		can_heart_12.bytes.byte_stru.communicationSta_remoter_mcu  = heart_frame01.pc_online;
    osDelay(50);
  }
  /* USER CODE END GX_AA55_Send_From_CAR_Task */
}

/* USER CODE BEGIN Header_GX_AA55_REC_Task */
/**
* @brief Function implementing the gxAA55RecfromRemoter thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GX_AA55_REC_Task */
void GX_AA55_REC_Task(void const * argument)
{
  /* USER CODE BEGIN GX_AA55_REC_Task */
		osDelay(3000);	
	//checkDebugMode();
  /* Infinite loop */
  for(;;)
  {
#if AA55_PORT_TYPE ==		UART
		if(uart_union[AA55_PORT].rx_state == 2)
		{
		  gx_aa55_receive_handler(uart_union[AA55_PORT].rx_buf,uart_union[AA55_PORT].rx_count);
			uart_union[AA55_PORT].rx_state = 0;
		}
#endif
		parse_a10_sbus();
    osDelay(1);
  }
  /* USER CODE END GX_AA55_REC_Task */
}

/* USER CODE BEGIN Header_SBUS_REC_Task */
/**
* @brief Function implementing the sbusReceive thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SBUS_REC_Task */
void SBUS_REC_Task(void const * argument)
{
  /* USER CODE BEGIN SBUS_REC_Task */
	
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END SBUS_REC_Task */
}

/* USER CODE BEGIN Header_Common_Host_Task */
/**
* @brief Function implementing the comMbH thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Common_Host_Task */

void Common_Host_Task(void const * argument)
{
  /* USER CODE BEGIN Common_Host_Task */
  /* Infinite loop */

  for(;;)
  {		
    osDelay(100);
  }
  /* USER CODE END Common_Host_Task */
}

/* USER CODE BEGIN Header_Driver_Control_Task */
/**
* @brief Function implementing the driverCtrl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Driver_Control_Task */
void Driver_Control_Task(void const * argument)
{
  /* USER CODE BEGIN Driver_Control_Task */

  /* Infinite loop */
  for(;;)
  {
		can_send(&hcan1,(CAN_COMMON_FRAME*)&can_general_10);osDelay(10);
		can_send(&hcan1,(CAN_COMMON_FRAME*)&can_joystick_11);osDelay(10);
		can_send(&hcan1,(CAN_COMMON_FRAME*)&can_heart_12);osDelay(10);
		can_send(&hcan1,(CAN_COMMON_FRAME*)&can_fire_monitor_13);osDelay(10);
    
  }
  /* USER CODE END Driver_Control_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
