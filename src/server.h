#include <sys/types.h>          
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../lib/robotArm.h"
#include "../lib/sharedMem.h"
void server(char *ip,int port);
