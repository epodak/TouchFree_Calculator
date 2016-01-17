#ifndef CIRCULARPROGRESSBARR_HEADER
#define CIRCULARPROGRESSBARR_HEADER
#include <string>
#include "opencv2/opencv.hpp"
using namespace cv;
#define TIME_COUNTER			15.0
#define NUMBER_COLOR			cv::Scalar(0, 0, 255)	// Sayilarin rengi
#define NUMBER2_COLOR			cv::Scalar(0, 200, 200)	// Secilen Sayilarin ekrandaki rengi
#define NUMBER3_COLOR			cv::Scalar(0, 200, 0)	// Secilen Sayilarin onay rengi
#define BORDER_COLOR			CV_RGB(120, 120, 120)	// cizgilerin rengi
#define PROGRESSBAR_COLOR		cv::Scalar(0, 250, 0)	// Progress Bar rengi
#define SHADOW_COLOR			CV_RGB(0, 0, 0)			// golge rengi

class CircularProgressBar
{
private:
	int keyTurn = -1;

public:
	void drawObject(Mat &frames, int x, int y);
	/* secilen kutucuk cevresine cember cizen fonksiyon */
	void drawProgressBar(Mat frames, Point center, Size size, int timeCounter);
	CircularProgressBar();
};
#endif