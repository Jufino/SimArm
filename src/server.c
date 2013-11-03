#include "server.h"
void chyba(char *text,int cislo){
        perror(text);
        exit(cislo);
}
int pocitadlo=0;

void server(char *ip,int port){
    int sockFileDesc, client;
    struct sockaddr_in adresa,pripojilSa;
    long data;
    socklen_t velkost;
    int endR,endW;
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
	printf("Cakam na noveho klienta\n");
	if((client=accept(sockFileDesc, (struct sockaddr *)&pripojilSa, &velkost))<0) chyba("Chyba pri vytvarani spojenia:\n",-4);
	//prijme klientov
	pocitadlo++;  

	switch(fork()){ //vytvori novy proces pre klienta
		case-1: chyba("Chyba pri vytvarani noveho procesu:\n",-104);
		case 0: if (close(sockFileDesc)<0)	chyba("Chyba pri zatvarani socketu:\n",-5);
			while(endR > 0){
				endR=0;
				endW=0;
				while((endR+=read(client,&data, sizeof(data))) < sizeof(data));
				while((endW+=write(client,&data, sizeof(data)))< sizeof(data));
				printf("Klient%d:data%d\n",pocitadlo,(int)data);
			}
			if (close(client)<0)	chyba("Chyba pri zatvarani socketu:\n",-6);
	    		printf("Spojenie ukoncene klient c.%d\n",pocitadlo);
	    		exit(0);
		default:
	    		if (close(client)<0)	chyba("Chyba pri zatvarani socketu:\n",-7);
	    		printf("Novy klient sa moze pripojit\n");     
		}
    }
}
