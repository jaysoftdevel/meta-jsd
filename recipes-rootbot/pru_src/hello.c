#include <stdio.h>
#include <unistd.h>
//#include <fcntl.h>
//#include <string.h>
#include "arm_comm.h"

/*
#define PRU1_NAME		"/dev/rpmsg_pru31"
#define FIRMWARE_SIZE 14
#define REMOTEPROC_STATE         "/sys/class/remoteproc/remoteproc2/state"
#define REMOTEPROC_FIRMWARE      "/sys/class/remoteproc/remoteproc2/firmware"
#define PRU1_FIRMWARE            "am335x-pru1-fw"*/
#define N		10
int CASSY;
//#define MAX_BUFFER_SIZE		512
//char buffer[MAX_BUFFER_SIZE];
extern unsigned short buffer_state; //expose buffer state
extern short plen;
extern unsigned char *pbuffer;

int main(void)
{
  int i,j;


  while(1){
    if(rpmsg_init(&CASSY) == Initialized){
      break;
    }
  }	

  for (i = 0,j=0; i < 2*N;) {
    if(j == 0){
      write(CASSY,"hello world!",13);
      j=1;
    }
    listen(CASSY);
    if(buffer_state != 0){
      printf("%d: ",i/2);
      for(;plen > 0;plen--,pbuffer++) printf("%c",*pbuffer);
      buffer_state = 0;
      if((i%2) == 1){
	j = 0;
	printf("\n");
      }
      i++;
    }
  }  
  rpmsg_deinit(CASSY);
  return 0;
}

