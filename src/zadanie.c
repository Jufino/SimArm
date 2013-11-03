#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "client5.h"
#include "server.h"
int main(int argc, const char* argv[]){
if (argc < 2){
	printf("\nPouzitie: %s -t[Typ] -i[IP adresa] -p[Port]\n",argv[0]);
	printf("\nTyp:\n \t-t1\tklient1\n\t-t2\tklient2\n\t-t3\tklient3\n\t-t4\tklient4\n");
//	printf("\t-t5\tklient5\n");
	printf("\t-ts\tserver\n");
	printf("\n Pre nastavenie IP adresy pouzite tvar\t\t -i192.168.1.1\n");
	printf("\n Pre nastavenie portu na 1212 pouzite tvar\t -p1212\n\n");
}
else{
int i;
char *typ;
char *ip;
char *port_s;
int port;
unsigned char is_exist=0;
for (i=1;i<argc;i++){
	if(argv[i][0] == '-'){
		switch(argv[i][1]){
			case 't':typ = (char *)malloc(sizeof(char)*(sizeof(argv[i])-2));
				 strncpy(typ,argv[i]+=2,strlen(argv[i])-2);
				 is_exist |= 1;	
			         break;
			case 'i':ip = (char *)malloc(sizeof(char)*(sizeof(argv[i])-2));
                                 strncpy(ip,argv[i]+=2,strlen(argv[i])-2);
			         is_exist |= 2;
				 break;
			case 'p':port_s = (char *)malloc(sizeof(char)*(sizeof(argv[i])-2));
                                 strncpy(port_s,argv[i]+=2,strlen(argv[i])-2);
				 is_exist |=4;
				 break;
		}
	}
	else{
		printf("Boli zadane neplatne argumenty\n");
		exit(1);
	}
}
if(!(is_exist&1)){ 
	printf("Nebol zadany typ aplikacie pomocou argumentu. Pouzite prosim -t\n");
	exit(2);

}
else{
	if(!(is_exist&2)){    
		ip = (char *)malloc(sizeof(char)*10);
		strcpy(ip,"localhost");
	}
        if(!(is_exist&4)) port=1212;
	else	          port=atoi(port_s);
	port_s = NULL;
	free(port_s);
	if(!strcmp(typ,"1")){
		printf("Pokus o vytvorenie klienta1(%s,%d)\n",ip,port);
		klient1(ip,port);
	}
	else if(!strcmp(typ,"2")){
		printf("Pokus o vytvorenie klienta2(%s,%d)\n",ip,port);
		klient2(ip,port);
	}
	else if(!strcmp(typ,"3")){
		printf("Pokus o vytvorenie klienta3(%s,%d)\n",ip,port);
		klient3(ip,port);
	}
	else if(!strcmp(typ,"4")){
		printf("Pokus o vytvorenie klienta4(%s,%d)\n",ip,port);
		klient4(ip,port);
	}
/*	else if(!strcmp(typ,"5")){
		printf("Pokus o vytvorenie klienta5(%s,%d)\n",ip,port);
//		klient5(ip,port);
	}*/
	else{
		printf("Pokus o vytvorenie serveru(%s,%d)\n",ip,port);
		server(ip,port);
	}
}
}
return 0;
}
