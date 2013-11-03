#include "proghead.h"
#include "../lib/socket.h"
#include "../lib/robotArm.h"
float rychlost = 0.5;


void klient1(char *ip,int port){
	pripoj(ip,port);
	struct RobotArm *dataArm = RobotArm_default;
	while(1){
		if (dataArm->alfa > dataArm->actAlfa)	dataArm->actAlfa+=0.001;
		else					dataArm->actAlfa-=0.001;
		sleep(rychlost);
	}
	uzavri();
}
