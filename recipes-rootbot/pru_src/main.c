#include <stdint.h>
#include <pru_cfg.h>
#include "pru_comm.h"

volatile register unsigned __R31;
extern unsigned short buffer_state,plen;
extern unsigned char *pbuffer;

unsigned short send(char *buf,int N); //defined in pru_comm.c

/*
 * Used to make sure the Linux drivers are ready for RPMsg communication
 * Found at linux-x.y.z/include/uapi/linux/virtio_config.h
 */
//#define VIRTIO_CONFIG_S_DRIVER_OK	4

//unsigned char payload[RPMSG_BUF_SIZE];

/*
 * main.c
 */
void main(void)
{
	/* Allow OCP master port access by the PRU so the PRU can read external memories */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while (1) {	        
	  if(rpmsg_init() == Initialized){
	    listen();
	    if(buffer_state != 0){			
#ifdef PRU0
	      send("PRU0 responding",15);
	      send((char *)pbuffer,plen);
#endif
#ifdef PRU1
	      send("PRU1 responding",15);
	      send((char *)pbuffer,plen);
#endif
	      buffer_state = 0;
	    }
	  }
	}
}
