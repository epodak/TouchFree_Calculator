#ifndef CIRCULARBUTTON_HEADER
#define CIRCULARBUTTON_HEADER
#include "AbstractButton.h"
#include "opencv2/opencv.hpp"
#include <vector>
using namespace cv;
#define NUMBER_COLOR			cv::Scalar(0, 0, 255)	// Sayilarin rengi
#define NUMBER2_COLOR			cv::Scalar(0, 200, 200)	// Secilen Sayilarin ekrandaki rengi
#define BORDER_COLOR			CV_RGB(120, 120, 120)	// cizgilerin rengi

class CircularButtons : public AbstractButton
{
private:
	std::vector<Point> centersOfButtons;
	int radius;
	void setRadius(int r);
	void setCenters();
public:
	int getRadius() { return radius; }
	std::vector<Point> getCentersOfButtons() { return centersOfButtons; }
	void drawButtons(Mat &frame);
	void drawNumbers(Mat &frame);
	void drawSettings();
	CircularButtons();
};

#endif
