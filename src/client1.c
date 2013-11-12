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
	printf("Moznost prijmania zo serveru");
	while(1){    
		while((length+=recv(sock,&dataArm, sizeof(dataArm),0)) < sizeof(dataArm));
		printf("Prijate od serveru: %f\n",dataArm.actAlfa);
		length=0;
	}
}
int main(int argc,char *argv[]){
	int rychlost=1;
	int port;
	char *ip;
 if(decodeArgv(argc,argv,&ip,&port)){
	sock = pripoj(ip,&port);
	int por=1;
	write(sock,&por,sizeof(int)*sizeof(por));
	pthread_t vlakno;
        pthread_create(&vlakno,NULL,&readSocket,NULL);
	while(1){
		if (pdataArm->alfa != pdataArm->actAlfa){
			if (pdataArm->alfa > pdataArm->actAlfa)	pdataArm->actAlfa+=0.01;
			else					pdataArm->actAlfa-=0.01;
		}
			printf("Odosielam data\n");
	  		odosliFloat(&pdataArm->actAlfa);
			printf("Data odoslane\n");
			sleep(1);
		}
	uzavri();
	return 0;
}
}
