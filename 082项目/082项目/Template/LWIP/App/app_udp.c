#include "usbd_cdc_if.h"
#include "gx_aa55_frame.h"
#include  "gx_config.h"
#include "app_udp.h"

#include "lwip/opt.h"

#include <lwip/sockets.h>
#include "lwip/api.h"
#include "lwip/sys.h"

#define RECV_DATA         (256)


uint8_t udp_flag = 0;






void gx_udp_send(uint8_t *message,uint8_t len)
{
    int sock = -1;
    struct sockaddr_in server_addr;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        usbprintf("Socket creation failed");
        
    }

		server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DEST_PORT);
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));
		

    // Convert IP address from string to network address structure
    if (inet_pton(AF_INET, DEST_IP, &server_addr.sin_addr) <= 0) {
        usbprintf("Invalid address/ Address not supported");
        close(sock);        
    }
    if (sendto(sock, message, len, 0, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        usbprintf("Sendto failed");
        close(sock);       
    }

    //usbprintf("Message sent to the server: %s\n", message);
    close(sock);
}




static void
udpecho_thread(void *arg)
{
  int sock = -1;
  char *recv_data;
  struct sockaddr_in udp_addr,seraddr;
  int recv_data_len;
  socklen_t addrlen;

 
  while(1)
  {
    recv_data = (char *)pvPortMalloc(RECV_DATA);
    if (recv_data == NULL)
    {
        usbprintf("No memory\n");
        goto __exit;
    }
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
      usbprintf("Socket error\n");
      goto __exit;
    }
    
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_addr.s_addr = INADDR_ANY;
    udp_addr.sin_port = htons(LOCAL_PORT);
    memset(&(udp_addr.sin_zero), 0, sizeof(udp_addr.sin_zero));
    
    if (bind(sock, (struct sockaddr *)&udp_addr, sizeof(struct sockaddr)) == -1)
    {
      usbprintf("Unable to bind\n");
      goto __exit;
    }
    while(1)
    {
      recv_data_len=recvfrom(sock,recv_data,
                             RECV_DATA,0,
                             (struct sockaddr*)&seraddr,
                             &addrlen);
#if AA55_PORT_TYPE == UDP	       
			gx_aa55_receive_handler((uint8_t *)recv_data,recv_data_len);
#endif														 
			udp_flag = 2;											 
    }
    
__exit:
    if (sock >= 0) closesocket(sock);
    if (recv_data) free(recv_data);
  }
}


void udpecho_init(void)
{
  sys_thread_new("udpecho_thread", udpecho_thread, NULL, 2048, 4);
}

