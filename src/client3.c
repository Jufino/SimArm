#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "robotArm.h"
#include "socket.h"
#include "decodeArgv.h"
#include <pthread.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
struct RobotArm dataArm=RobotArm_default;
struct RobotArm *pdataArm=&dataArm;
struct RobotArm ble;
int stop=0;
void *readSocket(void *){
	while(1){	if(stop==0) nacitajRobotArm(&dataArm);
			else nacitajRobotArm(&ble);	
	}	
}
char buff[15];
char prem[15];
char mod=0;
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
char *x[] = {"r0","r1","x2","y2","rych0","rych1","x0","y0"};
void *readKey(void *){
	while(1){
		if (kbhit()){
			if(mod != -1){
				int i,a;
				char znak = getchar();
				if(znak!='\n' && znak != 127 && znak < 256)	sprintf(buff,"%s%c",buff,znak);
				else if(znak == '\n'){
					if(mod == 0){
						sprintf(prem,"%s",buff);	
						mod = -1;
						for(i=0;i<8;i++){ 
							if(!strcmp(buff,x[i])){
								mod = 1;
								break;
							}
							else if(!strcmp(buff,"odosli")){
								mod = 0;
								if(angleArmEnd(&dataArm)==0){
                                                        		odosliRobotArm(&dataArm);
                                                		}
								stop=0;
								break;
							}
							else if(!strcmp(buff,"nastav")){
								mod = 0;
								stop=1;
								break;			
							}
						}
					}
					else{
						mod = 0;
						if(!strcmp(prem,x[0]))		dataArm.r0 = atof(buff);
						else if(!strcmp(prem,x[1]))  	dataArm.r1 = atof(buff);
						else if(!strcmp(prem,x[2]))  	dataArm.x2 = atof(buff);
						else if(!strcmp(prem,x[3]))  	dataArm.y2 = atof(buff);
						else if(!strcmp(prem,x[4]))  	dataArm.rych0 = atof(buff);
						else if(!strcmp(prem,x[5]))  	dataArm.rych1 = atof(buff); 
						else if(!strcmp(prem,x[6]))     dataArm.x0 = atof(buff);
						else if(!strcmp(prem,x[7]))     dataArm.y0 = atof(buff);
					}
					buff[0]='\0';
				}
				else if(znak == 127)	buff[strlen(buff)-1]='\0';
			}
			else{
				getchar();
				mod = 0;
			}
		}
	}
}

int main(int argc,char *argv[]){
	int rychlost=1;
	int length=0;
	int port;
	float a=0;
	char *ip;
 if(decodeArgv(argc,argv,&ip,&port)){
	int sock = pripoj(ip,&port);
	buff[0]='\0';
	int por=3;
	int n=0;
	write(sock,&por,sizeof(por));
	pthread_t vlakno;
        pthread_attr_t parametre;
        if(pthread_attr_init(&parametre)) perror("Problem inicializacie vlakna");
	pthread_attr_setdetachstate(&parametre, PTHREAD_CREATE_DETACHED);  
        pthread_create(&vlakno,&parametre,readSocket,NULL);
//------
        pthread_t vlakno1;
        pthread_attr_t parametre1;
        if(pthread_attr_init(&parametre1)) perror("Problem inicializacie vlakna");
        pthread_attr_setdetachstate(&parametre1, PTHREAD_CREATE_DETACHED);
        pthread_create(&vlakno1,&parametre1,readKey,NULL);
//-------------
	usleep(10000);
	while(1){
			printf("x0:%f\t\t\tx1:%f\t\t\tactX1:%f\t\t\tx2:%f\t\t\tactX2:%f\n",pdataArm->x0,pdataArm->x1,pdataArm->actX1,pdataArm->x2,pdataArm->actX2);
			printf("y0:%f\t\t\ty1:%f\t\t\tactY1:%f\t\t\ty2:%f\t\t\tactY2:%f\n",pdataArm->y0,pdataArm->y1,pdataArm->actY1,pdataArm->y2,pdataArm->actY2);
			printf("alfa:%f\t\t\tbeta:%f\t\t\tactAlfa:%f\t\tactBeta:%f\n",pdataArm->alfa,pdataArm->beta,pdataArm->actAlfa,pdataArm->actBeta);
			printf("rych0:%f\t\t\trych1:%f\n",pdataArm->rych0,pdataArm->rych1);
			printf("r0:%f\t\t\tr1:%f\n",pdataArm->r0,pdataArm->r1);
			if (mod ==0)		printf("Vyber premennu:%s",buff);
			else if(mod==1)		printf("Nastav premennu %s na:%s",prem,buff);
			else if(mod==-1)	printf("Nebola zadana platna premenna");
			usleep(100000);
			system("clear");
		}
	uzavri();
	return 0;
}
}
