C=gcc
CP=g++
CPP=$(CROSS_COMPILE)g++ -Wall -g
OFLAGS=`pkg-config --libs --cflags opencv`
#localizacia, moduly jadra, autotools, 
#sockety,server,procesy, vlakna,dynamkniznice,casovace,signaly,semafor
all:server client1 client2 client3 client4 client5
server: libsemafor.o libdecodeArgv.o librobotArm.o libsharedMem.o server.c
	$(CP) server.c librobotArm.o libsharedMem.o libdecodeArgv.o libsemafor.o -lpthread -o server -lm -g
client1:libdecodeArgv.o libsocket.o librobotArm.o client1.c
	$(CP) client1.c libsocket.o librobotArm.o libdecodeArgv.o -lpthread -o client1 -lm -g -std=c++11 
client2:libsocket.o librobotArm.o client2.c
	$(CP) client2.c libsocket.o librobotArm.o libdecodeArgv.o -pthread -o client2 -lm -g -std=c++11 
client3:libtimer.o libsocket.o librobotArm.o client3.c
	$(CP) client3.c libsocket.o librobotArm.o libdecodeArgv.o libtimer.o -pthread -lrt -o client3 -lm -g -std=c++11 
client4:libsocket.o librobotArm.o client4.c
	$(CP) client4.c libsocket.o librobotArm.o libdecodeArgv.o -pthread -o client4 -lm -g -std=c++11 
client5:libsocket.o librobotArm.o libdecodeArgv.o client5.c
	$(CPP) client5.c librobotArm.o libsocket.o libdecodeArgv.o -o client5 -std=c++11 $(OFLAGS)
librobotArm.o:robotArm.h robotArm.c
	$(CP) -c robotArm.c -o librobotArm.o -lm
libsocket.o:socket.h socket.c
	$(CP) -c socket.c -lrobotArm -o libsocket.o -lm
libsharedMem.o:sharedMem.h sharedMem.c
	$(CP) -c sharedMem.c -lrobotArm -o libsharedMem.o -lm
libdecodeArgv.o:decodeArgv.h decodeArgv.c
	$(CP) -c decodeArgv.c -o libdecodeArgv.o
libsemafor.o:semafor.c semafor.h
	$(CP) -c semafor.c -o libsemafor.o
libtimer.o: timer.c timer.h
	$(CP) -c timer.c -o libtimer.o

clean:
	rm -f client1
	rm -f client2
	rm -f client3
	rm -f client4
	rm -f client5
	rm -f server
	rm -f *.o
shared: 
	ipcrm -M 12345
