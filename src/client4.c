#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "robotArm.h"
#include "socket.h"
#include "decodeArgv.h"
struct RobotArm dataArm;
int main(int argc, char* argv[]){
	int rychlost=1;
	int length=0;
	int port;
	char*ip;
 if(decodeArgv(argc,argv,&ip,&port)){
	int sock = pripoj(ip,&port);
	struct act aktualne;	
	int *por=(int*)malloc(sizeof(int));
        *por=4;
        odosliInt(&(*por));
        printf("Klient c.%d pripojeny(%s,%d)\n",*por,ip,port);
        free(por);
	while(1){
		nacitajRobotArm(&dataArm);
		angleArmAct(&dataArm);
		aktualne = {dataArm.actX1,dataArm.actY1,dataArm.actX2,dataArm.actY2};
		int length=0;
        	while((length+=send(sock,&aktualne, sizeof(aktualne),0)) < sizeof(aktualne));
	}
	uzavri();
}
	return 0;
}
