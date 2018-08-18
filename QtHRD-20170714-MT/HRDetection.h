/*
**Non-contact heart rate detection software based on OpenCV3.1 and Qt 5.7
**Author:Jason
**Date:2016-08-02
**
**
*/

//HeartRateDetect class defintion
#ifndef _HeartRateDetect_H
#define _HeartRateDetect_H

// OpenCV 3.1 Library
#include<opencv2\opencv.hpp>

// Cpp System Library
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
#include<chrono>
#include<ctime>

//facedetect library
#include"facedetect-dll.h"

//Qt 5
#include<qapplication.h>
#include<qdebug.h>
#include<qlabel.h>
#include<qguiapplication.h>
#include<qdialog.h>
#include<qwidget.h>
#include<qmainwindow.h>
#include<qtextcodec.h>
#include<QObject>
#include<qmessagebox.h>
#include<QtConcurrent\qtconcurrentrun.h>
#include<qthread.h>


#define MAX_LENGTH 300
#define MAX_SIZE 65536
#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640
#define ROI_ROWS 40
#define ROI_COLS 30
#define PI 3.141592653589793
#define DELAY 1000 / 25

using namespace std;
using namespace cv;
using namespace cv::face;

class HeartRateDetect :public QObject
{
	Q_OBJECT

public:
	static int st_num;
	int levels;
	bool isFirstTime;
	bool isFace;
	float fl;
	float fh;
	float fps;
	float heartRate;
	float time;
	int LENGTH;

	Mat frames[MAX_LENGTH];
	Mat tmp_frame;
	Mat faceCover;
	int faceBorder[4];
	float landmark[68][2];
	float bvp[MAX_LENGTH][ROI_ROWS][ROI_COLS];
	float perFrame_BVP[MAX_LENGTH];

	HeartRateDetect();

	bool faceModified();
	bool identification();
	void GaussStack();
	void IdealBandPass();
	bool fsAutoAdjust(const float&thisTime);
	void debugRecorder(ofstream&debug, string str);

	void ComputeHeartRate();
	bool faceIsFound(Mat&face);

signals:
	// test 
	void playVoiceSIGNAL(int fileName);
	//void setHRValueSIGNAL(const float&heartRate);
	//void setHRPlotSIGNAL(const float*bvp);
	void setFaceCoverSIGNAL(Mat&face, ofstream&debug);
};

#endif