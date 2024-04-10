
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "main.h"
#include "cmsis_os.h"

#include "shell.h"
#include "usbd_cdc_if.h"
#include "gx_aa55_frame.h"
#include "gx_can_frame.h"

//#include "cevent.h"
//#include "log.h"


Shell shell;
char shellBuffer[512];

static SemaphoreHandle_t shellMutex; 

short userShellWrite(char *data, unsigned short len)
{
    CDC_Transmit_FS((uint8_t *)data, len);
    return len;
}



short userShellRead(char *data, unsigned short len)
{
	  if(shell.Rx_status == 2)
		{
	   memcpy(data, UserRxBufferFS, shell.Rx_Len); 	
     shell.Rx_status	= 0;		
     return shell.Rx_Len;
		}
		else
			return 0;
}


int userShellLock(Shell *shell)
{
    xSemaphoreTakeRecursive(shellMutex, portMAX_DELAY);
    return 0;
}


int userShellUnlock(Shell *shell)
{
    xSemaphoreGiveRecursive(shellMutex);
    return 0;
}


void userShellInit(void)
{
    shellMutex = xSemaphoreCreateMutex();

    shell.write = userShellWrite;
    shell.read = userShellRead;
    shell.lock = userShellLock;
    shell.unlock = userShellUnlock;
    shellInit(&shell, shellBuffer, 512);
    if (xTaskCreate(shellTask, "shell", 256, &shell, 5, NULL) != pdPASS)
    {
        usbprintf("shell task creat failed\r\n");
    }
}

void arrayToHexStringWithSpaces(const unsigned char *array, size_t array_length, char **hex_string) {
    *hex_string = (char*)malloc(array_length * 3 + 3);  // Allocate space for the hex string with spaces
    if (*hex_string == NULL) {
       shellPrint(&shell, "memory NULL\r\n");
    }

    for (size_t i = 0; i < array_length; i++) {
        sprintf(*hex_string + i * 3, "%02X ", array[i]);  // Convert each byte to two hexadecimal characters with a space
    }

    (*hex_string)[array_length * 3 - 1] = '\r';  
		(*hex_string)[array_length * 3 - 0] = '\n';
		(*hex_string)[array_length * 3 + 1] = '\0';
}
uint8_t  getAA55Frame(uint8_t uid)
{	
	char *hex_string_with_spaces;
	if(p_frame.frame[uid] == NULL)
	{
		shellPrint(&shell, "uid doesn't exist\r\n");
		return -1;
	}
	arrayToHexStringWithSpaces(p_frame.frame[uid], p_frame.len[uid], &hex_string_with_spaces);
	shellPrint(&shell, hex_string_with_spaces);
	free(hex_string_with_spaces);
	return uid;
}
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),getAA55Frame, getAA55Frame, display AA55 frame details);



uint8_t  getCanFrame(uint8_t uid)
{	
	char *hex_string_with_spaces;
	if(can_common_frame_p.frame[uid] == NULL)
	{
		shellPrint(&shell, "uid doesn't exist\r\n");
		return -1;
	}
	arrayToHexStringWithSpaces(can_common_frame_p.frame[uid], 9, &hex_string_with_spaces);// ID + DATA[8]
	shellPrint(&shell, hex_string_with_spaces);
	free(hex_string_with_spaces);
	return uid;
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),getCanFrame, getCanFrame, display CAN frame details);


//#define STRING(x) #x
//uint8_t  test(void)
//{	

//	shellPrint(&shell, STRING(hello world\r\n));
//	return 0;
//}

//SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC),test, test, this is a test);







