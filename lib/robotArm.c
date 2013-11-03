#include "robotArm.h"
#define na2(a) (a*a)
char angleArmEnd(struct RobotArm *data){
	if (data->x2 <0){
	float c2 = (na2(data->x2)+na2(data->y2)-na2(data->r0)-na2(data->r1))/(2*(data->r0)*(data->r1));
	if((1-na2(c2))>=0){
		float s2 = sqrt(1-na2(c2));
		float K1 = data->r0+data->r1*c2;
		float K2 = data->r1*s2;
		data->alfa = atan2(data->y2,data->x2)-atan2(K2,K1);
		data->x1 = cos(data->alfa)*(data->r0)+(data->x0);
		data->y1 = sin(data->alfa)*(data->r0)+(data->y0);
		data->beta = atan2(s2,c2);
		data->x2 +=data->x0;
		data->y2 +=data->y0;
		return 0;
	}
	else	return -1;
	}
	else{
	data->x2 *=-1;
        float c2 = (na2(data->x2)+na2(data->y2)-na2(data->r0)-na2(data->r1))/(2*(data->r0)*(data->r1));
        if((1-na2(c2))>=0){
                float s2 = sqrt(1-na2(c2));
                float K1 = data->r0+data->r1*c2;
                float K2 = data->r1*s2;
                data->alfa = atan2(data->y2,data->x2)-atan2(K2,K1);
                data->x1 = data->x0+(-1)*cos(data->alfa)*(data->r0);
                data->y1 = sin(data->alfa)*(data->r0)+(data->y0);
                data->beta = atan2(s2,c2);
                data->x2 =data->x0+data->x2*(-1);
                data->y2 =data->y0+data->y2;
                return 0;
        }
        else    return -1;
	}
}
void angleArmAct(struct RobotArm *data){
	data->actX1 = cos(data->actAlfa)*(data->r0)+(data->x0);
	data->actY1 = sin(data->actAlfa)*(data->r0)+(data->y0);
	data->actX2 = cos((data->actAlfa)+(data->actBeta))*(data->r1)+(data->actX1);
	data->actY2 = sin((data->actAlfa)+(data->actBeta))*(data->r1)+(data->actY1);
}
