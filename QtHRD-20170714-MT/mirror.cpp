#include "mirror.h"
#include"Tools.h"
#include<iostream>
#include<Windows.h>
#include<process.h>
#include<mmsystem.h>
#include<cstdio>
#include<ctime>
#include<chrono>
#include<iomanip>
#include<QtConcurrent\qtconcurrentrun.h>
#include<cassert>

// 
#pragma comment(lib,"WinMM.Lib")

ofstream g_debug("./info/Mirror_Global_Debug.txt");
//volatile bool vistitAccess = true;

/*
**@brief - MultiThread methods to detect HR.
**@parameter - heartRate,Heart rate value of the detection.
*/
bool Mirror::MultiThreadHRD()
{
	debugRecorder(g_debug, "[MultiThreadHRD]the thread function will be called!");
	// initialize the double circular list.
	initialization();

	QtConcurrent::run(this, &Mirror::subThreadGetFrames);
	QtConcurrent::run(this, &Mirror::subThreadCaculateHRD);
	debugRecorder(g_debug, "[MultiThreadHRD]this function will be over!");
	return true;
}

/*
**@brief - initialize the double circular linked list.
**@parameter - void
*/
void Mirror::initialization(){

	debugRecorder(g_debug, "[initialization]beginning...");
	float tickTime = getTickCount();
	head = new struct data;
	tail = new struct data;
	current = new struct data;

	tail->next = head;
	head->piror = tail;

	head->next = current;
	current->piror = head;

	int index(0);
	head->num = index;
	current->num = ++index;

	while (index < THREAD_FRAMES_COUNTS - 1){
		frames temp = new struct data;
		index++;
		temp->num = index;
		current->next = temp;
		temp->piror = current;
		current = temp;
	}
	tail->num = THREAD_FRAMES_COUNTS;
	current->next = tail;
	tail->piror = current;

	tickTime = (getTickCount() - tickTime) / getTickFrequency();
	debugRecorder(g_debug, "[initialization]" + to_string(tickTime) + " s");
}

/*
**@brief - Thread function which is used to get frames first.
**@parameter - PVOID pm
*/
/*unsigned int __stdcall*/
void Mirror::subThreadGetFrames(/*PVOID pm*/)
{
	ofstream debug("./info/Mirror_subThreadGetFrames.txt", ios::app);
	debugRecorder(g_debug, "[subThreadGetFrames]beginning...");
getFrames_restart:
	Mat temp;
	bool isFirstSetCover = true;
	volatile bool isFirstCaculation = true;

	debugRecorder(debug, "[=====================================]");
	capture.open(0);
	if (capture.isOpened()){
		current = head;
		capture.set(CAP_PROP_FPS, FPS);
		capture.set(CAP_PROP_FRAME_HEIGHT, 480);
		capture.set(CAP_PROP_FRAME_WIDTH, 640);
		namedWindow("Video", WINDOW_AUTOSIZE);
	}
	else{
		capture.release();
		goto getFrames_restart;
	}
initilization:
	// Abandon the first 20 frames.
	int cammerInitilization = 20;
	while (cammerInitilization--){
		capture >> temp;
	}
check:
	int checkCount(0);
	// Check that the num member whether correct.
	while (current->frame.empty() && checkCount<THREAD_FRAMES_COUNTS){
		debugRecorder(debug, "current->num = " + to_string(current->num) + " check!");
		current = current->next;
		checkCount++;
	}
start:
	// When we begin to collect data at first time, we start with the head pointer.
	current = head;
	int index(0);

	// The temp variable is the intermediate variable used to receive the capture object.
	debugRecorder(g_debug, "[subThreadGetFrames]continue get frames...");
	while (continueGetFrames){
		/*****************************************
		the construction of while loop.
		while
		1. set first frame's cover.
		2. capture frame and check whether vaild.
		3. show the frame.
		4. update the control variable.
		end
		*******************************************/
		capture >> temp;
		// 1. The first frame image needs to set the cover.
		if (isFirstSetCover && current->num == 0){
			debugRecorder(debug, "index = " + to_string(current->num) + " ,emit setFaceCover");
			isFirstSetCover = false;
			face = temp.clone();
			emit setFaceCoverSIGNAL(face, debug);
		}
		// 2.capture frame and check whether vaild.
		current->frame = temp.clone();
		if (current->frame.empty()){
			debugRecorder(debug, "index = " + to_string(current->num) + " is empty!");
			continueGetFrames = false;
			continue;
		}
		else{
			debugRecorder(debug, "index = " + to_string(current->num) + " frames,memory is correct!");
		}
		// 3. show the frame.
		imshow("Video", temp);
		waitKey(DELAY / 10);

		if (isFirstCaculation && index == THREAD_FRAMES_COUNTS / 2){
			countsByGetFrames = index - 1;
			// activate the subthread of the HRD caculation.
			waitForHRD = false;
		}
		else if (isFirstCaculation && index == THREAD_FRAMES_COUNTS - 30){
			countsByGetFrames = index - 1;
			// close the subsection of the initialization.
			isFirstCaculation = false;
		}

		// 4. update the control variable.
		if (index == THREAD_FRAMES_COUNTS && continueGetFrames){
			countsByGetFrames = index - (int)FPS - 1;
			index = 0;
		}
		// The variable continueGetFrames control loop continues.
		if (continueGetFrames)
		{
			current = current->next;
			index++;
		}
		else{
			break;
		}
	}// while loop is end.
	destroyAllWindows();
	debugRecorder(debug, "[subThreadGetFrames]thread funcion is over!");
	//return 0;
}

/*
**@brief - Thread function which is used to caculate the HRD.
**@parameter - PVOID pm
*/
/*unsigned int __stdcall*/
void Mirror::subThreadCaculateHRD(/*PVOID pm*/)
{
	ofstream debug("./info/Mirror_subThreadCaculateHRD.txt", ios::app);
	debugRecorder(debug, "=======================================");
	debugRecorder(debug, "beginning...");

	debugRecorder(g_debug, "[subThreadCaculateHRD]beginning...");

	while (waitForHRD != false){
		// wait for the signal of HRD start.
	}

	// this variable index is used to count the number of the caculated frames
	int index(1);
	while (continueCaculateHRD&&continueGetFrames){
		float tickTime = getTickCount();
		// get the copy of current pointer.
		frames temp = current;
		// the 1st pointer node is abandoned.
		temp = temp->piror;
		// create an object of HRD and connect the SIGNAL function to this object.

		debugRecorder(debug, "All connection is combined!");
		// input the frames into HRD class
		// It conld be a bug!
		if (countsByGetFrames>100 && countsByGetFrames <= 200){
			HRD->LENGTH = countsByGetFrames;
		}
		debugRecorder(debug, "HRD->LENGTH = " + to_string(HRD->LENGTH));
		for (size_t i = 0; i < HRD->LENGTH; i++)
		{
			HRD->frames[HRD->LENGTH - i - 1] = temp->frame.clone();
			temp = temp->piror;
		}
		// modified the face included frame.
		if (!HRD->faceModified()){
			// if facedetect is failed,continue next loop.
			continue;
		}
		debugRecorder(debug, "HRD->faceModified has been excuted!");

		// Gauss pyramid.
		HRD->GaussStack();
		debugRecorder(debug, "HRD->GaussStack has been excuted!");

		// Ideal band passing.
		HRD->IdealBandPass();
		debugRecorder(debug, "HRD->ldealBandPass has been excuted!");

		// Caculate the value of heart rate.
		HRD->ComputeHeartRate();
		debugRecorder(debug, "HRD->ComputeHeartRate has been excuted!");

		if (visitAccess_setHRVaule){
			emit setHRValueSIGNAL(HRD->heartRate);
			debugRecorder(debug, "times = " + to_string(times) + " visitAccess_setHRVaule = " + to_string(visitAccess_setHRVaule) + " setHRValueSIGNAL is emit!");
		}
		else{
			debugRecorder(debug, "times = " + to_string(times) + " setHRValueSIGNAL is NOT emit!");
		}

		if (visitAccess_setHRPlot){
			emit setHRPlotSIGNAL(HRD->perFrame_BVP);
		}
		else{
			debugRecorder(g_debug, "[subThreadCaculateHRD]times = " + to_string(times) + " setHRPlotSIGNAL is NOT emit!");
		}

		tickTime = (getTickCount() - tickTime) / getTickFrequency();
		debugRecorder(debug, "at " + to_string(times) + " times detection,"
			+ "heartrate detection time:" + to_string(tickTime)
			+ " s, heartrate is " + to_string(HRD->heartRate));

		debugRecorder(g_debug, "[subThreadCaculateHRD]at " + to_string(times) + " times detection,"
			+ "heartrate detection time:" + to_string(tickTime)
			+ " s, heartrate is " + to_string(HRD->heartRate));

		// Update the control variable.
		index++;
		times++;
		//delete HRD;
		waitKey(1000);
	}
	delete HRD;
	HRD = nullptr;
	debugRecorder(debug, "at function subThreadCaculateHRD ending.this function will be over!");
	//return 0;
}

/*
**@brief - The constructor of the class Mirror to initialize the member variable.
**@parameter - void
*/
Mirror::Mirror(QWidget *parent)
: QWidget(parent),
ui(new Ui::MirrorClass)
{
	ui->setupUi(this);
	// HRD = new HeartRateDetect();

	countsByGetFrames = 0;
	continueCaculateHRD = true;
	continueGetFrames = true;
	waitForHRD = true;
	visitAccess_setHRPlot = true;
	visitAccess_setHRVaule = true;
	times = 1;

	debugRecorder(g_debug, "[Mirror constructor]all the variable is initialized!");

	HRD = new HeartRateDetect();
	if (HRD != nullptr){
		debugRecorder(g_debug, "[Mirror constructor]a new object is created!");
	}
	connect(HRD, SIGNAL(setFaceCoverSIGNAL(Mat&, ofstream&)), this, SLOT(setFaceCover(Mat&, ofstream&)), Qt::BlockingQueuedConnection);
	connect(this, SIGNAL(setHRValueSIGNAL(const float&)), this, SLOT(setHRValue(const float&)));
	connect(this, SIGNAL(setHRPlotSIGNAL(const float*)), this, SLOT(setHRPlot(const float*)));

	forecast_date_list << ui->forecast_0_date
		<< ui->forecast_1_date
		<< ui->forecast_2_date
		<< ui->forecast_3_date;
	forecast_temp_list << ui->forecast_0_temp
		<< ui->forecast_1_temp
		<< ui->forecast_2_temp
		<< ui->forecast_3_temp;
	forecast_icon_list << ui->forecast_0_icon
		<< ui->forecast_1_icon
		<< ui->forecast_2_icon
		<< ui->forecast_3_icon;

	ui->HR_Plot->setBackground(QColor(0, 0, 0));
	ui->HR_ValueLabel->setText(QStringLiteral("0.0"));

	choose = 0;
	manager = new QNetworkAccessManager(this);

	URL_1 = "http://wthrcdn.etouch.cn/weather_mini?city=";
	URL_2 = "http://wthrcdn.etouch.cn/WeatherApi?city=";

	time = new QTimer(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
	connect(time, SIGNAL(timeout()), this, SLOT(showTime()));
	connect(time, SIGNAL(timeout()), this, SLOT(showDateLabel()));
	connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(exitButton()));
	//
	connect(this, SIGNAL(setFaceCoverSIGNAL(Mat&, ofstream&)), this, SLOT(setFaceCover(Mat&, ofstream&)), Qt::BlockingQueuedConnection);

	time->start(1);
	manager->get(QNetworkRequest(QUrl("http://int.dpool.sina.com.cn/iplookup/iplookup.php")));

	setWindowFlags(Qt::FramelessWindowHint);
	showFullScreen();
	debugRecorder(g_debug, "[Mirror constructor]all the initialization is completed!");
}

Mirror::~Mirror()
{
	debugRecorder(g_debug, "[Mirror destructor]a object of class Mirror is destroied!");
}

/*
**@brief - After calculation,Heart rate value is displayed in the Qt interface.
**@parameter - heartRate,Heart rate value of the detection.
*/
void Mirror::setHRValue(const float&heartRate){

	ofstream debug("./info/Mirror_setHRValue.txt", ios::app);
	visitAccess_setHRVaule = false;

	debugRecorder(g_debug, "[setHRValue]beginning...");
	debugRecorder(debug, "==================================");
	debugRecorder(debug, "at " + to_string(times) + " times' setting Value!");
	// Keep two decimal precision
	int int_heartRate = (int)(heartRate * 100);
	float float2_heartRate = (float)int_heartRate / 100;

	// set the font size to 75 and type to YaHei.
	QFont heartRateFont("Microsoft YaHei", 75, 75);
	ui->HR_ValueLabel->setFont(heartRateFont);
	// Set the font color to white.
	QPalette color;
	color.setColor(QPalette::WindowText, Qt::white);
	ui->HR_ValueLabel->setPalette(color);
	ui->HR_ValueLabel->setText(QString::number(float2_heartRate));

	debugRecorder(debug, "float2_heartRate = " + to_string(float2_heartRate));
	debugRecorder(debug, "HR_ValueLabel is setted!");
	debugRecorder(g_debug, "[setHRValue]HR_ValueLabel is setted!");
	debugRecorder(g_debug, "[setHRValue]heart rate value is " + to_string(float2_heartRate));
	visitAccess_setHRVaule = true;
}

/*
**@brief - After calculation,draw the waveform of the heartrate.
**@parameter - bvp,the array of the
*/
void Mirror::setHRPlot(const float*bvp){

	ofstream debug("./info/Mirror_setHRPlot.txt", ios::app);
	visitAccess_setHRPlot = false;

	debugRecorder(g_debug, "[setHRPlot]beginning...");
	debugRecorder(debug, "======================================");
	debugRecorder(debug, "at " + to_string(times) + " times' setting Plots!");
	debugRecorder(debug, "visitAccess_setHRPlot = " + to_string(visitAccess_setHRPlot));
	debugRecorder(debug, "HRD->LENGTH=" + to_string(HRD->LENGTH));

	QVector<double> x(MAX_LENGTH), y(MAX_LENGTH);
	for (size_t i = 0; i < HRD->LENGTH; i++)
	{
		x[i] = i;
		y[i] = bvp[i];
	}

	ui->HR_Plot->addGraph();
	ui->HR_Plot->graph(0)->setData(x, y);

	ui->HR_Plot->xAxis->setLabel("time(s)");
	ui->HR_Plot->yAxis->setLabel("bvp-wave");

	ui->HR_Plot->rescaleAxes();
	ui->HR_Plot->setBackground(QColor(0, 0, 0));
	ui->HR_Plot->graph(0)->setPen(QPen(QColor(255, 255, 255), 3.0));

	ui->HR_Plot->replot();
	ui->HR_Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	debugRecorder(g_debug, "[setHRPlot]the plot is setted!");
	debugRecorder(debug, "the plot is setted!");
	visitAccess_setHRPlot = true;
}

/*
**@brief - When the face of frame is detected,refresh interface in the location specified.
**@parameter - void
*/
void Mirror::setFaceCover(Mat&face, ofstream&debug){
	// get the width of desktop.
	int width = QApplication::desktop()->width();
	debugRecorder(debug, "[setFaceCover]desktop width is" + to_string(width));
	cv::Size size;
	// Adjust the cover size according to the desktop size.
	if (width > 1440){
		size.width = 500;
		size.height = 500;
	}
	else{
		size.width = 300;
		size.height = 300;
	}

	int border[4];
	bool flag = true;
	faceDetect(face, border);
	if (border[2] == 0 && border[3] == 0 && face.data){
		flag = false;
	}
	else{
		flag = true;
		face = face(Rect(border[0], border[1], border[2], border[3])).clone();
	}
	debugRecorder(debug, "[setFaceCover]flag = " + to_string(flag));
	// According to the boolean variable flag,decide the cover setting.
	if (flag){

		cv::resize(face, face, size);
		face.convertTo(face, CV_8UC3);
		cvtColor(face, face, COLOR_BGR2RGB);

		QImage image((const unsigned char*)face.data,
			face.cols, face.rows,
			face.cols*face.channels(),
			QImage::Format_RGB888);

		ui->FaceCover->setPixmap(QPixmap::fromImage(image));
		debugRecorder(debug, "[setFaceCover]face cover is setted!");
	}
	else{
		Mat src(size, CV_8UC3, Scalar(0, 0, 0));
		cvtColor(src, src, COLOR_BGR2RGB);
		QImage image((const unsigned char*)src.data,
			src.cols, src.rows,
			src.cols*src.channels(),
			QImage::Format_RGB888);

		ui->FaceCover->setPixmap(QPixmap::fromImage(image));
		debugRecorder(debug, "[setFaceCover]face cover is NOT setted!");
	}
	debugRecorder(debug, "[setFaceCover]this function setFaceCover is indeed called!");
	debugRecorder(debug, "[setFaceCover]at setFaceCover function,the face cover is already setted!");
}


/*
**@brief - At Qt interface,show the current time.
**@parameter - void
**@notation - This function will be called frequently.
*/
void Mirror::showTime()
{
	QTime time = QTime::currentTime();
	QString timeStr = time.toString("hh:mm:ss");
	// set time in the interface.
	ui->timeLabel->setText(timeStr);
}

/*
**@brief - At Qt interface,show the current date.
**@parameter - void
*/
void Mirror::showDateLabel()
{
	//debugRecorder(g_debug, "at showTime function, QDate class is created!");
	QDate date = QDate::currentDate();
	QString dateStr = date.toString("dddd,MMM d,yyyy");
	// set date in the interface.
	ui->dateLabel->setText(dateStr);
	//debugRecorder(g_debug, "at showTime function, Qt Date Label is setted!");
}

/*
**@brief - This function is to achieve the forecast module function.
**@parameter - reply,Accept the QNetworkManager Object's requests.
*/
void Mirror::replayFinished(QNetworkReply *reply)
{
	debugRecorder(g_debug, "[replayFinished]Qt NetworkReply class is begin to work..");

	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray bytes = reply->readAll();
		// According to the IP address query city.
		if (choose == 0)
		{
			QString result = QString::fromLocal8Bit(bytes);
			debugRecorder(g_debug, "[replayFinished]searching city...");
			parseCity(result);
		}
		// According to the city query the weather of today.
		else if (choose == 1)
		{
			QString result(bytes);
			debugRecorder(g_debug, "[replayFinished]parse XML...");
			parseXml(result);
		}
		// According to the city query the weather over the next four days.
		else if (choose == 2)
		{
			QString result(bytes);
			debugRecorder(g_debug, "[replayFinished]parse JSON...");
			parseJson(result);
		}
	}
	else{
		QMessageBox::information(this, QStringLiteral("Error!"),
			QStringLiteral("Network error, please check the network connection"),
			QMessageBox::Ok, QMessageBox::Ok);
	}
	debugRecorder(g_debug, "[replayFinished]replay is over!");
}

/*
**@brief - Parsing the JSON data format
**@parameter - Json,The weather forecast of the JSON data format.
*/
void Mirror::parseJson(QString Json)
{
	debugRecorder(g_debug, "[parseJson]beginning");
	QByteArray byte_array;
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(Json), &json_error);

	if (json_error.error == QJsonParseError::NoError)
	{
		QJsonObject obj = parse_doucment.object();

		QJsonValue desc = obj.take("desc");
		if (desc.toString() != "OK")
		{
			debugRecorder(g_debug, "[parseJson]the network is disconnected!");
			QMessageBox::information(this, QStringLiteral("Sorry"), QStringLiteral("No the weather in this city"), QMessageBox::Ok, QMessageBox::Ok);
			return;
		}

		QJsonValue data = obj.take("data");
		today.ganmao = data.toObject().take("ganmao").toString();
		QJsonValue forecast1 = data.toObject().take("forecast");
		QJsonArray forecast2 = forecast1.toArray();
		for (int i = 0; i<5; i++)
		{
			QJsonValue value = forecast2.at(i);
			QJsonObject object = value.toObject();
			forecast[i].fengxiang = object.take("fengxiang").toString();
			forecast[i].date = object.take("date").toString();
			forecast[i].fengli = object.take("fengli").toString();
			forecast[i].high = object.take("high").toString();
			forecast[i].low = object.take("low").toString();
			forecast[i].type = object.take("type").toString();
		}

		for (int i = 0; i<4; i++)
		{
			// Set the date.
			forecast_date_list[i]->setText(QStringLiteral("%1").arg(forecast[i].date));
			// Set the temperature range.
			forecast_temp_list[i]->setText(QStringLiteral("%1 - %2").arg(forecast[i].low.split(" ").at(1)).arg(forecast[i].high.split(" ").at(1)));
			// Set the icon of weather's type.
			forecast_icon_list[i]->setPixmap(QPixmap(QStringLiteral("./images/%1").arg(forecast[i].type)));
		}

		ui->forecast_0_date->setText(QStringLiteral("今天"));

		QString url = URL_2 + city;
		choose = 1;
		manager->get(QNetworkRequest(QUrl(url)));
		debugRecorder(g_debug, "[parseJson]all the data about weather is setted,the request has send to search the city name");
	}
	else
	{
		QMessageBox::information(this, QStringLiteral("出错啦"), QStringLiteral("数据出错,请重试"), QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	debugRecorder(g_debug, "at parseJson function,parse is over");
}

/*
**@brief - Parsing the XML data format
**@parameter - Xml,The weather forecast of the XML data format.
*/
void Mirror::parseXml(QString Xml)
{
	debugRecorder(g_debug, "[parseXml]beginning...");
	QXmlStreamReader xml(Xml);

	while (!xml.atEnd())
	{
		if (xml.hasError())
		{
			debugRecorder(g_debug, "[parseXml]XML data is error!");
			QMessageBox::information(this, QStringLiteral("Error!"), QStringLiteral("Data error, please try again"), QMessageBox::Ok, QMessageBox::Ok);
			return;
		}
		else if (xml.isStartElement())
		{
			if (xml.name() == "city")
			{
				today.city = xml.readElementText();
			}
			else if (xml.name() == "updatetime")
			{
				today.updatetime = xml.readElementText();
			}
			else if (xml.name() == "wendu")
			{
				today.wendu = xml.readElementText();
			}
			else if (xml.name() == "fengli")
			{
				today.fengli = xml.readElementText();
			}
			else if (xml.name() == "shidu")
			{
				today.shidu = xml.readElementText();
			}
			else if (xml.name() == "fengxiang")
			{
				today.fengxiang = xml.readElementText();
			}
			else if (xml.name() == "sunrise_1")
			{
				today.sunrise = xml.readElementText();
			}
			else if (xml.name() == "sunset_1")
			{
				today.sunset = xml.readElementText();
				xml.clear();

				ui->todayTemp->setText(QStringLiteral("%1").arg(today.wendu));
				ui->windPower->setText(QStringLiteral("%1").arg(today.fengli));
				ui->windType->setText(QStringLiteral("%1").arg(today.fengxiang));

				return;
			}
			else
				xml.readNext();
		}
		else
			xml.readNext();
	}
	xml.clear();
	debugRecorder(g_debug, "[parseXml]XML data has parsed!");
}

/*
**@brief - Parsing the city's name to make the whole URL.
**@parameter - City,The name of the location.
*/
void Mirror::parseCity(QString City)
{
	debugRecorder(g_debug, "[parseCity]beginning...");
	city = City.split(QStringLiteral("	")).at(5);
	if (city == "")
	{
		debugRecorder(g_debug, "[parseCity]city data is null,network maybe disconnect!");
		/*QMessageBox::information(this, QStringLiteral("Prompt"), QStringLiteral("Can't locate the city, please query manually"), QMessageBox::Ok, QMessageBox::Ok);
		return;*/
	}

	ui->city->setText(city);

	debugRecorder(g_debug, "[parseCity]city name is " + city.toStdString());
	QString url = URL_1 + city;
	choose = 2;
	manager->get(QNetworkRequest(QUrl(url)));
	debugRecorder(g_debug, "[parseCity]the request to search weather has send!");
}

/*
**@brief - The exit button,force to exit the program.
**@parameter - void
*/
void Mirror::exitButton(){
	// Note that exit cannot close VideCapture, can only use the release.
	debugRecorder(g_debug, "[exitButton]beginning...");
	close();
	destroyAllWindows();

	continueCaculateHRD = false;
	continueGetFrames = false;
	debugRecorder(g_debug, "[exitButton]continueCaculateHRD = " + to_string(continueCaculateHRD));
	debugRecorder(g_debug, "[exitButton]continueGerFrames = " + to_string(continueGetFrames));
	waitForHRD = false;

	debugRecorder(g_debug, "[exitButton]In three seconds, the program will exit");

	while (HRD != nullptr){
		debugRecorder(g_debug, "[exitButton]HRD is NOT nullptr!!!");
	}

	debugRecorder(g_debug, "[exitButton]HRD = nullptr!the program will exit now!!!");
	if (capture.isOpened()){
		capture.release();
		debugRecorder(g_debug, "[exitButton]capture have been released!");
	}
	// delete the list of pointer 
	int index(0);
	while (index<THREAD_FRAMES_COUNTS){
		current = head;
		head = head->next;
		if (current->frame.empty()){
			delete current;
		}
		index++;
	}
	debugRecorder(g_debug, "[exitButton]All the node is deleted!!!");

	forecast_date_list.clear();
	forecast_icon_list.clear();
	forecast_temp_list.clear();
	qDeleteAll(forecast_date_list);
	qDeleteAll(forecast_icon_list);
	qDeleteAll(forecast_temp_list);
	debugRecorder(g_debug, "[exitButton]All the Qt list have been destroied be qDeleteAll!");

	delete manager;
	debugRecorder(g_debug, "[exitButton]manager is deleted!");
	delete time;
	debugRecorder(g_debug, "[exitButton]time is deleted!");
	delete ui;
	debugRecorder(g_debug, "[exitButton]ui is deleted!");
	delete this;
	debugRecorder(g_debug, "[exitButton]Object is deleted!");

	//g_debug.close();
	debugRecorder(g_debug, "[exitButton]All is Over!!!");
}

/*
**@brief - Real-time display dynamic waveform
**@parameter - void
*/
void Mirror::realTimeDrawPlot(){

}

/*
**@brief - As a slot function, play the voice of the specified type.
**@parameter - fileName, which voice file will be played.
*/
void Mirror::playVoice(int&fileName){

	LPCWSTR voice;
	if (fileName == 1){
		voice = TEXT("1.wav");
	}
	else if (fileName == 2){
		voice = TEXT("2.wav");
	}
	else if (fileName == 3){
		voice = TEXT("3.wav");
	}
	PlaySound(voice, NULL, SND_FILENAME | SND_SYNC);
}


/*
**@brief - Record the time of the debug.
**@parameter - ofstream debug:pass the file pointer.
*/
void Mirror::debugRecorder(ofstream&debug, string str){
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	debug << "[" << std::put_time(std::localtime(&t), "%y-%m-%d %H:%M:%S") << "]" << str << endl;
}