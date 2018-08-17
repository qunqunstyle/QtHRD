#include"HRDetection.h"
#include"Tools.h"
#include"facedetect-dll.h"
using namespace std;
// 获取系统时间，并组装成文件名
string Get_Time()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	string day = to_string(sys.wDay);
	string month = to_string(sys.wMonth);
	string year = to_string(sys.wYear);
	string hour = to_string(sys.wHour);
	string min = to_string(sys.wMinute);
	string sec = to_string(sys.wSecond);
	string fileName = year + "-" + month + "-" + day + " " + hour + "-" + min + "-" + sec;
	return fileName;
}

//Video_Capture 函数实现录制视频并保存的功能
string Video_Capture()
{
	namedWindow("Video", CV_WINDOW_AUTOSIZE);
	ofstream debug_Video_Captrue(".//info//dinfo_Video_Captrue.txt");
	VideoCapture capture(0);
	if (capture.isOpened()){
		debug_Video_Captrue << "Video Capture is open!" << endl;
	}

	capture.set(CV_CAP_PROP_FPS, 30.0);
	Mat frame;

	int fs = 30;
	int isColor = 1;
	int height = 640;
	int weight = 480;
	string filename = Get_Time();
	cout << filename << endl;
	VideoWriter writer(filename, CV_FOURCC('D', 'I', 'V', 'X'), fs, Size(height, weight), isColor);
	//VideoWriter writer(filename, CV_FOURCC('M', 'J', 'P', 'G'), fs, Size(height, weight), isColor);
	//VideoWriter writer(filename, -1, fs, Size(height, weight), isColor);

	for (int i = 0; i < 330; i++){
		capture >> frame;
		writer << frame;
		imshow("Video", frame);
		waitKey(1000 / 1000);
	}

	debug_Video_Captrue << "Video Capture is over!" << endl;
	destroyWindow("Video");
	capture.release();
	return filename;
}


//Video_Get函数实现输入一个文件名，对改文件名进行测试，如果可以打开，则传递该文件名
string Video_Get(string filename)
{
	filename = ".\\data\\" + filename + ".avi";
	VideoCapture capture(filename);
	if (!capture.isOpened()){
		cout << "Open file is Wrong!" << endl;
		cout << filename << endl;
		system("pause");
		exit(0);
	}
	else{
		cout << filename << " is avaiable!" << endl;
		system("pause");
		system("cls");
	}
	capture.release();
	return filename;
}

// RGB往NTSC色域的转换  0-B-Q,1-G-I,2-R-Y
Mat Rgb2Ntsc(Mat&frame)
{
	Mat dst = frame.clone();
	frame.convertTo(frame, CV_32FC3);
	dst.convertTo(dst, CV_32FC3);

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++){
			dst.at<Vec3f>(i, j)[2] = saturate_cast<float>(((0.299*frame.at<Vec3f>(i, j)[2] +
				0.587*frame.at<Vec3f>(i, j)[1] +
				0.114*frame.at<Vec3f>(i, j)[0])) / 255);
			dst.at<Vec3f>(i, j)[1] = saturate_cast<float>(((0.596*frame.at<Vec3f>(i, j)[2] +
				-0.274*frame.at<Vec3f>(i, j)[1] +
				-0.322*frame.at<Vec3f>(i, j)[0])) / 255);
			dst.at<Vec3f>(i, j)[0] = saturate_cast<float>(((0.211*frame.at<Vec3f>(i, j)[2] +
				-0.523*frame.at<Vec3f>(i, j)[1] +
				0.312*frame.at<Vec3f>(i, j)[0])) / 255) * 200;
		}
	}
	return dst;
}

int compare(const void*x, const void*y)
{
	return *(int*)x - *(int*)y;
}

int min4(int a, int b, int c, int d)
{
	int sortArray[] = { a, b, c, d };
	qsort(sortArray, 4, sizeof(float), compare);
	return sortArray[0];
}

void node(float&X, float&Y, float&theta, float bboxPoints[][2])
{
	float X1[] = { bboxPoints[0][0], bboxPoints[0][1] };
	float Y1[] = { bboxPoints[2][0], bboxPoints[2][1] };
	float X2[] = { bboxPoints[1][0], bboxPoints[1][1] };
	float Y2[] = { bboxPoints[3][0], bboxPoints[3][1] };

	/*cout << "In node,cheek the array X and Y:" << endl;

	cout << "X1=" << X1[0] << " " << X1[1] << endl;
	cout << "Y1=" << Y1[0] << " " << Y1[1] << endl;
	cout << "X2=" << X2[0] << " " << X2[1] << endl;
	cout << "Y2=" << Y2[0] << " " << Y2[1] << endl;

	*/

	float k1(0), k2(0);
	float b1(0), b2(0);
	if (X1[0] == Y1[0]){
		//cout << "At node if-1" << endl;
		X = X1[0];
		k2 = (Y2[1] - X2[1]) / (Y2[0] - X2[0]);
		b2 = X2[1] - k2*X2[0];
		Y = k2*X + b2;
		theta = 45;
	}

	if (X2[0] == Y2[0]){
		cout << "At node if-2" << endl;
		X = X2[0];
		k1 = (Y1[1] - X1[1]) / (Y1[0] - X1[0]);
		b1 = X1[1] - k1*X1[0];
		Y = k1*X + b1;
		theta = atan(k1) * 180 / PI;
		if (theta >= 0){
			theta = theta - 45;
		}
		else{
			theta = 135 + theta;
		}
	}

	if (X1[0] != Y1[0] && X2[0] != Y2[0]){
		//cout << "At node if-3" << endl;
		k1 = (Y1[1] - X1[1]) / (Y1[0] - X1[0]);
		k2 = (Y2[1] - X2[1]) / (Y2[0] - X2[0]);
		b1 = X1[1] - k1*X1[0];
		b2 = X2[1] - k2*X2[0];
		theta = atan(k1) * 180 / PI;

		/*cout << "k1=" << k1 << endl;
		cout << "k2=" << k2 << endl;
		cout << "b1=" << b1 << endl;
		cout << "b2=" << b2 << endl;
		cout << "theta=" << theta << endl;*/
		if (theta >= 0){
			theta -= 45;
		}
		else{
			theta += 135;
		}
		if (k1 == k2){
			X = 0;
			Y = 0;
		}
		else{
			X = (b2 - b1) / (k1 - k2);
			Y = k1*X + b1;
		}
	}
}

// 根据旋转角，以及旋转中心坐标，得到新的边界
void prerotate(Mat&frame, Mat&faceImg,
	float&theta, float&X, float&Y,
	int bbox[],
	float bboxnew[])
{
	if (abs(theta) <= 1){
		if ((bbox[2] % 2) == 0){
			bboxnew[2] = bbox[2] + 10;
		}
		else{
			bboxnew[2] = bbox[2] + 11;
		}

		if ((bbox[3] % 2) == 0){
			bboxnew[3] = bbox[3] + 10;
		}
		else{
			bboxnew[3] = bbox[3] + 11;
		}
		bboxnew[0] = round(X - bboxnew[2] / 2);
		bboxnew[1] = round(Y - bboxnew[3] / 2);

	}
	else if (abs(theta <= 5)){
		if ((bbox[2] % 2) == 0){
			bboxnew[2] = bbox[2] + 40;
		}
		else{
			bboxnew[2] = bbox[2] + 41;
		}

		if ((bbox[3] % 2) == 0){
			bboxnew[3] = bbox[3] + 40;
		}
		else{
			bboxnew[3] = bbox[3] + 41;
		}
		bboxnew[0] = round(X - bboxnew[2] / 2);
		bboxnew[1] = round(Y - bboxnew[3] / 2);
	}
	else{
		bboxnew[2] = min4(round(X), round(640 - X), round(Y), round(480 - Y)) * 2 - 2;
		bboxnew[3] = bboxnew[2];
		bboxnew[1] = round(Y - bboxnew[3] / 2);
		bboxnew[0] = round(X - bboxnew[2] / 2);
	}

	//cout << "bboxnew=(" << bboxnew[0] << "," << bboxnew[1] << "," << bboxnew[2] << "," << bboxnew[3] << ")" << endl;

	faceImg = (frame(Rect(bboxnew[0], bboxnew[1], bboxnew[2], bboxnew[3]))).clone();
}
// frame转double型
Mat frame2double(Mat&frame)
{
	Mat dst = frame.clone();
	frame.convertTo(frame, CV_32FC3);
	dst.convertTo(dst, CV_32FC3);

	for (int i = 0; i < frame.rows; i++)
	{
		for (int j = 0; j < frame.cols; j++){
			dst.at<Vec3f>(i, j)[2] = frame.at<Vec3f>(i, j)[2] / 255;
			dst.at<Vec3f>(i, j)[1] = frame.at<Vec3f>(i, j)[1] / 255;
			dst.at<Vec3f>(i, j)[0] = frame.at<Vec3f>(i, j)[0] / 255;
		}
	}
	return dst;
}

void frame3Cheek(int rows, int cols, Mat frame)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//cout << frame.at<Vec3f>(i, j) << endl;
		}
	}
}

void show(string title, string note, Mat&src)
{

	if (!note.empty()){
		//cout << note << endl;
	}
	/*namedWindow(title, WINDOW_NORMAL);
	imshow(title, src);
	waitKey(0);
	destroyWindow(title);*/
}

void bbox2Points(int bbox[], float bboxPoints[][2])
{
	// 左上角
	bboxPoints[0][0] = bbox[0];
	bboxPoints[0][1] = bbox[1];
	// 右上角
	bboxPoints[1][0] = bbox[0] + bbox[2];
	bboxPoints[1][1] = bbox[1];
	// 左下角
	bboxPoints[2][0] = bbox[0] + bbox[2];
	bboxPoints[2][1] = bbox[1] + bbox[3];
	// 右下角
	bboxPoints[3][0] = bbox[0];
	bboxPoints[3][1] = bbox[1] + bbox[3];
}

// 将1x4的双通道Mat传值到4x2的float二维矩阵当中
void Mat2Array(Mat&src, float bboxPoints[][2])
{
	// src是1*4的双通道矩阵，代表4个点的坐标
	for (int i = 0; i < 4; i++){
		for (int c = 0; c < 2; c++){
			bboxPoints[i][c] = src.at<Vec2f>(i)[c];
		}
	}
}

int cmp(const void*x, const void*y){
	return *(int*)y - *(int*)x;
}

float max2(float*pows)
{
	qsort(pows, 148, sizeof(float), cmp);
	return pows[0];
}

int max3(float*pows, int length)
{
	int flag(0);
	int temp(pows[0]);
	for (int i = 0; i < length; i++){
		if (temp < pows[i]){
			flag = i;
			temp = pows[i];
		}
	}
	return flag;
}

void faceDetect(Mat&src, int*faceBorder)
{
	int index(0);
	int* pResults = NULL;

	Mat frame = src.clone();
	short x(0);
	short y(0);
	short w(0);
	short h(0);
	cvtColor(frame, frame, CV_BGR2GRAY);
	pResults = facedetect_frontal_tmp((unsigned char*)(frame.ptr(0)),
		frame.cols, frame.rows, frame.step,
		1.2f, 5, 24);

	for (int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short*)(pResults + 1)) + 6 * i;
		x = p[0];
		y = p[1];
		w = p[2];
		h = p[3];
	}

	faceBorder[0] = x;
	faceBorder[1] = y;
	faceBorder[2] = w;
	faceBorder[3] = h;
}

void faceDetect(Mat&face, Rect&rect){

	int index(0);
	int* pResults = NULL;

	Mat frame = face.clone();

	short x(0);
	short y(0);
	short w(0);
	short h(0);

	cvtColor(frame, frame, CV_BGR2GRAY);
	pResults = facedetect_frontal_tmp((unsigned char*)(frame.ptr(0)),
		frame.cols, frame.rows, frame.step,
		1.2f, 5, 24);

	for (int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short*)(pResults + 1)) + 6 * i;
		x = p[0];
		y = p[1];
		w = p[2];
		h = p[3];
	}

	rect.x = x;
	rect.y = y;
	rect.width = w;
	rect.height = h;
}

int faceReco(Mat&face, int type){
	// load the xml model by type.
	if (!face.data){
		return -1;
	}
	Ptr<FaceRecognizer> model;
	int predict(-1);

	switch (type){
	case 0:
	{
			  model = createLBPHFaceRecognizer();
			  model->load("./xml/MyFaceLBPModel.xml");
			  break;
	}
	case 1:
	{
			  model = createEigenFaceRecognizer();
			  model->load("./xml/MyFacePCAModel.xml");
			  break;
	}
	case 2:
	{
			  model = createFisherFaceRecognizer();
			  model->load("./xml/MyFaceFisherFaceRecognizer.xml");
			  break;
	}
	default:
	{
			   std::cout << "this face recognition type is not support!" << endl;
			   return -1;
	}
	}
	Mat faceRec;
	cvtColor(face, faceRec, CV_BGR2GRAY);
	equalizeHist(faceRec, faceRec);
	Rect faceBorderRect;
	int border[4];
	// detect to get the boredr of the face,and convert the array to the rect.
	faceDetect(faceRec, faceBorderRect);

	if (faceRec.rows > 120){
		resize(faceRec, faceRec, Size(92, 112));
	}

	if (faceRec.data){
		predict = model->predict(faceRec);
	}
	return predict;
}

// 根据检测出的人脸插入矩形框
void InsertFaceBorder(Mat&frame, int*Border)
{
	Mat temp = frame.clone();
	faceDetect(temp, Border);

	rectangle(frame, Point(Border[0], Border[1]),
		Point(Border[0] + Border[2], Border[1] + Border[3]),
		Scalar(0, 255, 255), 1, LINE_8, 0);

	//delete Border;
	namedWindow("ROI-Face", WINDOW_AUTOSIZE);
	imshow("ROI-Face", frame);
	waitKey(0);
	destroyAllWindows();
}

int findPeaks(float*num, int count)
{
	vector<float> sign;
	for (int i = 1; i<count; i++){
		float diff = num[i] - num[i - 1];
		if (diff>0){
			sign.push_back(1);
		}
		else if (diff<0){
			sign.push_back(-1);
		}
		else{
			sign.push_back(0);
		}
	}
	vector<float> indMax;
	vector<float> indMin;

	for (int j = 1; j<sign.size(); j++){
		float diff = sign[j] - sign[j - 1];
		if (diff<0){
			indMax.push_back(j);
		}
		else if (diff>0){
			indMin.push_back(j);
		}
	}
	cout << "peaks'number = " << indMax.size() << endl;
	return indMax.size();
}

float sum(float*a, int length)
{
	float sum = 0.0f;
	for (int i = 0; i < length; i++)
	{
		sum += a[i];
	}
	return sum;
}

Mat fftshift(Mat&X, int length)
{
	Mat dst(X.size(), CV_32F);
	if (length % 2){
		int i;
		for (i = 0; i < length / 2; i++)
		{
			dst.at<float>(i) = X.at<float>(length / 2 + i + 1);
			dst.at<float>(length / 2 + i) = X.at<float>(i);
		}
		dst.at<float>(length - 1) = X.at<float>(length / 2);
	}
	else{
		for (int i = 0; i < length / 2; i++)
		{
			dst.at<float>(i) = X.at<float>(length / 2 + i);
			dst.at<float>(length / 2 + i) = X.at<float>(i);
		}
	}
	return dst;
}

float IFE_Detecting(float*bvp, float fs, int Q, int LENGTH)
{
	int N = LENGTH;
	bool show_flag = false;

	Mat tmp_X(1, N, CV_32F, bvp);
	Mat X = tmp_X.clone();
	X.mul(100);
	// 检查输入矩阵
	if (show_flag){
		cout << "cheek the input:" << endl;
		for (int i = 0; i < X.cols; i++)
		{
			cout << "X.at<float>(" << i << ")=" << X.at<float>(i) << endl;
		}
		cin.get();
		system("cls");
	}

	Mat planes[] = { Mat_<float>(X), Mat::zeros(X.size(), CV_32F) };
	Mat complexI;

	merge(planes, 2, complexI);
	dft(complexI, complexI);



	// 傅里叶变换后，检查变换结果
	if (show_flag){
		cout << "After dft,cheek the planes:" << endl;
		for (int i = 0; i < planes[0].cols; i++)
		{
			cout << "complexI.at<Vec2f>(" << i << ")=" << complexI.at<Vec2f>(i) << endl;
		}
		cin.get();
		system("cls");
	}

	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	// 复数取模之后，检查结果
	if (show_flag){
		cout << "After magnitude,cheek the planes:" << endl;
		for (int i = 0; i < planes[0].cols; i++)
		{
			cout << "planes[0].at<float>(" << i << ")=" << planes[0].at<float>(i) << endl;
		}
		cin.get();
		system("cls");
	}

	// 对傅里叶变换的结果进行移频
	Mat shift_planes = fftshift(planes[0], planes[0].cols);
	// 检查移频之后的结果
	if (show_flag){
		cout << "After fftshift,cheek the shift_planes:" << endl;
		for (int i = 0; i < shift_planes.cols; i++)
		{
			cout << "shift_planes.at<float>(" << i << ")=" << shift_planes.at<float>(i) << endl;
		}
		cin.get();
		system("cls");
	}

	// k是构造频谱的临时矩阵
	Mat k(1, N, CV_32F);
	// freq是对应的频谱
	Mat freq_All(1, N, CV_32F);

	int fN = N - N % 2;
	float temp = -fN / 2;

	for (int i = 0; i < LENGTH; i++)
	{
		k.at<float>(0, i) = temp++;
	}

	float T = N / fs;
	float detaF = 1 / T;

	freq_All = k.mul(detaF);
	// 检查频谱
	if (show_flag){
		cout << "cheek the freq:" << endl;
		for (int i = 0; i < freq_All.cols; i++){
			cout << "freq_All.at<float>(" << i << ")=" << freq_All.at<float>(i) << endl;
		}
		cin.get();
		system("cls");
	}

	int one_IDX = fN / 2 + 1;

	Mat freq_Positive = freq_All(Rect(one_IDX, 0, N - one_IDX, 1)).clone();
	// 检查频域正半轴截取结果
	if (show_flag){
		cout << "cheek the freq_Positive:" << endl;
		for (int i = 0; i < freq_Positive.cols; i++)
		{
			cout << "freq_Positive.at<float>(" << i << ")=" << freq_Positive.at<float>(i) << endl;
		}
		cin.get();
		system("cls");
	}

	Mat amp = shift_planes(Rect(one_IDX, 0, N - one_IDX, 1)).clone();
	// 检查功率谱对应正半轴截取结果
	if (show_flag){
		cout << "cheek the amp:" << endl;
		for (int i = 0; i < amp.cols; i++){
			cout << "amp[" << i << "]=" << amp.at<float>(0, i) << endl;
		}
		cin.get();
		system("cls");
	}

	float*pows = new float[LENGTH];
	for (int i = 0; i < amp.cols; i++){
		pows[i] = pow(amp.at<float>(i), 2);
	}
	// 检查最后计算得到的功率谱
	if (show_flag){
		cout << "cheek pows elements:" << endl;
		for (int i = 0; i < amp.cols; i++){
			cout << "pows[" << i << "]=" << pows[i] << endl;
		}
		cin.get();
	}

	int max_pos = max3(pows, amp.cols);
	cout << "amp.cols=" << amp.cols << endl;
	cout << "max_pos=" << max_pos << endl;
	cout << "freq_Positive[" << max_pos << "]=" << freq_Positive.at<float>(max_pos) << endl;

	float dQ = detaQ(bvp, max_pos, LENGTH, 500);

	cout << "detaQ=" << dQ << endl;
	cout << "detaF=" << detaF << endl;
	cout << "deta=" << dQ*detaF << endl;

	delete[] pows;
	return abs((freq_Positive.at<float>(max_pos)) + dQ*detaF)*60.0f;
}

float detaQ(float*bvp, float max_IDX, int N, int Q)
{
	bool show_flag = false;
	max_IDX++;
	if (show_flag){
		cout << "Before start,cheek the input:" << endl;
		for (int i = 0; i < 100; i++)
		{
			cout << "bvp[" << i << "]=" << bvp[i] << endl;
		}
		cin.get();
		system("cls");
	}

	float deta = 0.0f;
	float p1 = -0.5f;
	float p2 = 0.5f;

	float*e1_Imaginary = new float[N];
	float*e1_Real = new float[N];

	float*e2_Imaginary = new float[N];
	float*e2_Real = new float[N];

	float H = 0.0f;;
	float x1_Real = 0.0f;
	float x1_Imaginary = 0.0f;

	float x2_Real = 0.0f;
	float x2_Imaginary = 0.0f;

	for (int j = 0; j < Q; j++)
	{
		x1_Real = 0.0f;
		x2_Real = 0.0f;
		x1_Imaginary = 0.0f;
		x2_Imaginary = 0.0f;

		float test1 = 0.0f;
		float test2 = 0.0f;

		for (int i = 0; i < N; i++)
		{
			x1_Real += cos((-2 * PI*(max_IDX + deta + p1) / N)*i)*bvp[i];
			x1_Imaginary += sin((-2 * PI*(max_IDX + deta + p1) / N)*i)*bvp[i];
			if (show_flag){
				cout << i << ":" << "A1=" << x1_Real << "+" << x1_Imaginary << "i" << endl;
				cin.get();
			}

			x2_Real += cos((-2 * PI*(max_IDX + deta + p2) / N)*i)*bvp[i];
			x2_Imaginary += sin((-2 * PI*(max_IDX + deta + p2) / N)*i)*bvp[i];

			if (show_flag){
				cout << i << ":" << "A2=" << x2_Real << "+" << x2_Imaginary << "i" << endl;
				cin.get();
			}
		}

		if (show_flag){
			cout << "x1_Real=" << x1_Real << endl;
			cout << "x1_Imaginary=" << x1_Imaginary << endl;
			cout << "test1=" << test1 << endl;
			cout << "test2=" << test2 << endl;
			cin.get();
		}
		for (int i = 0; i < N; i++)
		{

		}

		if (show_flag){
			cout << "x2_Real=" << x2_Real << endl;
			cout << "x2_Imaginary=" << x2_Imaginary << endl;
			cin.get();
		}

		H = 0.5*(pow((pow(x2_Real, 2) + pow(x2_Imaginary, 2)), 0.5) - pow((pow(x1_Real, 2) + pow(x1_Imaginary, 2)), 0.5)) /
			(pow((pow(x2_Real, 2) + pow(x2_Imaginary, 2)), 0.5) + pow((pow(x1_Real, 2) + pow(x1_Imaginary, 2)), 0.5));
		deta += H;
		if (show_flag){
			cout << j << ":" << "deta=" << deta << endl;
			cin.get();
		}
	}
	delete[] e1_Imaginary;
	delete[] e1_Real;
	delete[] e2_Imaginary;
	delete[] e2_Real;

	return deta;
}

Mat XT_Cut(Mat&src)
{
	Mat temp;
	/*int cenH(320);
	int cenW(320);
	int Lcut = 100;
	int halfHLcut = Lcut / 2;
	int halfWLcut = Lcut / 2;*/
	//resize(src, src, Size(200, 200));
	int width = src.cols*0.2;
	int height = src.rows*0.4;
	int cutLen = src.rows*0.6;
	temp = src(Rect(width, height, cutLen, cutLen)).clone();
	resize(temp, temp, Size(400, 400));
	return temp;
}