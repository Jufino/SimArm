#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "robotArm.h"
#include "socket.h"
#include "decodeArgv.h"
//#include <pthread.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <thread>
using namespace cv;
#define hrubka_ciary 10
#define nazov_okna "Simulacia roboticka ruka"
#define width 500
#define height 250
struct RobotArm dataArm=RobotArm_default;
struct RobotArm *pdataArm = &dataArm;

void drawLine(Mat img, Point start, Point end,int hrubka){ line(img, start, end, Scalar( 255, 255, 255 ),hrubka, 8); }
void drawCircle(Mat img, Point center,double r ){          circle(img, center, r, Scalar( 0, 0, 255 ), -1, 8); }
void plot(int x[],int y[],int length){
        int i;
        IplImage *img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
        cvSet(img, cvScalar(0, 0, 0, 0));
        for(i=0;i<length-1;i++){
                drawLine(img,Point(x[i],height-y[i]),Point(x[i+1],height-y[i+1]),hrubka_ciary);
                if(i<length-1) drawCircle(img,Point(x[i],height-y[i]),15);
                cvShowImage(nazov_okna, img);
        }
        cvReleaseImage(&img);
}
int mouseX=0;
int mouseY=200;
int mod = 3;
void mouseEvent(int evt, int x, int y, int flags, void* param){
     if(evt==CV_EVENT_LBUTTONDOWN){
	mod=2;
	usleep(100000);
        mouseX = x;
        mouseY = height-y;
	dataArm.x2 = mouseX;
	dataArm.y2 = mouseY;
        if(angleArmEnd(&dataArm)==0){	mod = 4;				  }
        else                        { printf("Bod nedosiahnutelny\n");    mod = 3;}
        printf("%d %d\n",mouseX,mouseY);
    }
}
int sock;
int test;
void *readSocket(void*){
while(1){
      if(mod==4){
        odosliInt(&mod);
	odosliRobotArm(&dataArm);
        mod=3;
      }
      else if(mod==3){
        odosliInt(&mod);
        nacitajRobotArm(&dataArm);
      }
}
	return 0;
}
int main(int argc,char *argv[]){
	int port;
	char *ip;
 if(decodeArgv(argc,argv,&ip,&port)){
	sock = pripoj(ip,&port);
	int *por=(int*)malloc(sizeof(int));
        *por=5;
        odosliInt(&(*por));
        printf("Klient c.%d pripojeny(%s,%d)\n",*por,ip,port);
        free(por);
	pthread_t vlakno;
        pthread_create(&vlakno,NULL,&readSocket,NULL);
	while(1){
	cvNamedWindow(nazov_okna, CV_WINDOW_AUTOSIZE);
        cvSetMouseCallback(nazov_okna, mouseEvent, 0);
        int q=-1;
        while(q!=27){
        	int x[] = {(int)dataArm.x0,(int)dataArm.actX1,(int)dataArm.actX2};
        	int y[] = {(int)dataArm.y0,(int)dataArm.actY1,(int)dataArm.actY2};
        	plot(x,y,3);
        	q = cvWaitKey(100);
	}
	cvDestroyWindow(nazov_okna);
	}
	uzavri();
	return 0;
}
}
