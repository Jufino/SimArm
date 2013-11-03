#ifndef _ROBOTARM_H
#define _ROBOTARM_H
#include <math.h>
#define RobotArm_default {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
struct RobotArm{	
float r0,r1;
float x0,y0;
float x1,y1;
float x2,y2;
float alfa,beta;
float actX1,actY1;
float actX2,actY2;
float actAlfa,actBeta;
};

char angleArmEnd(struct RobotArm *data);
void angleArmAct(struct RobotArm *data);
#endif
