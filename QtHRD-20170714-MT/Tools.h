#ifndef TOOLS_H_
#define TOOLS_H_

#include<sstream>
#include<iomanip>
#include<vector>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<windows.h>
#include<fstream>
#include<cstddef>
#include<algorithm>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

//Utils.cpp function declaration
string Get_Time();
string Video_Capture();
string Video_Get(string filename);

Mat Rgb2Ntsc(Mat&frame);
int min4(int a, int b, int c, int d);
Mat frame2double(Mat&frame);
void node(float&X, float&Y, float&theta, float bboxPoints[][2]);

void prerotate(Mat&frame, Mat&faceImg,
	float&theta, float&X, float&Y,
	int bbox[],
	float bboxnew[]);

void frame3Cheek(int rows, int cols, Mat frame);
void show(string title, string note, Mat&src);
void bbox2Points(int bbox[], float bboxPoints[][2]);
void Mat2Array(Mat&src, float bboxPoints[][2]);
float sum(float*a, int length);
Mat fftshift(Mat&X, int length);
float max2(float*pows);
int max3(float*pows, int length);
void faceDetect(Mat&src, int*faceBorder);
void faceDetect(Mat&face, Rect&rect);
int faceReco(Mat&face, int tpye = 0);
void InsertFaceBorder(Mat&frame, int*Border);
int findPeaks(float*num, int count);
float IFE_Detecting(float*bvp, float fs, int Q, int LENGTH);
float detaQ(float*bvp, float max_IDX, int N, int Q);
Mat XT_Cut(Mat&src);
#endif
