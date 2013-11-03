#include "socket.h"         
void pripoj(char *ip,int port){
	if((sockFileDesc=socket(AF_INET, SOCK_STREAM, 0))<0){
        	perror("Chyba pri vytvarani socketu:\n");
        	exit(1);
    	}
	adresa.sin_family=AF_INET;
   	adresa.sin_port=htons(port);
	if((host=gethostbyname(ip))==NULL){
        	perror("Pocitac neexistuje:\n");
        	exit(2);
    	}
    	adresa.sin_addr.s_addr=*((in_addr_t *)(host->h_addr_list[0]));
	if((connect(sockFileDesc, (struct sockaddr *)&adresa, sizeof(adresa)))!=0){
        	perror("Chyba pripojenia\n");
        	exit(3);
    	}
}
void odosli(const void *buff){
	write(sockFileDesc,&buff, sizeof(buff));
}             
void nacitaj(void *buff){
	read(sockFileDesc,&buff, sizeof(buff));
}            
void uzavri(void){
	if(close(sockFileDesc)<0){
		perror("Nepodarilo sa uzavriet socket");
		exit(4);
	}
}
