#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "robotArm.h"
#include "socket.h"
#include "decodeArgv.h"
//#include <pthread.h>
#include <cstdio>
#include <string>
#include <iostream>

#include <thread>
struct RobotArm dataArm=RobotArm_default;
struct RobotArm *pdataArm = &dataArm;
int sock;
void *readSocket(void*){
	int length=0;
	while(1){    
		while((length+=recv(sock,&dataArm, sizeof(dataArm),0)) < sizeof(dataArm));
		length=0;
	}
}
int main(int argc,char *argv[]){
	int port;
	char *ip;
 if(decodeArgv(argc,argv,&ip,&port)){
	sock = pripoj(ip,&port);
	int por=1;
	write(sock,&por,sizeof(int)*sizeof(por));
	pthread_t vlakno;
        pthread_create(&vlakno,NULL,&readSocket,NULL);
//	printf("%f",pdataArm->rych0);
	while(1){
		if (pdataArm->alfa != pdataArm->actAlfa){
			if (pdataArm->alfa-0.005 > pdataArm->actAlfa)	pdataArm->actAlfa+=0.01;
			else if (pdataArm->alfa+0.005 < pdataArm->actAlfa)	pdataArm->actAlfa-=0.01;
		}
//			printf("Odosielam data\n");
	  		odosliFloat(&pdataArm->actAlfa);
//			printf("Data odoslane\n");
			usleep(1000000/(pdataArm->rych0/0.01));
		}
	uzavri();
	return 0;
}
}
