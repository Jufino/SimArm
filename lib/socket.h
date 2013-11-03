#include <sys/types.h>
#include <sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<stdio.h>
int sockFileDesc;
struct sockaddr_in adresa;
socklen_t velkost;
struct hostent *host;
void *buff;

void pripoj(char *ip,int port);
void odosli(const void *buff);
void nacitaj(void *buff);
void uzavri(void);
void *nacitajAsyn(void);
void vytvorAsyn(int socket);      
