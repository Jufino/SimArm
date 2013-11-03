#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include "../lib/robotArm.h"
#include "../lib/socket.h"

using namespace cv;
#define hrubka_ciary 10
#define nazov_okna "Simulacia roboticka ruka"

void drawLine(Mat img, Point start, Point end,int hrubka){ line(img, start, end, Scalar( 255, 255, 255 ),hrubka, 8); }
void drawCircle(Mat img, Point center,double r ){ 	   circle(img, center, r, Scalar( 0, 0, 255 ), -1, 8); }
void plot(int x[],int y[],int length){
	int i;
	IplImage *img = cvCreateImage(cvSize(500, 500), IPL_DEPTH_8U, 3);
	cvSet(img, cvScalar(0, 0, 0, 0));
	for(i=0;i<length-1;i++){
		drawLine(img,Point(x[i],500-y[i]),Point(x[i+1],500-y[i+1]),hrubka_ciary);
		if(i<length-1) drawCircle(img,Point(x[i],500-y[i]),15);
                cvShowImage(nazov_okna, img);
	}
	cvReleaseImage(&img);
}
int mouseX=0;
int mouseY=200;
void mouseEvent(int evt, int x, int y, int flags, void* param){
     if(evt==CV_EVENT_LBUTTONDOWN){
	mouseX = x-250;
	mouseY = 500-y-20;
	printf("%d %d\n",mouseX,mouseY);
    }
}
void client5(char *ip,int port)
{
	struct RobotArm test = RobotArm_default;
	test.r0 = 100;
	test.r1 = 100;
	test.x0 = 250;
	test.y0 = 20;
	test.x2 = 0;
	test.y2 = 250;
	cvNamedWindow(nazov_okna, CV_WINDOW_AUTOSIZE);
	cvSetMouseCallback(nazov_okna, mouseEvent, 0);
	int q=-1;
	while(q!=27){
	test.x2 = mouseX;
	test.y2 = mouseY;
	if(angleArmEnd(&test)==0){
		int x[] = {(int)test.x0,(int)test.x1,(int)test.x2};
		int y[] = {(int)test.y0,(int)test.y1,(int)test.y2};
		plot(x,y,3);
	}
	else printf("Nie je mozne dosiahnut pozadovany bod\n");
	q = cvWaitKey(5);
}
cvDestroyWindow(nazov_okna);
}
