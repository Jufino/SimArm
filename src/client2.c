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
	while(1){    
    		nacitajRobotArm(&dataArm);
		printf("Prijate od serveru: %f\n",pdataArm->actAlfa);
	}
}
int main(int argc,char *argv[]){
	int rychlost=1;
	int length=0;
	int port;
	float a=0;
	char *ip;
	pdataArm->beta=-3;
 if(decodeArgv(argc,argv,&ip,&port)){
	int sock = pripoj(ip,&port);
	int por=2;
	write(sock,&por,sizeof(int)*sizeof(por));
	pthread_t vlakno;
        pthread_attr_t parametre;
        if(pthread_attr_init(&parametre)) perror("Problem inicializacie vlakna");
	pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);  
        pthread_create(&vlakno,&parametre,readSocket,NULL);
	while(1){
		if (pdataArm->beta != pdataArm->actBeta){
			if (pdataArm->beta > pdataArm->actBeta)	pdataArm->actBeta+=0.01;
			else					pdataArm->actBeta-=0.01;
		}
			printf("Odosielam data\n");
	  		odosliFloat(&pdataArm->actBeta);
			printf("Data odoslane\n");
			sleep(1);
		}
	uzavri();
	return 0;
}
}
