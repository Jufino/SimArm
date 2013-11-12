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
void chyba(char *text,int cislo){
        perror(text);
        exit(cislo);
}
int *pocitadlo=0;
int main(int argc,char *argv[]){
    int sockFileDesc, client;
    struct sockaddr_in adresa,pripojilSa;
    struct RobotArm dataArm = RobotArm_default;
    struct RobotArm *pdataArm=&dataArm;
    pdataArm = &dataArm;
    int length=0;
//    struct datSock dataSocket;
    int port;
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
    while(1)
    {
	printf("Cakam na noveho klienta na porte %d\n",port);
	if((client=accept(sockFileDesc, (struct sockaddr *)&pripojilSa, &velkost))<0) chyba("Chyba pri vytvarani spojenia:\n",-4);
	//prijme klientov`
	switch(fork()){ //vytvori novy proces pre klienta
		case-1: chyba("Chyba pri vytvarani noveho procesu:\n",-104);break;
		case 0: if (close(sockFileDesc)<0)	chyba("Chyba pri zatvarani socketu:\n",-5);
			int por;
		//	float a=0;
			read(client,&por,sizeof(int));
			printf("%d\n",por);
			vytvorZP(12345); 
			pripojZP(&pdataArm);	//spoji zdielanu pamet so strukturou armData
			printf("Pripojeny klient c:%d\n",por);
			pdataArm->alfa=5;
			pdataArm->beta=5;
                        pdataArm->r0=100;
                        pdataArm->r1=50;
                        pdataArm->x0=200;
			pdataArm->y0=10;
			switch(por){
				case 1:while(1){
						length=0;
						while((length+=recv(client,&pdataArm->actAlfa, sizeof(pdataArm->actAlfa),0)) < sizeof(pdataArm->actAlfa));
						length=0;
        					while((length+=send(client,&(*pdataArm), sizeof(*pdataArm),0)) < sizeof(*pdataArm));				
					}break;
				case 2:while(1){
                                                length=0;
                                                while((length+=recv(client,&pdataArm->actBeta, sizeof(pdataArm->actBeta),0)) < sizeof(pdataArm->actBeta));
                                                length=0;
                                                while((length+=send(client,&(*pdataArm), sizeof(*pdataArm),0)) < sizeof(*pdataArm)); 
                                       }break;
				default:
					//printf("ostatny clienti\n");
					pripojZP(&pdataArm); 
					while(1){
                                        //        length=0;
                                        //        while((length+=recv(client,&pdataArm->actBeta, sizeof(pdataArm->actBeta),0)) < sizeof(pdataArm->actBeta));
                                                length=0;
                                                while((length+=send(client,&(*pdataArm), sizeof(*pdataArm),0)) < sizeof(*pdataArm));
	                                sleep(1); 
      					}break;
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
