#ifndef MIRROR_H
#define MIRROR_H
// UI Library
#include <QtWidgets/QWidget>
#include "ui_mirror.h"

// OpenCV 3.2 Basic Library
#include<opencv2\opencv.hpp>
// OpenCV 3.2 opencv-contribe Library
#include<opencv2\face.hpp>

// C++11 System Library
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
#include<ctime>

//facedetect library
#include"facedetect-dll.h"

//Qt 5
#include<QApplication.h>
#include<QDebug.h>
#include<QLabel.h>
#include<QGuiapplication.h>
#include<QDialog.h>
#include<QWidget.h>
#include<QMainwindow.h>
#include<QTextcodec.h>
#include<QObject>
#include<QMessagebox.h>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QPixmap>
#include<QPaintEvent>
#include<QPainter>
#include<QPoint>
#include<QByteArray>
#include<QJsonParseError>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonValue>
#include<QXmlStreamReader>
#include<qtimer.h>
#include<QtConcurrent\qtconcurrentrun.h>

//HeartRateDetect Class
#include<HRDetection.h>

// Voice lib
#include<mmsystem.h>
#include<cassert>

// define pargma
// THREAD_FRAMES_COUNTS can not more than 500, 300 is suitable.
#define THREAD_FRAMES_COUNTS 350
#define FPS 25.0f
using namespace std;
using namespace cv;
using namespace cv::face;

typedef struct data* frames;

struct data{
	int num;
	Mat frame;
	frames piror;
	frames next;
};

struct Forecast
{
	QString fengxiang;
	QString fengli;
	QString high;
	QString type;
	QString low;
	QString date;
};

struct Today
{
	QString ganmao;
	QString city;
	QString updatetime;
	QString wendu;
	QString fengli;
	QString fengxiang;
	QString sunrise;
	QString sunset;
	QString shidu;
};

class Mirror : public QWidget
{
	Q_OBJECT

	protected slots:
	void replayFinished(QNetworkReply *reply);

private:
	bool isOK;

	// capture frames;
	VideoCapture capture;
	// control the function caculateHRD operator by contsByGetFrames.
	volatile int countsByGetFrames;
	volatile bool continueGetFrames;
	volatile bool continueCaculateHRD;
	volatile bool waitForHRD;
	volatile bool visitAccess_setHRPlot;
	volatile bool visitAccess_setHRVaule;
	volatile int times;
	// the object of MirrorClass pointer ui is used to contr
	Ui::MirrorClass*ui;
	// the object of HRDClass pointer.
	HeartRateDetect*HRD;
	// flag to choose weather type.
	int choose;

	// declare the struct variable.
	Forecast forecast[5];
	Today today;
	frames head;
	frames tail;
	frames current = head;
	// declare the Qt System Class Object variable. 
	QNetworkAccessManager *manager;
	QString URL_1;
	QString URL_2;
	QPixmap pixmap;
	QPoint move_point;

	QList<QLabel *> forecast_date_list;
	QList<QLabel *> forecast_temp_list;
	QList<QLabel *> forecast_icon_list;

	QString city;
	QTimer *time;

public:
	// face cover in the UI.
	Mat face;
	// declare the member function.
	Mirror(QWidget *parent = 0);
	~Mirror();

	void initialization();
	void debugRecorder(ofstream&debug, string str);

	void subThreadCaculateHRD();
	void subThreadGetFrames();
	bool MultiThreadHRD();
	void parseJson(QString Json);
	void parseXml(QString Xml);
	void parseCity(QString City);

	public slots:
	// Qt slots function's declaration
	void showTime();
	void showDateLabel();
	void exitButton();
	void setHRValue(const float&heartRate);
	void setHRPlot(const float*bvp);
	void setFaceCover(Mat&face, ofstream&debug);
	void playVoice(int&type);
	void realTimeDrawPlot();

signals:
	void setFaceCoverSIGNAL(Mat&face, ofstream&debug);
	void setHRValueSIGNAL(const float&);
	void setHRPlotSIGNAL(const float*);
};

#endif // MIRROR_H