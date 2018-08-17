/*
**	Author:Jason
**	Date:2016-11-04
*/

#include"HRDetection.h"
#include"Tools.h"

int HeartRateDetect::st_num = 0;
static ofstream g_debug("./info/HRD_Gobal_debug.txt", ios::app);
/*
** @brief - Constructor of the class HeartRateDetect Object.
** @parameter - void
*/
HeartRateDetect::HeartRateDetect()
{
	isFirstTime = true;
	levels = 4;
	fl = 2.0f;
	fh = 2.6f;
	fps = 30.0f;
	heartRate = 0.0f;
	LENGTH = MAX_LENGTH;

	for (size_t i = 0; i < LENGTH; i++)
	{
		perFrame_BVP[i] = 0;
	}

	for (size_t i = 0; i < 4; i++)
	{
		faceBorder[i] = 0;
	}
	//connect(this, SIGNAL(setFaceCover(Mat&)), this, SLOT(setFaceCover(Mat&)));
}

/*
**@brief - Determine whether there is face in the video frames
**@parameter - void
*/
bool HeartRateDetect::faceIsFound(Mat&face)
{
	ofstream debug(".//info//faceIsFound.txt");
	bool flag(true);

	faceDetect(face, faceBorder);
	if (faceBorder[2] == 0 && faceBorder[3] == 0){
		flag = false;
		isFace = false;
	}
	else{
		faceCover = face(Rect(faceBorder[0], faceBorder[1], faceBorder[2], faceBorder[3])).clone();
		if (isFirstTime){
			emit playVoiceSIGNAL(1);
			isFirstTime = false;
		}
		isFace = true;
	}
	debug << "setFaceCover is emit!!!" << endl;

	return flag;
}

/*
**@brief - Do not use the rotation correction method.
**@parameter - void
*/
bool HeartRateDetect::faceModified(){
	ofstream debug("./info/HRD_faceModified.txt", ios::app);
	debugRecorder(g_debug, "at faceModified beginning...");
	bool ModifiedIsOK(true);
	for (size_t i = 0; i < LENGTH; i++)
	{
		if (i % 30 == 0){
			faceDetect(frames[i], faceBorder);

			debugRecorder(debug, "at faceModified function,i = " + to_string(i) +
				",faceBorder[0] = " + to_string(faceBorder[0]) +
				",faceBorder[1] = " + to_string(faceBorder[1]) +
				",faceBorder[2] = " + to_string(faceBorder[2]) +
				",faceBorder[3] = " + to_string(faceBorder[3]));

			if (faceBorder[2] == 0 && faceBorder[3] == 0){
				ModifiedIsOK = false;
				break;
			}
			else if (i == 0){
				Mat temp = frames[i](Rect(faceBorder[0], faceBorder[1], faceBorder[2], faceBorder[3])).clone();
				debugRecorder(debug, "at faceModified,FaceCover is emitted!!!");
				emit setFaceCoverSIGNAL(temp, g_debug);
			}
		}
		frames[i] = frames[i](Rect(faceBorder[0], faceBorder[1], faceBorder[2], faceBorder[3])).clone();
	}
	debugRecorder(g_debug, "at faceModified,all is over!");
	return ModifiedIsOK;
}

/*
**@brief - Gaussian pyramid image decomposition
**@parameter - void
*/
void HeartRateDetect::GaussStack(){

	int index(0);
	debugRecorder(g_debug, "GaussStack is begin!");

	do
	{
		// Cut out the XT profile first
		Mat gaussFrame = XT_Cut(frames[index]);
		for (int i = 0; i < levels; i++){
			GaussianBlur(gaussFrame, gaussFrame, Size(5, 5), 0, 0, BORDER_DEFAULT);
			pyrDown(gaussFrame, gaussFrame, Size(gaussFrame.cols / 2, gaussFrame.rows / 2));
		}
		// The conversion of color gamut decomposition by the top pyramid
		Mat YIQ_tmp(gaussFrame.size(), CV_32FC3);
		YIQ_tmp = Rgb2Ntsc(gaussFrame);

		frames[index] = YIQ_tmp.clone();
		index++;

		//emit updateProcessProgress(msg, floor((index)* 100.0 / LENGTH));
	} while (frames[index].data&&index < LENGTH);
	debugRecorder(g_debug, "pyrDown is over!!!");
	//emit closeProgressDialog();
}

/*
**@brief - Ideal band-pass filter, get the heart rate signal.
**@parameter - void
*/
void HeartRateDetect::IdealBandPass(){

	debugRecorder(g_debug, "IdealBand_PerPiexl is start...");

	float* Freq = new float[LENGTH];

	for (int i = 0; i < LENGTH; i++){
		Freq[i] = ((float)i) / LENGTH * fps;
	}

	float *mask_array = new float[LENGTH];
	for (int i = 0; i < LENGTH; i++){
		if (Freq[i]<fh&&Freq[i]>fl){
			mask_array[i] = 1.0f;
		}
		else{
			mask_array[i] = 0.0f;
		}
	}
	Mat mask(1, LENGTH, CV_32F, mask_array);

	int rowsNum = frames[0].rows;
	int colsNum = frames[0].cols;

	float*perPixel = new float[LENGTH];

	//I, j pixel control position , k control frames
	for (int i = 0; i < rowsNum; i++)
	{
		for (int j = 0; j < colsNum; j++)
		{
			for (int k = 0; k < LENGTH; k++){
				perPixel[k] = frames[k].at<Vec3f>(i, j)[0];
			}
			Mat temp(1, LENGTH, CV_32F, perPixel);


			dft(temp, temp);
			mulSpectrums(temp, mask, temp, DFT_ROWS);
			idft(temp, temp);

			for (int k = 0; k < LENGTH; k++){
				bvp[k][i][j] = temp.at<float>(k);
			}
		}
	}
	delete[] Freq;
	delete[] mask_array;
	delete[] perPixel;
	debugRecorder(g_debug, "IdealBand_PerPiexl is over.");
}

/*
**@brief - Compute the heartRate by perFrame_bvp.
**@parameter - void
*/
void HeartRateDetect::ComputeHeartRate(){

	debugRecorder(g_debug, "computeHR is begin!!!");

	float sum(0.0f);
	float avg_sum(0.0f);

	int rowsNum = frames[0].rows;
	int colsNum = frames[0].cols;

	debugRecorder(g_debug, "bvp compution is begin!!!");

	for (int k = 0; k < LENGTH; k++){
		sum = 0.0f;
		for (int i = 0; i < rowsNum; i++){
			for (int j = 0; j < colsNum; j++){
				sum += bvp[k][i][j];
			}
		}
		avg_sum = sum / (rowsNum*colsNum);
		perFrame_BVP[k] = avg_sum;
	}
	debugRecorder(g_debug, "bvp compution is over!!!");

	int peaksNum = findPeaks(perFrame_BVP, LENGTH);
	int heartRate1 = peaksNum*fps * 60 / LENGTH;

	heartRate = IFE_Detecting(perFrame_BVP, fps, 500, LENGTH);

	//emit setHRValueSIGNAL(heartRate);
	//emit setHRPlotSIGNAL(perFrame_BVP);

	debugRecorder(g_debug, "fl = " + to_string(fl) + "fh = " + to_string(fh));
	debugRecorder(g_debug, "At compute HR,the heartrate is " + to_string(heartRate));
	debugRecorder(g_debug, "The result of heartRate1 is " + to_string(heartRate1));
}

/*
**@brief - After the video input, adjust the frame rate.
**@parameter - void
*/
bool HeartRateDetect::fsAutoAdjust(const float&thisTime)
{
	bool isAdjust(true);
	fps = LENGTH / thisTime;
	return isAdjust;
}

/*
**@brief - face recongnition function.
**@parameter - .
*/
bool HeartRateDetect::identification()
{
	bool Recongnition(false);
	int predict = faceReco(faceCover);
	if (predict != -1){
		Recongnition = true;
	}
	return Recongnition;
}
/*
**@brief - Record the time of the debug.
**@parameter - ofstream debug:pass the file pointer.
*/
void HeartRateDetect::debugRecorder(ofstream&debug, string str)
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	debug << "[" << std::put_time(std::localtime(&t), "%y-%m-%d %H:%M:%S") << "][INFO : " << str << "]" << endl;
}