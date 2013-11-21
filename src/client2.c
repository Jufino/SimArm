#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "robotArm.h"
#include "socket.h"
#include "decodeArgv.h"
#include <pthread.h>
struct RobotArm dataArm=RobotArm_default;
struct RobotArm *pdataArm=&dataArm;
void *readSocket(void *){
	while(1)	nacitajRobotArm(&dataArm);
}
int main(int argc,char *argv[]){
	int length=0;
	int port;
	float a=0;
	char *ip;
	if(decodeArgv(argc,argv,&ip,&port)){
		int sock = pripoj(ip,&port);
                int *por=(int*)malloc(sizeof(int));
                *por=2;
                odosliInt(&(*por));
                printf("Klient c.%d pripojeny(%s,%d)\n",*por,ip,port);
                free(por);
		pthread_t vlakno;
       		pthread_attr_t parametre;
        	if(pthread_attr_init(&parametre)) perror("Problem inicializacie vlakna");
		pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);  
        	pthread_create(&vlakno,&parametre,readSocket,NULL);
		while(1){
			if (pdataArm->beta != pdataArm->actBeta){
				if (pdataArm->beta-0.005 > pdataArm->actBeta)	pdataArm->actBeta+=0.01;
				else if (pdataArm->beta+0.005 < pdataArm->actBeta) pdataArm->actBeta-=0.01;
			}
	  		odosliFloat(&pdataArm->actBeta);
			usleep(1000000/(pdataArm->rych1/0.01));
		}
		uzavri();
	}
	return 0;
}
