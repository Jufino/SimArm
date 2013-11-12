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
int main(int argc, const char* argv[]){
	int rychlost=1;
	int length=0;
	int *port;
	char*ip;
 if(decodeArgv(argc,argv,&ip,&port)){
	int sock = pripoj(ip,port);
	int *por=1;
	write(sock,&por,sizeof(int)*sizeof(por));
//
	pthread_t vlakno;
        pthread_attr_t parametre;
        if(pthread_attr_init(&parametre)) perror("Problem inicializacie vlakna");
	pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);  
        pthread_create(&vlakno,&parametre,readSocket,NULL);
	while(1){
		if (pdataArm->alfa != pdataArm->actAlfa){
			if (pdataArm->alfa > pdataArm->actAlfa)	pdataArm->actAlfa+=0.001;
			else					pdataArm->actAlfa-=0.001;
			printf("Odosielam data\n");
        		odosliFloat(&(pdataArm->actAlfa));
			printf("Data odoslane\n");
			sleep(rychlost);
			length=0;
		}
	}
	uzavri();
}
	return 0;
}
