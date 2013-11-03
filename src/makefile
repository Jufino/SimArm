zadanie:server.o client1.o client2.o client3.o client4.o client5.o robotArm.o sharedMem.o zadanie.c
	gcc zadanie.c ../cmp/server.o ../cmp/client1.o ../cmp/client2.o ../cmp/client3.o ../cmp/client4.o ../cmp/sharedMem.o ../cmp/socket.o -o zadanie
server.o:server.c proghead.h robotArm.o sharedMem.o
	gcc -c server.c ../cmp/sharedMem.o ../cmp/robotArm.o  -o ../cmp/server.o
client1.o:client1.c socket.o proghead.h robotArm.o
	gcc -c client1.c ../cmp/socket.o ../cmp/robotArm.o -o ../cmp/client1.o
client2.o:client2.c socket.o proghead.h robotArm.o
	gcc -c client2.c ../cmp/socket.o ../cmp/robotArm.o -o ../cmp/client2.o
client3.o:client3.c socket.o proghead.h robotArm.o
	gcc -c client3.c ../cmp/socket.o ../cmp/robotArm.o -o ../cmp/client3.o
client4.o:client4.c socket.o proghead.h robotArm.o
	gcc -c client4.c ../cmp/socket.o ../cmp/robotArm.o -o ../cmp/client4.o
client5.o:client5.c socket.o proghead.h robotArm.o 
	$(CROSS_COMPILE)g++ -Wall -g -c client5.c ../cmp/robotArm.o -o ../cmp/client5.o `pkg-config --libs --cflags opencv`
robotArm.o:../lib/robotArm.h ../lib/robotArm.c
	gcc -c ../lib/robotArm.c -o ../cmp/robotArm.o
socket.o:../lib/socket.h ../lib/socket.c
	gcc -c ../lib/socket.c -o ../cmp/socket.o
sharedMem.o:../lib/sharedMem.h ../lib/sharedMem.c
	gcc -c ../lib/sharedMem.c -o ../cmp/sharedMem.o
clean:
	rm -f ../cmp/*
