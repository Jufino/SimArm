#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "robotArm.h"
#include "socket.h"
#include "decodeArgv.h"
struct RobotArm dataArm=RobotArm_default;
struct RobotArm *pdataArm=&dataArm;
int main(int argc, char* argv[]){
	int rychlost=1;
	int length=0;
	int port;
	char*ip;
 if(decodeArgv(argc,argv,&ip,&port)){
	int sock = pripoj(ip,&port);
	int por=4;
	write(sock,&por,sizeof(int)*sizeof(por));
	while(1){
		nacitajRobotArm(&dataArm);
		angleArmAct(&dataArm);
		odosliFloat(&pdataArm->actX1);
		odosliFloat(&pdataArm->actY1);
		odosliFloat(&pdataArm->actX2);
		odosliFloat(&pdataArm->actY2);
	}
	uzavri();
}
	return 0;
}
