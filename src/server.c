#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "robotArm.h"
#include "sharedMem.h"
#include "socket.h"
#include "decodeArgv.h"
#include <pthread.h>
#include "semafor.h"
void chyba(const char *text,int cislo){
        perror(text);
        exit(cislo);
}
int *pocitadlo=0;
int client;
struct RobotArm dataArm;
struct RobotArm *pdataArm=&dataArm;
int main(int argc,char *argv[]){
    int sockFileDesc;
    struct sockaddr_in adresa,pripojilSa;
    pdataArm = &dataArm;
    int length=0;
//    struct datSock dataSocket;
    int port;
    int a=0;
if(decodeArgv(argc,argv,NULL,&port)){
    socklen_t velkost;
  if((sockFileDesc=socket(AF_INET, SOCK_STREAM, 0))<0)	chyba("Chyba pri vytvarani socketu:\n",-1);

//vytvorenie parametrickej struktury
    adresa.sin_family=AF_INET;
    adresa.sin_port=htons(port);
    adresa.sin_addr.s_addr=INADDR_ANY;
//Vystavenie socketu
    if(bind(sockFileDesc, (struct sockaddr *)&adresa, sizeof(adresa))<0)	chyba("Chyba pri vystavovani socketu:\n",-2);
//Nastavenie socketu
    if(listen(sockFileDesc,2)<0)						chyba("Chyba pri nastavovani pocuvania socketu:\n",-3);
    vytvorZP(12345);
    pripojZP(&pdataArm);    //spoji zdielanu pamet so strukturou armData
    initRobotArm(&(*pdataArm));
//defaultne hodnoty
    pdataArm->r0=100;
    pdataArm->r1=100;
    pdataArm->x0=250;
    pdataArm->y0=10;
    pdataArm->rych0=0.4;
    pdataArm->rych1=0.4;
//-------------------------
    int sem_id = semCreate(12345,1);   //vytvor semafor
    semInit(sem_id,0,1);
//-------------------------
    while(1)
    {
	printf("Cakam na noveho klienta na porte %d\n",port);
	if((client=accept(sockFileDesc, (struct sockaddr *)&pripojilSa, &velkost))<0) chyba("Chyba pri vytvarani spojenia:\n",-4);
	//prijme klientov`
	switch(fork()){ //vytvori novy proces pre klienta
		case-1: chyba("Chyba pri vytvarani noveho procesu:\n",-104);break;
		case 0: if (close(sockFileDesc)<0)	chyba("Chyba pri zatvarani socketu:\n",-5);
			int por;
/*			        struct timeval timeout;
		        timeout.tv_sec = 4;
        		timeout.tv_usec = 0;
        		if (setsockopt (client, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0);
        		if (setsockopt (client, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0);
*/			recv(client,&por, sizeof(por),0);
			pripojZP(&pdataArm);	//spoji zdielanu pamet so strukturou armData	
			printf("Pripojeny klient c:%d\n",por);
			switch(por){
				case 1: usleep(100);
					while(1){
						semWait(sem_id,0);
                                                recv(client,&pdataArm->actAlfa, sizeof(pdataArm->actAlfa),0);
						send(client,&(*pdataArm), sizeof(*pdataArm),0);
						semPost(sem_id,0);
					}break;
				case 2: usleep(200);
					while(1){
						semWait(sem_id,0);
                                               	recv(client,&pdataArm->actBeta, sizeof(pdataArm->actBeta),0);
                                                send(client,&(*pdataArm), sizeof(*pdataArm),0);  
						semPost(sem_id,0);  
				}break;
				case 5: usleep(200);
				case 3:	usleep(300);
					while(1){
						recv(client,&a, sizeof(a),0);
						semWait(sem_id,0);
						length=0;
						if(a==4)	recv(client,&(*pdataArm), sizeof(*pdataArm),0);
						else		send(client,&(*pdataArm), sizeof(*pdataArm),0);
						semPost(sem_id,0);
					}break;
				case 4:	struct act aktualne;
					usleep(400);
					while(1){
						semWait(sem_id,0);
						send(client,&(*pdataArm), sizeof(*pdataArm),0);
						recv(client,&aktualne, sizeof(aktualne),0);
						pdataArm->actX1 = aktualne.datX1;
						pdataArm->actY1 = aktualne.datY1;
						pdataArm->actX2 = aktualne.datX2;
						pdataArm->actY2 = aktualne.datY2;
						semPost(sem_id,0);
					}
					break;
			}
//			uvolniZP();*/
			if (close(client)<0)	chyba("Chyba pri zatvarani socketu:\n",-6);
	    		printf("Spojenie ukoncene klient c.%d\n",por);
	    		exit(0);					
		default:
	    		if (close(client)<0)	chyba("Chyba pri zatvarani socketu:\n",-7);
		}
    }
//    uzavriZP();
}
}
