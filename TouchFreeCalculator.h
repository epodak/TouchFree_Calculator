#ifndef TOUCHFREECALCULATOR_HEADER
#define TOUCHFREECALCULATOR_HEADER
#include <GL/glut.h>
#include <AR/gsub.h>
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>
#include "Calculator.h"
#include "MarkerPoint.h"
#include "RectangularButtons.h"
#include "CircularButtons.h"
#include "CircularProgressBar.h"
#include <string>
#include <iostream>
using namespace cv;
#define TIME_COUNTER	15.0

class TouchFreeCalculator
{
private:
	Calculator cal;
	CircularProgressBar progress;
	std::string numbers = "";
	int timeCounter = 0;
	bool num_color = true;
	int keyTurn = -1;
	Mat frame;
	ARParam	gARTCparam;
	MarkerPoint* mp;
	AbstractButton* buttonRect;
	CircularButtons * circ;
	RectangularButtons * rect;
	cv::VideoCapture video;
	void evaluateInput(char input);
	void drawPoint(int x, int y);
	std::string intToString(int number);
	int returnPosition(double x, double y);
	// ekrana çizen fonksiyon.
	void drawWindow(cv::Point& coordinate);
	int chooseType(cv::Point& coordinate);
	//Point findMarkers(Mat frame);
public:

	void startCalculator();

	TouchFreeCalculator();
	~TouchFreeCalculator();
};
#endif
